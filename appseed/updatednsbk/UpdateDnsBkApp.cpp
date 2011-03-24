#include "StdAfx.h"
#include "UpdateDnsBkService.h"
#include "UpdateDnsBkApp.h"

UpdateDnsBkApp::UpdateDnsBkApp(void)
{
}

UpdateDnsBkApp::~UpdateDnsBkApp(void)
{
}

bool UpdateDnsBkApp::initialize_instance()
{
   if(!ex2::application::initialize_instance())
      return false;

   SetRegistryKey("ca2core");

   WriteProfileString("configuration", "init", "first time ok");
    try
    {
       gen::command_line commandline;

       _001ParseCommandLine(commandline);

#ifdef DEBUG
       if (command_line().m_varQuery.has_property("debugbreak"))
        {
            ::DebugBreak();
        }
 
        if (command_line().m_varQuery.has_property("console"))
        {
            UpdateDnsBkService service(this);
            service.Start(0);
            
            printf("Press the Enter key to stop the service.\n");
            while(true)
            {
               if(getc(stdin) == 13)
                  break;
            }

            service.Stop(0);
        }
        else
#endif
        if (command_line().m_varQuery.has_property("run"))
        {
            UpdateDnsBkService service(this);
			   service.ServiceThread();
        }
        else
        if (command_line().m_varQuery.has_property("service"))
        {
           return TRUE;
        }
        else
        if (command_line().m_varQuery.has_property("install"))
        {
           CreateService();
           return FALSE;
        }
        else if (command_line().m_varQuery.has_property("remove"))
        {
           RemoveService();
           return FALSE;
        }

    }
    catch (const _template::CAtlException& e)
    {
       TRACE("Error: 0x%08x\n", e.m_hr);
    }

   return false;
}

BOOL UpdateDnsBkApp::run()
{
   UpdateDnsBkService service(this);
   service_base::run(service);
   return TRUE;
}


BOOL UpdateDnsBkApp::exit_instance()
{
   return TRUE;
}

int UpdateDnsBkApp::CreateService()
{
	SC_HANDLE hdlSCM = OpenSCManager(0, 0, SC_MANAGER_CREATE_SERVICE);

	string strCalling = m_strModulePath + " service";

	if (hdlSCM == 0) return ::GetLastError();
 
   SC_HANDLE hdlServ = ::CreateService(
		hdlSCM,                    // SCManager database 
		"CGCLCSTvotagusCa2FontopusMainUpdateDnsBk",               // name of service 
		"ccvotagus ca2 fontopus updatednsbk",        // service name to display 
		STANDARD_RIGHTS_REQUIRED,  // desired access 
		SERVICE_WIN32_OWN_PROCESS, // service type 
		SERVICE_AUTO_START,      // start type 
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

int UpdateDnsBkApp::RemoveService()
{
	SC_HANDLE hdlSCM = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);

	string strCalling = m_strModulePath + " service";

	if (hdlSCM == 0) return ::GetLastError();
 
   SC_HANDLE hdlServ = ::OpenService(
		hdlSCM,                    // SCManager database 
		"CGCLCSTvotagusCa2FontopusMainUpdateDnsBk",               // name of service 
		SC_MANAGER_ALL_ACCESS);                     // no password 
 
   DWORD Ret = 0;
   if (!hdlServ) Ret = ::GetLastError();
  ::DeleteService(hdlServ);
   CloseServiceHandle(hdlServ);
   return Ret;
}