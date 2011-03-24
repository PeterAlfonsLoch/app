#include "StdAfx.h"


namespace icube
{

            
   CLASS_DECL_ca class system * create_system()
   {
      return new class system;
   }
      
   CLASS_DECL_ca void destroy_system(system * & psystem)
   {
      delete psystem;
      psystem = NULL;
   }










   HANDLE g_hmutexBoot = NULL;

   CLASS_DECL_ca int ca2_cube_install(const char * pszId)
   {
      g_hmutexBoot = NULL;
      SECURITY_ATTRIBUTES MutexAttributes;
      ZeroMemory( &MutexAttributes, sizeof(MutexAttributes) );
      MutexAttributes.nLength = sizeof( MutexAttributes );
      MutexAttributes.bInheritHandle = FALSE; // object uninheritable
      // declare and initialize a security descriptor
      SECURITY_DESCRIPTOR SD;
      BOOL bInitOk = InitializeSecurityDescriptor(
                        &SD,
                        SECURITY_DESCRIPTOR_REVISION );
      if ( bInitOk )
      {
         // give the security descriptor a Null Dacl
         // done using the  "TRUE, (PACL)NULL" here
         BOOL bSetOk = SetSecurityDescriptorDacl( &SD,
                                               TRUE,
                                               (PACL)NULL,
                                               FALSE );
         if ( bSetOk )
         {
            // Make the security attributes point
            // to the security descriptor
            MutexAttributes.lpSecurityDescriptor = &SD;
            g_hmutexBoot = ::CreateMutex(&MutexAttributes, FALSE, "Global\\ca2::fontopus::ccvotagus_ca2_spa::7807e510-5579-11dd-ae16-0800200c7784");
            if(::GetLastError() == ERROR_ALREADY_EXISTS)
            {
               while(::GetLastError() == ERROR_ALREADY_EXISTS)
               {
                  ::CloseHandle(g_hmutexBoot);
                  Sleep(1984 + 1977);
                  g_hmutexBoot = ::CreateMutex(&MutexAttributes, FALSE, "Global\\ca2::fontopus::ccvotagus_ca2_spa::7807e510-5579-11dd-ae16-0800200c7784");
               }
            }
            ::CloseHandle(g_hmutexBoot);
         }
         else
         {
            ::OutputDebugString("error when trying to analyze if another instance of spa is already running");
            Sleep(1984 + 1977);
            return -200;
         }
      }
      else
      {
         ::OutputDebugString("error when trying to analyze if another instance of spa is already running");
         Sleep(1984 + 1977);
         return -201;
      }


//      spa_set_id(pszId);
      string strPlatform;
#ifdef _X86_
      strPlatform = "x86";
#else
      strPlatform = "x64";
#endif
      string strSp = "C:\\ca2\\stage\\"+strPlatform+"\\spaboot.exe";

      SHELLEXECUTEINFO sei;
      memset(&sei, 0, sizeof(sei));
      sei.cbSize = sizeof(sei);
      sei.fMask = SEE_MASK_NOCLOSEPROCESS;
      sei.lpFile = strSp;
      sei.nShow = SW_SHOWNORMAL;
      string strParameters;

      strParameters = "starter_start=";
      strParameters += pszId;
      strParameters += " background";
      sei.lpParameters =  strParameters;

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
      string strInstall;



      /*std::string strUrl;
      std::string strApp;
      strUrl = "http://spaignition.ca2api.net/query?node=install_application&id=";
      strUrl += g_strId;
      strUrl += "&key=system";
      int iRetry = 0;
      while(true)
      {
         strApp = ms_get(strUrl.c_str());
         if(strApp.length() > 0)
            break;
         iRetry++;
         if(iRetry > 30)
            break;
         Sleep(1984 + 1977);
      }
      if(iRetry > 30)
      {
         return 1;
      }*/

      return 0;
   }





















} // namespace icube