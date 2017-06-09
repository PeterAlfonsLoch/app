//#include "framework.h"
//#include <Shellapi.h>
//#include <string.h>


int32_t call_async(const char * pszPath, const char * pszParam, const char * pszDir, int32_t iShow, bool bPrivileged, unsigned int *puiPid)
{

   SHELLEXECUTEINFOW info ={};

   wstring wstrFile = u16(pszPath);
   wstring wstrParam = u16(pszParam);
   wstring wstrDir = u16(pszDir);

   info.cbSize          = sizeof(SHELLEXECUTEINFOW);
   info.nShow           = iShow;
   info.lpFile         = wstrFile;
   info.lpParameters   = wstrParam;
   info.lpDirectory    = wstrDir;

   if(bPrivileged)
   {

      info.lpVerb = L"RunAs";

   }

   if (puiPid != NULL)
   {

      info.fMask |= SEE_MASK_NOCLOSEPROCESS;

   }


   int iOk = ::ShellExecuteExW(&info);

   if (puiPid != NULL)
   {

      *puiPid = ::GetProcessId(info.hProcess);

      ::CloseHandle(info.hProcess);
   
   }

   DWORD dwGetLastError = GetLastError();

   return iOk;

}


uint32_t call_sync(const char * pszPath, const char * pszParam, const char * pszDir, int32_t iShow, int32_t iRetry, int32_t iSleep, PFNCALLSYNCONRETRY pfnOnRetry, uint_ptr dwParam, unsigned int * puiPid)
{

   SHELLEXECUTEINFOA infoa;

   memset_dup(&infoa, 0, sizeof(infoa));

   infoa.cbSize         = sizeof(infoa);
   infoa.lpFile         = pszPath;
   infoa.lpParameters   = pszParam;
   infoa.lpDirectory    = pszDir;
   infoa.nShow          = iShow;

   infoa.fMask |= SEE_MASK_NOCLOSEPROCESS | SEE_MASK_NOASYNC | SEE_MASK_FLAG_NO_UI;

   ::ShellExecuteExA(&infoa);

   if (puiPid != NULL)
   {

      *puiPid = ::GetProcessId(infoa.hProcess);

   }

   DWORD dwExitCode;
   
   int32_t iTry = 0;

   while(iRetry < 0 || iTry <= iRetry)
   {
      
      if(!GetExitCodeProcess(infoa.hProcess, &dwExitCode))
         break;
      
      if(dwExitCode != STILL_ACTIVE)
         break;
      
      Sleep(iSleep);

      if(pfnOnRetry != NULL)
      {

         if(!pfnOnRetry(iTry, dwParam))
            break;

      }

      iTry++;

   }

   ::CloseHandle(infoa.hProcess);

   return dwExitCode;

}


int32_t get_current_processor_index()
{


   return ::GetCurrentProcessorNumber();


}

int32_t get_current_process_maximum_affinity()
{
   
   DWORD_PTR dwProcessAffinityMask;
   DWORD_PTR dwSystemAffinityMask;
   if(!GetProcessAffinityMask(::GetCurrentProcess(), &dwProcessAffinityMask, & dwSystemAffinityMask))
   {
      return 0;
   }
   int32_t iMax = -1;
   uint_ptr dwMask = 1;
   for(int32_t i = 0; i < sizeof(dwProcessAffinityMask) * 8; i++)
   {
      if((dwMask & dwProcessAffinityMask) != 0)
      {
         iMax = i;
      }
      dwMask = dwMask << 1;
   }

   return iMax;

}

int32_t get_current_process_affinity_order()
{
   
   
   DWORD_PTR dwProcessAffinityMask;
   DWORD_PTR dwSystemAffinityMask;

   if(!GetProcessAffinityMask(::GetCurrentProcess(), &dwProcessAffinityMask, & dwSystemAffinityMask))
   {

      return 0;

   }

   int32_t iCount = 0;
   uint_ptr dwMask = 1;
   for(int32_t i = 0; i < sizeof(dwProcessAffinityMask) * 8; i++)
   {
      if((dwMask & dwProcessAffinityMask) != 0)
      {
         iCount++;
      }
      dwMask = dwMask << 1;
   }

   return iCount;


}

