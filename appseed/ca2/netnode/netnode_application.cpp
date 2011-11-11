#include "StdAfx.h"
#include <openssl/rsa.h>
#include <openssl/engine.h>
#include <openssl/err.h>


void KickNetNodeThread();


namespace netnode
{


   application::application(void)
   {
      m_bService        = true;
      m_pservice        = NULL;
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

      if(!cube2::application::initialize_instance())
         return false;


      ERR_load_RSA_strings();

      ERR_load_crypto_strings();

      return true;

   }

   void application::on_request(::ca::create_context * pcreatecontext)
   {

      ::cube4::application::on_service_request(pcreatecontext);

      if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("debugbreak"))
      {
         ::DebugBreak();
      }
      else if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("launch"))
      {
         string str;
         str = pcreatecontext->m_spCommandLine->m_varQuery["launch"];
         get_script_manager()->run(str);
      }
      else if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("edgify"))
      {
         string str;
         str = pcreatecontext->m_spCommandLine->m_varQuery["edgify"];
         get_script_manager()->run(str);
      }

   }

   void application::netnode_run()
   {


   }





   int application::exit_instance()
   {

      if(m_pservice != NULL)
      {
         m_pservice->Stop(0);
      }

      try
      {
         m_pscriptmanager->PostThreadMessage(WM_QUIT, 0, 0);
      }
      catch(...)
      {
      }

      int iRet = 0;
      try
      {
         iRet = ::cube4::application::exit_instance();
      }
      catch(...)
      {
         iRet = -1;
      }

      return iRet;
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
      cube4::application::pre_translate_message(pobj);
//xxx      ::whiteboard::application::pre_translate_message(pobj);
   }

   bool application::does_launch_window_on_startup()
   {
      return false;
   }

   void application::process(machine_event_data * pdata)
   {
      if(pdata->m_fixed.m_bRequestCloseApplication)
         return;
      ::cube2::application::process(pdata);
   }

   dynamic_source::script_manager * application::get_script_manager()
   {
      return m_pscriptmanager;
   }


   bool application::is_serviceable()
   {
      return true;
   }

   service_base * application::allocate_new_service()
   {
      return new ::netnode::service(this);
   }

   ::netnode::service * application::get_service()
   {
      return dynamic_cast < ::netnode::service * > (::cube4::application::get_service());
   }

   bool application::on_install()
   {
      if(!::cube4::application::on_install())
         return false;
      return true;
   }
      
   bool application::on_uninstall()
   {
      if(!::cube4::application::on_uninstall())
         return false;
      return true;
   }


} // namespace netnode


