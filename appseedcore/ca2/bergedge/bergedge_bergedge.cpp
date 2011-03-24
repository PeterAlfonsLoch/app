#include "StdAfx.h"


namespace bergedge
{

   bergedge::bergedge()
   {
      m_pnaturedocument       = NULL;
      m_pplatformdocument     = NULL;
      m_pbergedgedocument     = NULL;
      
   }

   bergedge::~bergedge()
   {

      POSITION pos = m_mapApplication.get_start_position();

      if(m_pnaturedocument != NULL)
      {
         m_pnaturedocument->on_close_document();
      }

      if(m_pplatformdocument != NULL)
      {
         m_pplatformdocument->on_close_document();
      }

      if(m_pbergedgedocument != NULL)
      {
         m_pbergedgedocument->on_close_document();
      }

      string strId;
      ::ca::application * pcaapp;

      while(pos != NULL)
      {
         
         strId.Empty();
         pcaapp = NULL;

         m_mapApplication.get_next_assoc(pos, strId, pcaapp);

         ::ca2::application * papp = dynamic_cast < ::ca2::application * > (pcaapp);

         papp->PostThreadMessageA(WM_QUIT, 0, 0);
      }

      //System.delete_temp();

      /*for(int i = m_appptra.get_upper_bound(); i >= 0; i--)
      {
         App(m_appptra[i]).m_pdocmanager->close_all_documents(true);
         m_appptra[i]->PostThreadMessageA(WM_QUIT, 0, 0);
      }
      System.m_ptemplate_platform->close_all_documents(false);
      System.m_ptemplate_bergedge->close_all_documents(false);*/
   /*restart_remove:
      system_map::pair * ppair = System.m_systemmap.PGetFirstAssoc();
      while(ppair != NULL)
      {
         if(ppair->m_value == this)
         {
            System.m_systemmap.remove_key(ppair->m_key);
            goto restart_remove;
         }
         ppair = System.m_systemmap.PGetNextAssoc(ppair);
      }*/
   }

   void bergedge::construct()
   {
      m_strAppName         = "bergedge";
      m_strBaseSupportId   = "votagus_ca2_bergedge";
      m_strInstallToken    = "bergedge";
      m_strLicense         = "";
      m_eexclusiveinstance = ::radix::ExclusiveInstanceNone;
   }

   bool bergedge::initialize_instance()
   {
      //m_puser                 = new ::fontopus::user(this);
      //m_puser->m_strLogin     = "bergedge";
      //create_user(m_puser);

      if(!ca84::application::initialize_instance())
         return false;

      initialize_bergedge_application_interface();


      GetStdFileManagerTemplate()->m_strLevelUp = "levelup";


      SetRegistryKey("ca2core");


      if(!InitializeLocalDataCentral())
      {
         simple_message_box(NULL, "Could not initialize Local data central");
         return false;
      }


      return true;
   }

   BOOL bergedge::exit_instance()
   {
      try
      {
         ::platform::application::exit_instance();
      }
      catch(...)
      {
      }
      return 0;
   }

   bool bergedge::bergedge_start()
   {
      return true;
   }



   void bergedge::_001OnFileNew()
   {
      userbase::application::m_pdocmanager->_001OnFileNew();
   }


   bool bergedge::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
         
   {
      return gen::application::_001OnCmdMsg(pcmdmsg);
   }

   ::ca::application * bergedge::get_app() const
   {
      return platform::application::get_app();
   }

   void bergedge::OnFileManagerOpenFile(
         ::filemanager::data * pdata, 
         ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      m_ptemplate_html->open_document_file(itema[0].m_strPath);
   }

   void bergedge::load_string_table()
   {
      ca77::application::load_string_table();
      ca77::application::load_string_table("platform");
   }

   bool bergedge::file_manager_open_file(
            ::filemanager::data * pdata, 
            ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      if(itema.get_size() > 0)
      {
         return true;
      }
      return false;
   }