CLASS_DECL_AURA DWORD_PTR translate_processor_affinity(int iOrder)
{

   DWORD_PTR dwProcessAffinityMask;
   DWORD_PTR dwSystemAffinityMask;
   if (!GetProcessAffinityMask(::GetCurrentProcess(), &dwProcessAffinityMask, &dwSystemAffinityMask))
   {
      return 0;
   }
   int32_t j = 0;
   uint_ptr dwMask = 1;
   for (int32_t i = 0; i < sizeof(dwProcessAffinityMask) * 8; i++)
   {
      if ((dwMask & dwProcessAffinityMask) != 0)
      {
         if (iOrder == j)
         {
            return dwMask;
         }
         j++;
      }
      dwMask = dwMask << 1;
   }

   return 0;

}


bool process_modules(stringa & stra, uint32_t processID)
{
   
   HANDLE hProcess;
   
   DWORD cbNeeded;
   
   uint32_t i;

   hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID );

   if (NULL == hProcess)
      return false;

   const int32_t iMaxModuleCount = 1024 * 8;
   
   HMODULE * hMods = new HMODULE[iMaxModuleCount];

   const int32_t iImageSize = MAX_PATH * 8;

   char * szImage = (char *) memory_alloc(iImageSize);

   if(EnumProcessModules(hProcess, hMods, sizeof(HMODULE) * iMaxModuleCount, &cbNeeded))
   {

      for ( i = 0; i < (cbNeeded / sizeof(HMODULE)); i++ )
      {

         if(GetModuleFileNameEx( hProcess, hMods[i], szImage, iImageSize / sizeof(char)))
         {
            
            stra.add(szImage);

         }

      }

   }

   memory_free_dbg(szImage, 0);

   delete hMods;

   CloseHandle( hProcess );

   return true;

}


bool load_modules_diff(stringa & straOld, stringa & straNew, const char * pszExceptDir)
{

   bool bFound;

   HMODULE hmodule;

   ::count iLenExcept;

   if(pszExceptDir != NULL)
   {
      
      iLenExcept = strlen_dup(pszExceptDir);

   }
   else
   {

      iLenExcept = 0;

   }

   for(int32_t i = 0; i < straOld.get_count(); i++)
   {

      bFound = false;

      if(iLenExcept > 0)
      {
         
         if(strlen_dup(straOld[i]) > iLenExcept)
         {
         
            if(_strnicmp(straOld[i], pszExceptDir, iLenExcept) == 0)
            {
            
               continue;

            }

         }

      }

      for(int32_t j = 0; j < straNew.get_count(); j++)
      {

         if(stricmp(straOld[i], straNew[j]) == 0)
         {
         
            bFound = true;

            break;

         }

      }

      if(!bFound)
      {
         
         hmodule = NULL;

         // double check, ensure, that the module has not been already loaded
         // it may happen by loading a missing module that loads dependencies that satisfies straOld modules state.

         if(::GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, straOld[i], &hmodule) == FALSE || hmodule == NULL)
         {

            try
            {

               ::LoadLibrary(straOld[i]);

            }
            catch(...)
            {

            }

         }

      }

   }

   return true;

}


namespace process
{


   bool set_priority(int32_t priority)
   {

      return (::SetPriorityClass(::GetCurrentProcess(),get_os_priority_class(priority)) != 0);


   }


} // namespace process








int_array module_path_get_pid(const char * pszModulePath, bool bModuleNameIsPropertyFormatted)
{

   ::file::path pathModule(pszModulePath);

   int_array iaPid;

   if(pathModule.is_empty())
   {

      return iaPid;

   }

   mutex veri_global_ca2(NULL,"Global\\the_veri_global_ca2");

   synch_lock lock_the_veri_global_ca2(&veri_global_ca2);

   HANDLE process_snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);

   PROCESSENTRY32 entry;

   if(Process32First(process_snap,&entry) && ::GetLastError() != ERROR_NO_MORE_FILES)
   {

   repeat_process:

      string strPath;

      strPath = module_path_from_pid(entry.th32ProcessID);

      //::output_debug_string(strPath + "\n");


      if (bModuleNameIsPropertyFormatted)
      {
         if (entry.th32ProcessID != 0 && strPath.CompareNoCase(pathModule) == 0)
         {

            iaPid.add(entry.th32ProcessID);

         }
      }
      else
      {
         if(entry.th32ProcessID != 0 && ::file::path(strPath) == pathModule)
         {

            iaPid.add(entry.th32ProcessID);

         }
      }

      if(Process32Next(process_snap,&entry) && ::GetLastError() != ERROR_NO_MORE_FILES)
      {

         goto repeat_process;

      }

   }

   ::CloseHandle(process_snap);

   return iaPid;

}



