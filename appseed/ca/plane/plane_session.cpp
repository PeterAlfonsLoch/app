#include "framework.h"


namespace plane
{


   session::session()
   {

      m_bDrawCursor              = true;
      m_pbergedge                = NULL;
/*      m_pnaturedocument          = NULL;
      m_pplatformdocument        = NULL;
      m_pbergedgedocument        = NULL;*/
      m_bShowPlatform            = false;
      m_pappCurrent              = NULL;
      m_psession                 = this;
      m_pbergedgeInterface       = NULL;

      ::fs::set * pset = new class ::fs::set(this);
      pset->m_spafsdata.add(new ::fs::native(this));
      m_spfsdata(pset);


      m_pifs                     = new ifs(this, "");
      m_prfs                     = new ::fs::remote_native(this, "");


      m_userpresence.set_app(this);

   }

   session::~session()
   {

/*      if(m_pnaturedocument != NULL)
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
      */
      string strId;
      ::ca::application * pcaapp;


      POSITION pos = m_mapApplication.get_start_position();

      while(pos != NULL)
      {

         strId.Empty();
         pcaapp = NULL;

         m_mapApplication.get_next_assoc(pos, strId, pcaapp);

         ::ca2::application * papp = dynamic_cast < ::ca2::application * > (pcaapp);

         papp->post_thread_message(WM_QUIT, 0, 0);
      }

   }

   void session::construct()
   {

      m_strAppName         = "session";
      m_strBaseSupportId   = "votagus_ca2_bergedge";
      m_strInstallToken    = "session";
      m_bLicense           = false;
      m_eexclusiveinstance = ::radix::ExclusiveInstanceNone;

   }

   bool session::initialize()
   {

      if(!::planebase::application::initialize())
         return false;

      if(!m_userpresence.initialize())
         return false;

      return true;

   }


   bool session::initialize_instance()
   {

      if(!::planebase::application::initialize_instance())
         return false;

      initialize_bergedge_application_interface();


      //GetStdFileManagerTemplate()->m_strLevelUp = "levelup";


      SetRegistryKey("ca2core");


      if(!InitializeLocalDataCentral())
      {
         simple_message_box(NULL, "Could not initialize Local data central");
         return false;
      }




      return true;
   }


   bool session::finalize()
   {

      bool bOk = true;

      try
      {
      
         bOk = m_userpresence.finalize();

      }
      catch(...)
      {

         bOk = false;
      }

      try
      {
      
         bOk = ::planebase::application::finalize();

      }
      catch(...)
      {

         bOk = false;
      }

      return bOk;

   }

   int32_t session::exit_instance()
   {
      try
      {
         ::planebase::application::exit_instance();
      }
      catch(...)
      {
      }
      return 0;
   }

   bool session::bergedge_start()
   {
      return true;
   }



   void session::_001OnFileNew()
   {
      //userbase::application::m_pdocmanager->_001OnFileNew();
   }


   bool session::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)

   {
      return gen::application::_001OnCmdMsg(pcmdmsg);
   }

   ::ca::application * session::get_app() const
   {
      return ::planebase::application::get_app();
   }

   void session::load_string_table()
   {
      ::ca4::application::load_string_table();
      ::ca4::application::load_string_table("plane", "");
   }

