//#include "framework.h"
//#include "core/user/user/user.h"
//#include "core/filesystem/filemanager/filemanager.h"


namespace core
{


   session::session(::aura::application * papp):
      object(papp),
      ::aura::session(papp),
      ::axis::session(papp),
      ::base::session(papp),
      ::thread(papp)
   {

      m_paurasystem                       = papp->m_paurasystem;

      m_paxissystem                       = papp->m_paxissystem;

      m_pbasesystem                       = papp->m_pbasesystem;

      m_paurasystem->m_pcoresession       = this;

      m_paxissession                      = this;
         
      m_pbasesession                      = this;

      m_pcoresession                      = this;

      m_pauraapp                          = this;

      m_paxisapp                          = this;

      m_pbaseapp                          = this;
      
      m_pcoreapp                          = this;

      m_pcoresession                      = this;

      m_pnaturedocument                   = NULL;
      m_pplatformdocument                 = NULL;
      m_pbergedgedocument                 = NULL;
      m_pnaturedocument                   = NULL;
      m_pplatformdocument                 = NULL;
      m_pbergedgedocument                 = NULL;
      m_bLicense				               = false;

      m_strAppName                        = "bergedge";

   }

   session::~platform_parent
   {

      if(m_pnaturedocument != NULL)
      {
         m_pnaturedocument.cast < ::user::document> ()->on_close_document();
      }

      if(m_pplatformdocument != NULL)
      {
         m_pplatformdocument.cast < ::user::document>()->on_close_document();
      }

      if(m_pbergedgedocument != NULL)
      {
         m_pbergedgedocument.cast < ::user::document>()->on_close_document();
      }

   }


   void session::construct(const char * pszAppId)
   {

      ::core::application::construct("session");

      m_strAppName         = "session";
      m_strBaseSupportId   = "ca2_bergedge";
      m_strInstallToken    = "session";
      m_bLicense           = false;
      m_eexclusiveinstance = ExclusiveInstanceNone;

   }


   void session::install_message_handling(::message::dispatch * pdispatch)
   {
      
      core::application::install_message_handling(pdispatch);
      base::session::install_message_handling(pdispatch);

   }


   bool session::process_initialize()
   {

      if(!::core::application::process_initialize())
         return false;

      if(!::base::session::process_initialize())
         return false;

      m_puserex = create_userex();

      if(m_puserex == NULL)
         return false;

      //m_puserex->construct(this);

      return true;

   }


   bool session::initialize1()
   {

      if(!::core::application::initialize1())
         return false;

      if(!::base::session::initialize1())
         return false;

      if(!m_puserex->initialize())
         return false;

      if(!m_puserex->initialize1())
         return false;

      if(!m_puserex->initialize2())
         return false;

      return true;


   }


   bool session::initialize()
   {

      if(!::core::application::initialize())
         return false;

      if(!::base::session::initialize())
         return false;

      return true;

   }

   
   bool session::initialize2()
   {
      
      if(!::core::application::initialize2())
         return false;
      
      if(!::base::session::initialize2())
         return false;

      return true;

   }


   bool session::on_initial_update()
   {

      m_pfilemanager = canew(::filemanager::filemanager(this));

      m_pfilemanager->construct(this);

      if(!m_pfilemanager->initialize())
      {
         return false;

      }

      filemanager().std().m_strLevelUp = "levelup";

      return true;

   }


   bool session::initialize_instance()
   {

      if(!::core::application::initialize_instance())
         return false;

      if(!::base::session::initialize_instance())
         return false;

      initialize_bergedge_application_interface();

      SetRegistryKey("ca2core");

      if(!InitializeLocalDataCentral())
      {

         simple_message_box(NULL, "Could not initialize Local data central");

         return false;

      }

      initialize_bergedge_application_interface();

      if(is_remote_session())
      {

         //Session.savings().save(::aura::resource_display_bandwidth);
         //Session.savings().save(::aura::resource_blur_background);
         //Session.savings().save(::aura::resource_blurred_text_embossing);
         //Session.savings().save(::aura::resource_translucent_background);

      }


      return true;

   }


