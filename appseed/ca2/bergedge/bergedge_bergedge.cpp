#include "framework.h"


namespace bergedge
{


   bergedge::bergedge()
   {


      m_bDrawCursor              = true;
      m_pnaturedocument          = ::null();
      m_pplatformdocument        = ::null();
      m_pbergedgedocument        = ::null();
      m_bShowPlatform            = false;
      m_pappCurrent              = ::null();
      m_bLicense				= false;

      m_strAppName               = "bergedge";


   }

   bergedge::~bergedge()
   {

      POSITION pos = m_mapApplication.get_start_position();

      if(m_pnaturedocument != ::null())
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

      string strId;
      sp(::ca::application) pcaapp;

      while(pos != ::null())
      {

         strId.Empty();
         pcaapp = ::null();

         m_mapApplication.get_next_assoc(pos, strId, pcaapp);

         sp(::ca::application) papp = (pcaapp);

         papp->post_thread_message(WM_QUIT, 0, 0);
      }

   }

   void bergedge::construct()
   {

      m_strAppName         = "bergedge";
      m_strBaseSupportId   = "ca2_bergedge";
      m_strInstallToken    = "bergedge";
      m_bLicense           = false;
      m_eexclusiveinstance = ::ca::ExclusiveInstanceNone;

   }

   bool bergedge::initialize_instance()
   {

      if(!cube::application::initialize_instance())
         return false;

      initialize_bergedge_application_interface();


      filemanager().std().m_strLevelUp = "levelup";


      //SetRegistryKey("ca2core");


      if(!InitializeLocalDataCentral())
      {
         simple_message_box(::null(), "Could not initialize Local data central");
         return false;
      }

      if(Session.is_remote_session())
      {
         /*Session.savings().save(::ca::resource_display_bandwidth);
         Session.savings().save(::ca::resource_blur_background);
         Session.savings().save(::ca::resource_blurred_text_embossing);
         Session.savings().save(::ca::resource_translucent_background);*/
      }

      /*      if(System.directrix()->m_varTopicQuery.has_property("install")
      || System.directrix()->m_varTopicQuery.has_property("uninstall"))
      {
      find_uinteractions_to_cache(m_mapUInteractionToLibrary);
      }
      else
      {
      find_uinteractions_from_cache(m_mapUInteractionToLibrary);
      }*/


      return true;


   }

