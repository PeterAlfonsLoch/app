#include "StdAfx.h"

// this dll is installed, so CRT is available.
// spalib may not be installed or may be outdated, so must not call spalib functions

int install_spa()
{
   std::string strPlatform;

#ifdef _X86_
   strPlatform = "x86";
#else
   strPlatform = "x64";
#endif

   std::string strSp = get_ca2_folder_dup() + "\\ca2\\stage\\"+strPlatform+"\\install_spaboot.exe";

   SHELLEXECUTEINFO sei;
   memset(&sei, 0, sizeof(sei));
   sei.cbSize = sizeof(sei);
   sei.fMask = SEE_MASK_NOCLOSEPROCESS;
   sei.lpFile = strSp.c_str();
   sei.nShow = SW_HIDE;
   std::string strParameters;
   sei.lpVerb = "runas";
   sei.lpParameters =  "-install_spaboot";

   if(!::ShellExecuteEx(&sei))
   {
      return 1;
   }

   DWORD dwExitCode;
   int i = 1;
   while(true)
   {
      if(!GetExitCodeProcess(sei.hProcess, &dwExitCode))
         break;
      if(dwExitCode != STILL_ACTIVE)
         break;
      Sleep(184);
      i++;
   }

   return 0;
}




void defer_install_spa()
{
   for(int i = 0; i < 8; i++)
   {
      if(i >= 1)
      {
         Sleep(1984 + 1977);
      }
      update_spa_installed();
      if(is_spa_installed())
      {
         update_spa_updated();
         if(is_spa_updated())
            break;
      }
      install_spa();
   }
}