string module_path_from_pid(uint32_t pid)
{
   
   //HANDLE hModuleSnap = INVALID_HANDLE_VALUE;

   //MODULEENTRY32 me32;

   //hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);

   //if(hModuleSnap == INVALID_HANDLE_VALUE)
   //{

   //   return "";

   //}

   //me32.dwSize = sizeof(MODULEENTRY32);

   //if(!Module32First(hModuleSnap,&me32))
   //{

   //   CloseHandle(hModuleSnap);           // clean the snapshot object

   //   return "";

   //}

   //string strName  = solve_relative_compressions(me32.szExePath);
   // 
   //CloseHandle(hModuleSnap);

   //return strName;

   

   HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE,pid);

   if(hProcess == NULL)
      return "";

   WCHAR path[MAX_PATH * 4];

   string strPath;

   if(GetModuleFileNameExW(hProcess,0,path, sizeof(path) / sizeof(path[0])))
   {
      strPath = solve_relative_compressions(string(path));

   }

   ::CloseHandle(hProcess);

   return strPath;
   
}


// http://stackoverflow.com/questions/4178443/get-the-full-path-from-a-pid-using-delphi
//function GetPathFromPID(const PID: cardinal): string;
//var
//hProcess: THandle;
//path: array[0..MAX_PATH - 1] of char;
//begin
//hProcess := OpenProcess(PROCESS_QUERY_INFORMATION or PROCESS_VM_READ,false,PID);
//if hProcess <> 0 then
//try
//if GetModuleFileNameEx(hProcess,0,path,MAX_PATH) = 0 then
//RaiseLastOSError;
//result:= path;
//finally
//CloseHandle(hProcess)
//end
//else
//RaiseLastOSError;
//end;



CLASS_DECL_AURA bool are_dlls_in_use(uint32_t processid, const stringa & straDll)
{

   HANDLE hModuleSnap = INVALID_HANDLE_VALUE;

   MODULEENTRY32 me32;

   bool bFound = false;

   hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processid);

   if (hModuleSnap == INVALID_HANDLE_VALUE)
   {

      return false;

   }

   me32.dwSize = sizeof(MODULEENTRY32);

   if (!Module32First(hModuleSnap, &me32))
   {

      ::CloseHandle(hModuleSnap);

      return false;

   }

   stringa straDllSuffixes;

   straDllSuffixes.prefix(straDll,  "\\");

   do
   {

      if (straDllSuffixes.any_suffixes_ci(me32.szModule) || straDll.contains_ci(me32.szModule))
      {

         bFound = true;

         break;

      }

   } while (Module32Next(hModuleSnap, &me32));

   ::CloseHandle(hModuleSnap);

   return bFound;

}


CLASS_DECL_AURA bool are_dlls_in_use(const stringa & straDll)
{

   HANDLE hProcessSnap;

   PROCESSENTRY32 pe32;

   hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

   if (hProcessSnap == INVALID_HANDLE_VALUE)
   {

      return false;

   }

   pe32.dwSize = sizeof(PROCESSENTRY32);

   if (!Process32First(hProcessSnap, &pe32))
   {

      ::CloseHandle(hProcessSnap);

      return false;

   }

   bool bUsing = false;

   do
   {

      if (are_dlls_in_use(pe32.th32ProcessID, straDll))
      {

         bUsing = true;

         break;

      }

   } while (Process32Next(hProcessSnap, &pe32));

   ::CloseHandle(hProcessSnap);

   return bUsing;

}



