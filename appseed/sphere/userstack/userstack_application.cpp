#include "framework.h"


namespace userstack
{


   application::application()
   {


      m_bDrawCursor              = true;
      m_bShowPlatform            = false;
      m_pappCurrent              = ::null();
      m_bLicense				      = false;

      m_strAppName               = "userstack";

   }

   application::~application()
   {



   }

   void application::construct()
   {

      m_strAppName         = "userstack";
      m_strBaseSupportId   = "ca2_userstack";
      m_strInstallToken    = "userstack";
      m_bLicense           = false;
      m_eexclusiveinstance = ::ca::ExclusiveInstanceNone;

   }

   bool application::initialize_instance()
   {

      if(!::asphere::application::initialize_instance())
         return false;

      initialize_bergedge_application_interface();


      filemanager().std().m_strLevelUp = "levelup";


      SetRegistryKey("ca2core");


      return true;


   }

   int32_t application::exit_instance()
   {
      try
      {
         ::asphere::application::exit_instance();
      }
      catch(...)
      {
      }

      string strId;
      sp(::ca::application) pcaapp;

      POSITION pos = m_mapApplication.get_start_position();

      while(pos != ::null())
      {

         strId.Empty();
         pcaapp = ::null();

         m_mapApplication.get_next_assoc(pos, strId, pcaapp);

         sp(::ca::application) papp = dynamic_cast < sp(::ca::application) > (pcaapp);

         papp->post_thread_message(WM_QUIT, 0, 0);
      }

      return 0;

   }

   bool application::bergedge_start()
   {
      return true;
   }



   void application::_001OnFileNew()
   {

      m_pdocmanager->_001OnFileNew();

   }


   bool application::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)

   {
      return ::ca::application::_001OnCmdMsg(pcmdmsg);
   }

   sp(::ca::application) application::get_app() const
   {
      return ::asphere::application::get_app();
   }

   void application::OnFileManagerOpenFile(
         ::filemanager::data * pdata,
         ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
   }

   void application::load_string_table()
   {
      ::asphere::application::load_string_table();
      ::asphere::application::load_string_table("platform", "");
   }

   bool application::file_manager_open_file(
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


   void application::initialize_bergedge_application_interface()
   {

      int32_t iCount = 32; // todo: get from bergedge profile

      System.factory().creatable < ::userstack::document > (iCount);
      System.factory().creatable < ::userstack::view > (iCount);
      System.factory().creatable < ::userstack::pane_view > (iCount);
      System.factory().creatable < ::userstack::frame > (iCount);

      m_ptemplate_pane    = new ::userbase::single_document_template(
         this,
         "bergedge/frame",
         System.type_info < document > (),
         System.type_info < frame > (),
         System.type_info < pane_view > ());

   }


   void application::launch_app(const char * psz)
   {
      UNREFERENCED_PARAMETER(psz);
   }

   void application::install_app(const char * psz)
   {
      UNREFERENCED_PARAMETER(psz);
   }

   void application::on_request(sp(::ca::create_context) pcreatecontext)
   {


      m_ptemplate_pane->open_document_file(pcreatecontext);

   }


   void application::on_exclusive_instance_conflict(::ca::EExclusiveInstance eexclusive)
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
         ::oswindow oswindow = ::FindWindowA(::null(), "::ca::fontopus::message_wnd::application::");

         ::SendMessage(oswindow, WM_COPYDATA, ::null(), (LPARAM) &data);
#else
         throw todo(get_app());
#endif
      }
   }


/*   void application::request(sp(::ca::create_context) pcreatecontext)
   {

      if(m_pappCurrent != ::null() && m_pappCurrent != this
         && (pcreatecontext->m_spCommandLine->m_strApp.is_empty()
         ||App(m_pappCurrent).m_strAppName == pcreatecontext->m_spCommandLine->m_strApp))
      {
         if(get_document() != ::null() && get_document()->get_typed_view < pane_view >() != ::null())
         {
            get_document()->get_typed_view < pane_view >()->set_cur_tab_by_id("app:" + App(m_pappCurrent).m_strAppName);
         }
         App(m_pappCurrent).request(pcreatecontext);
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
            else
            {
               on_request(pcreatecontext);
            }
         }
         else if(pcreatecontext->m_spCommandLine->m_strApp.has_char() &&
            get_document() != ::null() && get_document()->get_typed_view < pane_view >() != ::null()
            && (!pcreatecontext->m_spApplicationBias.is_set() || pcreatecontext->m_spApplicationBias->m_puiParent == ::null()))
         {
            //MessageBox(::null(), "request3", "request3", MB_ICONEXCLAMATION);
            get_document()->get_typed_view < pane_view >()->set_cur_tab_by_id("app:" + pcreatecontext->m_spCommandLine->m_strApp);
            App(m_pappCurrent).request(pcreatecontext);
         }
         else
         {
            //MessageBox(::null(), "request4", "request4", MB_ICONEXCLAMATION);
            on_request(pcreatecontext);
         }
      }
   }*/

   void application::request_topic_file(var & varQuery)
   {
   }

   void application::request_topic_file()
   {
   }


   sp(::ca::application) application::application_get(const char * pszType, const char * pszId, bool bCreate, bool bSynch, ::ca::application_bias * pbiasCreate)
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

   sp(::ca::application) application::get_current_application()
   {
      return m_pappCurrent;
   }


   void application::check_topic_file_change()
   {
      if(m_varCurrentViewFile != m_varTopicFile && !m_varTopicFile.is_empty())
      {
         m_varCurrentViewFile = m_varTopicFile;
         request_topic_file();
      }
   }

