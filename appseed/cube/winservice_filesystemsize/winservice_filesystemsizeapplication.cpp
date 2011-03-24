#include "StdAfx.h"
#include "application.h"

namespace winservice_filesystemsize
{

   application::application(void)
   {
   }

   void application::construct(void)
   {
      m_eexclusiveinstance    = ::radix::ExclusiveInstanceLocal;
      m_strAppName            = "winservice_filesystemsize";
      m_strBaseSupportId      = "votagus_ca2_winservice_filesystemsize";
      m_strLicense            = "winservice_filesystemsize";
      m_pwnd = NULL;
   }

   application::~application(void)
   {
   }

   bool application::initialize_instance()
   {
      if(!ca8::application::initialize_instance())
         return false;

      m_pwnd = new FileSystemSizeWnd(this);
      m_pwnd->CreateServer();
      SetMainWnd(m_pwnd->m_p);
      return true;

   }

   int application::exit_instance()
   {
      return 0;
   }

   bool application::bergedge_start()
   {
      return m_ptemplate_html->open_document_file(NULL) != NULL;
   }

   bool application::InstallStartupLinks()
   {
      string strStartup;
      strStartup = System.dir().appdata("loginstartup\\run");
      string str;
      str.Format("<service name=\"CGCLCSTvotagusCa2Fontopus_WinService_FileSystemSize\" control=\"start\" />");
      string strLink;
      strLink = System.dir().path(strStartup, "winservice_filesystemsizestart.link");
      System.dir().mk(System.dir().name(strLink));
      System.file().put_contents(strLink, str);
      return true;
   }

   int application::RunService()
   {
      SC_HANDLE hdlSCM = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);

      if (hdlSCM == 0) return ::GetLastError();
    
      SC_HANDLE hdlServ = ::OpenService(
         hdlSCM,                    // SCManager database 
         "CGCLCSTvotagusCa2Fontopus_WinService_FileSystemSize",               // name of service 
         SC_MANAGER_ALL_ACCESS);                     // no password 
    
      DWORD Ret = 0;
      if (!hdlServ) 
         Ret = ::GetLastError();
      ::StartService(hdlServ, 0, NULL);

      CloseServiceHandle(hdlServ);

      return Ret;
   }



   bool application::RunShellLink()
   {
      return ((int) ::ShellExecute(NULL, NULL, System.dir().votagus("stage\\ca2\\fontopus\\cast\\main\\front\\Release\\winshelllinkapp.exe"),
         ": usehostlogin", NULL, SW_HIDE)) >= 32;
   }


   void application::_001CloseApplication()
   {
      System.service().stop("CGCLCSTvotagusCa2Fontopus_WinService_FileSystemSize");
   }

} // namespace winservice_filesystemsize




CLASS_DECL_CA2_CUBE ::ca::application * winservice_filesystemsize_get_new_app()
{
   return new winservice_filesystemsize::application;
}
