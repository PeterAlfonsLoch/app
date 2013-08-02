#include "framework.h"


namespace plane
{


   session::session()
   {

      m_bDrawCursor              = true;
      m_pnaturedocument          = NULL;
      m_pplatformdocument        = NULL;
      m_pbergedgedocument        = NULL;
      m_bShowPlatform            = false;
      m_pappCurrent              = NULL;
      m_psession                 = this;

      ::fs::set * pset = new class ::fs::set(this);
      pset->m_spafsdata.add(new ::fs::native(this));
      m_spfsdata = pset;


      m_pifs                     = new ifs(this, "");
      m_prfs                     = new ::fs::remote_native(this, "");

      m_ecursorDefault  = ::visual::cursor_arrow;
      m_ecursor         = ::visual::cursor_default;

      m_bDrawCursor              = true;
      m_pnaturedocument          = NULL;
      m_pplatformdocument        = NULL;
      m_pbergedgedocument        = NULL;
      m_bShowPlatform            = false;
      m_pappCurrent              = NULL;
      m_bLicense				= false;

      m_strAppName               = "bergedge";

   }

   session::~session()
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
      sp(::ca2::application) pcaapp;

      while(pos != NULL)
      {

         strId.Empty();
         pcaapp = NULL;

         m_mapApplication.get_next_assoc(pos, strId, pcaapp);

         sp(::ca2::application) papp = (pcaapp);

         papp->post_thread_message(WM_QUIT);
      }


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
      //      string strId;
      sp(::ca2::application) papp;


      //      POSITION pos = m_mapApplication.get_start_position();

      pos = m_mapApplication.get_start_position();

