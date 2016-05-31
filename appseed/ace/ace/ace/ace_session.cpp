//#include "framework.h"



namespace ace
{


   session::session(::ace::application * papp):
      object(papp),
      ::thread(papp)
   {

      m_pappCurrent = NULL;

      m_psockets = NULL;

      m_pacesession    = this;

      m_bMatterFromHttpCache = m_pacesystem->m_bMatterFromHttpCache;

#ifdef WINDOWS

      if(m_hinstance == NULL)
      {

         m_hinstance = m_paceapp->m_hinstance;

      }

#endif

      m_psavings                 = canew(class ::ace::savings(this));

      m_bZipIsDir                = true;

//      m_pacesystem->m_basesessionptra.add_unique(this);


      m_iEdge                    = 0;
      m_bShowPlatform            = false;
      m_pappCurrent              = NULL;


   }


   void session::construct(::ace::application * papp,int iPhase)
   {

   }


   session::~session_parent
   {


   }


      bool session::is_session()
   {

      return true;

   }


   sp(::ace::application) session::start_application(const char * pszType,const char * pszAppId,sp(::create) pcreatecontext)
   {

      string strApp(pszAppId);

      sp(::ace::application) papp = application_get(pszType,strApp,true,true,pcreatecontext->m_spCommandLine->m_pbiasCreate);
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

         papp->post_thread_message(uiMessage,2,pcreatecontext);

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

      Session.m_appptra.add(papp);

      return papp;

   }






   COLORREF session::get_default_color(uint64_t ui)
   {

      switch(ui)
      {
      case COLOR_3DFACE:
         return ARGB(127,192,192,184);
      case COLOR_WINDOW:
         return ARGB(127,255,255,255);
      case COLOR_3DLIGHT:
         return ARGB(127,218,218,210);
      case COLOR_3DHIGHLIGHT:
         return ARGB(127,238,238,230);
      case COLOR_3DSHADOW:
         return ARGB(127,138,138,130);
      case COLOR_3DDKSHADOW:
         return ARGB(127,84,84,77);
      default:
         break;
      }

      return ARGB(127,0,0,0);

   }






   bool  session::get_window_minimum_size(LPSIZE lpsize)
   {

      lpsize->cx = 184 + 177;

      lpsize->cy = 184 + 177;

      return true;

   }




   bool session::process_initialize()
   {

      if(!::ace::application::process_initialize())
         return false;


      m_puserstrcontext = canew(::ace::str_context(this));

      if(m_puserstrcontext == NULL)
         return false;


      return true;

   }


   bool session::initialize1()
   {

      if(!::ace::application::initialize1())
         return false;





      return true;

   }


   bool session::initialize2()
   {

      if(!::ace::application::initialize2())
         return false;

      return true;

   }



   bool session::initialize_instance()
   {




      if(!::ace::application::initialize_instance())
         return false;


      return true;

   }


   bool session::initialize()
   {

      if(!::ace::application::initialize())
         return false;


      return true;

   }


   bool session::finalize()
   {

      bool bOk = true;


      try
      {

         bOk = ::ace::application::finalize();

      }
      catch(...)
      {

         bOk = false;
      }

      return bOk;

   }


   int32_t session::exit_instance()
   {


      ::ace::application::exit_instance();

      return 0;

   }


   application_ptra & session::appptra()
   {

      return m_appptra;

   }

   //// only usable from base.dll and dependants
   //::sockets::sockets & session::sockets()
   //{ 

   //   throw interface_only_exception(get_app());
   //   
   //   return *((::sockets::sockets *) NULL); // only usable from base.dll and dependants
   //
   //}








   void session::frame_pre_translate_message(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

   }




   



