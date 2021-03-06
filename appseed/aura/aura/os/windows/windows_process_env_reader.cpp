
/**
* @ ProcessEnvReader.cpp - Implementation File for CProcessEnvReader class
* @ Author - Sarath C
**/

#include <Winternl.h>
#include <psapi.h>

#define SHOW_ERR_DLG( x ) ::MessageBox( 0, x,_T("Exception"), MB_ICONERROR )

#pragma comment (lib,"psapi.lib" )
#pragma comment (lib,"Shell32.lib")

/**
* Wrapper to call NtQueryInformationProcess API by Run-Time Dynamic Linking
* Check MSDN Documentation : http://msdn2.microsoft.com/en-us/library/ms684280(VS.85).aspx
**/
NTSTATUS CProcessEnvReader::QueryInformationProcesss(
   IN HANDLE ProcessHandle,
   IN PROCESSINFOCLASS ProcessInformationClass,
   OUT PVOID ProcessInformation,
   IN ULONG ProcessInformationLength,
   OUT PULONG ReturnLength OPTIONAL
   )
{
   typedef NTSTATUS(__stdcall *QueryInfoProcess) (
      IN HANDLE ProcessHandle,
      IN PROCESSINFOCLASS ProcessInformationClass,
      OUT PVOID ProcessInformation,
      IN ULONG ProcessInformationLength,
      OUT PULONG ReturnLength OPTIONAL
      );

   HMODULE hModNTDll = LoadLibrary(_T("ntdll.dll"));

   if(!hModNTDll)
   {
      SHOW_ERR_DLG(_T("Error Loading library"));
   }

   QueryInfoProcess QueryProcInfo = (QueryInfoProcess)GetProcAddress(hModNTDll,
      "NtQueryInformationProcess");
   if(!QueryProcInfo)
   {
      SHOW_ERR_DLG(_T("Can't find NtQueryInformationProcess in ntdll.dll"));
      return FALSE;
   }

   NTSTATUS ntStat =  QueryProcInfo(ProcessHandle,
      ProcessInformationClass,
      ProcessInformation,
      ProcessInformationLength,
      ReturnLength);

   FreeLibrary(hModNTDll);

   return ntStat;
}


/**
* Function to Read teh environment block of specified process
**/
BOOL CProcessEnvReader::ReadEnvironmentBlock(HANDLE hProcess,_ENVSTRING_t& stEnvData)
{
   // Buffer to hold the string read from process	
   UCHAR* pchBuffEnvString = 0;
   stEnvData.Clear();
   __try
   {
      PROCESS_BASIC_INFORMATION stBasiProcInfo ={0};
      ULONG uReturnLength = 0;
      NTSTATUS ntStat =  QueryInformationProcesss(hProcess,
         ProcessBasicInformation,
         &stBasiProcInfo,
         sizeof(stBasiProcInfo),
         &uReturnLength);

      // Read the process environment block
      PEB peb ={0};
      SIZE_T nReturnNumBytes = 0;
      // Check read access of specified location in the processs and get the size of block
      ReadProcessMemory(hProcess,(LPCVOID)stBasiProcInfo.PebBaseAddress,&peb,sizeof(peb),&nReturnNumBytes);


      // Get the address of RTL_USER_PROCESS_PARAMETERS structure 
      UCHAR* puPEB = (UCHAR*)&peb;
      UCHAR* pRTLUserInfo = (UCHAR*)*((int_ptr*)(puPEB + 0x10));

      int nReadbleSize = 0;
      if(!HasReadAccess(hProcess,pRTLUserInfo,nReadbleSize))
      {
         SHOW_ERR_DLG(_T("Error Reading Process Memory"));
         return FALSE;
      }

      // Get the first 0x64 bytes of RTL_USER_PROCESS_PARAMETERS strcuture
      char cBuffRTLUserInfo[0x64] ={0};
      ReadProcessMemory(hProcess,(LPCVOID)pRTLUserInfo,cBuffRTLUserInfo,0x64,&nReturnNumBytes);

      // Validate the read operation
      if(!nReturnNumBytes)
      {
         SHOW_ERR_DLG(_T("Error Reading Process Memory"));
         return FALSE;
      }

      // Get the value at offset 0x48 to get the pointer to environment string block
      UCHAR* pAddrEnvStrBlock = (UCHAR*)*((int_ptr*)(&cBuffRTLUserInfo[0] + 0x48));

      if(!HasReadAccess(hProcess,pAddrEnvStrBlock,nReadbleSize))
      {
         SHOW_ERR_DLG(_T("Error Reading Process Memory"));
         return FALSE;
      }

      // Allocate buffer for to copy the block
      pchBuffEnvString = new UCHAR[nReadbleSize];
      memset(pchBuffEnvString,0,sizeof(UCHAR)* nReadbleSize);

      // Read the environment block
      ReadProcessMemory(hProcess,(LPCVOID)pAddrEnvStrBlock,
         pchBuffEnvString,nReadbleSize,&nReturnNumBytes);

      // Cleanup existing data if any

      if(nReturnNumBytes)
      {
         // Set the values in the return pointer
         stEnvData.pData = (LPCWSTR)pchBuffEnvString;
         stEnvData.nSize = (int) nReturnNumBytes;
         return TRUE;
      }
      else
      {
         SHOW_ERR_DLG(_T("Error Reading Process Memory"));
      }
   }
   __except(SHOW_ERR_DLG(_T("Exception occured on reading process memory")))
   {
      SAFE_ARRAY_CLEANUP(pchBuffEnvString);
   }

   return FALSE;
}