   bool session::finalize()
   {

      bool bOk = true;

      try
      {

         bOk = ::base::session::finalize();

      }
      catch(...)
      {

         bOk = false;
      }

      try
      {

         bOk = ::core::application::finalize();

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

         ::base::session::exit_instance();

      }
      catch(...)
      {

      }


      try
      {

         ::core::application::exit_instance();

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


   bool session::_001OnCmdMsg(::aura::cmd_msg * pcmdmsg)
   {

      return application::_001OnCmdMsg(pcmdmsg);

   }


   void session::load_string_table()
   {

      application::load_string_table();
      application::load_string_table("plane", "");
      application::load_string_table();
      application::load_string_table("session", "");

   }


   void session::launch_app(const char * psz)
   {
      UNREFERENCED_PARAMETER(psz);
   }

   void session::install_app(const char * psz)
   {
      UNREFERENCED_PARAMETER(psz);
   }

   void session::on_request(sp(::create) pcreatecontext)
   {

      ::base::session::on_request(pcreatecontext);

   }



   bool session::open_by_file_extension(const char * pszPathName, application_bias * pbiasCreate)
   {

      sp(::create) cc(allocer());

      cc->m_spCommandLine->m_varFile = pszPathName;

      if(pbiasCreate != NULL)
      {
         cc->m_spApplicationBias->operator=(*pbiasCreate);
      }

      return open_by_file_extension(cc);

   }


   bool session::open_by_file_extension(::create * pcreatecontext)
   {

      string strId;

      string strOriginalPathName(pcreatecontext->m_spCommandLine->m_varFile);

      ::file::path strPathName(strOriginalPathName);

      strsize iFind = strPathName.find("?");

      if(iFind >= 0)
      {

         strPathName = strPathName.Left(iFind);

      }

      if(::str::ends_ci(strPathName, ".ca2"))
      {

      }

      string strProtocol = System.url().get_protocol(strPathName);

      if(strProtocol == "app")
      {

         strId = System.url().get_server(strPathName);

         string str = System.url().get_object(strPathName);

         ::str::begins_eat(str, "/");

         pcreatecontext->m_spCommandLine->m_varFile = str;

      }
      else
      {

         string strExtension = strPathName.extension();

         stringa straApp;

         System.filehandler().get_extension_app(straApp, strExtension);

         if(straApp.get_count() == 1)
         {
            strId = straApp[0];
         }
         else
         {
            strId = "app/sphere/default_file_handler";
         }

      }

      ::aura::application * papp = application_get("application", strId, true, true, pcreatecontext->m_spApplicationBias);

      if(papp == NULL)
         return false;

      papp->m_pcoreapp->::object::create(pcreatecontext);

      return true;

   }



   session::run_application::run_application()
   {
      m_pauraapp = NULL;
      m_puiParent = NULL;
   }

   //   void session::on_exclusive_instance_conflict(EExclusiveInstance eexclusive)
   //   {
   //
   //      if(eexclusive == ExclusiveInstanceLocalId)
   //      {
   //         /*
   //         ::file::memory_buffer file(get_app());
   //         file.from_string(command()->m_varTopicFile);
   //         COPYDATASTRUCT data;
   //         data.dwData = 1984;
   //         data.cbData = (uint32_t) file.get_length();
   //         data.lpData = file.get_data();
   //         oswindow oswindow = ::FindWindowA(NULL, "::draw2d::fontopus::message_wnd::session::");
   //
   //         ::SendMessage(oswindow, WM_COPYDATA, NULL, (LPARAM) &data);*/
   //
   //#if defined(WINDOWSEX) || defined(LINUX) || defined(APPLEOS)
   //
   //         ::aura::ipc::tx channel;
   //
   //         if(channel.open("::draw2d::fontopus::message_wnd::session::"))
   //         {
   //            channel.send(command()->m_varTopicFile, false);
   //            channel.close();
   //         }
   //
   //#else
   //
   //          throw todo(get_app());
   //
   //#endif
   //
   //
   //      }
   //
   //   }
   //

   void session::request_create(sp(::create) pcreatecontext)
   {

      ::base::session::request_create(pcreatecontext);

//
//      //      if(m_pbergedgeInterface != NULL)
//      {
//
//         if(m_pappCurrent != NULL && m_pappCurrent != this
//            && (pcreatecontext->m_spCommandLine->m_strApp.is_empty()
//            ||App(m_pappCurrent).m_strAppName == pcreatecontext->m_spCommandLine->m_strApp))
//         {
//            //if(get_document() != NULL && get_document()->get_typed_view < ::bergedge::pane_view >() != NULL)
//            //{
//            //   get_document()->get_typed_view < ::bergedge::pane_view >()->set_cur_tab_by_id("app:" + App(m_pappCurrent).m_strAppName);
//            //}
//            App(m_pappCurrent).request_create(pcreatecontext);
//            if(pcreatecontext->m_spCommandLine->m_varQuery["document"].cast < ::user::document > () == NULL)
//            {
//  //             goto alt1;
//            }
//
//         }
//         else
//         {
////alt1:
//            if(pcreatecontext->m_spCommandLine->m_varFile.get_type() == var::type_string)
//            {
//               if(::str::ends_ci(pcreatecontext->m_spCommandLine->m_varFile, ".core"))
//               {
//                  string strCommand = Application.file().as_string(pcreatecontext->m_spCommandLine->m_varFile);
//                  if(::str::begins_eat(strCommand, "ca2prompt\r")
//                     || ::str::begins_eat(strCommand, "ca2prompt\n"))
//                  {
//                     strCommand.trim();
//                     command()->add_fork_uri(strCommand);
//                  }
//                  return;
//               }
//               //else if(pcreatecontext->m_spCommandLine->m_strApp.has_char()
//               //   && get_document() != NULL
//               //   && get_document()->get_typed_view < ::bergedge::pane_view >() != NULL)
//               //{
//               //   get_document()->get_typed_view < ::bergedge::pane_view >()->set_cur_tab_by_id("app:" + pcreatecontext->m_spCommandLine->m_strApp);
//               //   App(m_pappCurrent).request_create(pcreatecontext);
//               //}
//               else
//               {
//                  on_request(pcreatecontext);
//               }
//            }
//            //else if(pcreatecontext->m_spCommandLine->m_strApp.has_char() &&
//            //   get_document() != NULL && get_document()->get_typed_view < ::bergedge::pane_view >() != NULL
//            //   && (!pcreatecontext->m_spApplicationBias.is_set() || pcreatecontext->m_spApplicationBias->m_puiParent == NULL))
//            //{
//            //   //simple_message_box(NULL, "request3", "request3", MB_ICONEXCLAMATION);
//            //   get_document()->get_typed_view < ::bergedge::pane_view >()->set_cur_tab_by_id("app:" + pcreatecontext->m_spCommandLine->m_strApp);
//            //   App(m_pappCurrent).request_create(pcreatecontext);
//            //}
//            //else
//            {
//               //simple_message_box(NULL, "request4", "request4", MB_ICONEXCLAMATION);
//               on_request(pcreatecontext);
//            }
//         }
//         return;
//
//      }
//
//      if(pcreatecontext->m_spCommandLine->m_varFile.get_type() == var::type_string)
//      {
//         if(::str::ends_ci(pcreatecontext->m_spCommandLine->m_varFile, ".core"))
//         {
//            string strCommand = Application.file().as_string(pcreatecontext->m_spCommandLine->m_varFile);
//            if(::str::begins_eat(strCommand, "ca2prompt\r")
//               || ::str::begins_eat(strCommand, "ca2prompt\n"))
//            {
//               strCommand.trim();
//               command()->add_fork_uri(strCommand);
//               System.m_bDoNotExitIfNoApplications = true;
//            }
//            return;
//         }
//         else
//         {
//            on_request(pcreatecontext);
//         }
//      }
//      else if(m_pappCurrent != NULL && m_pappCurrent != this
//         && (pcreatecontext->m_spCommandLine->m_strApp.is_empty()
//         ||App(m_pappCurrent).m_strAppName == pcreatecontext->m_spCommandLine->m_strApp))
//      {
//
//
//         /*         if(get_document() != NULL && get_document()->get_typed_view < ::session::pane_view >() != NULL)
//         {
//         get_document()->get_typed_view < ::session::pane_view >()->set_cur_tab_by_id("app:" + App(m_pappCurrent).m_strAppName);
//         }*/
//         App(m_pappCurrent).request_create(pcreatecontext);
//      }
//      else
//      {
//         on_request(pcreatecontext);
//      }
   }

   void session::request_topic_file(var & varQuery)
   {
      request_file_query(Session.m_varTopicFile, varQuery);
   }

   void session::request_topic_file()
   {
      request_file(Session.m_varTopicFile);
   }

   /*void session::request_application(const char * pszId, var varFile, var varQuery, application_bias * pbiasCreate)
   {

   ::core::application_request request;

   request.m_iEdge         = m_iEdge;
   request.m_strApp        = pszId;
   request.m_varFile       = varFile;
   request.m_varQuery      = varQuery;
   request.m_pbiasCreate   = pbiasCreate;

   request_application(&request);

   }*/
   /*
   sp(::aura::application) session::application_get(const char * pszType, const char * pszId, bool bCreate, bool bSynch, application_bias * pbiasCreate)
   {
   ::aura::application * papp = NULL;

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
   catch(::exception::exception &)
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
   */
   bool session::is_session()
   {
      return true;
   }

   sp(::aura::application) session::get_current_application()
   {
      return Session.m_pappCurrent;
   }




   bool session::on_install()
   {

      string strFormat;

      string strSentinelPath;

      strSentinelPath = System.dir().element() / "stage/x86/app.sentinel.exe";

      System.os().local_machine_set_run("core app.sentinel", "\"" + strSentinelPath + "\"");

      System.os().defer_register_ca2_plugin_for_mozilla();

      return ::core::application::on_install();

   }




   bool session::is_remote_session()
   {


      return System.os().is_remote_session();


   }


   bool session::is_mouse_button_pressed(::user::e_mouse emouse)
   {

      if(emouse == ::user::mouse_left_button)
      {
         return Session.is_key_pressed(::user::key_lbutton);
      }
      else if(emouse == ::user::mouse_right_button)
      {
         return Session.is_key_pressed(::user::key_rbutton);
      }
      else if(emouse == ::user::mouse_middle_button)
      {
         return Session.is_key_pressed(::user::key_mbutton);
      }
      else
      {
         throw "not expected e_mouse value";
      }


   }



   void session::OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema)
   {

      UNREFERENCED_PARAMETER(pdata);

      m_ptemplate_html->open_document_file(itema[0]->m_strPath);

   }


   bool session::open_file(::filemanager::data * pdata, ::fs::item_array & itema)
   {

      UNREFERENCED_PARAMETER(pdata);

      if(itema.get_size() > 0)
      {

         return true;

      }

      return false;

   }


   void session::initialize_bergedge_application_interface()
   {
//      int32_t iCount = 32; // todo: get from bergedge profile
      m_pnaturedocument = NULL;
   }



   void session::on_app_request_bergedge_callback(::aura::application * papp)
   {
      if(&App(papp) != NULL)
      {

         Session.m_pappCurrent = papp;

      }

      if(Session.m_bShowPlatform)
      {
         //sp(::simple_frame_window) pframeApp = get_document()->get_typed_view < ::bergedge::pane_view >()->get_view_uie();
         //if(pframeApp != NULL)
         //{
         //   pframeApp->WfiFullScreen();
         //}
         //sp(::simple_frame_window) pframe = get_document()->get_typed_view < ::bergedge::pane_view >()->GetParentFrame();
         //if(pframe != NULL)
         //{
         //   pframe->ShowWindow(SW_SHOW);
         //}
      }
      else
      {
         //if(get_document() != NULL && get_document()->get_typed_view < ::bergedge::view >() != NULL)
         //{
         //   sp(::simple_frame_window) pframe = get_document()->get_typed_view < ::bergedge::view >()->GetParentFrame();
         //   if(pframe != NULL)
         //   {
         //      pframe->ShowWindow(SW_SHOW);
         //      if(pframe->GetTypedParent < ::plugin::host_interaction > () != NULL)
         //      {
         //         pframe->GetTypedParent < ::plugin::host_interaction > ()->layout();
         //      }
         //      else
         //      {
         //         pframe->InitialFramePosition();
         //      }
         //   }
         //}
      }

      if(Session.m_pappCurrent != NULL && Session.m_pappCurrent->m_pbasesession->m_pfontopus->m_puser != NULL)
      {
         try
         {
            get_view()->GetParentFrame()->SetWindowText(Session.m_pappCurrent->m_pbasesession->m_pfontopus->m_puser->m_strLogin);
         }
         catch(...)
         {
         }
      }

   }


   sp(::user::document) session::get_document()
   {
      return m_pbergedgedocument;
   }

   sp(::user::impact) session::get_view()
   {
      if(get_document() == NULL)
         return NULL;
//      return get_document()->get_bergedge_view();
      return NULL;
   }

   sp(::user::document) session::get_platform()
   {
      return m_pplatformdocument;
   }

   sp(::user::document) session::get_nature()
   {
      return m_pnaturedocument;
   }


   bool session::InitializeLocalDataCentral()
   {

      //m_pdatabase = new nature::database(this);

      //if(m_pdatabase == NULL)
      //{
      //   TRACE("VmpLightApp::initialize_instance failed to instatiate LightDB\n");
      //   return false;
      //}

      //if(!m_pdatabase->Initialize())
      //{
      //   TRACE("VmpLightApp::initialize_instance failed to initialize LightDB\n");
      //   return false;
      //}

      return true;

   }

   string session::filemanager_get_initial_browse_path()
   {
      return filemanager().get_initial_browse_path();
   }

   void session::on_exclusive_instance_conflict(EExclusiveInstance eexclusive)
   {
      if(eexclusive == ExclusiveInstanceLocalId)
      {
#ifdef WINDOWSEX
         ::file::memory_buffer file(get_app());
         file.from_string(command()->m_varTopicFile);
         COPYDATASTRUCT data;
         data.dwData = 1984;
         data.cbData = (uint32_t) file.get_length();
         data.lpData = file.get_data();
         ::oswindow oswindow = ::FindWindowA(NULL, "::draw2d::fontopus::message_wnd::bergedge::");


         ::SendMessage(oswindow, WM_COPYDATA, 0, (LPARAM) &data);

#else

         throw todo(get_app());

#endif

      }
   }


   /*void session::request_application(const char * pszId, var varFile, var varQuery, application_bias * pbiasCreate)
   {

   ::core::application_request request;

   request.m_iEdge         = m_iEdge;
   request.m_strApp        = pszId;
   request.m_varFile       = varFile;
   request.m_varQuery      = varQuery;
   request.m_pbiasCreate   = pbiasCreate;

   request_application(&request);

   }*/

   sp(::aura::application) session::application_get(const char * pszType, const char * pszId, bool bCreate, bool bSynch, application_bias * pbiasCreate)
   {

      sp(::aura::application) papp = NULL;

      if(m_pbasesession->m_mapApplication.Lookup(string(pszType) + ":" + string(pszId),papp))
      {
         
         return papp;

      }
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
         catch(::exception::exception & e)
         {

            if(!App(this).on_run_exception(e))
               throw exit_exception(get_app());

         }
         catch(...)
         {

            papp = NULL;

         }

         if(papp == NULL)
            return NULL;

         if(&App(papp) == NULL)
         {

            try
            {

               papp.release();

            }
            catch(...)
            {

            }

            return NULL;

         }
         
         m_pbasesession->m_mapApplication.set_at(string(pszType) + ":" + string(pszId), papp);

         return papp;

      }

   }