/*   sp(::user::interaction) application::get_request_parent_ui(sp(::userbase::main_frame) pmainframe, sp(::ca::create_context) pcreatecontext)
   {

      return get_request_parent_ui((sp(::user::interaction) ) pmainframe, pcreatecontext);

   }

   sp(::user::interaction) application::get_request_parent_ui(sp(::user::interaction) pinteraction, sp(::ca::create_context) pcreatecontext)
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


      if(pui == ::null() && m_puiInitialPlaceHolderContainer != ::null())
      {
         pui = m_puiInitialPlaceHolderContainer;
      }*/

/*      if(pui == ::null() && m_bShowPlatform && m_pbergedge->get_document() != ::null())
      {
         pui = Bergedge.get_document()->get_bergedge_view();
      }

      return pui;

   }*/

  /*    if(pinteraction->get_app()->is_bergedge() || pcreatecontext->m_bClientOnly ||
         Application.directrix()->m_varTopicQuery["client_only"] != 0 ||
         pcreatecontext->m_bOuterPopupAlertLike)
      {
         return puiParent;
      }

      if(!create_bergedge(pcreatecontext))
      {
         return ::null();
      }




      sphere8::application & app = App(pinteraction->get_app());

      string strAppName = app.m_strAppName;

      if(strAppName != "bergedge")
      {

         if(get_document() != ::null())
         {

            if(get_document()->get_typed_view < ::application::pane_view >() != ::null())
            {

               get_document()->get_typed_view < ::application::pane_view >()->set_cur_tab_by_id("app:" + strAppName);

               puiParent = get_document()->get_typed_view < ::application::pane_view >()->get_tab_holder(get_document()->get_typed_view < ::application::pane_view >()->get_tab_by_id("app:" + strAppName));

            }
            else
            {

               puiParent = get_document()->get_typed_view < ::application::view >();

            }

         }

      }

      return puiParent;

   }

   ::user::place_holder_ptra application::get_place_holder(sp(::userbase::main_frame) pmainframe, sp(::ca::create_context) pcreatecontext)
   {

      UNREFERENCED_PARAMETER(pcreatecontext);

      ::user::place_holder_ptra holderptra;


      sphere8::application & app = App(pmainframe->get_app());

      string strAppName = app.m_strAppName;

      if(get_document()->get_typed_view < ::application::pane_view >() != ::null())
      {

         get_document()->get_typed_view < ::application::pane_view >()->set_cur_tab_by_id("app:" + strAppName);

         holderptra.add(get_document()->get_typed_view < ::application::pane_view >()->get_tab_holder(get_document()->get_typed_view < ::application::pane_view >()->get_tab_by_id("app:" + strAppName)));

      }
      else
      {

         holderptra.add(get_document()->get_typed_view < ::application::view >());

      }

      return holderptra;

   }

   bool application::place(sp(::userbase::main_frame) pmainframe, sp(::ca::create_context) pcreatecontext)
   {

      get_place_holder(pmainframe, pcreatecontext).hold(pmainframe);

      return true;

   }

   */

   void application::get_screen_rect(LPRECT lprect)
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

   bool application::on_install()
   {

      string strFormat;

      string strSentinelPath;

      strSentinelPath = System.dir().ca2("stage/x86/app-sentinel.exe");

      System.os().local_machine_set_run("ca app-sentinel", "\"" + strSentinelPath + "\"");

      return ::asphere::application::on_install();
   }


   void application::set_app_title(const char * pszType, const char * pszAppId, const char * pszTitle)
   {

      sp(::ca::application) papp = ::null();

      if(m_mapApplication.Lookup(string(pszType) + ":" + string(pszAppId), papp) && papp != ::null())
      {

         sp(pane_view) ppaneview = get_document()->get_typed_view < pane_view >();

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


   bool application::initialize1()
   {


      if(!::asphere::application::initialize1())
         return false;


      return true;


   }

   bool application::initialize()
   {


      if(!::asphere::application::initialize())
         return false;


      return true;


   }

   bool application::os_native_bergedge_start()
   {

      return ::asphere::application::os_native_bergedge_start();

   }

   int32_t application::main()
   {


      return ::asphere::application::main();


   }

   bool application::on_uninstall()
   {

      bool bOk1 = false;


      try
      {
         bOk1 = ::asphere::application::on_uninstall();
      }
      catch(...)
      {
         bOk1 = false;
      }


      return bOk1;


   }

   bool application::is_serviceable()
   {


      return false;


   }

   service_base * application::allocate_new_service()
   {


      return ::null();


   }


} // namespace userstack



