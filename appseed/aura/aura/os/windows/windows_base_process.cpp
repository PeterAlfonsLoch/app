//#include "framework.h"
//#include <Shellapi.h>
//#include <string.h>


int32_t call_async(
   const char * pszPath, 
   const char * pszParam, 
   const char * pszDir,
   int32_t iShow,
   bool bPrivileged)
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

   int iOk = ::ShellExecuteExW(&info);
   
   DWORD dwGetLastError = GetLastError();

   return iOk;

}



uint32_t call_sync(
   const char * pszPath, 
   const char * pszParam, 
   const char * pszDir,
   int32_t iShow,
   int32_t iRetry, 
   int32_t iSleep, 
   int32_t (* pfnOnRetry)(int32_t iTry, uint_ptr dwParam),
   uint_ptr dwParam)
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

   DWORD dwExitCode;
   
   int32_t iTry = 0;

   while(iRetry < 0 || iTry <= iRetry)
   {
      if(!GetExitCodeProcess(infoa.hProcess, &dwExitCode))
         break;
      if(dwExitCode != STILL_ACTIVE)
         break;
      Sleep(100);
      if(pfnOnRetry != NULL)
      {
         if(!pfnOnRetry(iTry, dwParam))
            break;
      }
      iTry++;
   }

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







extern "C"
int module_name_get_count(const char * pszModuleName)
{

   mutex veri_global_ca2(get_app(),"Global\\the_veri_global_ca2");

   synch_lock lock_the_veri_global_ca2(&veri_global_ca2);

   HANDLE process_snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);

   string strModule(pszModuleName);

   PROCESSENTRY32 entry;

   if(Process32First(process_snap,&entry) && ::GetLastError() != ERROR_NO_MORE_FILES)
   {

   repeat_process:

      if(strModule.CompareNoCase(entry.szExeFile,strModule))
      {

         m_iInstanceId++;

      }

      if(Process32Next(process_snap,&entry) && ::GetLastError() != ERROR_NO_MORE_FILES)
      {

         goto repeat_process;

      }

   }

   ::CloseHandle(process_snap);

}



string module_path_from_pid(uint32_t pid)
{
   string strRet = "[Unknown Process]";
   char ImageFileName[1024] ={0};
   HANDLE ph = OpenProcess(PROCESS_QUERY_INFORMATION,FALSE,pid);
   if(ph)
   {
      CloseHandle(ph);

      string sTmp = ImageFileName;
      string strSearch = "\\Device\\HarddiskVolume";
      strsize ind = sTmp.find(strSearch);
      if(ind != -1)
      {
         ind = sTmp.find('\\',ind + strSearch.get_length());
         if(ind != -1)
         {
            string sReplace = "#:";
            sReplace.set_at(0,GetDriveLetter(sTmp.Left(ind)));

            strRet = sReplace + sTmp.Mid(ind);
         }
      }
   }
   return strRet;
}
