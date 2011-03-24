#include "StdAfx.h"


netshareserverApp::netshareserverApp(void)
{
}

netshareserverApp::~netshareserverApp(void)
{
}

bool netshareserverApp::InitInstance()
{
   set_locale("pt-br");
   set_style("pt-br");
   if(!ca84::application::InitInstance())
      return false;


   SetRegistryKey("ca2core");
   WriteProfileString("configuration", "init", "first time ok");
   try
   {
      gen::CommandLineInfo commandline;
      Ex1::GetApp()->_001ParseCommandLine(commandline);
      if (commandline.m_propertysetParameters.has_property("run"))
      {
         netshareserverService service(this);
			service.ServiceThread();
      }
#ifdef DEBUG
      else if(commandline.m_propertysetParameters.has_property("debugbreak"))
      {
         ::DebugBreak();
      }
      else if (commandline.m_propertysetParameters.has_property("console"))
      {
         netshareserverService service(this);
         service.Start(0);
         std::wcout << L"Press the Enter key to stop the service." << std::endl;
         std::wcin.get();
         service.Stop(0);
      }
#endif
      else if (commandline.m_propertysetParameters.has_property("service"))
      {
         return true;
      }
      else if (commandline.m_propertysetParameters.has_property("install"))
      {
         CreateService();
         return false;
      }
      else if (commandline.m_propertysetParameters.has_property("remove"))
      {
         RemoveService();
         return false;
      }
      else if (commandline.m_propertysetParameters.has_property("install_run"))
      {
         int iRet = RemoveService();
         if(!(iRet == ERROR_SUCCESS
           || iRet == ERROR_SERVICE_DOES_NOT_EXIST))
         {
            goto install_error;
         }
         if(CreateService() != ERROR_SUCCESS)
         {
            goto install_error;
         }
         if(RunService() != ERROR_SUCCESS)
         {
            goto install_error;
         }
         if(!RunShellLink())
         {
            goto install_error;
         }
         if(!InstallStartupLinks())
         {
            goto install_error;
         }
         install().remove_spa_start("_set_filemanager");
         string strFileManager = dir().votagus("stage\\ca2\\fontopus\\app\\main\\front\\Release\\filemanagerapp.exe");
         ::ShellExecute(NULL, NULL, strFileManager, ": usehostlogin", NULL, SW_SHOW);
         install().add_app_install("_set_filemanager");
         return false;
      }
   }
   catch (const ATL::CAtlException& e)
   {
      std::wcout.setf(std::ios_base::hex, 
                      std::ios_base::basefield);

      std::wcout << L"Error: 0x"
                 << e.m_hr
                 << std::endl;
   }
   return false;
install_error:
   Application.install().add_spa_start("_set_netshare");
   if(::MessageBox(NULL, "The computer need to be restarted!!\n\nDo you want to restart now?\n\nWe recommend you to close all other applications first and then agree with this question using the buttons below.", "Restart Needed!!", MB_ICONEXCLAMATION | MB_YESNO)
      == IDYES)
   {
      os().reboot();
   }
   return false;
}

BOOL netshareserverApp::Run()
{
   netshareserverService service(this);
   Kerr::ServiceBase::Run(service);
   return TRUE;
}


BOOL netshareserverApp::ExitInstance()
{
   return TRUE;
}


Ex1FactoryImpl * netshareserverApp::Ex1AppGetFactoryImpl()
{
   return new WinFactoryImpl();
}

int netshareserverApp::CreateService()
{
	SC_HANDLE hdlSCM = OpenSCManager(0, 0, SC_MANAGER_CREATE_SERVICE);

	string strCalling = m_strModulePath + " service /userhostlogin";

	if (hdlSCM == 0) return ::GetLastError();
 
   SC_HANDLE hdlServ = ::CreateService(
		hdlSCM,                    // SCManager database 
		"CGCLCSTvotagusCa2FontopusMainNetShareServer",               // name of service 
		"ccvotagus ca2 fontopus netshare server",        // service name to display 
		STANDARD_RIGHTS_REQUIRED,  // desired access 
		SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS, // service type 
		SERVICE_DEMAND_START,      // start type 
		SERVICE_ERROR_NORMAL,      // error control type 
      strCalling,                   // service's binary Path name
		0,                      // no load ordering group 
		0,                      // no tag identifier 
		0,                      // no dependencies 
		0,                      // LocalSystem account 
		0);                     // no password 
 
   DWORD Ret = 0;
   if (!hdlServ) Ret = ::GetLastError();
      CloseServiceHandle(hdlServ);
   return Ret;
}

int netshareserverApp::RemoveService()
{
   return service().remove("CGCLCSTvotagusCa2FontopusMainNetShareServer");
}

int netshareserverApp::RunService()
{
   return service().remove("CGCLCSTvotagusCa2FontopusMainNetShareServer");
}


bool netshareserverApp::RunShellLink()
{
   //return ((int) ::ShellExecute(NULL, NULL, ca2::app(this).dir().votagus("stage\\ca2\\fontopus\\app\\main\\front\\Release\\winshelllinkapp.exe"),
     // "/usehostlogin", NULL, SW_HIDE)) >= 32;
   return true;
}


bool netshareserverApp::InstallStartupLinks()
{
   string strStartup;
   strStartup = dir().appdata("loginstartup\\run");
   string str;
   str.Format("<service name=\"CGCLCSTvotagusCa2FontopusMainNetShareServer\" control=\"start\" />");
   string strLink;
   strLink = dir().path(strStartup, "netshareserver_servicestart.link");
   dir().mk(dir().name(strLink));
   file().put_contents(strLink, str);
   return true;
}
