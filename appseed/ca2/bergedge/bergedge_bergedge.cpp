#include "StdAfx.h"


namespace bergedge
{


   bergedge::bergedge()
   {


      m_bDrawCursor              = true;
      m_pnaturedocument          = NULL;
      m_pplatformdocument        = NULL;
      m_pbergedgedocument        = NULL;
      m_bShowPlatform            = false;
      m_pappCurrent              = NULL;

      m_strAppName               = "bergedge";


      ::fs::set * pset = new class ::fs::set(this);
      pset->m_spafsdata.add(new ::fs::native(this));
      m_spfsdata(pset);


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

      if(!cube2::application::initialize_instance())
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
      cube1::application::load_string_table();
      cube1::application::load_string_table("platform", "");
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
         System.template type_info < document > (),
         System.template type_info < frame > (),
         System.template type_info < view > ());
      m_ptemplate_platform    = new ::userbase::single_document_template(
         this,
         "bergedge/frame",
         System.template type_info < platform::document > (),
         System.template type_info < platform::frame > (),
         System.template type_info < platform::pane_view > ());
      m_ptemplate_nature      = new ::userbase::single_document_template(
         this,
         "bergedge/frame",
         System.template type_info < nature::document > (),
         System.template type_info < nature::frame > (),
         System.template type_info < nature::view > ());
      m_pnaturedocument = NULL;
   }

   bool bergedge::create_bergedge(::ca::create_context * pcreatecontext)
   {
      if(m_pbergedgedocument == NULL)
      {

         ::ca::create_context_sp createcontextBergedge(get_app());
         createcontextBergedge.oattrib(pcreatecontext);
         createcontextBergedge->m_spCommandLine->m_varFile.set_type(var::type_empty);
         createcontextBergedge->m_bMakeVisible = false;

         m_pbergedgedocument = dynamic_cast < document * > (m_ptemplate_bergedge->open_document_file(createcontextBergedge));
         m_pbergedgedocument->m_psession = m_psession;
      
      }
      if(m_bShowPlatform)
      {
         if(m_pplatformdocument == NULL)
         {

            ::ca::create_context_sp createcontextPlatform;
            createcontextPlatform.oattrib(pcreatecontext);
            createcontextPlatform->m_spCommandLine->m_varFile.set_type(var::type_empty);
            createcontextPlatform->m_bMakeVisible = true;
            createcontextPlatform->m_puiParent = m_pbergedgedocument->get_bergedge_view();

            m_pplatformdocument  = dynamic_cast < platform::document * > (m_ptemplate_platform->open_document_file(createcontextPlatform));
            m_pplatformdocument->m_pbergedgedocument =  m_pbergedgedocument;
            //m_pnaturedocument    =
            // dynamic_cast < nature::document * > (
             //  papp->m_ptemplate_nature->open_document_file(NULL, false, m_pbergedgedocument->get_bergedge_view()));

            m_pbergedgedocument->set_platform(m_pplatformdocument);
            //m_pbergedgedocument->set_nature(m_pnaturedocument);
         }
      }
      return m_pbergedgedocument != NULL;
   }

   void bergedge::launch_app(const char * psz)
   {
      UNREFERENCED_PARAMETER(psz);
   }

   void bergedge::install_app(const char * psz)
   {
      UNREFERENCED_PARAMETER(psz);
   }

   void bergedge::on_request(::ca::create_context * pcreatecontext)
   {

      m_varCurrentViewFile = pcreatecontext->m_spCommandLine->m_varFile;


      string strApp;

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
         }
         else if(m_bShowPlatform)
         {
            create_bergedge(pcreatecontext);
            if(get_document() != NULL && get_document()->get_typed_view < ::bergedge::view >() != NULL)
            {
               ::simple_frame_window * pframe = dynamic_cast < ::simple_frame_window * > (get_document()->get_typed_view < ::bergedge::view >()->GetParentFrame());
               if(pframe != NULL)
               {
                  pframe->ShowWindow(SW_SHOW);
                  pframe->InitialFramePosition();
               }
            }
         }
         bCreate = false;
      }
      if(bCreate)
      {
         if(pcreatecontext->m_spCommandLine->m_strApp == "bergedge")
         {
            if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("session_start"))
            {
               strApp = pcreatecontext->m_spCommandLine->m_varQuery["session_start"];
            }
            else
            {
               strApp = "bergedge";
            }
         }
         else
         {
            strApp = pcreatecontext->m_spCommandLine->m_strApp;
         }

         if(strApp.is_empty() || strApp == "bergedge")
         {
            return;
         }

         ::ca2::application * papp = dynamic_cast < ::ca2::application * > (application_get(strApp, true, true, pcreatecontext->m_spCommandLine->m_pbiasCreate));
         if(papp == NULL)
            return;

         if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("install")
         || pcreatecontext->m_spCommandLine->m_varQuery.has_property("uninstall"))
         {
            return;
         }

         pcreatecontext->m_spCommandLine->m_eventReady.ResetEvent();

         if(strApp != "bergedge")
         {


            DWORD dw = WM_APP + 2043;

            papp->PostThreadMessage(dw, 2, (LPARAM) (::ca::create_context *) pcreatecontext);

            pcreatecontext->m_spCommandLine->m_eventReady.wait();


         }

         m_pappCurrent = papp;

      }



      
      if(m_bShowPlatform)
      {
         ::simple_frame_window * pframeApp = dynamic_cast < ::simple_frame_window * > (get_document()->get_typed_view < ::bergedge::pane_view >()->get_view_uie());
         if(pframeApp != NULL)
         {
            pframeApp->WfiFullScreen(true, false);
         }
         ::simple_frame_window * pframe = dynamic_cast < ::simple_frame_window * > (get_document()->get_typed_view < ::bergedge::pane_view >()->GetParentFrame());
         if(pframe != NULL)
         {
            pframe->ShowWindow(SW_SHOW);
         }
      }
      else
      {
         if(get_document() != NULL && get_document()->get_typed_view < ::bergedge::view >() != NULL)
         {
            ::simple_frame_window * pframe = dynamic_cast < ::simple_frame_window * > (get_document()->get_typed_view < ::bergedge::view >()->GetParentFrame());
            if(pframe != NULL)
            {
               pframe->ShowWindow(SW_SHOW);
               if(pframe->GetTypedParent < ::plugin::host_interaction > () != NULL)
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

      if(m_pappCurrent != NULL && dynamic_cast < ::fontopus::application * > (m_pappCurrent)->m_puser != NULL)
      {
         try
         {
            get_view()->GetParentFrame()->SetWindowTextA(dynamic_cast < ::fontopus::application * > (m_pappCurrent)->m_puser->m_strLogin);
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
      if(get_document() == NULL)
         return NULL;
      return get_document()->get_bergedge_view();
   }

   ::platform::document * bergedge::get_platform()
   {
      return m_pplatformdocument;
   }

   ::nature::document * bergedge::get_nature()
   {
      return m_pnaturedocument;
   }

   bool bergedge::open_by_file_extension(const char * pszPathName, ::ca::application_bias * pbiasCreate)
   {
      
      ::ca::create_context_sp cc(get_app());

      cc->m_spCommandLine->m_varFile = pszPathName;

      if(pbiasCreate != NULL)
      {
         cc->m_spApplicationBias->operator=(*pbiasCreate);
      }

      return open_by_file_extension(cc);

   }

   bool bergedge::open_by_file_extension(::ca::create_context * pcreatecontext)
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

         Cube.filehandler().get_extension_app(straApp, strExtension);
     

         if(straApp.get_count() == 1)
         {
            strId = straApp[0];
         }
         else
         {
            strId = "default_file_handler";
         }

      }


      /*|| gen::str::ends_ci(strPathName, ".cpp")
      || gen::str::ends_ci(strPathName, ".html"))
      {
         strId = "devedge";
      }
      else if(gen::str::ends_ci(strPathName, ".ca2"))
      {
         strId = Application.file().as_string(strOriginalPathName);
         if(gen::str::begins_eat(strId, "ca2prompt\r\n"))
         {
            strId.trim();
         }
         return false;
      }
      else if(gen::str::ends_ci(strPathName, ".txt")
      || gen::str::ends_ci(strOriginalPathName, ".pac"))
      {
         strId = "veriedit";
      }
      else if(gen::str::ends_ci(strPathName, ".ogv")
         || gen::str::ends_ci(strPathName, ".flv"))
      {
         strId = "verisimplevideo";
      }
      else if(gen::str::ends_ci(strPathName, ".kar")
      || gen::str::ends_ci(strPathName, ".mid")
      || gen::str::ends_ci(strPathName, ".mp3")
      || gen::str::ends_ci(strPathName, ".mk1"))
      {
         strId = "mplite";
      }
      else if(gen::str::ends_ci(strPathName, ".flv"))
      {
         strId = "verisimplevideo";
      }
      else if(gen::str::ends_ci(strPathName, ".bmp")
           || gen::str::ends_ci(strPathName, ".jpg")
           || gen::str::ends_ci(strPathName, ".jpeg")
           || gen::str::ends_ci(strPathName, ".png")
           || gen::str::ends_ci(strPathName, ".gif"))
      {
         strId = "eluce";
      }
      else if(gen::str::begins(strPathName, "rtprx://"))
      {
         strId = "rtprx";
      }
      else if(gen::str::begins(strPathName, "rtptx://"))
      {
         strId = "rtptx";
      }
      else
      {
#ifdef WINDOWS
         ::ShellExecuteW(
            NULL,
            L"open",
            gen::international::utf8_to_unicode(strPathName),
            NULL,
            NULL,
            SW_SHOW);
#endif
         return true;
      }*/
      ::user::application * papp = dynamic_cast < ::user::application * > (application_get(strId, true, true, pcreatecontext->m_spApplicationBias));
      if(papp == NULL)
         return false;
      papp->::ex1::request_interface::create(pcreatecontext);
      return true;
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

   void bergedge::on_exclusive_instance_conflict(::radix::EExclusiveInstance eexclusive)
   {
      if(eexclusive == ::radix::ExclusiveInstanceLocalId)
      {
         gen::memory_file file(get_app());
         file.from_string(command().m_varTopicFile);
         COPYDATASTRUCT data;
         data.dwData = 1984;
         data.cbData = (DWORD) file.get_length();
         data.lpData = file.get_data();
         HWND hwnd = (HWND) ::FindWindowA(NULL, "ca2::fontopus::message_wnd::bergedge::");

         ::SendMessage(hwnd, WM_COPYDATA, NULL, (LPARAM) &data);
      }
   }


   void bergedge::request(::ca::create_context * pcreatecontext)
   {
      
      if(m_pappCurrent != NULL && m_pappCurrent != this 
         && (pcreatecontext->m_spCommandLine->m_strApp.is_empty() 
         ||App(m_pappCurrent).m_strAppName == pcreatecontext->m_spCommandLine->m_strApp))
      {
         if(get_document() != NULL && get_document()->get_typed_view < ::bergedge::pane_view >() != NULL)
         {
            get_document()->get_typed_view < ::bergedge::pane_view >()->set_cur_tab_by_id("app:" + App(m_pappCurrent).m_strAppName);
         }
         App(m_pappCurrent).request(pcreatecontext);
      }
      else if(pcreatecontext->m_spCommandLine->m_varFile.get_type() == var::type_string)
      {
         if(gen::str::ends_ci(pcreatecontext->m_spCommandLine->m_varFile, ".ca2"))
         {
            string strCommand = Application.file().as_string(pcreatecontext->m_spCommandLine->m_varFile);
            if(gen::str::begins_eat(strCommand, "ca2prompt\r")
            || gen::str::begins_eat(strCommand, "ca2prompt\n"))
            {
               strCommand.trim();
               command().add_fork_uri(strCommand);
            }
            return;
         }
         else
         {
            on_request(pcreatecontext);
         }
      }
      else if(pcreatecontext->m_spCommandLine->m_strApp.has_char() &&
         get_document() != NULL && get_document()->get_typed_view < ::bergedge::pane_view >() != NULL
         && (!pcreatecontext->m_spApplicationBias.is_set() || pcreatecontext->m_spApplicationBias->m_puiParent == NULL))
      {
         get_document()->get_typed_view < ::bergedge::pane_view >()->set_cur_tab_by_id("app:" + pcreatecontext->m_spCommandLine->m_strApp);
         App(m_pappCurrent).request(pcreatecontext);
      }
      else
      {
         on_request(pcreatecontext);
      }
   }

   void bergedge::request_topic_file(var & varQuery)
   {
      request(m_varTopicFile, varQuery);
   }

   void bergedge::request_topic_file()
   {
      request(m_varTopicFile);
   }

   /*void bergedge::request_application(const char * pszId, var varFile, var varQuery, ::ca::application_bias * pbiasCreate)
   {

      ::ca2::application_request request;

      request.m_iEdge         = m_iEdge;
      request.m_strApp        = pszId;
      request.m_varFile       = varFile;
      request.m_varQuery      = varQuery;
      request.m_pbiasCreate   = pbiasCreate;

      request_application(&request);

   }*/

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
         Session.m_mapApplication.set_at(pszId, papp);
         return papp;
      }
   }

   bool bergedge::is_bergedge()
   {
      return true;
   }

   ::ca::application * bergedge::get_current_application()
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

   ::user::interaction * bergedge::get_request_parent_ui(::userbase::main_frame * pmainframe, ::ca::create_context * pcreatecontext)
   {

      return get_request_parent_ui((::user::interaction * ) pmainframe, pcreatecontext);

   }

   ::user::interaction * bergedge::get_request_parent_ui(::user::interaction * pinteraction, ::ca::create_context * pcreatecontext)
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

      if(!create_bergedge(pcreatecontext))
      {
         return NULL;
      }




      cube8::application & app = App(pinteraction->get_app());

      string strAppName = app.m_strAppName;

      if(strAppName != "bergedge")
      {

         if(get_document() != NULL)
         {

            if(get_document()->get_typed_view < ::bergedge::pane_view >() != NULL)
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

   ::user::place_holder_ptra bergedge::get_place_holder(::userbase::main_frame * pmainframe, ::ca::create_context * pcreatecontext)
   {

      UNREFERENCED_PARAMETER(pcreatecontext);

      ::user::place_holder_ptra holderptra;


      cube8::application & app = App(pmainframe->get_app());

      string strAppName = app.m_strAppName;

      if(get_document()->get_typed_view < ::bergedge::pane_view >() != NULL)
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

   bool bergedge::place(::userbase::main_frame * pmainframe, ::ca::create_context * pcreatecontext)
   {

      get_place_holder(pmainframe, pcreatecontext).hold(pmainframe);

      return true;

   }

   void bergedge::get_screen_rect(LPRECT lprect)
   {
      if(get_document() != NULL && get_view() != NULL)
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

      win::registry::Key keyKar(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", true);
      keyKar.SetValue("ca2 app-sentinel", "\"" + strSentinelPath + "\"");

      return platform::application::on_install();
   }


   void bergedge::set_app_title(const char * pszAppId, const char * pszTitle)
   {

      ::ca::application * papp = NULL;

      if(m_mapApplication.Lookup(pszAppId, papp) && papp != NULL)
      {

         ::bergedge::pane_view * ppaneview = get_document()->get_typed_view < ::bergedge::pane_view >();

         if(ppaneview != NULL)
         {
         
            string strAppName(pszAppId);

            ::user::tab::pane * ppane = ppaneview->get_pane_by_id("app:" + strAppName);

            if(ppane != NULL)
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

   int bergedge::main()
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



