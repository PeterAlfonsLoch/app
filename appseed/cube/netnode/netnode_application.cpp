#include "StdAfx.h"
#include "netnodeService.h"
#include "netnodeScriptManager.h"

void KickNetNodeThread();

namespace netnode
{

   application::application(void)
   {
      m_bService = true;
   }

   application::~application(void)
   {
   }

   void application::construct()
   {
      m_pscriptmanager           = NULL;
      m_strAppName               = "netnode";
      m_strLicense               = "netnode";
      m_bShouldInitializeGTwf    = false;
   }

   bool application::initialize_instance()
   {
      m_dataid = "netnode";

      if(!ca84::application::initialize_instance())
         return false;

      return true;

   }

   void application::on_request(var & varFile, var & varQuery)
   {
      if(varQuery.has_property("debugbreak"))
      {
         ::DebugBreak();
      }
      else if(varQuery.has_property("run"))
      {
         netnode_run();
//         return true;
      }
      else if(varQuery.has_property("service"))
      {
         //return true;
      }
      else if(varQuery.has_property("create_service"))
      {
         CreateService();
         //return false;
      }
      else if(varQuery.has_property("remove"))
      {
         RemoveService();
         //return false;
      }
      else if(varQuery.has_property("launch"))
      {
         string str;
         str = varQuery["launch"];
         get_script_manager()->run(str);
         //return true;
      }
      else if(varQuery.has_property("edgify"))
      {
         string str;
         str = varQuery["edgify"];
         get_script_manager()->run(str);
         //return true;
      }
      else
      {
         netnode_run();
         //return true;
      }
      //return ::acube::application::bergedge_start();
   }

   void application::netnode_run()
   {
      m_pservice = new netnodeService(this);
      m_pservice->Start(0);
   }

   BOOL application::run()
   {
      gen::command_line commandline;

      _001ParseCommandLine(commandline);

      if(command_line().m_varQuery.has_property("run"))
      {
         return ca84::application::run();
      }
      else if (command_line().m_varQuery.has_property("service"))
      {
         netnodeService service(this);
         Sleep(15000);
         service_base::run(service);
      }
      else
      {
         return ca84::application::run();
      }
      return TRUE;
   }

   BOOL application::ExitInstance()
   {
      return TRUE;
   }

   int application::CreateService()
   {
      SC_HANDLE hdlSCM = OpenSCManager(0, 0, SC_MANAGER_CREATE_SERVICE);

      string strCalling = m_strModulePath + " : app=netnode service usehostlogin";

      if (hdlSCM == 0) return ::GetLastError();
    
      SC_HANDLE hdlServ = ::CreateService(
         hdlSCM,                    // SCManager database 
         "CGCLCSTvotagusCa2FontopusMainNetNode",               // name of service 
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
         "CGCLCSTvotagusCa2FontopusMainNetNode",               // name of service 
         SC_MANAGER_ALL_ACCESS);                     // no password 
    
      DWORD Ret = 0;
      if (!hdlServ) Ret = ::GetLastError();
     ::DeleteService(hdlServ);
      CloseServiceHandle(hdlServ);
      return Ret;
   }


   void application::get_Votagus_folder(string &strVotagusFolder)
   {
      strVotagusFolder = get_module_folder();
      System.file().path().eat_end_level(strVotagusFolder, 7, "\\");
   }

   /*void application::sync_load_url(const char * lpcszFile, const char * lpcszServer, const char * lpcszUri)
   {
      CInternetSession session;
      session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 1,000 * 20);
      session.SetOption(INTERNET_OPTION_CONNECT_BACKOFF, 1000);
      session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);
      CHttpConnection* pServer = NULL;   
      pServer = session.GetHttpConnection(lpcszServer,
                                       80, "", "");
      CHttpFile* pFile = NULL;
      const char * pstrAcceptTypes;
      char pstrVersion[80];
      DWORD dwHttpRequestFlags = INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_RELOAD;





      pFile = pServer->OpenRequest("GET",
                                lpcszUri,
                                "desktopaccess",
                                1,
                                &pstrAcceptTypes,
                                NULL,
                                dwHttpRequestFlags);
      
      pFile->SendRequest();

      DWORD dwRet;
      pFile->QueryInfoStatusCode(dwRet);

      if(dwRet == HTTP_STATUS_OK)
      {
         int len = pFile->get_length();
         char buf[128000];
         int numread;
         ex1::filesp myfile(lpcszFile,
            ::ex1::file::mode_create|::ex1::file::mode_write|::ex1::file::type_binary);
         while ((numread = pFile->read(buf,sizeof(buf)-1)) > 0)
         {
            myfile.write(buf, numread);
         }
         myfile.close();
      }
      pFile->close(); 
      delete pFile;
      pServer->close();
      delete pServer;
      session.close();
   }*/

   bool application::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
   {
      return gen::application::_001OnCmdMsg(pcmdmsg);
   }

   void application::pre_translate_message(gen::signal_object * pobj)
   {
      ::whiteboard::application::pre_translate_message(pobj);
   }

   bool application::does_launch_window_on_startup()
   {
      return false;
   }

   void application::process(machine_event_data * pdata)
   {
      if(pdata->m_fixed.m_bRequestCloseApplication)
         return;
      ::ca84::application::process(pdata);
   }

   netnodeScriptManager * application::get_script_manager()
   {
      return m_pscriptmanager;
   }


} // namespace netnode


CLASS_DECL_CA2_CUBE ::ca::application * netnode_get_new_app()
{
   return new ::netnode::application;
}
