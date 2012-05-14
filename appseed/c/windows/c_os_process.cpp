#include "framework.h"
#include <ShellAPI.h> // TODO: try to remove - by replacing -  SHELLEXECUTEINFOA from execute_sync



CLASS_DECL_c int call_async(
   const char * pszPath, 
   const char * pszParam, 
   const char * pszDir,
   int iShow)
{

   SHELLEXECUTEINFOA infoa;

   memset_dup(&infoa, 0, sizeof(infoa));

   infoa.cbSize         = sizeof(infoa);
   infoa.lpFile         = pszPath;
   infoa.lpParameters   = pszParam;
   infoa.lpDirectory    = pszDir;
   infoa.nShow          = iShow;

   int iOk = ::ShellExecuteExA(&infoa);

   return iOk;

}



CLASS_DECL_c DWORD call_sync(
   const char * pszPath, 
   const char * pszParam, 
   const char * pszDir,
   int iShow,
   int iRetry, 
   int iSleep, 
   int (* pfnOnRetry)(int iTry, DWORD_PTR dwParam),
   DWORD_PTR dwParam)
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
   
   int iTry = 0;

   while(iRetry < 0 || iTry <= iRetry)
   {
      if(!GetExitCodeProcess(infoa.hProcess, &dwExitCode))
         break;
      if(dwExitCode != STILL_ACTIVE)
         break;
      Sleep(84);
      if(pfnOnRetry != NULL)
      {
         if(!pfnOnRetry(iTry, dwParam))
            break;
      }
      iTry++;
   }

   return dwExitCode;

}




int get_current_processor_index()
{


   return ::GetCurrentProcessorNumber();


}

int get_current_process_maximum_affinity()
{
   
   DWORD_PTR dwProcessAffinityMask;
   DWORD_PTR dwSystemAffinityMask;
   if(!GetProcessAffinityMask(::GetCurrentProcess(), &dwProcessAffinityMask, & dwSystemAffinityMask))
   {
      return 0;
   }
   int iMax = -1;
   DWORD_PTR dwMask = 1;
   for(int i = 0; i < sizeof(dwProcessAffinityMask) * 8; i++)
   {
      if((dwMask & dwProcessAffinityMask) != 0)
      {
         iMax = i;
      }
      dwMask = dwMask << 1;
   }

   return iMax;

}

int get_current_process_affinity_order()
{
   
   
   DWORD_PTR dwProcessAffinityMask;
   DWORD_PTR dwSystemAffinityMask;
   if(!GetProcessAffinityMask(::GetCurrentProcess(), &dwProcessAffinityMask, & dwSystemAffinityMask))
   {
      return 0;
   }
   int iCount = 0;
   DWORD_PTR dwMask = 1;
   for(int i = 0; i < sizeof(dwProcessAffinityMask) * 8; i++)
   {
      if((dwMask & dwProcessAffinityMask) != 0)
      {
         iCount++;
      }
      dwMask = dwMask << 1;
   }

   return iCount;


}