   bool session::is_licensed(const char * pszId,bool bInteractive)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   void session::on_request(sp(::create) pcreatecontext)
   {

      TRACE("::ace::session::on_request(sp(::create)) " + demangle(typeid(*this).name()));

      ::output_debug_string("::ace::session::on_request(sp(::create)) " + THIS_FRIENDLY_NAME());

      if(pcreatecontext->m_spCommandLine->m_varQuery["app"].array_get_count() > 1)
      {
         start_application("application",pcreatecontext->m_spCommandLine->m_varQuery["app"].stra()[0],pcreatecontext);
         return;
      }

      string strApp = pcreatecontext->m_spCommandLine->m_strApp;

      if(strApp == "app/sphere/userstack")
      {
         start_application("application","app/sphere/userstack",pcreatecontext);
         return;
      }

      //      if(m_pbergedgeInterface != NULL)
      {


         m_varCurrentViewFile = pcreatecontext->m_spCommandLine->m_varFile;


         string strApp;
         string strType;

         if((pcreatecontext->m_spCommandLine->m_varQuery["app"].array_get_count() > 1
            || pcreatecontext->m_spCommandLine->m_varQuery["show_platform"] == 1 || command()->m_varTopicQuery["show_platform"] == 1)
            && (!(bool)pcreatecontext->m_spCommandLine->m_varQuery.has_property("client_only") && !(bool)command()->m_varTopicQuery.has_property("client_only"))
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
               //create_bergedge(pcreatecontext);
               //if(get_document() != NULL && get_document()->get_typed_view < ::bergedge::view >() != NULL)
               //{
               //   sp(::simple_frame_window) pframe =  (get_document()->get_typed_view < ::bergedge::view >()->GetParentFrame());
               //   if(pframe != NULL)
               //   {
               //      pframe->ShowWindow(SW_SHOW);
               //      pframe->InitialFramePosition();
               //   }
               //}
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


            if(pcreatecontext->m_spCommandLine->m_varQuery["app"].stra().find_first_ci(strApp) < 0)
            {

               pcreatecontext->m_spCommandLine->m_varQuery["app"].stra().insert_at(0,strApp);
               pcreatecontext->m_spCommandLine->m_varQuery["app_type"].stra().insert_at(0,strType);

            }

            for(int32_t i = 0; i < pcreatecontext->m_spCommandLine->m_varQuery["app"].stra().get_count(); i++)
            {

               strApp = pcreatecontext->m_spCommandLine->m_varQuery["app"].stra()[i];
               if(i < pcreatecontext->m_spCommandLine->m_varQuery["app_type"].stra().get_count())
                  strType = pcreatecontext->m_spCommandLine->m_varQuery["app_type"].stra()[i];
               else
                  strType.Empty();


               //simple_message_box(NULL, "create", strApp, MB_ICONEXCLAMATION);

               if(strApp.is_empty() || strApp == "bergedge")
               {

                  return;

               }

               if(strApp == "session")
               {

                  continue;

               }

               if(strType.is_empty())
                  strType = "application";

               ::ace::application * papp = (application_get(strType,strApp,true,true,pcreatecontext->m_spCommandLine->m_pbiasCreate));
               if(papp == NULL)
                  return;

               //simple_message_box(NULL, "appok", strApp, MB_ICONEXCLAMATION);

               //if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("install")
               //   || pcreatecontext->m_spCommandLine->m_varQuery.has_property("uninstall"))
               //{
               //   continue;
               //}

               pcreatecontext->m_spCommandLine->m_eventReady.ResetEvent();

               if(strApp != "bergedge")
               {


                  //pcreatecontext->m_spCommandLine->m_varQuery["bergedge_callback"] = dynamic_cast < ::ace::application * > (this);

                  papp->m_paceapp->command()->command(pcreatecontext);
 
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
         && (!(bool)pcreatecontext->m_spCommandLine->m_varQuery.has_property("client_only") && !(bool)command()->m_varTopicQuery.has_property("client_only"))
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
            //          ::exception::throw_not_implemented(get_app());
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
         else if(pcreatecontext->m_spCommandLine->m_varQuery["app"].stra().get_count() > 1)
         {
            start_application("application","app/core/bergedge",pcreatecontext);
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
                  //System.planesessionptra().remove(this);
                  return;
               }
               return;
            }

            if(strType.is_empty())
            {
               strType = "application";
            }

            start_application(strType,strApp,pcreatecontext);

         }

      }

   }

   bool session::open_by_file_extension(const char * pszPathName,application_bias * pbiasCreate)
   {
      
      return Application.platform_open_by_file_extension(m_iEdge,pszPathName,pbiasCreate);

   }


   bool session::open_by_file_extension(::create * pcc)
   {

      return Application.platform_open_by_file_extension(m_iEdge,pcc);

   }

   ::ace::application * session::application_get(const char * pszType,const char * pszId,bool bCreate,bool bSynch,application_bias * pbiasCreate)
   {

      ::ace::application * papp = NULL;

      if(m_pacesession->m_mapApplication.Lookup(string(pszType) + ":" + string(pszId),papp))
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

            papp = create_application(pszType,pszId,bSynch,pbiasCreate);

         }
         catch(::exit_exception & e)
         {

            throw e;

         }
         catch(::exception::exception & e)
         {

            // ace::session, axis::session and ::base::session, could get more specialized handling in core::application (core::system)
            // Thank you Mummi (em São Paulo, cuidando do Lucinho e ajudando um monte a Carô 2015-02-03) !! Thank you God!!
            if(!Sys(this).on_run_exception(e)) 
            {
               if(!App(this).on_run_exception(e))
               {
                  throw exit_exception(get_app());
               }
            }

         }
         catch(...)
         {

            papp = NULL;

         }

         if(papp == NULL)
            return NULL;

         if(&App(papp) == NULL)
         {

            ::ace::del(papp);

            return NULL;

         }

         m_pacesession->m_mapApplication.set_at(string(pszType) + ":" + string(pszId),papp);

         return papp;

      }

   }


   ::ace::application * session::get_new_app(::ace::application * pappNewApplicationParent,const char * pszType,const char * pszAppId)
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

         strBuildNumber = "installed";

      }

