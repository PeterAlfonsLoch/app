#include "StdAfx.h"
#include <shlwapi.h>


// spa is installed and updated :
// CRT is available,
// spalib is available

/*
class handle
{
public:
   handle(HANDLE handle) : m_handle(handle) {}
   HANDLE m_handle;
};


class close_handle :
   virtual public handle
{
public:
   close_handle(HANDLE handleParam) : handle(handleParam) {}
   virtual ~close_handle() { ::CloseHandle(m_handle); }
};

*/

HANDLE g_hmutexBoot = NULL;
DWORD g_dwPrepareSmallBell = 0;

//void parse_spaboot_file(const char * psz);

int APIENTRY ca2_cube_install(const char * pszId)
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


   spa_set_id(pszId);
   std::string strPlatform = spa_get_platform();
   std::string strSp = get_ca2_folder_dup() + "\\ca2\\stage\\"+strPlatform+"\\spaboot.exe";

   SHELLEXECUTEINFO sei;
   memset(&sei, 0, sizeof(sei));
   sei.cbSize = sizeof(sei);
   sei.fMask = SEE_MASK_NOCLOSEPROCESS;
   sei.lpFile = strSp.c_str();
   sei.nShow = SW_SHOWNORMAL;
   std::string strParameters;

   strParameters = "starter_start=";
   strParameters += pszId;
   strParameters += " background";
   sei.lpParameters =  strParameters.c_str();

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


/*

void parse_spaboot(XNode & node)
{
   if(node.name == "spa" && node.childs.size() > 0)
   {
      LPXNode lpnode = &node;
      for(unsigned int ui = 0; ui < lpnode->childs.size(); ui++)
      {
         if(lpnode->childs[ui]->name == "index")
         {
            if(lpnode->childs[ui]->GetAttr("start") != NULL)
            {
               if(std::string(lpnode->childs[ui]->GetAttrValue("start")).length() > 0)
               {
                  spa_set_id(std::string(lpnode->childs[ui]->GetAttrValue("start")).c_str());
               }
            }
         }
      }
   }
}


bool parse_spaboot_document(XNode & node)
{
   int iOkCount = 0;
   std::string strInstalledBuild;
   std::string strRequestedBuild;
   if(node.name == "spa" && node.childs.size() > 0)
   {
      LPXNode lpnode = &node;
      for(unsigned int ui = 0; ui < lpnode->childs.size(); ui++)
      {
         if(lpnode->childs[ui]->name == "index")
         {
            if(lpnode->childs[ui]->GetAttr("start") != NULL)
            {
               if(std::string(lpnode->childs[ui]->GetAttrValue("start")).length() > 0)
               {
                  spa_set_id(std::string(lpnode->childs[ui]->GetAttrValue("start")).c_str());
                  iOkCount++;
               }
               else
               {
                  return false;
               }
            }
            else
            {
               return false;
            }
         }
         else
         {
            return false;
         }
         if(lpnode->childs[ui]->GetAttr("build") != NULL)
         {
            if(std::string(lpnode->childs[ui]->GetAttrValue("build")).length() > 0)
            {
               strInstalledBuild = file::get_contents((get_ca2_folder_dup() + "\\ca2\\app\\build.txt").c_str());
               if(strInstalledBuild.length() <= 0)
                  return false;
               strRequestedBuild = std::string(lpnode->childs[ui]->GetAttrValue("build")).c_str();
               if(strRequestedBuild.length() <= 0)
                  return false;
               iOkCount++;
            }
            else
            {
               return false;
            }
         }
         else
         {
            return false;
         }
      }
   }
   if(iOkCount < 3)
      return false;
   if(strRequestedBuild != strInstalledBuild)
      return false;
   if(!is_installed(spa_get_id().c_str()))
      return false;
   return true;
}

bool parse_spaboot_file(const char * psz)
{
   XNode node;
   node.Load(file::get_contents(psz).c_str());
   return parse_spaboot_document(node);
}*/
/*

int perform_application_installation(const char * pszVersion, const char * pszId)
{
   STARTUPINFO si;
   PROCESS_INFORMATION pi;
   std::string strInstall;
   std::string strVersion = pszVersion;
   std::string strId = pszId;
   std::string strPlatform = spa_get_platform();
   if(strId == "_set_windesk")
   {
      strInstall = get_ca2_folder_dup() + "\\ca2\\stage\\" + strPlatform + "\\cubeapp.exe : app=winservice_1";
      memset(&si, 0, sizeof(si));
      memset(&pi, 0, sizeof(pi));
      if(!::CreateProcess(NULL, (LPSTR)  strInstall.c_str(),
         NULL, NULL, FALSE, 0, NULL, NULL,
         &si, &pi))
      {
         return 1;
      }
   }
   else
   {
      strInstall = get_ca2_folder_dup() + "\\ca2\\stage\\" + strPlatform + "\\cubeapp.exe";
      strInstall += " : ";
      strInstall += "app=bergedge bergedge_start=";
      strInstall += strId;
      memset(&si, 0, sizeof(si));
      memset(&pi, 0, sizeof(pi));
      if(!::CreateProcess(NULL, (LPSTR)  strInstall.c_str(),
         NULL, NULL, FALSE, 0, NULL, NULL,
         &si, &pi))
      {
         return 1;
      }
   }
   
   return 0;
}


*/