      while(pos != NULL)
      {

         strId.Empty();

         m_mapApplication.get_next_assoc(pos, strId, papp);

         papp->post_thread_message(WM_QUIT);

      }

   }

   void session::construct()
   {

      m_strAppName         = "session";
      m_strBaseSupportId   = "ca2_bergedge";
      m_strInstallToken    = "session";
      m_bLicense           = false;
      m_eexclusiveinstance = ::ca2::ExclusiveInstanceNone;

   }

   bool session::initialize()
   {

      if(!::plane::application::initialize())
         return false;


      return true;

   }


   bool session::initialize_instance()
   {

      if(!::plane::application::initialize_instance())
         return false;

      initialize_bergedge_application_interface();


      //filemanager().std().m_strLevelUp = "levelup";


      SetRegistryKey("ca2core");


      if(!InitializeLocalDataCentral())
      {
         simple_message_box(NULL, "Could not initialize Local data central");
         return false;
      }

      initialize_bergedge_application_interface();


      filemanager().std().m_strLevelUp = "levelup";


      //SetRegistryKey("ca2core");


      if(!InitializeLocalDataCentral())
      {
         simple_message_box(NULL, "Could not initialize Local data central");
         return false;
      }

      if(Session.is_remote_session())
      {
         /*Session.savings().save(::ca2::resource_display_bandwidth);
         Session.savings().save(::ca2::resource_blur_background);
         Session.savings().save(::ca2::resource_blurred_text_embossing);
         Session.savings().save(::ca2::resource_translucent_background);*/
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

         bOk = ::plane::application::finalize();

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
         ::plane::application::exit_instance();
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
      return ::ca2::application::_001OnCmdMsg(pcmdmsg);
   }

   ::ca2::application * session::get_app() const
   {
      return ::plane::application::get_app();
   }

   void session::load_string_table()
   {
      ::ca2::application::load_string_table();
      ::ca2::application::load_string_table("plane", "");
      ::ca2::application::load_string_table();
      ::ca2::application::load_string_table("platform", "");


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



   bool session::create_bergedge(sp(::ca2::create_context) pcreatecontext)
   {
      //m_psession->m_pbergedge = this;
      //m_psession->m_pbergedgeInterface = this;


      if(m_pbergedgedocument == NULL)
      {

         sp(::ca2::create_context) createcontextBergedge(allocer());
         createcontextBergedge.oattrib(pcreatecontext);
         createcontextBergedge->m_spCommandLine->m_varFile.set_type(var::type_empty);
         createcontextBergedge->m_bMakeVisible = false;

         m_pbergedgedocument =  (m_ptemplate_bergedge->open_document_file(createcontextBergedge).m_p);
         m_pbergedgedocument->m_papp->m_psession = m_psession;

      }
      if(m_bShowPlatform)
      {
         if(m_pplatformdocument == NULL)
         {

            sp(::ca2::create_context) createcontextPlatform;
            createcontextPlatform.oattrib(pcreatecontext);
            createcontextPlatform->m_spCommandLine->m_varFile.set_type(var::type_empty);
            createcontextPlatform->m_bMakeVisible = true;
            createcontextPlatform->m_puiParent = m_pbergedgedocument->get_bergedge_view();

            m_pplatformdocument  =  (m_ptemplate_platform->open_document_file(createcontextPlatform).m_p);
            m_pplatformdocument->m_pbergedgedocument =  m_pbergedgedocument;
            //m_pnaturedocument    =
            // dynamic_cast < sp(::nature::document) > (
            //  papp->m_ptemplate_nature->open_document_file(NULL, false, m_pbergedgedocument->get_bergedge_view()));

            m_pbergedgedocument->set_platform(m_pplatformdocument);
            //m_pbergedgedocument->set_nature(m_pnaturedocument);
         }
      }
      return m_pbergedgedocument != NULL;


      //if(m_pbergedgeInterface != NULL)
      {

         //         m_pbergedgeInterface->create_bergedge(pcreatecontext);
         //return false;

      }

      m_varCurrentViewFile = pcreatecontext->m_spCommandLine->m_varFile;


      string strApp;

      if((pcreatecontext->m_spCommandLine->m_varQuery["show_platform"] == 1 || command()->m_varTopicQuery["show_platform"] == 1)
         && (!(bool)pcreatecontext->m_spCommandLine->m_varQuery["client_only"] && !(bool)command()->m_varTopicQuery["client_only"])
         && (!pcreatecontext->m_spCommandLine->m_varQuery.has_property("client_only") && !command()->m_varTopicQuery.has_property("client_only")))
      {
         m_bShowPlatform = true;
      }

      strApp = "bergedge";

      pcreatecontext->m_spCommandLine->m_varQuery["show_platform"] = 1;

      sp(::ca2::application) pcaapp = application_get("application", strApp, true, true, pcreatecontext->m_spCommandLine->m_pbiasCreate);

      sp(::plane::session) papp = pcaapp;

      if(papp == NULL)
      {

         pcaapp.release();

         return false;

      }


      UINT uiMessage = WM_APP + 2043;

      papp->post_thread_message(uiMessage, 2, pcreatecontext);

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

   void session::on_request(sp(::ca2::create_context) pcreatecontext)
   {

      TRACE("::plane::session::on_request(sp(::ca2::create_context))");


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

      //      if(m_pbergedgeInterface != NULL)
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
                  if(m_pappCurrent != NULL)
                  {
                     App(m_pappCurrent).request_command(pcreatecontext->m_spCommandLine);
                  }
               }
            }
            else if(m_bShowPlatform)
            {
               create_bergedge(pcreatecontext);
               if(get_document() != NULL && get_document()->get_typed_view < ::bergedge::view >() != NULL)
               {
                  sp(::simple_frame_window) pframe =  (get_document()->get_typed_view < ::bergedge::view >()->GetParentFrame());
                  if(pframe != NULL)
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


               //MessageBox(NULL, "create", strApp, MB_ICONEXCLAMATION);

               if(strApp.is_empty() || strApp == "bergedge")
               {
                  return;
               }

               if(strType.is_empty())
                  strType = "application";

               sp(::ca2::application) papp = (application_get(strType, strApp, true, true, pcreatecontext->m_spCommandLine->m_pbiasCreate));
               if(papp == NULL)
                  return;

               //MessageBox(NULL, "appok", strApp, MB_ICONEXCLAMATION);

               if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("install")
                  || pcreatecontext->m_spCommandLine->m_varQuery.has_property("uninstall"))
               {
                  continue;
               }

               pcreatecontext->m_spCommandLine->m_eventReady.ResetEvent();

               if(strApp != "bergedge")
               {


                  uint32_t dw = WM_APP + 2043;

                  pcreatecontext->m_spCommandLine->m_varQuery["bergedge_callback"] = (sp(::plane::session) ) this;

                  papp->post_thread_message(dw, 2, pcreatecontext);

                  m_pappCurrent = papp;

                  Session.m_pappCurrent = papp;

                  //pcreatecontext->m_spCommandLine->m_eventReady.wait();


               }

            }

         }



         return;

      }

      m_varCurrentViewFile = pcreatecontext->m_spCommandLine->m_varFile;


      string strType;




      if((pcreatecontext->m_spCommandLine->m_varQuery["show_platform"] == 1 || command()->m_varTopicQuery["show_platform"] == 1)
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
               if(m_pappCurrent != NULL)
               {
                  App(m_pappCurrent).request_command(pcreatecontext->m_spCommandLine);
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
            /*if(get_document() != NULL && get_document()->get_typed_view < ::session::user::view >() != NULL)
            {
            sp(::simple_frame_window) pframe =  (get_document()->get_typed_view < ::session::user::view >()->GetParentFrame());
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


   sp(::plane::application) session::start_application(const char * pszType, const char * pszAppId, sp(::ca2::create_context) pcreatecontext)
   {

      string strApp(pszAppId);

      sp(::plane::application) papp = application_get(pszType, strApp, true, true, pcreatecontext->m_spCommandLine->m_pbiasCreate);
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



         UINT uiMessage = WM_APP + 2043;

         papp->post_thread_message(uiMessage, 2, pcreatecontext);

         while(get_run())
         {

            if(pcreatecontext->m_spCommandLine->m_eventReady.wait(millis(84)).signaled())
               break;

         }

         if(!get_run())
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

      }

      return papp;

   }


   /*::sessionsp(::document) session::get_document()
   {
   return m_pbergedgedocument;
   }

   ::sessionsp(::user::view) session::get_view()
   {
   if(get_document() == NULL)
   return NULL;
   return get_document()->get_bergedge_view();
   }

   ::planesp(::document) session::get_platform()
   {
   return m_pplatformdocument;
   }

   sp(::nature::document) session::get_nature()
   {
   return m_pnaturedocument;
   }
   */


   bool session::open_by_file_extension(const char * pszPathName, ::ca2::application_bias * pbiasCreate)
   {

      sp(::ca2::create_context) cc(allocer());

      cc->m_spCommandLine->m_varFile = pszPathName;

      if(pbiasCreate != NULL)
      {
         cc->m_spApplicationBias->operator=(*pbiasCreate);
      }

      return open_by_file_extension(cc);

   }


   bool session::open_by_file_extension(::ca2::create_context * pcreatecontext)
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

      if(::ca2::str::ends_ci(strPathName, ".cgcl"))
      {

      }

      string strProtocol = System.url().get_protocol(strPathName);

      if(strProtocol == "app")
      {

         strId = System.url().get_server(strPathName);

         string str = System.url().get_object(strPathName);

         ::ca2::str::begins_eat(str, "/");

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

      sp(::plane::application) papp = application_get("application", strId, true, true, pcreatecontext->m_spApplicationBias);

      if(papp == NULL)
         return false;

      papp->::ca2::request_interface::create(pcreatecontext);

      return true;

   }



   session::run_application::run_application()
   {
      m_papp = NULL;
      m_puiParent = NULL;
   }

   //   void session::on_exclusive_instance_conflict(::ca2::EExclusiveInstance eexclusive)
   //   {
   //
   //      if(eexclusive == ::ca2::ExclusiveInstanceLocalId)
   //      {
   //         /*
   //         ::primitive::memory_file file(get_app());
   //         file.from_string(command()->m_varTopicFile);
   //         COPYDATASTRUCT data;
   //         data.dwData = 1984;
   //         data.cbData = (uint32_t) file.get_length();
   //         data.lpData = file.get_data();
   //         oswindow oswindow = ::FindWindowA(NULL, "::draw2d::fontopus::message_wnd::session::");
   //
   //         ::SendMessage(oswindow, WM_COPYDATA, NULL, (LPARAM) &data);*/
   //
   //#if defined(WINDOWSEX) || defined(LINUX) || defined(MACOS)
   //
   //         small_ipc_tx_channel channel;
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

   void session::request_create(sp(::ca2::create_context) pcreatecontext)
   {

      //      if(m_pbergedgeInterface != NULL)
      {

         if(m_pappCurrent != NULL && m_pappCurrent != this
            && (pcreatecontext->m_spCommandLine->m_strApp.is_empty()
            ||App(m_pappCurrent).m_strAppName == pcreatecontext->m_spCommandLine->m_strApp))
         {
            if(get_document() != NULL && get_document()->get_typed_view < ::bergedge::pane_view >() != NULL)
            {
               get_document()->get_typed_view < ::bergedge::pane_view >()->set_cur_tab_by_id("app:" + App(m_pappCurrent).m_strAppName);
            }
            App(m_pappCurrent).request_create(pcreatecontext);
            if(pcreatecontext->m_spCommandLine->m_varQuery["document"].ca2 < ::user::document_interface > () == NULL)
            {
               goto alt1;
            }

         }
         else
         {
alt1:
            if(pcreatecontext->m_spCommandLine->m_varFile.get_type() == var::type_string)
            {
               if(::ca2::str::ends_ci(pcreatecontext->m_spCommandLine->m_varFile, ".ca2"))
               {
                  string strCommand = Application.file().as_string(pcreatecontext->m_spCommandLine->m_varFile);
                  if(::ca2::str::begins_eat(strCommand, "ca2prompt\r")
                     || ::ca2::str::begins_eat(strCommand, "ca2prompt\n"))
                  {
                     strCommand.trim();
                     command()->add_fork_uri(strCommand);
                  }
                  return;
               }
               else if(pcreatecontext->m_spCommandLine->m_strApp.has_char()
                  && get_document() != NULL
                  && get_document()->get_typed_view < ::bergedge::pane_view >() != NULL)
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
               get_document() != NULL && get_document()->get_typed_view < ::bergedge::pane_view >() != NULL
               && (!pcreatecontext->m_spApplicationBias.is_set() || pcreatecontext->m_spApplicationBias->m_puiParent == NULL))
            {
               //MessageBox(NULL, "request3", "request3", MB_ICONEXCLAMATION);
               get_document()->get_typed_view < ::bergedge::pane_view >()->set_cur_tab_by_id("app:" + pcreatecontext->m_spCommandLine->m_strApp);
               App(m_pappCurrent).request_create(pcreatecontext);
            }
            else
            {
               //MessageBox(NULL, "request4", "request4", MB_ICONEXCLAMATION);
               on_request(pcreatecontext);
            }
         }
         return;

      }

      if(pcreatecontext->m_spCommandLine->m_varFile.get_type() == var::type_string)
      {
         if(::ca2::str::ends_ci(pcreatecontext->m_spCommandLine->m_varFile, ".ca2"))
         {
            string strCommand = Application.file().as_string(pcreatecontext->m_spCommandLine->m_varFile);
            if(::ca2::str::begins_eat(strCommand, "ca2prompt\r")
               || ::ca2::str::begins_eat(strCommand, "ca2prompt\n"))
            {
               strCommand.trim();
               command()->add_fork_uri(strCommand);
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
         App(m_pappCurrent).request_create(pcreatecontext);
      }
      else
      {
         on_request(pcreatecontext);
      }
   }

   void session::request_topic_file(var & varQuery)
   {
      request_file_query(m_varTopicFile, varQuery);
   }

   void session::request_topic_file()
   {
      request_file(m_varTopicFile);
   }

   /*void session::request_application(const char * pszId, var varFile, var varQuery, ::ca2::application_bias * pbiasCreate)
   {

   ::ca2::application_request request;

   request.m_iEdge         = m_iEdge;
   request.m_strApp        = pszId;
   request.m_varFile       = varFile;
   request.m_varQuery      = varQuery;
   request.m_pbiasCreate   = pbiasCreate;

   request_application(&request);

   }*/
   /*
   sp(::ca2::application) session::application_get(const char * pszType, const char * pszId, bool bCreate, bool bSynch, ::ca2::application_bias * pbiasCreate)
   {
   sp(::ca2::application) papp = NULL;

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
   catch(::ca2::exception & e)
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

   sp(::ca2::application) session::get_current_application()
   {
      return m_pappCurrent;
   }


   /*void session::check_topic_file_change()
   {
   if(m_varCurrentViewFile != m_varTopicFile && !m_varTopicFile.is_empty())
   {
   m_varCurrentViewFile = m_varTopicFile;
   request_topic_file();
   }
   }*/
   //   
   //
   //   sp(::user::interaction) session::get_request_parent_ui(sp(::user::interaction) pinteraction, sp(::ca2::create_context) pcreatecontext)
   //   {
   //
   //
   //      sp(::user::interaction) puiParent = NULL;
   //
   //      if(pcreatecontext->m_spCommandLine->m_varQuery["uicontainer"].ca2 < ::user::interaction >() != NULL)
   //         puiParent = pcreatecontext->m_spCommandLine->m_varQuery["uicontainer"].ca2 < ::user::interaction >();
   //
   //      if(puiParent == NULL && pcreatecontext->m_puiParent != NULL)
   //      {
   //         puiParent = pcreatecontext->m_puiParent;
   //      }
   //
   //      if(puiParent == NULL && pcreatecontext->m_spCommandLine->m_pbiasCreate != NULL)
   //      {
   //         puiParent = pcreatecontext->m_spCommandLine->m_pbiasCreate->m_puiParent;
   //      }
   //
   //      if(puiParent == NULL && pcreatecontext->m_spApplicationBias.is_set())
   //      {
   //         puiParent = pcreatecontext->m_spApplicationBias->m_puiParent;
   //      }
   //
   //
   ///*      if(pui == NULL && m_puiInitialPlaceHolderContainer != NULL)
   //      {
   //         pui = m_puiInitialPlaceHolderContainer;
   //      }*/
   //
   ///*      if(pui == NULL && m_bShowPlatform && m_pbergedge->get_document() != NULL)
   //      {
   //         pui = Session.get_document()->get_bergedge_view();
   //      }
   //
   //      return pui;
   //
   //   }*/
   //
   //      if(pinteraction->get_app()->is_session() || pcreatecontext->m_bClientOnly ||
   //         Application.directrix()->m_varTopicQuery["client_only"] != 0 ||
   //         pcreatecontext->m_bOuterPopupAlertLike)
   //      {
   //         return puiParent;
   //      }
   //
   //      /*if(!create_bergedge(pcreatecontext))
   //      {
   //         return NULL;
   //      }*/
   //
   //
   //
   //
   ///*      plane::application & app = App(pinteraction->get_app());
   //
   //      string strAppName = app.m_strAppName;
   //
   //      if(strAppName != "session")
   //      {
   //
   //         if(get_document() != NULL)
   //         {
   //
   //            if(get_document()->get_typed_view < ::session::pane_view >() != NULL)
   //            {
   //
   //               get_document()->get_typed_view < ::session::pane_view >()->set_cur_tab_by_id("app:" + strAppName);
   //
   //               puiParent = get_document()->get_typed_view < ::session::pane_view >()->get_tab_holder(get_document()->get_typed_view < ::session::pane_view >()->get_tab_by_id("app:" + strAppName));
   //
   //            }
   //            else
   //            {
   //
   //               puiParent = get_document()->get_typed_view < ::session::user::view >();
   //
   //            }
   //
   //         }
   //
   //      }*/
   //
   //      return puiParent;
   //
   //   }
   //
   /*   ::user::place_holder_ptra session::get_place_holder(sp(::user::main_frame) pmainframe, sp(::ca2::create_context) pcreatecontext)
   {

   UNREFERENCED_PARAMETER(pcreatecontext);

   ::user::place_holder_ptra holderptra;


   plane::application & app = App(pmainframe->get_app());

   string strAppName = app.m_strAppName;

   if(get_document()->get_typed_view < ::session::pane_view >() != NULL)
   {

   get_document()->get_typed_view < ::session::pane_view >()->set_cur_tab_by_id("app:" + strAppName);

   holderptra.add(get_document()->get_typed_view < ::session::pane_view >()->get_tab_holder(get_document()->get_typed_view < ::session::pane_view >()->get_tab_by_id("app:" + strAppName)));

   }
   else
   {

   holderptra.add(get_document()->get_typed_view < ::session::user::view >());

   }

   return holderptra;

   }*/

   /*
   bool session::place(sp(::user::main_frame) pmainframe, sp(::ca2::create_context) pcreatecontext)
   {

   get_place_holder(pmainframe, pcreatecontext).hold(pmainframe);

   return true;

   }
   */



   bool session::on_install()
   {

      string strFormat;

      string strSentinelPath;

      strSentinelPath = System.dir().ca2("stage/x86/app-sentinel.exe");

      System.os().local_machine_set_run("ca2 app-sentinel", "\"" + strSentinelPath + "\"");


      System.os().defer_register_ca2_plugin_for_mozilla();



      return ::plane::application::on_install();
   }




   bool session::is_remote_session()
   {


      return System.os().is_remote_session();


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
         return NULL;
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




   void session::OnFileManagerOpenFile(
      ::filemanager::data * pdata,
      ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      m_ptemplate_html->open_document_file(itema[0].m_strPath);
   }

   bool session::file_manager_open_file(
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


   void session::initialize_bergedge_application_interface()
   {
      int32_t iCount = 32; // todo: get from bergedge profile
      System.factory().creatable < ::bergedge::document > (iCount);
      System.factory().creatable < ::bergedge::view > (iCount);
      System.factory().creatable < ::bergedge::pane_view > (iCount);
      System.factory().creatable < ::bergedge::frame > (iCount);
      System.factory().creatable < platform::document > (iCount);
      System.factory().creatable < ::platform::view > (iCount);
      System.factory().creatable < platform::pane_view > (iCount);
      System.factory().creatable < platform::frame > (iCount);
      System.factory().creatable < nature::document > (iCount);
      System.factory().creatable < ::nature::view > (iCount);
      System.factory().creatable < nature::pane_view > (iCount);
      System.factory().creatable < nature::frame > (iCount);
      m_ptemplate_bergedge    = new ::user::single_document_template(
         this,
         "bergedge/frame",
         System.type_info < bergedge::document > (),
         System.type_info < bergedge::frame > (),
         System.type_info < bergedge::view > ());
      m_ptemplate_platform    = new ::user::single_document_template(
         this,
         "bergedge/frame",
         System.type_info < platform::document > (),
         System.type_info < platform::frame > (),
         System.type_info < platform::pane_view > ());
      m_ptemplate_nature      = new ::user::single_document_template(
         this,
         "bergedge/frame",
         System.type_info < nature::document > (),
         System.type_info < nature::frame > (),
         System.type_info < ::nature::view > ());
      m_pnaturedocument = NULL;
   }



   void session::on_app_request_bergedge_callback(sp(::ca2::application) papp)
   {
      if(&App(papp) != NULL)
      {

         m_pappCurrent = papp;

      }

      if(m_bShowPlatform)
      {
         sp(::simple_frame_window) pframeApp =  (get_document()->get_typed_view < ::bergedge::pane_view >()->get_view_uie().m_p);
         if(pframeApp != NULL)
         {
            pframeApp->WfiFullScreen(true, false);
         }
         sp(::simple_frame_window) pframe =  (get_document()->get_typed_view < ::bergedge::pane_view >()->GetParentFrame());
         if(pframe != NULL)
         {
            pframe->ShowWindow(SW_SHOW);
         }
      }
      else
      {
         if(get_document() != NULL && get_document()->get_typed_view < ::bergedge::view >() != NULL)
         {
            sp(::simple_frame_window) pframe =  (get_document()->get_typed_view < ::bergedge::view >()->GetParentFrame());
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

      if(m_pappCurrent != NULL && m_pappCurrent->m_pappThis->fontopus()->m_puser != NULL)
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


   sp(::bergedge::document) session::get_document()
   {
      return m_pbergedgedocument;
   }

   sp(::bergedge::view) session::get_view()
   {
      if(get_document() == NULL)
         return NULL;
      return get_document()->get_bergedge_view();
   }

   sp(::platform::document) session::get_platform()
   {
      return m_pplatformdocument;
   }

   sp(::nature::document) session::get_nature()
   {
      return m_pnaturedocument;
   }


   bool session::InitializeLocalDataCentral()
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

   void session::on_exclusive_instance_conflict(::ca2::EExclusiveInstance eexclusive)
   {
      if(eexclusive == ::ca2::ExclusiveInstanceLocalId)
      {
#ifdef WINDOWSEX
         ::primitive::memory_file file(get_app());
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


   /*void session::request_application(const char * pszId, var varFile, var varQuery, ::ca2::application_bias * pbiasCreate)
   {

   ::ca2::application_request request;

   request.m_iEdge         = m_iEdge;
   request.m_strApp        = pszId;
   request.m_varFile       = varFile;
   request.m_varQuery      = varQuery;
   request.m_pbiasCreate   = pbiasCreate;

   request_application(&request);

   }*/

   sp(::ca2::application) session::application_get(const char * pszType, const char * pszId, bool bCreate, bool bSynch, ::ca2::application_bias * pbiasCreate)
   {
      sp(::ca2::application) papp = NULL;

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
         catch(::ca2::exception & e)
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
         m_mapApplication.set_at(string(pszType) + ":" + string(pszId), papp);
         Session.m_mapApplication.set_at(string(pszType) + ":" + string(pszId), papp);
         return papp;
      }
   }



   void session::check_topic_file_change()
   {
      if(m_varCurrentViewFile != m_varTopicFile && !m_varTopicFile.is_empty())
      {
         m_varCurrentViewFile = m_varTopicFile;
         request_topic_file();
      }
   }

   sp(::user::interaction) session::get_request_parent_ui(sp(::user::interaction) pinteraction, sp(::ca2::create_context) pcreatecontext)
   {


      sp(::user::interaction) puiParent = NULL;

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
      pui = Session.get_document()->get_bergedge_view();
      }

      return pui;

      }*/

      if( pcreatecontext->m_bClientOnly ||
         Application.directrix()->m_varTopicQuery["client_only"] != 0 ||
         pcreatecontext->m_bOuterPopupAlertLike)
      {
         return puiParent;
      }


      bool bCreateBergedge = false;

      if(bCreateBergedge)
      {

         if(!create_bergedge(pcreatecontext))
         {
            return NULL;


         }

      }




      plane::application & app = App(pinteraction->get_app());

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

   ::user::place_holder_ptra session::get_place_holder(sp(::user::frame_window) pmainframe, sp(::ca2::create_context) pcreatecontext)
   {

      UNREFERENCED_PARAMETER(pcreatecontext);

      ::user::place_holder_ptra holderptra;


      plane::application & app = App(pmainframe->get_app());

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

   bool session::place(sp(::user::main_frame) pmainframe, sp(::ca2::create_context) pcreatecontext)
   {

      get_place_holder(pmainframe, pcreatecontext).hold(pmainframe);

      return true;

   }

   void session::get_screen_rect(LPRECT lprect)
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



   void session::set_app_title(const char * pszType, const char * pszAppId, const char * pszTitle)
   {

      sp(::ca2::application) papp = NULL;

      if(m_mapApplication.Lookup(string(pszType) + ":" + string(pszAppId), papp) && papp != NULL)
      {

         sp(::bergedge::pane_view) ppaneview = get_document()->get_typed_view < ::bergedge::pane_view >();

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



   sp(::plane::session) session::get_session()
   {

      return this;

   }


   bool session::initialize1()
   {

      if(!::platform::application::initialize1())
         return false;


      m_puserpresence            = canew(::userpresence::userpresence(this));

      if(m_puserpresence.is_null())
      {
         TRACE("Failed to create new User Presence");
         return false;
      }

      try
      {

         m_puserpresence->construct(this);

      }
      catch(...)
      {

         TRACE("Failed to construct User Presence");

         return false;

      }


      if(!m_puserpresence->initialize())
      {

         TRACE("Failed to initialize User Presence");

         return false;

      }




      return true;


   }


   bool session::is_serviceable()
   {


      return ::platform::application::is_serviceable();


   }


   bool session::on_uninstall()
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




      return bOk1 && bOk2;


   }


   bool session::os_native_bergedge_start()
   {

      return ::platform::application::os_native_bergedge_start();

   }


   service_base * session::allocate_new_service()
   {


      return ::platform::application::allocate_new_service();


   }


} // namespace plane