/**
* Helper function to check the read access to the virtual memory of specified process
**/
BOOL CProcessEnvReader::HasReadAccess(HANDLE hProcess,
   void* pAddress,int& nSize)
{
   MEMORY_BASIC_INFORMATION memInfo;
   __try
   {
      VirtualQueryEx(hProcess,pAddress,&memInfo,sizeof(memInfo));
      if(PAGE_NOACCESS == memInfo.Protect ||
         PAGE_EXECUTE == memInfo.Protect)
      {
         nSize = 0;
         return FALSE;
      }

      nSize = (int) memInfo.RegionSize;
      return TRUE;
   }
   __except(SHOW_ERR_DLG(_T("Failed to close Handle")))
   {

   }
   return FALSE;
}


/**
* Function to open the specified process to read or query information
**/
HANDLE CProcessEnvReader::OpenProcessToRead(DWORD dwPID)
{
   HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
      PROCESS_VM_READ,FALSE,dwPID);
   return hProcess;
}


/**
* Function release an opened handle
**/
void CProcessEnvReader::ReleaseHandle(HANDLE hHandle)
{
   __try
   {
      if(hHandle)
         CloseHandle(hHandle);
   }
   __except(SHOW_ERR_DLG(_T("Failed to close Handle")))
   {

   }
}


/**
* Function to enumerate and update process tree
**/
void CProcessEnvReader::EnumProcessInfo(ProcessInfoArray& arrProcessInfo)
{
   HANDLE hProcessSnap;
   PROCESSENTRY32 pe32;

   // Take a snapshot of all processes in the system.
   hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
   if(hProcessSnap == INVALID_HANDLE_VALUE)
   {
      return;
   }

   // Set the size of the structure before using it.
   pe32.dwSize = sizeof(PROCESSENTRY32);

   // Retrieve information about the first process, and exit if unsuccessful
   if(!Process32First(hProcessSnap,&pe32))
   {
      CloseHandle(hProcessSnap);    // Must clean up the
                                    //   snapshot object!
      return;
   }

   // Now walk the snapshot of processes, and
   // display information about each process in turn
   string csProcessInfo;
   int i = 0;
   do
   {
      arrProcessInfo.push_back(pe32);

   } while(Process32Next(hProcessSnap,&pe32));

   CloseHandle(hProcessSnap);
}

/**
* Get the name of the process from handle
**/
string CProcessEnvReader::GetProcessNameFromHandle(HANDLE hProcess)
{
   TCHAR szProcessName[MAX_PATH] ={0};
   GetModuleFileNameEx(hProcess,0,szProcessName,MAX_PATH);
   return szProcessName;
}