/*   bool session::file_manager_open_file(
            ::filemanager::data * pdata,
            ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      if(itema.get_size() > 0)
      {
         return true;
      }
      return false;
   }*/


   void session::initialize_bergedge_application_interface()
   {
//      int32_t iCount = 32;  todo: get from session profile
/*      System.factory().creatable < ::session::document > (iCount);
      System.factory().creatable < ::session::view > (iCount);
      System.factory().creatable < ::session::pane_view > (iCount);
      System.factory().creatable < ::session::frame > (iCount);
      System.factory().creatable < plane::document > (iCount);
      System.factory().creatable < plane::view > (iCount);
      System.factory().creatable < plane::pane_view > (iCount);
      System.factory().creatable < plane::frame > (iCount);
      System.factory().creatable < nature::document > (iCount);
      System.factory().creatable < nature::view > (iCount);
      System.factory().creatable < nature::pane_view > (iCount);
      System.factory().creatable < nature::frame > (iCount);
      m_ptemplate_bergedge    = new ::userbase::single_document_template(
         this,
         "session/frame",
         System.type_info < document > (),
         System.type_info < frame > (),
         System.type_info < view > ());
      m_ptemplate_platform    = new ::userbase::single_document_template(
         this,
         "session/frame",
         System.type_info < plane::document > (),
         System.type_info < plane::frame > (),
         System.type_info < plane::pane_view > ());
      m_ptemplate_nature      = new ::userbase::single_document_template(
         this,
         "session/frame",
         System.type_info < nature::document > (),
         System.type_info < nature::frame > (),
         System.type_info < nature::view > ());
      m_pnaturedocument = NULL;*/
   }

   bool session::create_bergedge(::ca::create_context * pcreatecontext)
   {


      //if(m_pbergedgeInterface != NULL)
      {

//         m_pbergedgeInterface->create_bergedge(pcreatecontext);
         //return false;

      }

      m_varCurrentViewFile = pcreatecontext->m_spCommandLine->m_varFile;


      string strApp;

      if((pcreatecontext->m_spCommandLine->m_varQuery["show_platform"] == 1 || command().m_varTopicQuery["show_platform"] == 1)
         && (!(bool)pcreatecontext->m_spCommandLine->m_varQuery["client_only"] && !(bool)command().m_varTopicQuery["client_only"])
         && (!pcreatecontext->m_spCommandLine->m_varQuery.has_property("client_only") && !command().m_varTopicQuery.has_property("client_only")))
      {
         m_bShowPlatform = true;
      }

      strApp = "bergedge";

      pcreatecontext->m_spCommandLine->m_varQuery["show_platform"] = 1;

      ::ca::application * pcaapp = application_get("application", strApp, true, true, pcreatecontext->m_spCommandLine->m_pbiasCreate);

      ::bergedge_interface * papp = dynamic_cast < ::bergedge_interface * > (pcaapp);

      if(papp == NULL)
      {

         try
         {

            delete pcaapp;

         }
         catch(...)
         {
         }

         return false;
      }

      m_pbergedge             = papp->get_bergedge();
      m_pbergedgeInterface    = papp;

      UINT uiMessage = WM_APP + 2043;

      papp->post_thread_message(uiMessage, 2, (LPARAM) (::ca::create_context *) pcreatecontext);

      pcreatecontext->m_spCommandLine->m_eventReady.wait();

      return false;

   }

   void session::launch_app(const char * psz)
   {
      UNREFERENCED_PARAMETER(psz);
   }

   void session::install_app(const char * psz)
   {
      UNREFERENCED_PARAMETER(psz);
   }

   void session::on_request(::ca::create_context * pcreatecontext)
   {



      if(pcreatecontext->m_spCommandLine->m_varQuery["app"].array_get_count() > 1
      && pcreatecontext->m_spCommandLine->m_varQuery["app"].stra()[0] == "app/ca2/userstack")
      {
         start_application("application", "app/ca2/userstack", pcreatecontext);
         return;
      }

      string strApp = pcreatecontext->m_spCommandLine->m_strApp;

      if(strApp == "app/ca2/userstack")
      {
         start_application("application", "app/ca2/userstack", pcreatecontext);
         return;
      }

      if(m_pbergedgeInterface != NULL)
      {

         m_pbergedgeInterface->on_request(pcreatecontext);
         return;

      }

      m_varCurrentViewFile = pcreatecontext->m_spCommandLine->m_varFile;


      string strType;




      if((pcreatecontext->m_spCommandLine->m_varQuery["show_platform"] == 1 || command().m_varTopicQuery["show_platform"] == 1)
         && (!(bool)pcreatecontext->m_spCommandLine->m_varQuery["client_only"] && !(bool)command().m_varTopicQuery["client_only"])
         && (!pcreatecontext->m_spCommandLine->m_varQuery.has_property("client_only") && !command().m_varTopicQuery.has_property("client_only")))
      {
         m_bShowPlatform = true;
      }

      bool bCreate = true;
      if(pcreatecontext->m_spCommandLine->m_strApp.is_empty())
      {
         if(!pcreatecontext->m_spCommandLine->m_varFile.is_empty())
         {
            if(!open_by_file_extension(pcreatecontext))
            {
               if(m_pappCurrent != NULL)
               {
                  App(m_pappCurrent).request(pcreatecontext->m_spCommandLine);
               }
            }
            bCreate = false;
         }
         else if(m_bShowPlatform)
         {
            strApp = "bergedge";
            strType = "application";
//            create_bergedge(pcreatecontext);
  //          throw not_implemented(get_app());
            /*if(get_document() != NULL && get_document()->get_typed_view < ::session::view >() != NULL)
            {
               ::simple_frame_window * pframe = dynamic_cast < ::simple_frame_window * > (get_document()->get_typed_view < ::session::view >()->GetParentFrame());
               if(pframe != NULL)
               {
                  pframe->ShowWindow(SW_SHOW);
                  pframe->InitialFramePosition();
               }
            }*/
            bCreate = true;
         }

      }
      if(bCreate)
      {

         if(pcreatecontext->m_spCommandLine->m_varQuery["app"].stra().get_count() <= 0)
         {
            pcreatecontext->m_spCommandLine->m_varQuery["app"].stra().add(strApp);
         }
         else if (pcreatecontext->m_spCommandLine->m_varQuery["app"].stra().get_count() > 1)
         {
            start_application("application", "app/ca2/bergedge", pcreatecontext);
            return;
         }

         for(int32_t i = 0; i < pcreatecontext->m_spCommandLine->m_varQuery["app"].stra().get_count(); i++)
         {

            string strApp = pcreatecontext->m_spCommandLine->m_varQuery["app"].stra()[i];

            if(strApp.is_empty() || strApp == "session")
            {
               if(pcreatecontext->m_spCommandLine->m_strApp == "session")
               {
                  if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("session_start"))
                  {
                     strApp = pcreatecontext->m_spCommandLine->m_varQuery["session_start"];
                     strType = pcreatecontext->m_spCommandLine->m_varQuery["app_type"];
                  }
                  else
                  {
                     strApp = "session";
                     strType = "application";
                  }
               }
               else
               {
                  strApp = pcreatecontext->m_spCommandLine->m_strApp;
                  strType = pcreatecontext->m_spCommandLine->m_strAppType;
               }
            }

            if(strApp.is_empty() || strApp == "session")
            {
               if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("install")
               || pcreatecontext->m_spCommandLine->m_varQuery.has_property("uninstall"))
               {
                  System.appptra().remove(this);
                  return;
               }
               return;
            }

            if(strType.is_empty())
            {
               strType = "application";
            }

            start_application(strType, strApp, pcreatecontext);

         }

      }

   }


   ::planebase::application * session::start_application(const char * pszType, const char * pszAppId, ::ca::create_context * pcreatecontext)
   {

      string strApp(pszAppId);

      ::plane::application * papp = dynamic_cast < ::plane::application * > (application_get(pszType, strApp, true, true, pcreatecontext->m_spCommandLine->m_pbiasCreate));
      if(papp == NULL)
         return NULL;

      if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("install")
      || pcreatecontext->m_spCommandLine->m_varQuery.has_property("uninstall"))
      {
         System.appptra().remove(papp);
         return NULL;
      }

      pcreatecontext->m_spCommandLine->m_eventReady.ResetEvent();

      if(strApp != "session")
      {

         if(strApp == "bergedge")
         {

            m_pbergedge             = papp->get_bergedge();

            m_pbergedgeInterface    = dynamic_cast < ::bergedge_interface * > (papp);

            if(m_pbergedgeInterface == NULL)
            {

               try
               {

                  delete papp;

               }
               catch(...)
               {
               }

               return NULL;

            }

         }


         UINT uiMessage = WM_APP + 2043;

         papp->post_thread_message(uiMessage, 2, (LPARAM) (::ca::create_context *) pcreatecontext);

         pcreatecontext->m_spCommandLine->m_eventReady.wait();


      }

      return papp;

   }


   /*::session::document * session::get_document()
   {
      return m_pbergedgedocument;
   }

   ::session::view * session::get_view()
   {
      if(get_document() == NULL)
         return NULL;
      return get_document()->get_bergedge_view();
   }

   ::plane::document * session::get_platform()
   {
      return m_pplatformdocument;
   }

   ::nature::document * session::get_nature()
   {
      return m_pnaturedocument;
   }
   */


   bool session::open_by_file_extension(const char * pszPathName, ::ca::application_bias * pbiasCreate)
   {

      ::ca::create_context_sp cc(get_app());

      cc->m_spCommandLine->m_varFile = pszPathName;

      if(pbiasCreate != NULL)
      {
         cc->m_spApplicationBias->operator=(*pbiasCreate);
      }

      return open_by_file_extension(cc);

   }


   bool session::open_by_file_extension(::ca::create_context * pcreatecontext)
   {

      string strId;

      string strOriginalPathName(pcreatecontext->m_spCommandLine->m_varFile);

      string strPathName(strOriginalPathName);

      strPathName.trim();

      strPathName.trim("\"");

      strsize iFind = strPathName.find("?");

      if(iFind >= 0)
      {

         strPathName = strPathName.Left(iFind);

      }

      if(gen::str::ends_ci(strPathName, ".cgcl"))
      {

      }

      string strProtocol = System.url().get_protocol(strPathName);

      if(strProtocol == "app")
      {

         strId = System.url().get_server(strPathName);

         string str = System.url().get_object(strPathName);

         gen::str::begins_eat(str, "/");

         pcreatecontext->m_spCommandLine->m_varFile = str;

      }
      else
      {

         string strExtension = System.file().extension(strPathName);

         stringa straApp;

         System.filehandler().get_extension_app(straApp, strExtension);

         if(straApp.get_count() == 1)
         {
            strId = straApp[0];
         }
         else
         {
            strId = "app/ca2/default_file_handler";
         }

      }

      ::plane::application * papp = dynamic_cast < ::plane::application * > (application_get("application", strId, true, true, pcreatecontext->m_spApplicationBias));

      if(papp == NULL)
         return false;

      papp->::ex1::request_interface::create(pcreatecontext);

      return true;

   }

   bool session::InitializeLocalDataCentral()
   {

/*      m_pdatabase = new nature::database(this);

      if(m_pdatabase == NULL)
      {
         TRACE("VmpLightApp::initialize_instance failed to instatiate LightDB\n");
         return false;
      }

      if(!m_pdatabase->Initialize())
      {
         TRACE("VmpLightApp::initialize_instance failed to initialize LightDB\n");
         return false;
      }*/

      return true;

   }

   session::run_application::run_application()
   {
      m_papp = NULL;
      m_puiParent = NULL;
   }

   void session::on_exclusive_instance_conflict(::radix::EExclusiveInstance eexclusive)
   {

      if(eexclusive == ::radix::ExclusiveInstanceLocalId)
      {
         /*
         gen::memory_file file(get_app());
         file.from_string(command().m_varTopicFile);
         COPYDATASTRUCT data;
         data.dwData = 1984;
         data.cbData = (uint32_t) file.get_length();
         data.lpData = file.get_data();
         oswindow oswindow = ::FindWindowA(NULL, "ca2::fontopus::message_wnd::session::");

         ::SendMessage(oswindow, WM_COPYDATA, NULL, (LPARAM) &data);*/

#if defined(WINDOWSEX) || defined(LINUX) || defined(MACOS)

         small_ipc_tx_channel channel;

         if(channel.open("ca2::fontopus::message_wnd::session::"))
         {
            channel.send(command().m_varTopicFile, false);
            channel.close();
         }

#else

          throw todo(get_app());

#endif


      }

   }


   void session::request(::ca::create_context * pcreatecontext)
   {

      if(m_pbergedgeInterface != NULL)
      {

         m_pbergedgeInterface->request(pcreatecontext);
         return;

      }

      if(pcreatecontext->m_spCommandLine->m_varFile.get_type() == var::type_string)
      {
         if(gen::str::ends_ci(pcreatecontext->m_spCommandLine->m_varFile, ".ca2"))
         {
            string strCommand = Application.file().as_string(pcreatecontext->m_spCommandLine->m_varFile);
            if(gen::str::begins_eat(strCommand, "ca2prompt\r")
            || gen::str::begins_eat(strCommand, "ca2prompt\n"))
            {
               strCommand.trim();
               command().add_fork_uri(strCommand);
               System.m_bDoNotExitIfNoApplications = true;
            }
            return;
         }
         else
         {
            on_request(pcreatecontext);
         }
      }
      else if(m_pappCurrent != NULL && m_pappCurrent != this
         && (pcreatecontext->m_spCommandLine->m_strApp.is_empty()
         ||App(m_pappCurrent).m_strAppName == pcreatecontext->m_spCommandLine->m_strApp))
      {


/*         if(get_document() != NULL && get_document()->get_typed_view < ::session::pane_view >() != NULL)
         {
            get_document()->get_typed_view < ::session::pane_view >()->set_cur_tab_by_id("app:" + App(m_pappCurrent).m_strAppName);
         }*/
         App(m_pappCurrent).request(pcreatecontext);
      }
      else
      {
         on_request(pcreatecontext);
      }
   }

   void session::request_topic_file(var & varQuery)
   {
      request(m_varTopicFile, varQuery);
   }

   void session::request_topic_file()
   {
      request(m_varTopicFile);
   }

   /*void session::request_application(const char * pszId, var varFile, var varQuery, ::ca::application_bias * pbiasCreate)
   {

      ::ca2::application_request request;

      request.m_iEdge         = m_iEdge;
      request.m_strApp        = pszId;
      request.m_varFile       = varFile;
      request.m_varQuery      = varQuery;
      request.m_pbiasCreate   = pbiasCreate;

      request_application(&request);

   }*/

   ::ca::application * session::application_get(const char * pszType, const char * pszId, bool bCreate, bool bSynch, ::ca::application_bias * pbiasCreate)
   {
      ::ca::application * papp = NULL;

      if(m_mapApplication.Lookup(string(pszType) + ":" + string(pszId), papp))
         return papp;
      else
      {

         if(!bCreate)
            return NULL;

         papp = NULL;

         try
         {

            papp = create_application(pszType, pszId, bSynch, pbiasCreate);

         }
         catch(::exit_exception & e)
         {

            throw e;

         }
         catch(::ca::exception & e)
         {

            if(!Application.on_run_exception(e))
               throw exit_exception(get_app());

         }
         catch(...)
         {

            papp = NULL;

         }

         if(papp == NULL)
            return NULL;

         m_mapApplication.set_at(string(pszType) + ":" + string(pszId), papp);
         return papp;
      }
   }

   bool session::is_session()
   {
      return true;
   }

   ::ca::application * session::get_current_application()
   {
      return m_pappCurrent;
   }


   void session::check_topic_file_change()
   {
      if(m_varCurrentViewFile != m_varTopicFile && !m_varTopicFile.is_empty())
      {
         m_varCurrentViewFile = m_varTopicFile;
         request_topic_file();
      }
   }

   ::user::interaction * session::get_request_parent_ui(::userbase::main_frame * pmainframe, ::ca::create_context * pcreatecontext)
   {

      return get_request_parent_ui((::user::interaction * ) pmainframe, pcreatecontext);

   }

   ::user::interaction * session::get_request_parent_ui(::user::interaction * pinteraction, ::ca::create_context * pcreatecontext)
   {


      ::user::interaction * puiParent = NULL;

      if(pcreatecontext->m_spCommandLine->m_varQuery["uicontainer"].ca2 < ::user::interaction >() != NULL)
         puiParent = pcreatecontext->m_spCommandLine->m_varQuery["uicontainer"].ca2 < ::user::interaction >();

      if(puiParent == NULL && pcreatecontext->m_puiParent != NULL)
      {
         puiParent = pcreatecontext->m_puiParent;
      }

      if(puiParent == NULL && pcreatecontext->m_spCommandLine->m_pbiasCreate != NULL)
      {
         puiParent = pcreatecontext->m_spCommandLine->m_pbiasCreate->m_puiParent;
      }

      if(puiParent == NULL && pcreatecontext->m_spApplicationBias.is_set())
      {
         puiParent = pcreatecontext->m_spApplicationBias->m_puiParent;
      }


/*      if(pui == NULL && m_puiInitialPlaceHolderContainer != NULL)
      {
         pui = m_puiInitialPlaceHolderContainer;
      }*/

/*      if(pui == NULL && m_bShowPlatform && m_pbergedge->get_document() != NULL)
      {
         pui = Bergedge.get_document()->get_bergedge_view();
      }

      return pui;

   }*/

      if(pinteraction->get_app()->is_bergedge() || pcreatecontext->m_bClientOnly ||
         Application.directrix().m_varTopicQuery["client_only"] != 0 ||
         pcreatecontext->m_bOuterPopupAlertLike)
      {
         return puiParent;
      }

      /*if(!create_bergedge(pcreatecontext))
      {
         return NULL;
      }*/




/*      cube8::application & app = App(pinteraction->get_app());

      string strAppName = app.m_strAppName;

      if(strAppName != "session")
      {

         if(get_document() != NULL)
         {

            if(get_document()->get_typed_view < ::session::pane_view >() != NULL)
            {

               get_document()->get_typed_view < ::session::pane_view >()->set_cur_tab_by_id("app:" + strAppName);

               puiParent = get_document()->get_typed_view < ::session::pane_view >()->get_tab_holder(get_document()->get_typed_view < ::session::pane_view >()->get_tab_by_id("app:" + strAppName));

            }
            else
            {

               puiParent = get_document()->get_typed_view < ::session::view >();

            }

         }

      }*/

      return puiParent;

   }