   void bergedge::initialize_bergedge_application_interface()
   {
      int iCount = 32; // todo: get from bergedge profile
      System.factory().creatable < ::bergedge::document > (iCount);
      System.factory().creatable < ::bergedge::view > (iCount);
      System.factory().creatable < ::bergedge::pane_view > (iCount);
      System.factory().creatable < ::bergedge::frame > (iCount);
      System.factory().creatable < platform::document > (iCount);
      System.factory().creatable < platform::view > (iCount);
      System.factory().creatable < platform::pane_view > (iCount);
      System.factory().creatable < platform::frame > (iCount);
      System.factory().creatable < nature::document > (iCount);
      System.factory().creatable < nature::view > (iCount);
      System.factory().creatable < nature::pane_view > (iCount);
      System.factory().creatable < nature::frame > (iCount);
      m_ptemplate_bergedge    = new ::userbase::single_document_template(
         this,
         "bergedge/frame",
         &typeid(document),
         &typeid(frame),
         &typeid(view));
      m_ptemplate_platform    = new ::userbase::single_document_template(
         this,
         "bergedge/frame",
         &typeid(platform::document),
         &typeid(platform::frame),
         &typeid(platform::pane_view));
      m_ptemplate_nature      = new ::userbase::single_document_template(
         this,
         "bergedge/frame",
         &typeid(nature::document),
         &typeid(nature::frame),
         &typeid(nature::pane_view));
      m_pnaturedocument = NULL;
   }

   document * bergedge::force_get_document()
   {
      if(m_pbergedgedocument == NULL)
      {
         m_pbergedgedocument = dynamic_cast < document * > (m_ptemplate_bergedge->open_document_file(NULL, true, m_papp->m_puiInitialPlaceHolderContainer));
         m_pbergedgedocument->m_pbergedge = this;
      }
      if(System.command_line().m_varQuery["show_platform"].get_integer() == 1 && m_pplatformdocument == NULL
      && !System.command_line().m_varQuery.has_property("client_only"))
      {
         m_pplatformdocument  = dynamic_cast < platform::document * > (m_ptemplate_platform->open_document_file(NULL, true, m_pbergedgedocument->get_bergedge_view()));
         m_pplatformdocument->m_pbergedgedocument =  m_pbergedgedocument;
         //m_pnaturedocument    = 
         // dynamic_cast < nature::document * > (
          //  papp->m_ptemplate_nature->open_document_file(NULL, false, m_pbergedgedocument->get_bergedge_view()));

         m_pbergedgedocument->set_platform(m_pplatformdocument);
         //m_pbergedgedocument->set_nature(m_pnaturedocument);
      }
      return m_pbergedgedocument;
   }

   void bergedge::launch_app(const char * psz)
   {
      UNREFERENCED_PARAMETER(psz);
   }

   void bergedge::install_app(const char * psz)
   {
      UNREFERENCED_PARAMETER(psz);
   }

