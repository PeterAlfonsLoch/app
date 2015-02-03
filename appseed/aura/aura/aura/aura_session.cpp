//#include "framework.h"



namespace aura
{


   session::session(::aura::application * papp):
      element(papp),
      ::thread(papp)
   {

      m_psockets = NULL;

      m_paurasession    = this;

      m_bMatterFromHttpCache = m_paurasystem->m_bMatterFromHttpCache;

#ifdef WINDOWS

      if(m_hinstance == NULL)
      {

         m_hinstance = m_pauraapp->m_hinstance;

      }

#endif

      m_psavings                 = canew(class ::aura::savings(this));

      m_bZipIsDir                = true;

      m_paurasystem->m_basesessionptra.add_unique(this);


      m_iEdge                    = 0;
      m_bShowPlatform            = false;
      m_pappCurrent              = NULL;


   }


   void session::construct(::aura::application * papp,int iPhase)
   {

   }


   session::~session_parent
   {

      m_paurasystem->m_basesessionptra.remove(this);

      POSITION pos = m_mapApplication.get_start_position();

      string strId;

      sp(::aura::application) pbaseapp;

      while(pos != NULL)
      {

         strId.Empty();

         pbaseapp = NULL;

         m_mapApplication.get_next_assoc(pos,strId,pbaseapp);

         ::aura::application * papp = (pbaseapp);

         papp->post_thread_message(WM_QUIT);

      }

   }


      bool session::is_session()
   {

      return true;

   }


   sp(::aura::application) session::start_application(const char * pszType,const char * pszAppId,sp(::create) pcreatecontext)
   {

      return m_pplatform->start_application(pszType,pszAppId,pcreatecontext);

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

      if(!::aura::application::process_initialize())
         return false;


      m_puserstrcontext = canew(::aura::str_context(this));

      if(m_puserstrcontext == NULL)
         return false;


      return true;

   }


   bool session::initialize1()
   {

      if(!::aura::application::initialize1())
         return false;





      return true;

   }


   bool session::initialize2()
   {

      if(!::aura::application::initialize2())
         return false;

      return true;

   }



   bool session::initialize_instance()
   {




      if(!::aura::application::initialize_instance())
         return false;


      return true;

   }


   bool session::initialize()
   {

      if(!::aura::application::initialize())
         return false;


      return true;

   }


   bool session::finalize()
   {

      bool bOk = true;


      try
      {

         bOk = ::aura::application::finalize();

      }
      catch(...)
      {

         bOk = false;
      }

      return bOk;

   }


   int32_t session::exit_instance()
   {


      ::aura::application::exit_instance();

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


   //::aura::interaction * session::get_active_guie()
   //{

   //   return NULL;

   //}


   //::aura::interaction * session::get_focus_guie()
   //{


   //   return NULL;

   //}




   bool session::is_licensed(const char * pszId,bool bInteractive)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   void session::on_request(sp(::create) pcreatecontext)
   {

      TRACE("::core::platform::on_request(sp(::create))");


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

               ::aura::application * papp = (application_get(strType,strApp,true,true,pcreatecontext->m_spCommandLine->m_pbiasCreate));
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

                  pcreatecontext->m_spCommandLine->m_varQuery["bergedge_callback"] = dynamic_cast < ::aura::application * > (this);

                  papp->m_pauraapp->post_thread_message(dw,2,pcreatecontext);

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
            //          ::exception::throw_not_implemented(get_app());
            /*if(get_document() != NULL && get_document()->get_typed_view < ::platform::aura::impact >() != NULL)
            {
            sp(::simple_frame_window) pframe =  (get_document()->get_typed_view < ::platform::aura::impact >()->GetParentFrame());
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

   sp(::aura::application) session::application_get(const char * pszType,const char * pszId,bool bCreate,bool bSynch,application_bias * pbiasCreate)
   {

      sp(::aura::application) papp = NULL;

      if(m_paurasession->m_mapApplication.Lookup(string(pszType) + ":" + string(pszId),papp))
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

         m_paurasession->m_mapApplication.set_at(string(pszType) + ":" + string(pszId),papp);

         return papp;

      }

   }


   sp(::aura::application) session::get_new_app(sp(::aura::application) pappNewApplicationParent,const char * pszType,const char * pszAppId)
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

      ::aura::library library(pappNewApplicationParent,0,NULL);

#if defined(METROWIN)
      string strLibrary = pszAppId;

      strLibrary.replace("/","_");
      strLibrary.replace("-","_");

#else
#ifdef CUBE

      string strLibrary = pszAppId;

      strLibrary.replace("/","_");
      strLibrary.replace("-","_");


#else

      string strLibrary = System.m_mapAppLibrary[pszAppId];

      if(strLibrary.is_empty())
      {

         System.find_applications_to_cache(false);

         strLibrary = System.m_mapAppLibrary[pszAppId];

         if(strLibrary.is_empty())
         {

            if(System.directrix()->m_varTopicQuery.has_property("uninstall") &&
               System.directrix()->m_varTopicQuery["app"] == strApplicationId)
               return NULL;

            throw not_installed(get_app(),System.install_get_version(),strBuildNumber,pszType,strApplicationId,Session.m_strLocale,Session.m_strSchema);

         }

      }

#endif
#endif
      ::aura::application * papp = NULL;

      if(!library.open(strLibrary,false,false))
         return NULL;

      if(!library.open_ca2_library())
         return NULL;

      papp = library.get_new_app(pszAppId);

      WCHAR wsz[1024];

      DWORD dwSize = sizeof(wsz) / sizeof(WCHAR);


#ifdef WINDOWSEX

      GetUserNameW(wsz,&dwSize);

      string strUserName = wsz;

#endif // WINDOWSEX


#ifndef METROWIN


      if(((!System.directrix()->m_varTopicQuery.has_property("install")
         && !System.directrix()->m_varTopicQuery.has_property("uninstall"))
         ) //         || (papp->is_serviceable() && !papp->is_user_service() && strUserName != "NetworkService"))
         && strId.has_char()
         && !System.install_is(System.install_get_version(),strBuildNumber,pszType,strApplicationId,Session.m_strLocale,Session.m_strSchema))
      {

         throw not_installed(papp,System.install_get_version(),strBuildNumber,pszType,strApplicationId,Session.m_strLocale,Session.m_strSchema);

      }

#endif

      if(!papp->is_serviceable() || papp->is_user_service())
      {

         System.m_spmutexUserAppData = canew(mutex(m_paurasystem,false,"Local\\ca2.UserAppData"));
         System.m_spmutexSystemAppData = canew(mutex(m_paurasystem,false,"Local\\ca2.SystemAppData"));

      }


      if(papp == NULL)
         return NULL;

      sp(::aura::application) pgenapp = (papp);

      if(pgenapp->m_strAppId.is_empty())
      {

         pgenapp->m_strAppId = pszAppId;

      }

      pgenapp->m_paurasystem = m_paurasystem;

      pgenapp->m_paxissystem = m_paxissystem;

      pgenapp->m_pbasesystem = m_pbasesystem;

      pgenapp->m_pcoresystem = m_pcoresystem;

      pgenapp->m_pcoreplatform = m_pcoreplatform;

      pgenapp->m_pplatform = m_pplatform;

#ifdef WINDOWS

      pgenapp->m_hinstance = m_hinstance;

#endif

      //pgenapp->construct(NULL);

      return papp;

   }


} // namespace aura
