#ifdef CUBE

      // Criar novo meio de instalação

#elif !defined(METROWIN)


#endif
      
#if !defined(METROWIN) && !defined(VSNORD) && !defined(APPLE_IOS)
      
      
      if(((!System.directrix()->m_varTopicQuery.has_property("install")
           && !System.directrix()->m_varTopicQuery.has_property("uninstall"))
          ) //         || (papp->is_serviceable() && !papp->is_user_service() && strUserName != "NetworkService"))
         && strId.has_char()
         && !System.install_is(System.install_get_version(),strBuildNumber,pszType,strApplicationId,Session.m_strLocale,Session.m_strSchema))
      {
         
         throw not_installed(get_app(),System.install_get_version(),strBuildNumber,pszType,strApplicationId,Session.m_strLocale,Session.m_strSchema);
         
      }
      
#endif

      
      ::ace::library library(pappNewApplicationParent,0,NULL);
      
      string strLibrary = pszAppId;

      strLibrary.replace("/","_");
      
      strLibrary.replace("-","_");
        
      ::output_debug_string("\n\n::ace::session::get_new_app assembled library path " + strLibrary + "\n\n");
         
      if(!library.open(strLibrary,false))
      {

#ifdef METROWIN

         simple_message_box(NULL,"where's the application DLL?", MB_OK);

#else

         if(System.directrix()->m_varTopicQuery.has_property("uninstall") &&
            System.directrix()->m_varTopicQuery["app"] == strApplicationId)
            return NULL;
            
         ::output_debug_string("\n\nSystem.find_applications_to_cache Failed(3) " + string(pszAppId) + "\n\n");

         throw not_installed(get_app(),System.install_get_version(),strBuildNumber,pszType,strApplicationId,Session.m_strLocale,Session.m_strSchema);
#endif

      }
            
      ::output_debug_string("\n\n::ace::session::get_new_app Found library : " + strLibrary + "\n\n");
      
      if(!library.is_opened())
      {
         
         ::output_debug_string("\n\n::ace::session::get_new_app Failed to load library : " + strLibrary + "\n\n");
         
         return NULL;
         
      }

      ::output_debug_string("\n\n::ace::session::get_new_app Opened library : " + strLibrary + "\n\n");
      
      if(!library.open_ca2_library())
      {
         
         ::output_debug_string("\n\n::ace::session::get_new_app open_ca2_library failed(2) : " + strLibrary+ "\n\n");
         
         return NULL;
         
      }

      ::output_debug_string("\n\n\n|(5)----");
      ::output_debug_string("| app : " + strApplicationId + "\n");
      ::output_debug_string("|\n");
      ::output_debug_string("|\n");
      ::output_debug_string("|----");

      sp(::ace::application) papp = library.get_new_app(pszAppId);
      
      ::output_debug_string("\n\n\n|(4)----");
      ::output_debug_string("| app : " + strApplicationId + "(papp="+::str::from(papp)+")\n");
      ::output_debug_string("|\n");
      ::output_debug_string("|\n");
      ::output_debug_string("|----");
      