   void session::check_topic_file_change()
   {
      if(Session.m_varCurrentViewFile != Session.m_varTopicFile && !Session.m_varTopicFile.is_empty())
      {
         Session.m_varCurrentViewFile = Session.m_varTopicFile;
         request_topic_file();
      }
   }

   sp(::user::interaction) session::get_request_parent_ui(sp(::user::interaction) pinteraction, sp(::create) pcreatecontext)
   {


      sp(::user::interaction) puiParent = NULL;

      if(pcreatecontext->m_spCommandLine->m_varQuery["uicontainer"].cast < ::user::interaction >() != NULL)
         puiParent = pcreatecontext->m_spCommandLine->m_varQuery["uicontainer"].cast < ::user::interaction >();

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
      pui = Session.get_document()->get_bergedge_view();
      }

      return pui;

      }*/

      if( pcreatecontext->m_bClientOnly ||
         Application.directrix()->m_varTopicQuery.has_property("client_only") ||
         pcreatecontext->m_bOuterPopupAlertLike)
      {
         return puiParent;
      }


      //bool bCreateBergedge = false;

      //if(bCreateBergedge)
      //{

      //   if(!create_bergedge(pcreatecontext))
      //   {
      //      return NULL;


      //   }

      //}




      ::core::application & app = App(pinteraction->get_app());

      string strAppName = app.m_strAppName;

      if(strAppName != "bergedge")
      {

         if(get_document() != NULL)
         {

            //if(get_document()->get_typed_view < ::bergedge::pane_view >() != NULL)
            //{

            //   get_document()->get_typed_view < ::bergedge::pane_view >()->set_cur_tab_by_id("app:" + strAppName);

            //   puiParent = get_document()->get_typed_view < ::bergedge::pane_view >()->get_tab_holder(get_document()->get_typed_view < ::bergedge::pane_view >()->get_tab_by_id("app:" + strAppName));

            //}
            //else
            //{

            //   puiParent = get_document()->get_typed_view < ::bergedge::view >();

            //}

         }

      }

      return puiParent;

   }

   //::user::place_holder_ptra session::get_place_holder(sp(::user::frame_window) pmainframe, sp(::create) pcreatecontext)
   //{

   //   UNREFERENCED_PARAMETER(pcreatecontext);

   //   ::user::place_holder_ptra holderptra;


   //   ::core::application & app = App(pmainframe->get_app());

   //   string strAppName = app.m_strAppName;

   //   //if(get_document()->get_typed_view < ::bergedge::pane_view >() != NULL)
   //   //{

   //   //   get_document()->get_typed_view < ::bergedge::pane_view >()->set_cur_tab_by_id("app:" + strAppName);

   //   //   holderptra.add(get_document()->get_typed_view < ::bergedge::pane_view >()->get_tab_holder(get_document()->get_typed_view < ::bergedge::pane_view >()->get_tab_by_id("app:" + strAppName)));

   //   //}
   //   //else
   //   //{

   //   //   holderptra.add(get_document()->get_typed_view < ::bergedge::view >());

   //   //}

   //   return holderptra;

   //}

   bool session::place(::user::main_frame * pmainframe, sp(::create) pcreatecontext)
   {

      //get_place_holder(pmainframe, pcreatecontext).hold(pmainframe);

      return true;

   }

   ::count session::get_monitor_count()
   {

      if(get_document() != NULL && get_view() != NULL)
      {
         
         return 1;

      }
      else
      {

         return ::base::session::get_monitor_count();

      }

   }


   bool session::get_monitor_rect(index iMonitor, LPRECT lprect)
   {
      
      if(get_document() != NULL && get_view() != NULL)
      {
         
         get_view()->GetWindowRect(lprect);

         return true;

      }
      else
      {

         return ::base::session::get_monitor_rect(iMonitor, lprect);

      }

   }



   void session::set_app_title(const char * pszType, const char * pszAppId, const char * pszTitle)
   {

      sp(::aura::application) papp = NULL;

      if(m_pbasesession->m_mapApplication.Lookup(string(pszType) + ":" + string(pszAppId), papp) && papp.is_set())
      {

         //sp(::bergedge::pane_view) ppaneview = get_document()->get_typed_view < ::bergedge::pane_view >();

         //if(ppaneview != NULL)
         //{

         //   string strAppName(pszAppId);

         //   ::user::tab::pane * ppane = ppaneview->get_pane_by_id("app:" + strAppName);

         //   if(ppane != NULL)
         //   {

         //      ppane->m_istrTitleEx = pszTitle;

         //      ppaneview->layout();

         //   }

         //}

      }

   }



   sp(::core::session) session::get_session()
   {

      return this;

   }
   
   

   bool session::is_serviceable()
   {


//      return ::session::application::is_serviceable();
      return false;


   }


   bool session::on_uninstall()
   {


      bool bOk1 = true;
      bool bOk2 = true;

      try
      {
         bOk1 = ::core::application::on_uninstall();
      }
      catch(...)
      {
         bOk1 = false;
      }




      return bOk1 && bOk2;


   }


   bool session::os_native_bergedge_start()
   {

      return ::core::application::os_native_bergedge_start();

   }


   service_base * session::allocate_new_service()
   {


      return ::core::application::allocate_new_service();


   }


   ::visual::cursor * session::get_cursor()
   {
      
      if(m_pbasesession->m_ecursor == ::visual::cursor_none)
         return NULL;
      else if(m_pbasesession->m_ecursor == ::visual::cursor_default)
         return System.visual().get_cursor(m_pbasesession->m_ecursorDefault);
      else
         return System.visual().get_cursor(m_pbasesession->m_ecursor);

   }


   ::visual::cursor * session::get_default_cursor()
   {
      
      return System.visual().get_cursor(m_pbasesession->m_ecursorDefault);

   }


   int32_t session::main()
   {


      return ::core::application::main();


   }

   /*   ::core::filehandler::handler & system::filehandler()
   {
   return *m_spfilehandler;
   }*/



   void session::register_bergedge_application(::aura::application * papp)
   {

      retry_single_lock rsl(m_pmutex,millis(84),millis(84));

      if(papp == NULL || papp->m_pcoreapp == NULL)
         return;

      Session.m_appptra.add_unique(papp);

      if(System.is_installing() || System.is_uninstalling())
         System.m_bDoNotExitIfNoApplications = false;
      else if(!papp->is_session()
         && !papp->is_system()
         && !papp->is_serviceable())
      {

         System.m_bDoNotExitIfNoApplications = false;

      }

   }

   void session::unregister_bergedge_application(::aura::application * papp)
   {

      retry_single_lock rsl(m_pmutex,millis(84),millis(84));

      Session.m_appptra.remove(papp);

   }




   sp(::core::session) session::query_bergedge()
   {

      sp(::core::session) psession = NULL;

      if(System.m_pbergedgemap == NULL)
         return NULL;

      if(!System.m_pbergedgemap->Lookup(0,psession))
      {
         return NULL;
      }

      return psession;

   }

   void session::on_user_login(::fontopus::user * puser)
   {

      ::base::session::on_user_login(puser);


   }



} // namespace plane



