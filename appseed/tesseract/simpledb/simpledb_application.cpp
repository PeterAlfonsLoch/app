#include "StdAfx.h"


namespace tesseract
{


   namespace simpledb
   {


      application::application()
      {
         m_pserver      = NULL;
         m_bServer      = false;
      }






      bool application::initialize_instance()
      {

         if(!cube8::application::initialize_instance())
            return false;


         return true;
      }

      int application::exit_instance()
      {

         try
         {
            user::application::exit_instance();
         }
         catch(...)
         {
         }


         return 0;


      }


      void application::on_request(::ca::create_context * pcreatecontext)
      {
         if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("debugbreak"))
         {
            ::DebugBreak();
         }
         else if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("run"))
         {
            simpledb_run();
         }
         else if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("service"))
         {
         }
         else if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("create_service"))
         {
            CreateService();
         }
         else if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("remove"))
         {
            RemoveService();
         }
         else
         {
            simpledb_run();
         }
      }

      void application::simpledb_run()
      {

         m_pservice = new ::simpledb::service(this);
         m_pservice->Start(0);

      }

      BOOL application::run()
      {

         if(command().m_varTopicQuery.has_property("run"))
         {
            return ::user::application::run();
         }
         else if(command().m_varTopicQuery.has_property("service"))
         {
            ::simpledb::service service(this);
            //Sleep(15000);
            service_base::run(service);
         }
         else
         {
            return ::user::application::run();
         }
         return TRUE;
      }


      int application::CreateService()
      {
         SC_HANDLE hdlSCM = OpenSCManager(0, 0, SC_MANAGER_CREATE_SERVICE);

         string strCalling = m_strModulePath + " : app=simpledb service usehostlogin";

         if (hdlSCM == 0) return ::GetLastError();
    
         SC_HANDLE hdlServ = ::CreateService(
            hdlSCM,                    // SCManager database 
            "CGCLCSTvotagusCa2FontopusMainSimpleDb",               // name of service 
            "ccvotagus ca2 fontopus netnode",        // service name to display 
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
            "CGCLCSTvotagusCa2FontopusMainSimpleDb",               // name of service 
            SC_MANAGER_ALL_ACCESS);                     // no password 
    
         DWORD Ret = 0;
         if (!hdlServ) Ret = ::GetLastError();
        ::DeleteService(hdlServ);
         CloseServiceHandle(hdlServ);
         return Ret;
      }


   } // namespace simpledb


} // namespace tesseract


