#include "framework.h"


namespace core
{


   platform::platform(sp(::aura::application) papp):
      element(papp),
      ::thread(papp)
   {

      m_paxissession                      = papp->m_paxissession;
         
      m_pbasesession                      = papp->m_pbasesession;

      m_pbasesession->m_pcoreplatform     = this;

      m_paxissystem                       = papp->m_paxissystem;

      m_pbasesystem                       = papp->m_pbasesystem;

      m_pbasesession->m_pplatformcomposite = this;

      m_pauraapp                          = this;

      m_pauraapp                         = this;
      
      m_pcoreapp                          = this;

      m_pcoreplatform                     = this;

      m_pbasesession->m_pcoreplatform     = this;

      m_pnaturedocument          = NULL;
      m_pplatformdocument        = NULL;
      m_pbergedgedocument        = NULL;
      m_bShowPlatform            = false;
      m_pappCurrent              = NULL;
      m_pnaturedocument          = NULL;
      m_pplatformdocument        = NULL;
      m_pbergedgedocument        = NULL;
      m_bShowPlatform            = false;
      m_pappCurrent              = NULL;
      m_bLicense				      = false;

      m_strAppName               = "bergedge";

   }

   platform::~platform_parent
   {

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

   }


   void platform::construct(const char * pszAppId)
   {

      ::core::application::construct("session");

      m_strAppName         = "session";
      m_strBaseSupportId   = "ca2_bergedge";
      m_strInstallToken    = "session";
      m_bLicense           = false;
      m_eexclusiveinstance = ExclusiveInstanceNone;

   }

   bool platform::process_initialize()
   {

      if(!::platform::application::process_initialize())
         return false;

      m_spuserex = create_userex();

      if(m_spuserex == NULL)
         return false;

      m_spuserex->construct(this);

      return true;

   }


   bool platform::initialize1()
   {

      if(!::platform::application::initialize1())
         return false;

      if(!m_spuserex->initialize())
         return false;

      if(!m_spuserex->initialize1())
         return false;

      if(!m_spuserex->initialize2())
         return false;

      return true;


   }


   bool platform::initialize()
   {

      if(!::core::application::initialize())
         return false;



      return true;

   }


   bool platform::initialize_instance()
   {

      if(!::core::application::initialize_instance())
         return false;

      m_pfilemanager = canew(::filemanager::filemanager(this));

      m_pfilemanager->construct(this);

      if (!m_pfilemanager->initialize())
         return false;

      initialize_bergedge_application_interface();

      SetRegistryKey("ca2core");

      if(!InitializeLocalDataCentral())
      {

         simple_message_box(NULL, "Could not initialize Local data central");

         return false;

      }

      initialize_bergedge_application_interface();

      filemanager().std().m_strLevelUp = "levelup";

      if(is_remote_session())
      {
         /*Session.savings().save(::aura::resource_display_bandwidth);
         Session.savings().save(::aura::resource_blur_background);
         Session.savings().save(::aura::resource_blurred_text_embossing);
         Session.savings().save(::aura::resource_translucent_background);*/
      }

      /*      if(System.directrix()->m_varTopicQuery.has_property("install")
      || System.directrix()->m_varTopicQuery.has_property("uninstall"))
      {
      find_wndfrms_to_cache(m_mapUInteractionToLibrary);
      }
      else
      {
      find_wndfrms_from_cache(m_mapUInteractionToLibrary);
      }*/

      return true;

   }