#ifdef WINDOWSEX

      WCHAR wsz[1024];

      DWORD dwSize = sizeof(wsz) / sizeof(WCHAR);

      GetUserNameW(wsz,&dwSize);

      string strUserName = wsz;

#endif // WINDOWSEX

      ::output_debug_string("\n\n\n|(3)----");
      ::output_debug_string("| app : " + strApplicationId + "\n");
      ::output_debug_string("|\n");
      ::output_debug_string("|\n");
      ::output_debug_string("|----");



      ::output_debug_string("\n\n\n|(2)----");
      ::output_debug_string("| app : " + strApplicationId + "\n");
      ::output_debug_string("|\n");
      ::output_debug_string("|\n");
      ::output_debug_string("|----");

#if !defined(VSNORD)

      if(!papp->is_serviceable() || papp->is_user_service())
      {

         System.m_spmutexUserAppData = canew(mutex(m_pacesystem,false,"Local\\ca2.UserAppData"));
         System.m_spmutexSystemAppData = canew(mutex(m_pacesystem,false,"Local\\ca2.SystemAppData"));

      }

#endif

      if(papp == NULL)
         return NULL;
      
      ::output_debug_string("\n\n\n|(1)----");
      ::output_debug_string("| app : " + strApplicationId + "\n");
      ::output_debug_string("|\n");
      ::output_debug_string("|\n");
      ::output_debug_string("|----");

      sp(::ace::application) pgenapp = (papp);

      if(pgenapp->m_strAppId.is_empty())
      {

         pgenapp->m_strAppId = pszAppId;

      }

      pgenapp->m_pacesystem = m_pacesystem;

      pgenapp->m_paxissystem = m_paxissystem;

      pgenapp->m_pbasesystem = m_pbasesystem;

      pgenapp->m_pcoresystem = m_pcoresystem;

      pgenapp->m_pcoresession = m_pcoresession;

#ifdef WINDOWS

      pgenapp->m_hinstance = m_hinstance;

#endif

      //pgenapp->construct(NULL);

      return papp;

   }



   void session::request_create(sp(::create) pcreatecontext)
   {
      
            //      if(m_pbergedgeInterface != NULL)
            {
      
               if(m_pappCurrent != NULL && m_pappCurrent != this
                  && (pcreatecontext->m_spCommandLine->m_strApp.is_empty()
                  ||App(m_pappCurrent).m_strAppName == pcreatecontext->m_spCommandLine->m_strApp))
               {
                  //if(get_document() != NULL && get_document()->get_typed_view < ::bergedge::pane_view >() != NULL)
                  //{
                  //   get_document()->get_typed_view < ::bergedge::pane_view >()->set_cur_tab_by_id("app:" + App(m_pappCurrent).m_strAppName);
                  //}
                  App(m_pappCurrent).request_create(pcreatecontext);
                  //if(pcreatecontext->m_spCommandLine->m_varQuery["document"].cast < ::user::document > () == NULL)
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
                     //else if(pcreatecontext->m_spCommandLine->m_strApp.has_char()
                     //   && get_document() != NULL
                     //   && get_document()->get_typed_view < ::bergedge::pane_view >() != NULL)
                     //{
                     //   get_document()->get_typed_view < ::bergedge::pane_view >()->set_cur_tab_by_id("app:" + pcreatecontext->m_spCommandLine->m_strApp);
                     //   App(m_pappCurrent).request_create(pcreatecontext);
                     //}
                     else
                     {
                        on_request(pcreatecontext);
                        return;
                     }
                  }
                  //else if(pcreatecontext->m_spCommandLine->m_strApp.has_char() &&
                  //   get_document() != NULL && get_document()->get_typed_view < ::bergedge::pane_view >() != NULL
                  //   && (!pcreatecontext->m_spApplicationBias.is_set() || pcreatecontext->m_spApplicationBias->m_puiParent == NULL))
                  //{
                  //   //simple_message_box(NULL, "request3", "request3", MB_ICONEXCLAMATION);
                  //   get_document()->get_typed_view < ::bergedge::pane_view >()->set_cur_tab_by_id("app:" + pcreatecontext->m_spCommandLine->m_strApp);
                  //   App(m_pappCurrent).request_create(pcreatecontext);
                  //}
                  //else
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


   ::visual::cursor * session::get_cursor()
   {

      return NULL;

   }


   ::visual::cursor * session::get_default_cursor()
   {

      return NULL;

   }


} // namespace ace
