   int32_t bergedge::exit_instance()
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
      m_pdocmanager->_001OnFileNew();
   }


   bool bergedge::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)

   {
      return ::ca::application::_001OnCmdMsg(pcmdmsg);
   }

   sp(::ca::application) bergedge::get_app() const
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
      
      cube::application::load_string_table();
      cube::application::load_string_table("platform", "");

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
      int32_t iCount = 32; // todo: get from bergedge profile
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
         System.type_info < document > (),
         System.type_info < frame > (),
         System.type_info < view > ());
      m_ptemplate_platform    = new ::userbase::single_document_template(
         this,
         "bergedge/frame",
         System.type_info < platform::document > (),
         System.type_info < platform::frame > (),
         System.type_info < platform::pane_view > ());
      m_ptemplate_nature      = new ::userbase::single_document_template(
         this,
         "bergedge/frame",
         System.type_info < nature::document > (),
         System.type_info < nature::frame > (),
         System.type_info < nature::view > ());
      m_pnaturedocument = ::null();
   }

   bool bergedge::create_bergedge(sp(::ca::create_context) pcreatecontext)
   {

      m_psession->m_pbergedge = this;
      m_psession->m_pbergedgeInterface = this;


      if(m_pbergedgedocument == ::null())
      {

         sp(::ca::create_context) createcontextBergedge(allocer());
         createcontextBergedge.oattrib(pcreatecontext);
         createcontextBergedge->m_spCommandLine->m_varFile.set_type(var::type_empty);
         createcontextBergedge->m_bMakeVisible = false;

         m_pbergedgedocument =  (m_ptemplate_bergedge->open_document_file(createcontextBergedge).m_p);
         m_pbergedgedocument->m_papp->m_psession = m_psession;

      }
      if(m_bShowPlatform)
      {
         if(m_pplatformdocument == ::null())
         {

            sp(::ca::create_context) createcontextPlatform;
            createcontextPlatform.oattrib(pcreatecontext);
            createcontextPlatform->m_spCommandLine->m_varFile.set_type(var::type_empty);
            createcontextPlatform->m_bMakeVisible = true;
            createcontextPlatform->m_puiParent = m_pbergedgedocument->get_bergedge_view();

            m_pplatformdocument  =  (m_ptemplate_platform->open_document_file(createcontextPlatform).m_p);
            m_pplatformdocument->m_pbergedgedocument =  m_pbergedgedocument;
            //m_pnaturedocument    =
            // dynamic_cast < sp(::nature::document) > (
            //  papp->m_ptemplate_nature->open_document_file(::null(), false, m_pbergedgedocument->get_bergedge_view()));

            m_pbergedgedocument->set_platform(m_pplatformdocument);
            //m_pbergedgedocument->set_nature(m_pnaturedocument);
         }
      }
      return m_pbergedgedocument != ::null();
   }

   void bergedge::launch_app(const char * psz)
   {
      UNREFERENCED_PARAMETER(psz);
   }

   void bergedge::install_app(const char * psz)
   {
      UNREFERENCED_PARAMETER(psz);
   }

   void bergedge::on_request(sp(::ca::create_context) pcreatecontext)
   {


      m_varCurrentViewFile = pcreatecontext->m_spCommandLine->m_varFile;


      string strApp;
      string strType;

      if((pcreatecontext->m_spCommandLine->m_varQuery["app"].array_get_count() > 1
         || pcreatecontext->m_spCommandLine->m_varQuery["show_platform"] == 1 || command()->m_varTopicQuery["show_platform"] == 1)
         && (!(bool)pcreatecontext->m_spCommandLine->m_varQuery["client_only"] && !(bool)command()->m_varTopicQuery["client_only"])
         && (!pcreatecontext->m_spCommandLine->m_varQuery.has_property("client_only") && !command()->m_varTopicQuery.has_property("client_only")))
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
                  App(m_pappCurrent).request_command(pcreatecontext->m_spCommandLine);
               }
            }
         }
         else if(m_bShowPlatform)
         {
            create_bergedge(pcreatecontext);
            if(get_document() != ::null() && get_document()->get_typed_view < ::bergedge::view >() != ::null())
            {
               sp(::simple_frame_window) pframe =  (get_document()->get_typed_view < ::bergedge::view >()->GetParentFrame());
               if(pframe != ::null())
               {
                  pframe->ShowWindow(SW_SHOW);
                  pframe->InitialFramePosition();
               }
            }
         }
         if(pcreatecontext->m_spCommandLine->m_varQuery["app"].array_get_count() <= 0)
         {
            bCreate = false;
         }
      }
      if(bCreate)
      {
         if(pcreatecontext->m_spCommandLine->m_strApp == "bergedge")
         {
            if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("session_start"))
            {
               strApp = pcreatecontext->m_spCommandLine->m_varQuery["session_start"];
               strApp = pcreatecontext->m_spCommandLine->m_varQuery["app_type"];
            }
            else
            {
               strApp = "bergedge";
               strType = "application";
            }
         }
         else
         {
            strApp = pcreatecontext->m_spCommandLine->m_strApp;
            strType = pcreatecontext->m_spCommandLine->m_strAppType;
         }

         if(pcreatecontext->m_spCommandLine->m_varQuery["app"].stra().get_count() <= 0)
         {

            pcreatecontext->m_spCommandLine->m_varQuery["app"].stra().add(strApp);

         }

         for(int32_t i = 0; i < pcreatecontext->m_spCommandLine->m_varQuery["app"].stra().get_count(); i++)
         {

            strApp = pcreatecontext->m_spCommandLine->m_varQuery["app"].stra()[i];


            //MessageBox(::null(), "create", strApp, MB_ICONEXCLAMATION);

            if(strApp.is_empty() || strApp == "bergedge")
            {
               return;
            }

            if(strType.is_empty())
               strType = "application";

            sp(::ca::application) papp = (application_get(strType, strApp, true, true, pcreatecontext->m_spCommandLine->m_pbiasCreate));
            if(papp == ::null())
               return;

            //MessageBox(::null(), "appok", strApp, MB_ICONEXCLAMATION);

            if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("install")
               || pcreatecontext->m_spCommandLine->m_varQuery.has_property("uninstall"))
            {
               continue;
            }

            pcreatecontext->m_spCommandLine->m_eventReady.ResetEvent();

            if(strApp != "bergedge")
            {


               uint32_t dw = WM_APP + 2043;

               pcreatecontext->m_spCommandLine->m_varQuery["bergedge_callback"] = (bergedge_interface * ) this;

               papp->post_thread_message(dw, 2, pcreatecontext);

               m_pappCurrent = papp;

               Session.m_pappCurrent = papp;

               //pcreatecontext->m_spCommandLine->m_eventReady.wait();


            }

         }

      }





   }


   void bergedge::on_app_request_bergedge_callback(sp(::ca::application) papp)
   {
      if(&App(papp) != ::null())
      {
             
         m_pappCurrent = papp;

      }

      if(m_bShowPlatform)
      {
         sp(::simple_frame_window) pframeApp =  (get_document()->get_typed_view < ::bergedge::pane_view >()->get_view_uie().m_p);
         if(pframeApp != ::null())
         {
            pframeApp->WfiFullScreen(true, false);
         }
         sp(::simple_frame_window) pframe =  (get_document()->get_typed_view < ::bergedge::pane_view >()->GetParentFrame());
         if(pframe != ::null())
         {
            pframe->ShowWindow(SW_SHOW);
         }
      }
      else
      {
         if(get_document() != ::null() && get_document()->get_typed_view < ::bergedge::view >() != ::null())
         {
            sp(::simple_frame_window) pframe =  (get_document()->get_typed_view < ::bergedge::view >()->GetParentFrame());
            if(pframe != ::null())
            {
               pframe->ShowWindow(SW_SHOW);
               if(pframe->GetTypedParent < ::plugin::host_interaction > () != ::null())
               {
                  pframe->GetTypedParent < ::plugin::host_interaction > ()->layout();
               }
               else
               {
                  pframe->InitialFramePosition();
               }
            }
         }
      }

      if(m_pappCurrent != ::null() && m_pappCurrent->m_pappThis->fontopus()->m_puser != ::null())
      {
         try
         {
            get_view()->GetParentFrame()->SetWindowText(m_pappCurrent->m_pappThis->fontopus()->m_puser->m_strLogin);
         }
         catch(...)
         {
         }
      }

   }


   ::bergedge::document * bergedge::get_document()
   {
      return m_pbergedgedocument;
   }

   ::bergedge::view * bergedge::get_view()
   {
      if(get_document() == ::null())
         return ::null();
      return get_document()->get_bergedge_view();
   }

   sp(::platform::document) bergedge::get_platform()
   {
      return m_pplatformdocument;
   }

   sp(::nature::document) bergedge::get_nature()
   {
      return m_pnaturedocument;
   }


   bool bergedge::InitializeLocalDataCentral()
   {

      m_pdatabase = new nature::database(this);

      if(m_pdatabase == ::null())
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

   void bergedge::on_exclusive_instance_conflict(::ca::EExclusiveInstance eexclusive)
   {
      if(eexclusive == ::ca::ExclusiveInstanceLocalId)
      {
#ifdef WINDOWSEX
         ::primitive::memory_file file(get_app());
         file.from_string(command()->m_varTopicFile);
         COPYDATASTRUCT data;
         data.dwData = 1984;
         data.cbData = (uint32_t) file.get_length();
         data.lpData = file.get_data();
         ::oswindow oswindow = ::FindWindowA(::null(), "::ca::fontopus::message_wnd::bergedge::");


         ::SendMessage(oswindow, WM_COPYDATA, 0, (LPARAM) &data);

#else

         throw todo(get_app());

#endif

      }
   }


   void bergedge::request_create(sp(::ca::create_context) pcreatecontext)
   {

      if(m_pappCurrent != ::null() && m_pappCurrent != this
         && (pcreatecontext->m_spCommandLine->m_strApp.is_empty()
         ||App(m_pappCurrent).m_strAppName == pcreatecontext->m_spCommandLine->m_strApp))
      {
         if(get_document() != ::null() && get_document()->get_typed_view < ::bergedge::pane_view >() != ::null())
         {
            get_document()->get_typed_view < ::bergedge::pane_view >()->set_cur_tab_by_id("app:" + App(m_pappCurrent).m_strAppName);
         }
         App(m_pappCurrent).request_create(pcreatecontext);
         if(pcreatecontext->m_spCommandLine->m_varQuery["document"].ca < ::user::document_interface > () == ::null())
         {
            goto alt1;
         }

      }
      else
      {
alt1:
         if(pcreatecontext->m_spCommandLine->m_varFile.get_type() == var::type_string)
         {
            if(::ca::str::ends_ci(pcreatecontext->m_spCommandLine->m_varFile, ".ca"))
            {
               string strCommand = Application.file().as_string(pcreatecontext->m_spCommandLine->m_varFile);
               if(::ca::str::begins_eat(strCommand, "ca2prompt\r")
                  || ::ca::str::begins_eat(strCommand, "ca2prompt\n"))
               {
                  strCommand.trim();
                  command()->add_fork_uri(strCommand);
               }
               return;
            }
            else if(pcreatecontext->m_spCommandLine->m_strApp.has_char() 
               && get_document() != ::null() 
               && get_document()->get_typed_view < ::bergedge::pane_view >() != ::null())
            {
               get_document()->get_typed_view < ::bergedge::pane_view >()->set_cur_tab_by_id("app:" + pcreatecontext->m_spCommandLine->m_strApp);
               App(m_pappCurrent).request_create(pcreatecontext);
            }
            else
            {
               on_request(pcreatecontext);
            }
         }
         else if(pcreatecontext->m_spCommandLine->m_strApp.has_char() &&
            get_document() != ::null() && get_document()->get_typed_view < ::bergedge::pane_view >() != ::null()
            && (!pcreatecontext->m_spApplicationBias.is_set() || pcreatecontext->m_spApplicationBias->m_puiParent == ::null()))
         {
            //MessageBox(::null(), "request3", "request3", MB_ICONEXCLAMATION);
            get_document()->get_typed_view < ::bergedge::pane_view >()->set_cur_tab_by_id("app:" + pcreatecontext->m_spCommandLine->m_strApp);
            App(m_pappCurrent).request_create(pcreatecontext);
         }
         else
         {
            //MessageBox(::null(), "request4", "request4", MB_ICONEXCLAMATION);
            on_request(pcreatecontext);
         }
      }
   }

   void bergedge::request_topic_file(var & varQuery)
   {
      request_file_query(m_varTopicFile, varQuery);
   }

   void bergedge::request_topic_file()
   {
      request_file(m_varTopicFile);
   }

   /*void bergedge::request_application(const char * pszId, var varFile, var varQuery, ::ca::application_bias * pbiasCreate)
   {

   ::ca::application_request request;

   request.m_iEdge         = m_iEdge;
   request.m_strApp        = pszId;
   request.m_varFile       = varFile;
   request.m_varQuery      = varQuery;
   request.m_pbiasCreate   = pbiasCreate;

   request_application(&request);

   }*/

   sp(::ca::application) bergedge::application_get(const char * pszType, const char * pszId, bool bCreate, bool bSynch, ::ca::application_bias * pbiasCreate)
   {
      sp(::ca::application) papp = ::null();

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

            if(!App(this).on_run_exception(e))
               throw exit_exception(get_app());

         }
         catch(...)
         {
            papp = ::null();
         }
         if(papp == ::null())
            return ::null();
         if(&App(papp) == ::null())
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
         m_mapApplication.set_at(string(pszType) + ":" + string(pszId), papp);
         Session.m_mapApplication.set_at(string(pszType) + ":" + string(pszId), papp);
         return papp;
      }
   }

   bool bergedge::is_bergedge()
   {
      return true;
   }

   sp(::ca::application) bergedge::get_current_application()
   {
      return m_pappCurrent;
   }


   void bergedge::check_topic_file_change()
   {
      if(m_varCurrentViewFile != m_varTopicFile && !m_varTopicFile.is_empty())
      {
         m_varCurrentViewFile = m_varTopicFile;
         request_topic_file();
      }
   }

   sp(::user::interaction) bergedge::get_request_parent_ui(sp(::user::interaction) pinteraction, sp(::ca::create_context) pcreatecontext)
   {


      sp(::user::interaction) puiParent = ::null();

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
         Application.directrix()->m_varTopicQuery["client_only"] != 0 ||
         pcreatecontext->m_bOuterPopupAlertLike)
      {
         return puiParent;
      }

      if(!create_bergedge(pcreatecontext))
      {
         return ::null();
      }




      cube::application & app = App(pinteraction->get_app());

      string strAppName = app.m_strAppName;

      if(strAppName != "bergedge")
      {

         if(get_document() != ::null())
         {

            if(get_document()->get_typed_view < ::bergedge::pane_view >() != ::null())
            {

               get_document()->get_typed_view < ::bergedge::pane_view >()->set_cur_tab_by_id("app:" + strAppName);

               puiParent = get_document()->get_typed_view < ::bergedge::pane_view >()->get_tab_holder(get_document()->get_typed_view < ::bergedge::pane_view >()->get_tab_by_id("app:" + strAppName));

            }
            else
            {

               puiParent = get_document()->get_typed_view < ::bergedge::view >();

            }

         }

      }

      return puiParent;

   }

   ::user::place_holder_ptra bergedge::get_place_holder(sp(::frame_window) pmainframe, sp(::ca::create_context) pcreatecontext)
   {

      UNREFERENCED_PARAMETER(pcreatecontext);

      ::user::place_holder_ptra holderptra;


      cube::application & app = App(pmainframe->get_app());

      string strAppName = app.m_strAppName;

      if(get_document()->get_typed_view < ::bergedge::pane_view >() != ::null())
      {

         get_document()->get_typed_view < ::bergedge::pane_view >()->set_cur_tab_by_id("app:" + strAppName);

         holderptra.add(get_document()->get_typed_view < ::bergedge::pane_view >()->get_tab_holder(get_document()->get_typed_view < ::bergedge::pane_view >()->get_tab_by_id("app:" + strAppName)));

      }
      else
      {

         holderptra.add(get_document()->get_typed_view < ::bergedge::view >());

      }

      return holderptra;

   }

   bool bergedge::place(sp(::userbase::main_frame) pmainframe, sp(::ca::create_context) pcreatecontext)
   {

      get_place_holder(pmainframe, pcreatecontext).hold(pmainframe);

      return true;

   }

   void bergedge::get_screen_rect(LPRECT lprect)
   {
      if(get_document() != ::null() && get_view() != ::null())
      {
         get_view()->GetWindowRect(lprect);
      }
      else
      {
         System.get_screen_rect(lprect);
      }
   }

   bool bergedge::on_install()
   {

      string strFormat;

      string strSentinelPath;

      strSentinelPath = System.dir().ca2("stage/x86/app-sentinel.exe");

      System.os().local_machine_set_run("ca app-sentinel", "\"" + strSentinelPath + "\"");

      return platform::application::on_install();
   }


   void bergedge::set_app_title(const char * pszType, const char * pszAppId, const char * pszTitle)
   {

      sp(::ca::application) papp = ::null();

      if(m_mapApplication.Lookup(string(pszType) + ":" + string(pszAppId), papp) && papp != ::null())
      {

         sp(::bergedge::pane_view) ppaneview = get_document()->get_typed_view < ::bergedge::pane_view >();

         if(ppaneview != ::null())
         {

            string strAppName(pszAppId);

            ::user::tab::pane * ppane = ppaneview->get_pane_by_id("app:" + strAppName);

            if(ppane != ::null())
            {

               ppane->m_istrTitleEx = pszTitle;

               ppaneview->layout();

            }

         }

      }

   }


   bool bergedge::initialize1()
   {


      if(!::platform::application::initialize1())
         return false;


      return true;


   }

   bool bergedge::initialize()
   {

      if(!::platform::application::initialize())
         return false;


      return true;


   }

   bool bergedge::os_native_bergedge_start()
   {

      return ::platform::application::os_native_bergedge_start();

   }

   int32_t bergedge::main()
   {


      return ::platform::application::main();


   }

   bool bergedge::on_uninstall()
   {


      bool bOk1 = false;
      bool bOk2 = false;

      try
      {
         bOk1 = ::platform::application::on_uninstall();
      }
      catch(...)
      {
         bOk1 = false;
      }


      try
      {
         bOk2 = ::platform::application::on_uninstall();
      }
      catch(...)
      {
         bOk2 = false;
      }


      return bOk1 && bOk2;


   }

   bool bergedge::is_serviceable()
   {


      return ::platform::application::is_serviceable();


   }

   service_base * bergedge::allocate_new_service()
   {


      return ::platform::application::allocate_new_service();


   }


   ::bergedge::bergedge * bergedge::get_bergedge()
   {

      return this;

   }



} // namespace bergedge




