#include "StdAfx.h"

namespace mydns
{

   application::application(void)
   {
      m_strAppName                  = "mydns";
      m_strBaseSupportId            = "mydns";
      m_strLicense                  = "";
      m_bService                    = true;
   }

   application::~application(void)
   {
   }


   int application::CreateService()
   {
	   SC_HANDLE hdlSCM = OpenSCManager(0, 0, SC_MANAGER_CREATE_SERVICE);

      string strCalling = m_strModulePath + " : service usehostlogin";

	   if (hdlSCM == 0) return ::GetLastError();
    
      SC_HANDLE hdlServ = ::CreateService(
		   hdlSCM,                    // SCManager database 
		   "CGCLCSTvotagusCa2FontopusMainNetShare",               // name of service 
		   "ccvotagus ca2 fontopus netshare",        // service name to display 
		   STANDARD_RIGHTS_REQUIRED,  // desired access 
		   SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS, // service type 
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

   int application::RemoveService()
   {
	   SC_HANDLE hdlSCM = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);

	   string strCalling = m_strModulePath + " service";

	   if (hdlSCM == 0) return ::GetLastError();
    
      SC_HANDLE hdlServ = ::OpenService(
		   hdlSCM,                    // SCManager database 
		   "CGCLCSTvotagusCa2FontopusMainNetShare",               // name of service 
		   SC_MANAGER_ALL_ACCESS);                     // no password 
    
      DWORD Ret = 0;
      if (!hdlServ) Ret = ::GetLastError();
     ::DeleteService(hdlServ);
      CloseServiceHandle(hdlServ);
      return Ret;
   }




   bool application::initialize_instance()
   {
      if(!ca84::application::initialize_instance())
         return false;
      m_strAppName                  = "mydns";
      return true;
   }

   void application::netnode_run()
   {
      m_pservice = new mydns::service(this);
      m_pservice->Start(0);
   }

   bool application::on_install()
   {
      CreateService();
      return true;
   }


   void application::on_request(var & varFile, var & varQuery)
   {
      if (varQuery.has_property("debugbreak"))
      {
         ::DebugBreak();
      }
      if (varQuery.has_property("run"))
      {
         netnode_run();
      }
      else if(varQuery.has_property("service"))
      {
         //return true;
      }
      else if (varQuery.has_property("install"))
      {
         //return false;
      }
      else if (varQuery.has_property("remove"))
      {
      }
      else if(varQuery.has_property("create_service"))
      {
         CreateService();
         //return false;
      }
      else if(varQuery.has_property("remove"))
      {
         RemoveService();
      }
      else
      {
         netnode_run();
      }
//      return true;
   }

   int application::run()
   {
      gen::command_line commandline;

      _001ParseCommandLine(commandline);

      if (command_line().m_varQuery.has_property("run"))
      {
         return ca84::application::run();
      }
      else if (command_line().m_varQuery.has_property("service"))
      {
         class service service(this);
         service_base::run(service);
         return ca84::application::run();
      }
      else
      {
         return ca84::application::run();
      }
      return TRUE;
   }



} // namespace mydns


CLASS_DECL_CA2_MYDNS ::ca::application * get_new_app()
{
   return new ::mydns::application;
}
