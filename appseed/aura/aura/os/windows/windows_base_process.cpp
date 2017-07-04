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


   string app_id_to_app_name(string strId)
   {

      string strName;

      for (index i = 0; i < strId.length(); i++)
      {

         if (strId[i] == L'-' || strId[i] == L'/' || strId[i] == L'\\')
         {

            strName += L"_";

         }
         else
         {

            strName += strId[i];

         }

      }

      return strName;

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
         if (entry.th32ProcessID != 0 && strPath.compare_ci(pathModule) == 0)
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




CLASS_DECL_AURA bool is_shared_library_busy(uint32_t processid, const stringa & stra)
{

   stringa straSuffix(stra);

   straSuffix.surround("\\");

   return ::windows::pred_process_module(processid, [&](auto & me32)
   {

      return !straSuffix.suffixes_ci(me32.szModule) && !stra.contains_ci(me32.szModule);

   });

}


CLASS_DECL_AURA bool is_shared_library_busy(const stringa & stra)
{

   return ::windows::pred_process([&](auto pid)
   {

      return !is_shared_library_busy(pid, stra);

   });

}


CLASS_DECL_AURA bool launch_application(::aura::application * papp, const string & strAppId, const string & strParams, int iBitCount)
{

   ::file::path path;

   if (iBitCount == 64)
   {

      path = ::dir::program_files_x86() / "ca2/install/x64/install.exe";

   }
   else if (iBitCount == 32)
   {

      path = ::dir::program_files_x86() / "ca2/install/x86/install.exe";

   }
   else
   {

#if OSBIT == 32

      path = ::dir::program_files_x86() / "ca2/install/x86/install.exe";

#else

      path = ::dir::program_files_x86() / "ca2/install/x64/install.exe";

#endif

   }

   string strApp(strAppId);

   string strExtra;

   if (strParams.has_char())
   {

      strExtra = " " + strParams;

   }


   ::fork(papp, [=]
   {

      unsigned int uiPid;

      ::call_async(path, ": app=" + strApp + strExtra, path.folder(), SW_SHOWNORMAL, false, &uiPid);

   });

   return true;

}





CLASS_DECL_AURA bool process_contains_module(string & strImage, DWORD processID, const char * pszLibrary)
{

   HANDLE hProcess;

   DWORD cbNeeded;

   uint32_t ui;

   hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);

   if (NULL == hProcess)
      return false;

   const int32_t iMaxModuleCount = 1024;

   array < HMODULE > hmods;

   hmods.set_size(iMaxModuleCount);

   const int32_t iImageSize = MAX_PATH * 8;

   memory mem;
   
   mem.allocate(iImageSize);

   GetModuleFileNameExW(hProcess, NULL, (WCHAR *) mem.get_data(), mem.get_size() / sizeof(WCHAR));

   strImage = (const wchar_t *) mem.get_data();

   wstring wstrLibrary(pszLibrary);

   bool bFound = false;

   if (EnumProcessModules(hProcess, hmods.get_data(), hmods.get_size_in_bytes(), &cbNeeded))
   {

      for (ui = 0; ui < (cbNeeded / sizeof(HMODULE)); ui++)
      {

         // Get the full path to the module's file.

         if (GetModuleFileNameExW(hProcess, hmods[ui], (WCHAR *) mem.get_data(), mem.get_size() / sizeof(WCHAR)))
         {

            if (!wcsicmp_dup((const wchar_t *) mem.get_data(), wstrLibrary))
            {

               bFound = true;

               break;

            }

         }

      }

   }

   CloseHandle(hProcess);

   return bFound;

}


CLASS_DECL_AURA void shared_library_process(dword_array & dwa, stringa & straProcesses, const char * pszLibrary)
{

   // Get the list of process identifiers.

   dword_array aProcesses;

   aProcesses.set_size(8192);

   DWORD cbNeeded, cProcesses;

   uint32_t ui;

   if (!EnumProcesses(aProcesses.get_data(), aProcesses.get_size_in_bytes(), &cbNeeded))
   {

      return;

   }

   // Calculate how many process identifiers were returned.

   cProcesses = cbNeeded / sizeof(DWORD);

   // Print the name of the modules for each process.

   string strImage;

   for (ui = 0; ui < cProcesses; ui++)
   {

      if (process_contains_module(strImage, aProcesses[ui], pszLibrary))
      {

         straProcesses.add(strImage); // there may processes with different pids but same image

         dwa.add(aProcesses[ui]);

      }

   }

}