/*   ::user::place_holder_ptra session::get_place_holder(::userbase::main_frame * pmainframe, ::ca::create_context * pcreatecontext)
   {

      UNREFERENCED_PARAMETER(pcreatecontext);

      ::user::place_holder_ptra holderptra;


      cube8::application & app = App(pmainframe->get_app());

      string strAppName = app.m_strAppName;

      if(get_document()->get_typed_view < ::session::pane_view >() != NULL)
      {

         get_document()->get_typed_view < ::session::pane_view >()->set_cur_tab_by_id("app:" + strAppName);

         holderptra.add(get_document()->get_typed_view < ::session::pane_view >()->get_tab_holder(get_document()->get_typed_view < ::session::pane_view >()->get_tab_by_id("app:" + strAppName)));

      }
      else
      {

         holderptra.add(get_document()->get_typed_view < ::session::view >());

      }

      return holderptra;

   }*/

   /*
   bool session::place(::userbase::main_frame * pmainframe, ::ca::create_context * pcreatecontext)
   {

      get_place_holder(pmainframe, pcreatecontext).hold(pmainframe);

      return true;

   }
   */

   void session::get_screen_rect(LPRECT lprect)
   {


/*      if(get_document() != NULL && get_view() != NULL)
      {
         get_view()->GetWindowRect(lprect);
      }
      else
      {
         System.get_screen_rect(lprect);
      }*/
   }

   bool session::on_install()
   {

      string strFormat;

      string strSentinelPath;

      strSentinelPath = System.dir().ca2("stage/x86/app-sentinel.exe");

      System.os().local_machine_set_run("ca2 app-sentinel", "\"" + strSentinelPath + "\"");


      System.os().defer_register_ca2_plugin_for_mozilla();



      return ::planebase::application::on_install();
   }


   void session::set_app_title(const char * pszType, const char * pszAppId, const char * pszTitle)
   {

      ::ca::application * papp = NULL;

      if(m_mapApplication.Lookup(string(pszType) + ":" + string(pszAppId), papp) && papp != NULL)
      {

/*         ::session::pane_view * ppaneview = get_document()->get_typed_view < ::session::pane_view >();

         if(ppaneview != NULL)
         {

            string strAppName(pszAppId);

            ::user::tab::pane * ppane = ppaneview->get_pane_by_id("app:" + strAppName);

            if(ppane != NULL)
            {

               ppane->m_strTitleEx = pszTitle;

               ppaneview->layout();

            }

         }*/

      }


   }

   //////////////////////////////////////////////////////////////////////////////////////////////////
   // Session/Bergedge
   //
   ::bergedge::view * session::get_view()
   {

      if(m_pbergedgeInterface != NULL)
      {
         return m_pbergedgeInterface->get_view();
      }

      return NULL;

   }

   ::bergedge::document * session::get_document()
   {

      if(m_pbergedgeInterface != NULL)
      {
         return m_pbergedgeInterface->get_document();
      }

      return NULL;

   }

   FileManagerTemplate * session::GetStdFileManagerTemplate()
   {

      if(m_pbergedgeInterface != NULL)
      {
         return m_pbergedgeInterface->GetStdFileManagerTemplate();
      }

      return NULL;

   }


   bool session::is_remote_session()
   {


      return System.os().is_remote_session() || (m_pbergedgeInterface != NULL && m_pbergedgeInterface->is_remote_session());


   }


   bool session::is_mouse_button_pressed(::user::e_mouse emouse)
   {

#ifdef METROWIN

      if(emouse == ::user::mouse_left_button)
      {
         return System.is_key_pressed(VK_LBUTTON);
      }
      else if(emouse == ::user::mouse_right_button)
      {
         return System.is_key_pressed(VK_RBUTTON);
      }
      else if(emouse == ::user::mouse_middle_button)
      {
         return System.is_key_pressed(VK_MBUTTON);
      }
      else
      {
         throw "not expected e_mouse value";
      }

#elif defined(WINDOWS)

      if(emouse == ::user::mouse_left_button)
      {
         return (::GetAsyncKeyState(VK_LBUTTON) & (int16_t) 0x8000) != 0;
      }
      else if(emouse == ::user::mouse_right_button)
      {
         return (::GetAsyncKeyState(VK_RBUTTON) & (int16_t) 0x8000) != 0;
      }
      else if(emouse == ::user::mouse_middle_button)
      {
         return (::GetAsyncKeyState(VK_MBUTTON) & (int16_t) 0x8000) != 0;
      }
      else
      {
         throw "not expected e_mouse value";
      }

#else

      throw todo(get_app());

#endif

   }


   COLORREF session::get_default_color(uint64_t ui)
   {

#ifdef WINDOWSEX
      return GetSysColor((int) ui);
#else
      return 0;
#endif

   }


} // namespace plane