   void bergedge::request_application(::ca2::application_request * prequest)
   {
      
      string strApp;

      if(prequest->m_strApp == "bergedge")
      {
         if(prequest->m_varQuery.has_property("bergedge_start"))
         {
            strApp = prequest->m_varQuery["bergedge_start"];
         }
         else
         {
            strApp = "bergedge";
         }
      }
      else
      {
         strApp = prequest->m_strApp;
      }

      if(strApp.is_empty())
      {
         force_get_document();
         return;
      }

      ::ca2::application * papp = dynamic_cast < ::ca2::application * > (application_get(strApp, true, true, prequest->m_pbiasCreate));
      if(papp == NULL)
         return;

      if(prequest->m_varQuery.has_property("install")
      || prequest->m_varQuery.has_property("uninstall"))
      {
         return;
      }

      prequest->m_eventReady.ResetEvent();
      
      int iEdge               = prequest->m_iEdge;

      prequest->m_strApp.Empty();
      prequest->m_iEdge = -1;

      DWORD_PTR dw = WM_APP + 2043;
      papp->PostThreadMessage(dw, 0, (LPARAM) prequest);
      CSingleLock sl(&prequest->m_eventReady, TRUE);

      prequest->m_strApp      = strApp;
      prequest->m_iEdge       = iEdge;
/*      if(papp != NULL)
      {
         papp->m_prunapp = prunapp;
         
         papp->m_bSessionSynchronizedCursor  = System.m_bSessionSynchronizedCursor;
         papp->m_bSessionSynchronizedScreen  = System.m_bSessionSynchronizedScreen;

         papp->m_hInstance = System.m_hInstance;
         if(!papp->InitApplication())
            return;
         
         if(!papp->process_initialize())
            return;
         papp->command_line().m_varQuery.parse_url_query(prunapp->m_strQuery);
         for(int i = 0; i < prunapp->m_setParameters.get_count(); i++)
         {
            papp->command_line().m_varQuery[prunapp->m_setParameters.m_propertya[i].name()] =
               prunapp->m_setParameters.m_propertya[i].get_value();
         }
         gen::command_line & rCmdInfo = papp->command_line();
         if(rCmdInfo.m_setParameters.has_property("uri"))
         {
            if(rCmdInfo.m_strFileName.has_char())
            {
               rCmdInfo.m_strFileName += ";";
               rCmdInfo.m_strFileName += rCmdInfo.m_setParameters["uri"];
            }
            else
            {
               rCmdInfo.m_strFileName = rCmdInfo.m_setParameters["uri"];
            }
            if(rCmdInfo.m_nShellCommand == gen::command_line::FileNew)
               rCmdInfo.m_nShellCommand = gen::command_line::FileOpen;
         }
         if(rCmdInfo.m_setParameters.has_property("uri_replace"))
         {
            rCmdInfo.m_strFileName = rCmdInfo.m_setParameters["uri_replace"];
            if(rCmdInfo.m_nShellCommand == gen::command_line::FileNew)
               rCmdInfo.m_nShellCommand = gen::command_line::FileOpen;
         }
         papp->m_puiInitialPlaceHolderContainer = prunapp->m_puiParent;
         papp->command_line().m_varQuery["local_mutex_id"] = "bergedge::edgify_app : papp->command_line().m_varQuery[\"local_mutex_id\"] = " + gen::str::itoa(prunapp->m_iEdge);
         if(!papp->initialize_instance())
            return;
         papp->initialize_bergedge_application_interface();
         document * pdoc = papp->get_edge(prunapp->m_iEdge, prunapp->m_bMakeVisible, prunapp->m_puiParent);
         papp->m_puiInitialPlaceHolderContainer = pdoc->get_bergedge_view();
         if(!papp->command_line().m_varQuery.has_property("install")
         && !papp->command_line().m_varQuery.has_property("uninstall"))
         {
            if(!papp->bergedge_start())
               return;
         }
         if(papp->does_launch_window_on_startup())
         {
            int iRetry = 100;
            while(papp->m_pwndMain == NULL && (iRetry > 0))
            {
               Sleep(100);
               iRetry--;
            }
            if(papp->m_pwndMain != NULL)
            {
               papp->m_pwndMain->SetParent(papp->m_puiInitialPlaceHolderContainer);
               papp->m_pwndMain->ModifyStyle(0, WS_CHILD);
               papp->m_pwndMain->SetWindowPos(NULL, 0, 0, 400, 400, SWP_SHOWWINDOW);
            }
         }
      }*/
   }

   ::bergedge::document * bergedge::get_document()
   {
      return m_pbergedgedocument;
   }

   ::platform::document * bergedge::get_platform()
   {
      return m_pplatformdocument;
   }

   ::nature::document * bergedge::get_nature()
   {
      return m_pnaturedocument;
   }

   bool bergedge::pre_process_command_line()
   {
      return platform::application::pre_process_command_line();
   }

   void bergedge::open_by_file_extension(const char * pszPathName)
   {
      string strId;
      if(gen::str::ends_ci(pszPathName, ".cgcl")
      || gen::str::ends_ci(pszPathName, ".cpp")
      || gen::str::ends_ci(pszPathName, ".html"))
      {
         strId = "devedge";
      }
      else if(gen::str::ends_ci(pszPathName, ".txt"))
      {
         strId = "veriedit";
      }
      else if(gen::str::ends_ci(pszPathName, ".kar")
      || gen::str::ends_ci(pszPathName, ".mid")
      || gen::str::ends_ci(pszPathName, ".mp3")
      || gen::str::ends_ci(pszPathName, ".mk1"))
      {
         strId = "mplite";
      }
      else if(gen::str::ends_ci(pszPathName, ".flv"))
      {
         strId = "verisimplevideo";
      }
      else
      {
         strId = System.file().extension(pszPathName);
      }
      ::user::application * papp = dynamic_cast < ::user::application * > (application_get(strId));
      if(papp == NULL)
         return;
      papp->open_document_file(pszPathName);
   }

