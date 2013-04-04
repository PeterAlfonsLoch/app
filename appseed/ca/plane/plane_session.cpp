#include "framework.h"


namespace plane
{


   session::session()
   {

      m_bDrawCursor              = true;
      m_pbergedge                = ::null();
/*      m_pnaturedocument          = ::null();
      m_pplatformdocument        = ::null();
      m_pbergedgedocument        = ::null();*/
      m_bShowPlatform            = false;
      m_pappCurrent              = ::null();
      m_psession                 = this;
      m_pbergedgeInterface       = ::null();

      ::fs::set * pset = new class ::fs::set(this);
      pset->m_spafsdata.add(new ::fs::native(this));
      m_spfsdata = pset;


      m_pifs                     = new ifs(this, "");
      m_prfs                     = new ::fs::remote_native(this, "");

      m_puserpresence            = new ::userpresence::userpresence();


      m_ecursorDefault  = ::visual::cursor_arrow;
      m_ecursor         = ::visual::cursor_default;


   }

   session::~session()
   {

/*      if(m_pnaturedocument != ::null())
      {
         m_pnaturedocument->on_close_document();
      }

      if(m_pplatformdocument != ::null())
      {
         m_pplatformdocument->on_close_document();
      }

      if(m_pbergedgedocument != ::null())
      {
         m_pbergedgedocument->on_close_document();
      }
      */
      string strId;
      ::ca::application * pcaapp;


      POSITION pos = m_mapApplication.get_start_position();

      while(pos != ::null())
      {

         strId.Empty();
         pcaapp = ::null();

         m_mapApplication.get_next_assoc(pos, strId, pcaapp);

         ::ca::application * papp = dynamic_cast < ::ca::application * > (pcaapp);

         papp->post_thread_message(WM_QUIT, 0, 0);
      }

   }

   void session::construct()
   {

      m_strAppName         = "session";
      m_strBaseSupportId   = "ca2_bergedge";
      m_strInstallToken    = "session";
      m_bLicense           = false;
      m_eexclusiveinstance = ::ca::ExclusiveInstanceNone;
      m_puserpresence->construct(this);

   }

   bool session::initialize()
   {

      if(!::planebase::application::initialize())
         return false;

      if(!m_puserpresence->initialize())
         return false;

      return true;

   }


   bool session::initialize_instance()
   {

      if(!::planebase::application::initialize_instance())
         return false;

      initialize_bergedge_application_interface();


      //filemanager().std().m_strLevelUp = "levelup";


      SetRegistryKey("ca2core");


      if(!InitializeLocalDataCentral())
      {
         simple_message_box(::null(), "Could not initialize Local data central");
         return false;
      }




      return true;
   }


   bool session::finalize()
   {

      bool bOk = true;

      try
      {

         bOk = m_puserpresence->finalize();

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
      //m_pdocmanager->_001OnFileNew();
   }


   bool session::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)

   {
      return ::ca::application::_001OnCmdMsg(pcmdmsg);
   }

   ::ca::application * session::get_app() const
   {
      return ::planebase::application::get_app();
   }

   void session::load_string_table()
   {
      ::ca::application::load_string_table();
      ::ca::application::load_string_table("plane", "");
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
      m_pnaturedocument = ::null();*/
   }