   bool platform::finalize()
   {

      bool bOk = true;

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


   int32_t platform::exit_instance()
   {

      try
      {

         ::core::application::exit_instance();

      }
      catch(...)
      {

      }

      return 0;

   }


   bool platform::bergedge_start()
   {

      return true;

   }


   void platform::_001OnFileNew()
   {

      //m_pdocmanager->_001OnFileNew();

   }


   bool platform::_001OnCmdMsg(::aura::cmd_msg * pcmdmsg)
   {

      return application::_001OnCmdMsg(pcmdmsg);

   }


   void platform::load_string_table()
   {

      application::load_string_table();
      application::load_string_table("plane", "");
      application::load_string_table();
      application::load_string_table("platform", "");

   }


   bool platform::create_bergedge(sp(::create_context) pcreatecontext)
   {

      if(m_pbergedgedocument == NULL)
      {

         sp(::create_context) createcontextBergedge(allocer());

         createcontextBergedge.oattrib(pcreatecontext);

         createcontextBergedge->m_spCommandLine->m_varFile.set_type(var::type_empty);
         
         createcontextBergedge->m_bMakeVisible = false;

         m_pbergedgedocument = m_ptemplate_bergedge->open_document_file(createcontextBergedge);

         //m_pbergedgedocument->m_pauraapp->m_pbasesession->m_pcoreplatform = this;

      }

      if(m_bShowPlatform)
      {

         if(m_pplatformdocument == NULL)
         {

            sp(::create_context) createcontextPlatform;

            createcontextPlatform.oattrib(pcreatecontext);

            createcontextPlatform->m_spCommandLine->m_varFile.set_type(var::type_empty);

            createcontextPlatform->m_bMakeVisible = true;

            createcontextPlatform->m_puiParent = m_pbergedgedocument->get_bergedge_view();

            m_pplatformdocument = m_ptemplate_platform->open_document_file(createcontextPlatform);

            m_pplatformdocument->m_pbergedgedocument =  m_pbergedgedocument;

            m_pbergedgedocument->set_platform(m_pplatformdocument);

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

      sp(::aura::application) pbaseapp = application_get("application", strApp, true, true, pcreatecontext->m_spCommandLine->m_pbiasCreate);

      sp(::core::platform) papp = pbaseapp;

      if(papp == NULL)
      {

         pbaseapp.release();

         return false;

      }


      UINT uiMessage = WM_APP + 2043;

      papp->m_pcoreapp->post_thread_message(uiMessage, 2, pcreatecontext);

      pcreatecontext->m_spCommandLine->m_eventReady.wait();

      return false;

   }

   void platform::launch_app(const char * psz)
   {
      UNREFERENCED_PARAMETER(psz);
   }

   void platform::install_app(const char * psz)
   {
      UNREFERENCED_PARAMETER(psz);
   }

   void platform::on_request(sp(::create_context) pcreatecontext)
   {

      TRACE("::core::platform::on_request(sp(::create_context))");


      if(pcreatecontext->m_spCommandLine->m_varQuery["app"].array_get_count() > 1)
      {
         start_application("application", pcreatecontext->m_spCommandLine->m_varQuery["app"].stra()[0], pcreatecontext);
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


            if (pcreatecontext->m_spCommandLine->m_varQuery["app"].stra().find_first_ci(strApp) < 0)
            {

               pcreatecontext->m_spCommandLine->m_varQuery["app"].stra().insert_at(0, strApp);
               pcreatecontext->m_spCommandLine->m_varQuery["app_type"].stra().insert_at(0, strType);

            }

            for(int32_t i = 0; i < pcreatecontext->m_spCommandLine->m_varQuery["app"].stra().get_count(); i++)
            {

               strApp = pcreatecontext->m_spCommandLine->m_varQuery["app"].stra()[i];
               if (i < pcreatecontext->m_spCommandLine->m_varQuery["app_type"].stra().get_count())
                  strType = pcreatecontext->m_spCommandLine->m_varQuery["app_type"].stra()[i];
               else
                  strType.Empty();


               //simple_message_box(NULL, "create", strApp, MB_ICONEXCLAMATION);

               if(strApp.is_empty() || strApp == "bergedge")
               {
                  
                  return;

               }

               if (strApp == "session")
               {
                  
                  continue;

               }

               if(strType.is_empty())
                  strType = "application";

               sp(::aura::application) papp = (application_get(strType, strApp, true, true, pcreatecontext->m_spCommandLine->m_pbiasCreate));
               if(papp == NULL)
                  return;

               //simple_message_box(NULL, "appok", strApp, MB_ICONEXCLAMATION);

               if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("install")
                  || pcreatecontext->m_spCommandLine->m_varQuery.has_property("uninstall"))
               {
                  continue;
               }

               pcreatecontext->m_spCommandLine->m_eventReady.ResetEvent();

               if(strApp != "bergedge")
               {


                  uint32_t dw = WM_APP + 2043;

                  pcreatecontext->m_spCommandLine->m_varQuery["bergedge_callback"] = (sp(::core::platform) ) this;

                  papp->m_pcoreapp->post_thread_message(dw, 2, pcreatecontext);

                  m_pappCurrent = papp;

                  m_pappCurrent = papp;

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
            /*if(get_document() != NULL && get_document()->get_typed_view < ::platform::user::impact >() != NULL)
            {
            sp(::simple_frame_window) pframe =  (get_document()->get_typed_view < ::platform::user::impact >()->GetParentFrame());
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
            start_application("application", "app/core/bergedge", pcreatecontext);
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
                  System.planesessionptra().remove(this);
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


   sp(::aura::application) platform::start_application(const char * pszType, const char * pszAppId, sp(::create_context) pcreatecontext)
   {

      string strApp(pszAppId);

      sp(::aura::application) papp = application_get(pszType, strApp, true, true, pcreatecontext->m_spCommandLine->m_pbiasCreate);
      if(papp == NULL)
         return NULL;

      if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("install")
         || pcreatecontext->m_spCommandLine->m_varQuery.has_property("uninstall"))
      {

         Session.appptra().remove(papp);

         return NULL;

      }

      pcreatecontext->m_spCommandLine->m_eventReady.ResetEvent();

      if(strApp != "session")
      {



         UINT uiMessage = WM_APP + 2043;

         papp->m_pcoreapp->post_thread_message(uiMessage, 2, pcreatecontext);

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


   /*::sessionsp(::document) platform::get_document()
   {
   return m_pbergedgedocument;
   }

   ::sessionsp(::user::impact) platform::get_view()
   {
   if(get_document() == NULL)
   return NULL;
   return get_document()->get_bergedge_view();
   }

   ::planesp(::document) platform::get_platform()
   {
   return m_pplatformdocument;
   }

   sp(::nature::document) platform::get_nature()
   {
   return m_pnaturedocument;
   }
   */


   bool platform::open_by_file_extension(const char * pszPathName, application_bias * pbiasCreate)
   {

      sp(::create_context) cc(allocer());

      cc->m_spCommandLine->m_varFile = pszPathName;

      if(pbiasCreate != NULL)
      {
         cc->m_spApplicationBias->operator=(*pbiasCreate);
      }

      return open_by_file_extension(cc);

   }


   bool platform::open_by_file_extension(::create_context * pcreatecontext)
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

         string strExtension = System.file().extension(strPathName);

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

      sp(::aura::application) papp = application_get("application", strId, true, true, pcreatecontext->m_spApplicationBias);

      if(papp == NULL)
         return false;

      papp->m_pcoreapp->::request_interface::create(pcreatecontext);

      return true;

   }



   platform::run_application::run_application()
   {
      m_pauraapp = NULL;
      m_puiParent = NULL;
   }

   //   void platform::on_exclusive_instance_conflict(EExclusiveInstance eexclusive)
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
   //         oswindow oswindow = ::FindWindowA(NULL, "::draw2d::fontopus::message_wnd::platform::");
   //
   //         ::SendMessage(oswindow, WM_COPYDATA, NULL, (LPARAM) &data);*/
   //
   //#if defined(WINDOWSEX) || defined(LINUX) || defined(APPLEOS)
   //
   //         small_ipc_tx_channel channel;
   //
   //         if(channel.open("::draw2d::fontopus::message_wnd::platform::"))
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

   void platform::request_create(sp(::create_context) pcreatecontext)
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
            if(pcreatecontext->m_spCommandLine->m_varQuery["document"].cast < ::user::document > () == NULL)
            {
  //             goto alt1;
            }

         }
         else
         {
//alt1:
            if(pcreatecontext->m_spCommandLine->m_varFile.get_type() == var::type_string)
            {
               if(::str::ends_ci(pcreatecontext->m_spCommandLine->m_varFile, ".core"))
               {
                  string strCommand = Application.file().as_string(pcreatecontext->m_spCommandLine->m_varFile);
                  if(::str::begins_eat(strCommand, "ca2prompt\r")
                     || ::str::begins_eat(strCommand, "ca2prompt\n"))
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
               //simple_message_box(NULL, "request3", "request3", MB_ICONEXCLAMATION);
               get_document()->get_typed_view < ::bergedge::pane_view >()->set_cur_tab_by_id("app:" + pcreatecontext->m_spCommandLine->m_strApp);
               App(m_pappCurrent).request_create(pcreatecontext);
            }
            else
            {
               //simple_message_box(NULL, "request4", "request4", MB_ICONEXCLAMATION);
               on_request(pcreatecontext);
            }
         }
         return;

      }

      if(pcreatecontext->m_spCommandLine->m_varFile.get_type() == var::type_string)
      {
         if(::str::ends_ci(pcreatecontext->m_spCommandLine->m_varFile, ".core"))
         {
            string strCommand = Application.file().as_string(pcreatecontext->m_spCommandLine->m_varFile);
            if(::str::begins_eat(strCommand, "ca2prompt\r")
               || ::str::begins_eat(strCommand, "ca2prompt\n"))
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


         /*         if(get_document() != NULL && get_document()->get_typed_view < ::platform::pane_view >() != NULL)
         {
         get_document()->get_typed_view < ::platform::pane_view >()->set_cur_tab_by_id("app:" + App(m_pappCurrent).m_strAppName);
         }*/
         App(m_pappCurrent).request_create(pcreatecontext);
      }
      else
      {
         on_request(pcreatecontext);
      }
   }

   void platform::request_topic_file(var & varQuery)
   {
      request_file_query(m_varTopicFile, varQuery);
   }

   void platform::request_topic_file()
   {
      request_file(m_varTopicFile);
   }

   /*void platform::request_application(const char * pszId, var varFile, var varQuery, application_bias * pbiasCreate)
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
   sp(::aura::application) platform::application_get(const char * pszType, const char * pszId, bool bCreate, bool bSynch, application_bias * pbiasCreate)
   {
   sp(::aura::application) papp = NULL;

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
   bool platform::is_session()
   {
      return true;
   }

   sp(::aura::application) platform::get_current_application()
   {
      return m_pappCurrent;
   }


   /*void platform::check_topic_file_change()
   {
   if(m_varCurrentViewFile != m_varTopicFile && !m_varTopicFile.is_empty())
   {
   m_varCurrentViewFile = m_varTopicFile;
   request_topic_file();
   }
   }*/
   //
   //
   //   sp(::user::interaction) platform::get_request_parent_ui(sp(::user::interaction) pinteraction, sp(::create_context) pcreatecontext)
   //   {
   //
   //
   //      sp(::user::interaction) puiParent = NULL;
   //
   //      if(pcreatecontext->m_spCommandLine->m_varQuery["uicontainer"].cast < ::user::interaction >() != NULL)
   //         puiParent = pcreatecontext->m_spCommandLine->m_varQuery["uicontainer"].cast < ::user::interaction >();
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
   ///*      ::core::application & app = App(pinteraction->get_app());
   //
   //      string strAppName = app.m_strAppName;
   //
   //      if(strAppName != "session")
   //      {
   //
   //         if(get_document() != NULL)
   //         {
   //
   //            if(get_document()->get_typed_view < ::platform::pane_view >() != NULL)
   //            {
   //
   //               get_document()->get_typed_view < ::platform::pane_view >()->set_cur_tab_by_id("app:" + strAppName);
   //
   //               puiParent = get_document()->get_typed_view < ::platform::pane_view >()->get_tab_holder(get_document()->get_typed_view < ::platform::pane_view >()->get_tab_by_id("app:" + strAppName));
   //
   //            }
   //            else
   //            {
   //
   //               puiParent = get_document()->get_typed_view < ::platform::user::impact >();
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
   /*   ::user::place_holder_ptra platform::get_place_holder(sp(::user::main_frame) pmainframe, sp(::create_context) pcreatecontext)
   {

   UNREFERENCED_PARAMETER(pcreatecontext);

   ::user::place_holder_ptra holderptra;


   ::core::application & app = App(pmainframe->get_app());

   string strAppName = app.m_strAppName;

   if(get_document()->get_typed_view < ::platform::pane_view >() != NULL)
   {

   get_document()->get_typed_view < ::platform::pane_view >()->set_cur_tab_by_id("app:" + strAppName);

   holderptra.add(get_document()->get_typed_view < ::platform::pane_view >()->get_tab_holder(get_document()->get_typed_view < ::platform::pane_view >()->get_tab_by_id("app:" + strAppName)));

   }
   else
   {

   holderptra.add(get_document()->get_typed_view < ::platform::user::impact >());

   }

   return holderptra;

   }*/

   /*
   bool platform::place(sp(::user::main_frame) pmainframe, sp(::create_context) pcreatecontext)
   {

   get_place_holder(pmainframe, pcreatecontext).hold(pmainframe);

   return true;

   }
   */



   bool platform::on_install()
   {

      string strFormat;

      string strSentinelPath;

      strSentinelPath = System.dir().element("stage/x86/app.sentinel.exe");

      System.os().local_machine_set_run("core app.sentinel", "\"" + strSentinelPath + "\"");


      System.os().defer_register_ca2_plugin_for_mozilla();



      return ::core::application::on_install();
   }




   bool platform::is_remote_session()
   {


      return System.os().is_remote_session();


   }


   bool platform::is_mouse_button_pressed(::user::e_mouse emouse)
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



   void platform::OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema)
   {

      UNREFERENCED_PARAMETER(pdata);

      m_ptemplate_html->open_document_file(itema[0]->m_strPath);

   }


   bool platform::open_file(::filemanager::data * pdata, ::fs::item_array & itema)
   {

      UNREFERENCED_PARAMETER(pdata);

      if(itema.get_size() > 0)
      {

         return true;

      }

      return false;

   }


   void platform::initialize_bergedge_application_interface()
   {
      int32_t iCount = 32; // todo: get from bergedge profile
      System.factory().creatable < ::bergedge::document > (iCount);
      System.factory().creatable < ::bergedge::view > (iCount);
      System.factory().creatable < ::bergedge::pane_view > (iCount);
      System.factory().creatable < ::bergedge::frame > (iCount);
      System.factory().creatable < ::platform::document > (iCount);
      System.factory().creatable < ::platform::view > (iCount);
      System.factory().creatable < ::platform::pane_view > (iCount);
      System.factory().creatable < ::platform::frame > (iCount);
      System.factory().creatable < ::nature::document > (iCount);
      System.factory().creatable < ::nature::view > (iCount);
      System.factory().creatable < ::nature::pane_view > (iCount);
      System.factory().creatable < ::nature::frame > (iCount);
      m_ptemplate_bergedge    = new ::user::single_document_template(
         this,
         "bergedge/frame",
         System.type_info < ::bergedge::document > (),
         System.type_info < ::bergedge::frame > (),
         System.type_info < ::bergedge::view > ());
      m_ptemplate_platform    = new ::user::single_document_template(
         this,
         "bergedge/frame",
         System.type_info < ::platform::document > (),
         System.type_info < ::platform::frame > (),
         System.type_info < ::platform::pane_view > ());
      m_ptemplate_nature      = new ::user::single_document_template(
         this,
         "bergedge/frame",
         System.type_info < ::nature::document > (),
         System.type_info < ::nature::frame > (),
         System.type_info < ::nature::view > ());
      m_pnaturedocument = NULL;
   }



   void platform::on_app_request_bergedge_callback(sp(::aura::application) papp)
   {
      if(&App(papp) != NULL)
      {

         m_pappCurrent = papp;

      }

      if(m_bShowPlatform)
      {
         sp(::simple_frame_window) pframeApp = get_document()->get_typed_view < ::bergedge::pane_view >()->get_view_uie();
         if(pframeApp != NULL)
         {
            pframeApp->WfiFullScreen();
         }
         sp(::simple_frame_window) pframe = get_document()->get_typed_view < ::bergedge::pane_view >()->GetParentFrame();
         if(pframe != NULL)
         {
            pframe->ShowWindow(SW_SHOW);
         }
      }
      else
      {
         if(get_document() != NULL && get_document()->get_typed_view < ::bergedge::view >() != NULL)
         {
            sp(::simple_frame_window) pframe = get_document()->get_typed_view < ::bergedge::view >()->GetParentFrame();
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

      if(m_pappCurrent != NULL && m_pappCurrent->m_pbasesession->m_pfontopus->m_puser != NULL)
      {
         try
         {
            get_view()->GetParentFrame()->SetWindowText(m_pappCurrent->m_pbasesession->m_pfontopus->m_puser->m_strLogin);
         }
         catch(...)
         {
         }
      }

   }


   sp(::bergedge::document) platform::get_document()
   {
      return m_pbergedgedocument;
   }

   sp(::bergedge::view) platform::get_view()
   {
      if(get_document() == NULL)
         return NULL;
      return get_document()->get_bergedge_view();
   }

   sp(::platform::document) platform::get_platform()
   {
      return m_pplatformdocument;
   }

   sp(::nature::document) platform::get_nature()
   {
      return m_pnaturedocument;
   }


   bool platform::InitializeLocalDataCentral()
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

   void platform::on_exclusive_instance_conflict(EExclusiveInstance eexclusive)
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


   /*void platform::request_application(const char * pszId, var varFile, var varQuery, application_bias * pbiasCreate)
   {

   ::core::application_request request;

   request.m_iEdge         = m_iEdge;
   request.m_strApp        = pszId;
   request.m_varFile       = varFile;
   request.m_varQuery      = varQuery;
   request.m_pbiasCreate   = pbiasCreate;

   request_application(&request);

   }*/

   sp(::aura::application) platform::application_get(const char * pszType, const char * pszId, bool bCreate, bool bSynch, application_bias * pbiasCreate)
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



   void platform::check_topic_file_change()
   {
      if(m_varCurrentViewFile != m_varTopicFile && !m_varTopicFile.is_empty())
      {
         m_varCurrentViewFile = m_varTopicFile;
         request_topic_file();
      }
   }

   sp(::user::interaction) platform::get_request_parent_ui(sp(::user::interaction) pinteraction, sp(::create_context) pcreatecontext)
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




      ::core::application & app = App(pinteraction->get_app());

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

   ::user::place_holder_ptra platform::get_place_holder(sp(::user::frame_window) pmainframe, sp(::create_context) pcreatecontext)
   {

      UNREFERENCED_PARAMETER(pcreatecontext);

      ::user::place_holder_ptra holderptra;


      ::core::application & app = App(pmainframe->get_app());

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

   bool platform::place(sp(::user::main_frame) pmainframe, sp(::create_context) pcreatecontext)
   {

      get_place_holder(pmainframe, pcreatecontext).hold(pmainframe);

      return true;

   }

   ::count platform::get_monitor_count()
   {

      if(get_document() != NULL && get_view() != NULL)
      {
         
         return 1;

      }
      else
      {

         return ::core::platform::get_monitor_count();

      }

   }


   bool platform::get_monitor_rect(index iMonitor, LPRECT lprect)
   {
      
      if(get_document() != NULL && get_view() != NULL)
      {
         
         get_view()->GetWindowRect(lprect);

         return true;

      }
      else
      {

         return ::core::platform::get_monitor_rect(iMonitor, lprect);

      }

   }



   void platform::set_app_title(const char * pszType, const char * pszAppId, const char * pszTitle)
   {

      sp(::aura::application) papp = NULL;

      if(m_pbasesession->m_mapApplication.Lookup(string(pszType) + ":" + string(pszAppId), papp) && papp != NULL)
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



   sp(::core::platform) platform::get_session()
   {

      return this;

   }
   
   

   bool platform::is_serviceable()
   {


      return ::platform::application::is_serviceable();


   }


   bool platform::on_uninstall()
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


   bool platform::os_native_bergedge_start()
   {

      return ::platform::application::os_native_bergedge_start();

   }


   service_base * platform::allocate_new_service()
   {


      return ::platform::application::allocate_new_service();


   }


   ::visual::cursor * platform::get_cursor()
   {
      
      if(m_pbasesession->m_ecursor == ::visual::cursor_none)
         return NULL;
      else if(m_pbasesession->m_ecursor == ::visual::cursor_default)
         return System.visual().get_cursor(m_pbasesession->m_ecursorDefault);
      else
         return System.visual().get_cursor(m_pbasesession->m_ecursor);

   }


   ::visual::cursor * platform::get_default_cursor()
   {
      
      return System.visual().get_cursor(m_pbasesession->m_ecursorDefault);

   }


   int32_t platform::main()
   {


      return ::platform::application::main();


   }

   /*   ::core::filehandler::handler & system::filehandler()
   {
   return *m_spfilehandler;
   }*/



   void platform::register_bergedge_application(sp(::aura::application) papp)
   {

      retry_single_lock rsl(m_pmutex,millis(84),millis(84));

      if(papp.is_null() || papp->m_pcoreapp == NULL)
         return;

      Session.m_appptra.add_unique(papp.m_p);

      if(System.is_installing() || System.is_uninstalling())
         System.m_bDoNotExitIfNoApplications = false;
      else if(!papp->is_session()
         && !papp->is_system()
         && !papp->is_serviceable())
      {

         System.m_bDoNotExitIfNoApplications = false;

      }

   }

   void platform::unregister_bergedge_application(sp(::aura::application) papp)
   {

      retry_single_lock rsl(m_pmutex,millis(84),millis(84));

      Session.m_appptra.remove(papp);

   }


   sp(::aura::application) platform::get_new_app(sp(::aura::application) pappNewApplicationParent,const char * pszType,const char * pszAppId)
   {

      string strId(pszAppId);

      string strApplicationId;

      if(strId == "app/core/bergedge")
      {

         strApplicationId = "bergedge";

      }
      else if(strId == "app/core/system")
      {

         strApplicationId = "system";

      }
      else
      {

         strApplicationId = strId;

      }


      string strBuildNumber = System.command()->m_varTopicQuery["build_number"];

      if(strBuildNumber.is_empty())
      {

         strBuildNumber = "latest";

      }

#ifdef CUBE

      // Criar novo meio de instalação

#elif !defined(METROWIN)

      if(!System.directrix()->m_varTopicQuery.has_property("install")
         && !System.directrix()->m_varTopicQuery.has_property("uninstall")
         && strId.has_char()
         && !System.install().is(NULL,strBuildNumber,pszType,strApplicationId,m_strLocale,m_strSchema))
      {

         throw not_installed(get_app(),NULL,strBuildNumber,pszType,strApplicationId,m_strLocale,m_strSchema);

      }

#endif

      ::aura::library library(pappNewApplicationParent,0,NULL);

#ifdef CUBE

      string strLibrary = pszAppId;

      strLibrary.replace("/","_");
      strLibrary.replace("-","_");


#else

      string strLibrary = System.m_mapAppLibrary[pszAppId];

      if(strLibrary.is_empty())
      {

         throw not_installed(get_app(),NULL,strBuildNumber,pszType,strApplicationId,m_strLocale,m_strSchema);

      }

#endif

      sp(::aura::application) papp = NULL;

      if(!library.open(strLibrary,false,false))
         return NULL;

      if(!library.open_ca2_library())
         return NULL;

      papp = library.get_new_app(pszAppId);

      if(papp == NULL)
         return NULL;

      sp(::aura::application) pgenapp = (papp);

      pgenapp->m_pcoreapp->m_strAppId = pszAppId;
      
      pgenapp->m_paurasystem = m_paurasystem;

      pgenapp->m_paxissystem = m_paxissystem;

      pgenapp->m_pbasesystem = m_pbasesystem;

      pgenapp->m_pcoresystem = &System;

      pgenapp->m_pcoreplatform = m_pcoreplatform;

#ifdef WINDOWS

      pgenapp->m_hinstance = m_hinstance;

#endif

      //pgenapp->construct(NULL);

      return papp;

   }


   sp(::core::platform) platform::query_bergedge()
   {

      sp(::core::platform) psession = NULL;

      if(System.m_pbergedgemap == NULL)
         return NULL;

      if(!System.m_pbergedgemap->Lookup(0,psession))
      {
         return NULL;
      }

      return psession;

   }

} // namespace plane