string CProcessEnvReader::GetProcessNameFromID(DWORD dwPID)
{
   HANDLE hProcess = OpenProcessToRead(dwPID);
   string csName = GetProcessNameFromHandle(hProcess);
   ReleaseHandle(hProcess);
   return csName;
}
/**
* Function to load Icon from a process
**/
void CProcessEnvReader::LoadIconFromProcess(HANDLE hProcess,HICON& hIconSmall,HICON& hIconLarge)
{
   if(hProcess)
   {
      ExtractIconEx(GetProcessNameFromHandle(hProcess),
         0,&hIconSmall,&hIconLarge,1);
   }
}


/**
* Helper function to convert Unicode string to Multibyte
**/
void CProcessEnvReader::ConvertUnicodeToMBCS(LPCWSTR lpStringToConvert,int nLen,string& csMBCSStr)
{
   char* buff = new char[nLen + 1];

   WideCharToMultiByte(CP_ACP,0,lpStringToConvert,-1,
      buff,nLen + 1,NULL,NULL);

   csMBCSStr = buff;
   delete[]buff;
}


/**
* Extract each strings
**/
void CProcessEnvReader::ParseEnvironmentStrings(LPCWSTR lpStringToConvert,int nLen,stringa& EnvStrArr)
{
   int nIdx = 0;

   EnvStrArr.remove_all();
   while(nIdx < nLen)
   {
      size_t nSingleLen = wcslen(&lpStringToConvert[nIdx]);
      if(nSingleLen == 0)
         break;

#ifdef _UNICODE // if UNICODE, no need to convert
      LPCTSTR lpcsStr = (wchar_t*)&lpStringToConvert[nIdx];
#else // Convert to MBCS otherwise
      string csValue;
      CProcessEnvReader::ConvertUnicodeToMBCS(&lpStringToConvert[nIdx],(int) nSingleLen,csValue);
      LPCTSTR lpcsStr = (LPCTSTR)csValue;
#endif
      nIdx += (int) nSingleLen + 1;
      EnvStrArr.add(lpcsStr); // add string to array
   }
}


/**
* Function to Seperate variables and values
* e.g PATH=C:\ will be changed to "PATH" and "C:\"
* this will do for entire array
**/
void CProcessEnvReader::SeparateVariablesAndValues(const stringa& EnvStrArray,EnvVarValArray& varValArr)
{

   int nLen = (int) EnvStrArray.get_size();
   for(int i = 0; i< nLen; i++)
   {
      const string& csVal = EnvStrArray[i];
      int nIndex = (int) csVal.find(_T("="),0);

      if(-1 == nIndex || 0 == nIndex)
      {
         continue;
      }

      EnvVariableValuePair ValPair;
      // get the LHS of "=" in the string
      ValPair.m_element1= csVal.Left(nIndex);

      ValPair.m_element2 = csVal.Right(csVal.length() - nIndex - 1);
      varValArr.push_back(ValPair);
   }
}


///**
//* Function to export the string to specified destination
//**/
//void CProcessEnvReader::ExportEnvStrings(const stringa& csArrEnvStr,
//   COPY_DEST_e Dest,
//   HWND hClipboardOwner)
//{
//   const int nSize = csArrEnvStr.get_count();
//   if(!nSize)
//      return;
//
//   // Prepare the string to export
//   string csVal;
//   for(int i = 0; i < nSize; i++)
//   {
//      csVal += csArrEnvStr[i];
//      csVal+="\r\n";
//   }
//
//   if(DEST_FILE == Dest) // Copy to file
//   {
//      static TCHAR szFilter[] = _T("Text File(*.txt)|*.txt||");
//      CFileDialog fileDlg(FALSE,_T("*.txt"),NULL,NULL,szFilter,NULL);
//      if(IDOK == fileDlg.DoModal())
//      {
//         string csFilePath = fileDlg.GetPathName();
//         CStdioFile file(csFilePath,CFile::modeCreate | CFile::modeWrite);
//         file.WriteString(csVal);
//      }
//   }
//   else //  Copy data to Clipboard
//   {
//      HGLOBAL hText;
//      hText = GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE,csVal.GetLength()*sizeof(TCHAR) + 1);
//      TCHAR* pText = (TCHAR*)GlobalLock(hText);
//      _tcscpy(pText,csVal);
//      GlobalUnlock(hText);
//      OpenClipboard(hClipboardOwner);
//      EmptyClipboard();
//      SetClipboardData(CF_TEXT,hText);
//      CloseClipboard();
//   }
//}