   bool session::create_bergedge(::ca::create_context * pcreatecontext)
   {


      //if(m_pbergedgeInterface != ::null())
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

      if(papp == ::null())
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

      TRACE("::plane::session::on_request(::ca::create_context *)");


      if(pcreatecontext->m_spCommandLine->m_varQuery["app"].array_get_count() > 1
      && pcreatecontext->m_spCommandLine->m_varQuery["app"].stra()[0] == "app/sphere/userstack")
      {
         start_application("application", "app/sphere/userstack", pcreatecontext);
         return;
      }

      string strApp = pcreatecontext->m_spCommandLine->m_strApp;

      if(strApp == "app/sphere/userstack")
      {
         start_application("application", "app/sphere/userstack", pcreatecontext);
         return;
      }

      if(m_pbergedgeInterface != ::null())
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
               if(m_pappCurrent != ::null())
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
            /*if(get_document() != ::null() && get_document()->get_typed_view < ::session::view >() != ::null())
            {
               ::simple_frame_window * pframe = dynamic_cast < ::simple_frame_window * > (get_document()->get_typed_view < ::session::view >()->GetParentFrame());
               if(pframe != ::null())
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
      if(papp == ::null())
         return ::null();

      if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("install")
      || pcreatecontext->m_spCommandLine->m_varQuery.has_property("uninstall"))
      {
         System.appptra().remove(papp);
         return ::null();
      }

      pcreatecontext->m_spCommandLine->m_eventReady.ResetEvent();

      if(strApp != "session")
      {

         if(strApp == "bergedge")
         {

            m_pbergedge             = papp->get_bergedge();

            m_pbergedgeInterface    = dynamic_cast < ::bergedge_interface * > (papp);

            if(m_pbergedgeInterface == ::null())
            {

               try
               {

                  delete papp;

               }
               catch(...)
               {
               }

               return ::null();

            }

         }


         UINT uiMessage = WM_APP + 2043;

         papp->post_thread_message(uiMessage, 2, (LPARAM) (::ca::create_context *) pcreatecontext);

         while(get_run())
         {

            if(pcreatecontext->m_spCommandLine->m_eventReady.wait(millis(84)).signaled())
               break;

         }

         if(!get_run())
         {
            try
            {
               delete papp;
            }
            catch(...)
            {
            }
            return ::null();
         }

      }

      return papp;

   }


   /*::session::document * session::get_document()
   {
      return m_pbergedgedocument;
   }

   ::session::view * session::get_view()
   {
      if(get_document() == ::null())
         return ::null();
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

      if(pbiasCreate != ::null())
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

      if(::ca::str::ends_ci(strPathName, ".cgcl"))
      {

      }

      string strProtocol = System.url().get_protocol(strPathName);

      if(strProtocol == "app")
      {

         strId = System.url().get_server(strPathName);

         string str = System.url().get_object(strPathName);

         ::ca::str::begins_eat(str, "/");

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

      if(papp == ::null())
         return false;

      papp->::ca::request_interface::create(pcreatecontext);

      return true;

   }

   bool session::InitializeLocalDataCentral()
   {

/*      m_pdatabase = new nature::database(this);

      if(m_pdatabase == ::null())
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
      m_papp = ::null();
      m_puiParent = ::null();
   }

   void session::on_exclusive_instance_conflict(::ca::EExclusiveInstance eexclusive)
   {

      if(eexclusive == ::ca::ExclusiveInstanceLocalId)
      {
         /*
         ::primitive::memory_file file(get_app());
         file.from_string(command().m_varTopicFile);
         COPYDATASTRUCT data;
         data.dwData = 1984;
         data.cbData = (uint32_t) file.get_length();
         data.lpData = file.get_data();
         oswindow oswindow = ::FindWindowA(::null(), "::ca::fontopus::message_wnd::session::");

         ::SendMessage(oswindow, WM_COPYDATA, ::null(), (LPARAM) &data);*/

#if defined(WINDOWSEX) || defined(LINUX) || defined(MACOS)

         small_ipc_tx_channel channel;

         if(channel.open("::ca::fontopus::message_wnd::session::"))
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

      if(m_pbergedgeInterface != ::null())
      {

         m_pbergedgeInterface->request(pcreatecontext);
         return;

      }

      if(pcreatecontext->m_spCommandLine->m_varFile.get_type() == var::type_string)
      {
         if(::ca::str::ends_ci(pcreatecontext->m_spCommandLine->m_varFile, ".ca"))
         {
            string strCommand = Application.file().as_string(pcreatecontext->m_spCommandLine->m_varFile);
            if(::ca::str::begins_eat(strCommand, "ca2prompt\r")
            || ::ca::str::begins_eat(strCommand, "ca2prompt\n"))
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
      else if(m_pappCurrent != ::null() && m_pappCurrent != this
         && (pcreatecontext->m_spCommandLine->m_strApp.is_empty()
         ||App(m_pappCurrent).m_strAppName == pcreatecontext->m_spCommandLine->m_strApp))
      {


/*         if(get_document() != ::null() && get_document()->get_typed_view < ::session::pane_view >() != ::null())
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

      ::ca::application_request request;

      request.m_iEdge         = m_iEdge;
      request.m_strApp        = pszId;
      request.m_varFile       = varFile;
      request.m_varQuery      = varQuery;
      request.m_pbiasCreate   = pbiasCreate;

      request_application(&request);

   }*/

   ::ca::application * session::application_get(const char * pszType, const char * pszId, bool bCreate, bool bSynch, ::ca::application_bias * pbiasCreate)
   {
      ::ca::application * papp = ::null();

      if(m_mapApplication.Lookup(string(pszType) + ":" + string(pszId), papp))
         return papp;
      else
      {

         if(!bCreate)
            return ::null();

         papp = ::null();

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

            papp = ::null();

         }

         if(papp == ::null())
            return ::null();

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


      ::user::interaction * puiParent = ::null();

      if(pcreatecontext->m_spCommandLine->m_varQuery["uicontainer"].ca < ::user::interaction >() != ::null())
         puiParent = pcreatecontext->m_spCommandLine->m_varQuery["uicontainer"].ca < ::user::interaction >();

      if(puiParent == ::null() && pcreatecontext->m_puiParent != ::null())
      {
         puiParent = pcreatecontext->m_puiParent;
      }

      if(puiParent == ::null() && pcreatecontext->m_spCommandLine->m_pbiasCreate != ::null())
      {
         puiParent = pcreatecontext->m_spCommandLine->m_pbiasCreate->m_puiParent;
      }

      if(puiParent == ::null() && pcreatecontext->m_spApplicationBias.is_set())
      {
         puiParent = pcreatecontext->m_spApplicationBias->m_puiParent;
      }


/*      if(pui == ::null() && m_puiInitialPlaceHolderContainer != ::null())
      {
         pui = m_puiInitialPlaceHolderContainer;
      }*/

/*      if(pui == ::null() && m_bShowPlatform && m_pbergedge->get_document() != ::null())
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
         return ::null();
      }*/




/*      cube::application & app = App(pinteraction->get_app());

      string strAppName = app.m_strAppName;

      if(strAppName != "session")
      {

         if(get_document() != ::null())
         {

            if(get_document()->get_typed_view < ::session::pane_view >() != ::null())
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


      cube::application & app = App(pmainframe->get_app());

      string strAppName = app.m_strAppName;

      if(get_document()->get_typed_view < ::session::pane_view >() != ::null())
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

      if(m_pbergedgeInterface != ::null())
      {

         m_pbergedgeInterface->get_screen_rect(lprect);

         return;

      }


/*      if(get_document() != ::null() && get_view() != ::null())
      {
         get_view()->GetWindowRect(lprect);
      }
      else
      {*/
         System.get_screen_rect(lprect);
      /*}*/
   }

   bool session::on_install()
   {

      string strFormat;

      string strSentinelPath;

      strSentinelPath = System.dir().ca2("stage/x86/app-sentinel.exe");

      System.os().local_machine_set_run("ca app-sentinel", "\"" + strSentinelPath + "\"");


      System.os().defer_register_ca2_plugin_for_mozilla();



      return ::planebase::application::on_install();
   }


   void session::set_app_title(const char * pszType, const char * pszAppId, const char * pszTitle)
   {

      ::ca::application * papp = ::null();

      if(m_mapApplication.Lookup(string(pszType) + ":" + string(pszAppId), papp) && papp != ::null())
      {

/*         ::session::pane_view * ppaneview = get_document()->get_typed_view < ::session::pane_view >();

         if(ppaneview != ::null())
         {

            string strAppName(pszAppId);

            ::user::tab::pane * ppane = ppaneview->get_pane_by_id("app:" + strAppName);

            if(ppane != ::null())
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

      if(m_pbergedgeInterface != ::null())
      {
         return m_pbergedgeInterface->get_view();
      }

      return ::null();

   }

   ::bergedge::document * session::get_document()
   {

      if(m_pbergedgeInterface != ::null())
      {
         return m_pbergedgeInterface->get_document();
      }

      return ::null();

   }

   bool session::is_remote_session()
   {


      return System.os().is_remote_session() || (m_pbergedgeInterface != ::null() && m_pbergedgeInterface->is_remote_session());


   }


   bool session::is_mouse_button_pressed(::user::e_mouse emouse)
   {

      if(emouse == ::user::mouse_left_button)
      {
         return System.is_key_pressed(::user::key_lbutton);
      }
      else if(emouse == ::user::mouse_right_button)
      {
         return System.is_key_pressed(::user::key_rbutton);
      }
      else if(emouse == ::user::mouse_middle_button)
      {
         return System.is_key_pressed(::user::key_mbutton);
      }
      else
      {
         throw "not expected e_mouse value";
      }


   }


   COLORREF session::get_default_color(uint64_t ui)
   {

      switch(ui)
      {
      case COLOR_3DFACE:
         return ARGB(127, 192, 192, 184);
      case COLOR_WINDOW:
         return ARGB(127, 255, 255, 255);
      case COLOR_3DLIGHT:
         return ARGB(127, 218, 218, 210);
      case COLOR_3DHIGHLIGHT:
         return ARGB(127, 238, 238, 230);
      case COLOR_3DSHADOW:
         return ARGB(127, 138, 138, 130);
      case COLOR_3DDKSHADOW:
         return ARGB(127, 84, 84, 77);
      default:
         break;
      }

      return ARGB(127, 0, 0, 0);

   }

   ::visual::cursor * session::get_cursor()
   {
      if(m_ecursor == ::visual::cursor_none)
         return ::null();
      else if(m_ecursor == ::visual::cursor_default)
         return System.visual().get_cursor(m_ecursorDefault);
      else
         return System.visual().get_cursor(m_ecursor);
   }


   void session::set_cursor(::visual::e_cursor ecursor)
   {
      m_ecursor = ecursor;
   }

   ::visual::cursor * session::get_default_cursor()
   {
      return System.visual().get_cursor(m_ecursorDefault);
   }

   void session::set_default_cursor(::visual::e_cursor ecursor)
   {
      if(ecursor == ::visual::cursor_default)
      {
         m_ecursorDefault = ::visual::cursor_arrow;
      }
      else
      {
         m_ecursorDefault = ecursor;
      }
   }


} // namespace plane