   bool bergedge::InitializeLocalDataCentral()
   {
      
      m_pdatabase = new nature::database(this);

      if(m_pdatabase == NULL)
      {
         TRACE("VmpLightApp::initialize_instance failed to instatiate LightDB\n");
         return false;
      }

      if(!m_pdatabase->Initialize())
      {
         TRACE("VmpLightApp::initialize_instance failed to initialize LightDB\n");
         return false;
      }

      return true;

   }

   bergedge::run_application::run_application()
   {
      m_papp = NULL;
      m_puiParent = NULL;
   }

   void bergedge::on_exclusive_instance_conflict(::radix::EExclusiveInstance eexclusive)
   {
      if(eexclusive == ::radix::ExclusiveInstanceLocalId)
      {
         gen::memory_file file(get_app());
         file.from_string(command_line().m_varFile);
         COPYDATASTRUCT data;
         data.dwData = 1984;
         data.cbData = file.get_length();
         data.lpData = file.GetAllocation();
         HWND hwnd = (HWND) ::FindWindowA(NULL, "ca2::fontopus::message_wnd::bergedge::");

         ::SendMessage(hwnd, WM_COPYDATA, NULL, (LPARAM) &data);
      }
   }


   void bergedge::request(var & varFile, var & varQuery)
   {
      if(m_pappCurrent != NULL)
      {
         App(m_pappCurrent).request(varFile, varQuery);
      }
/*      else
      {
         gen::property_set & set = varQuery.propset();
         bergedge::document * pdocument   = NULL;
         bool bSynch                      = false;
         bool bMakeVisible                = true;
         int iEdge                        = 0;

         if(set.has_property("install")
         || set.has_property("uninstall"))
         {
            bMakeVisible   = false;
         }

         pdocument      = get_edge(iEdge, bMakeVisible);
         m_puiInitialPlaceHolderContainer = pdocument->get_bergedge_view();

         gen::property_set setParameters(get_app());
         if(set.has_property("bergedge_start"))
         {
            ::bergedge::application * papp = get_app(set["bergedge_start"]);
            if(papp != NULL)
               papp->request(varFile, varQuery);
         }
         else if(set.has_property("app")
         && set["app"] != "bergedge")
         {
            ::bergedge::application * papp = get_app(set["bergedge_start"]);
            bergedge_run_app(
               iEdge,
               command_line().m_varQuery["app"].get_string(), 
               bMakeVisible,
               NULL,
               setParameters);
         }
         else if(command_line().m_nShellCommand == gen::command_line::FileOpen)
         {
            open_by_file_extension(iEdge, command_line().m_strFileName, bMakeVisible, bSynch);
         }
         else if(command_line().m_varQuery["file"].get_value().get_type() == var::type_propset)
         {
            open_by_file_extension(iEdge, command_line().m_varQuery["file"].propset()["url"].get_string(), bMakeVisible, bSynch);
         }
      }*/
   }


   void bergedge::request_application(const char * pszId, var varFile, var varQuery, ::ca::application_bias * pbiasCreate)
   {
      
      ::ca2::application_request request;
      
      request.m_iEdge         = m_iEdge;
      request.m_strApp        = pszId;
      request.m_varFile       = varFile;
      request.m_varQuery      = varQuery;
      request.m_pbiasCreate   = pbiasCreate;
      
      request_application(&request);

   }

   ::ca::application * bergedge::application_get(const char * pszId, bool bCreate, bool bSynch, ::ca::application_bias * pbiasCreate)
   {
      ::ca::application * papp = NULL;

      if(m_mapApplication.Lookup(pszId, papp))
         return papp;
      else
      {
         if(!bCreate)
            return NULL;
         papp = NULL;
         try
         {
            papp = create_application(pszId, bSynch, pbiasCreate);
         }
         catch(...)
         {
            papp = NULL;
         }
         if(papp == NULL)
            return NULL;
         m_mapApplication.set_at(pszId, papp);
         return papp;
      }
   }


} // namespace bergedge


