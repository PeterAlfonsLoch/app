#include "framework.h"



#if defined(LINUX) || defined(MACOS)
#include <dlfcn.h>
#endif



namespace plane
{
   void trace_progress(index iStep);
   void progress();


   application::application() :
      m_simpledb(this)
   {

      m_pbaseapp      = this;
      m_pplaneapp  = this;


      m_bIfs            = true;



   }

/*   application::application(const char * pszId)
   {


      m_pbaseapp      = this;
      m_pplaneapp  = this;

      construct(pszId);

   }*/

   void application::construct(const char *pszId)
   {
      //if(m_strAppName.has_char())
      //   return;
      //m_strAppName.Empty();
      //m_strId.Empty();
      if(pszId == NULL)
      {
#ifdef WINDOWSEX
         wstring wstr = ::GetCommandLineW();
         string str = ::str::international::unicode_to_utf8(wstr);
         strsize iFind = str.find(" : ");
         if(iFind >= 0)
         {
            iFind = str.find("app=", iFind);
            if(iFind >= 0)
            {
               strsize iEnd = str.find(" ", iFind);
               if(iEnd < 0)
               {
                  m_strId = str.Mid(iFind + 4);
               }
               else
               {
                  m_strId = str.Mid(iFind + 4, iEnd - iFind - 4);
               }
               ::str::begins_eat(m_strId, "\"");
               ::str::ends_eat(m_strId, "\"");
            }
         }
#endif
      }
      else
      {
         m_strId = pszId;
      }
      if(m_strId.is_empty())
         m_strId = "mplite";
      construct();
      if(m_strAppName.is_empty())
      {
         if(m_strAppId.has_char())
            m_strAppName = m_strAppId;
         else if(m_strInstallToken.has_char())
            m_strAppName = m_strInstallToken;
      }
   }

   application::~application()
   {
   }

   sp(base_application) application::get_system()
   {
      return new application();
   }

   void application::construct()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }

      ::application::construct();

   }




   void application::_001OnFileNew()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      ::application::_001OnFileNew(NULL);
   }


   bool application::bergedge_start()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      return ::application::bergedge_start();
   }



   bool application::on_install()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      return ::application::on_install();
   }

   bool application::on_uninstall()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      return ::application::on_uninstall();
   }


   void application::on_request(sp(::create_context) pcreatecontext)
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      return ::application::on_request(pcreatecontext);


   }

   bool application::is_serviceable()
   {


      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      return ::application::is_serviceable();
   }



   sp(::user::object) application::_001OpenDocumentFile(var varFile)
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      return ::application::_001OpenDocumentFile(varFile);

   }


   int32_t application::run()
   {

      if((command()->m_varTopicQuery.has_property("install")
      || command()->m_varTopicQuery.has_property("uninstall"))
      &&
      ((is_session() && command()->m_varTopicQuery["session_start"] == "session")))
      {
      }
      else if(!is_system() && !is_session())
      {
         if(command()->m_varTopicQuery.has_property("install")
         || command()->m_varTopicQuery.has_property("uninstall"))
         {

         }
         else if(command()->m_varTopicQuery.has_property("service"))
         {
            create_new_service();
            ::service_base::serve(*m_pservice);
         }
         else if(command()->m_varTopicQuery.has_property("run") || is_serviceable())
         {
            create_new_service();
            m_pservice->Start(0);
            return ::application::run();
         }
         else
         {
            return ::application::run();
         }
      }
      else
      {
         return ::application::run();
      }

      return 0;

   }




   sp(::plane::application) application::assert_running(const char * pszAppId)
   {


      sp(::plane::application) papp = NULL;


      try
      {

         bool bFound = false;

         for(int32_t i  = 0; i < System.m_appptra.get_count(); i++)
         {
            try
            {

               papp = System.m_appptra(i);

               if(papp->m_pplaneapp->m_strAppName == pszAppId)
               {
                  bFound = true;
                  break;
               }

            }
            catch(...)
            {
            }

         }

         bool bCreate = !bFound;

         if(bFound)
         {

            bool bRunning = false;

            try
            {
               if(papp->m_pplaneapp->is_running())
               {
                  bRunning = true;
               }
            }
            catch(...)
            {
            }

            if(!bRunning)
            {

               try
               {
                  papp->m_pplaneapp->post_thread_message(WM_QUIT);
               }
               catch(...)
               {
               }
               try
               {
                  papp.release();
               }
               catch(...)
               {
               }

               bCreate = true;

            }


         }

         if(bCreate)
         {

            sp(::create_context) spcreatecontext(allocer());

            papp = Session.start_application("application", pszAppId, spcreatecontext);

         }

      }
      catch(const ::exit_exception & e)
      {

         throw e;

      }
      catch(const ::exception::exception & e)
      {

         if(!Application.on_run_exception((::exception::exception &) e))
            throw exit_exception(get_app());

      }
      catch(...)
      {

         papp = NULL;

      }


      return papp;

   }





typedef  void (* PFN_ca2_factory_exchange)(sp(base_application) papp);




   ::file::binary_buffer_sp application::friendly_get_file(var varFile, UINT nOpenFlags)
   {

      try
      {

         return m_file.get_file(varFile, nOpenFlags);

      }
      catch(::file::exception & e)
      {

         string strMessage = e.get_message();

         App(this).simple_message_box(NULL, strMessage, MB_OK);

         return NULL;

      }

   }




   ::user::user * application::create_user()
   {

      return canew(::user::user(this));

   }


   ::userex::userex * application::create_userex()
   {

      return canew(::userex::userex(this));

   }


   ::userfs::userfs * application::create_userfs()
   {

      return canew(::userfs::userfs(this));

   }


   ::html::html * application::create_html()
   {

      return canew(::html::html(this));

   }



   bool application::is_installing()
   {

      return directrix()->has_property("install");

   }


   bool application::is_uninstalling()
   {

      return directrix()->has_property("uninstall");

   }


   bool application::create_new_service()
   {

      if(m_pservice != NULL)
         return false;

      m_pservice = allocate_new_service();

      if(m_pservice == NULL)
         return false;

      return true;

   }



   bool application::create_service()
   {

      return System.os().create_service(this);

   }

   bool application::remove_service()
   {

      return System.os().remove_service(this);

   }

    bool application::start_service()
   {

      return System.os().start_service(this);

   }

   bool application::stop_service()
   {

      return System.os().stop_service(this);

   }


   void application::on_service_request(sp(::create_context) pcreatecontext)
   {

      if(!is_serviceable())
         return;

      if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("create_service"))
      {
         create_service();
      }
      else if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("start_service"))
      {
         start_service();
      }
      else if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("stop_service"))
      {
         stop_service();
      }
      else if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("remove_service"))
      {
         remove_service();
      }

   }



   void application::defer_initialize_twf()
   {
      if(System.m_ptwf == NULL && (System.m_bShouldInitializeGTwf && m_bShouldInitializeGTwf && m_bInitializeProDevianMode))
      {
         System.create_twf();
      }
   }





   sp(base_application) application::instantiate_application(const char * pszType, const char * pszId, application_bias * pbias)
   {

      sp(base_application) papp = NULL;

      string strId(pszId);

      if(strId.CompareNoCase("session") == 0)
      {

         ::plane::session * psession = new ::plane::session(this);

         papp = psession;

         psession->construct();

         if(m_psystem != NULL && m_psystem->m_psession == NULL)
         {

            m_psystem->m_psession = psession;

         }

         psession->m_strAppId = "session";

      }
      else
      {

         string strNewId;

         if(strId == "bergedge")
         {

            strNewId = "app/core/bergedge";

         }
         else if(strId == "cube")
         {

            strNewId = "app/core/cube";

         }
         else
         {

            strNewId = strId;

         }

         papp = System.get_new_app(this, pszType, strNewId);

         if(papp == NULL)
            return NULL;

         papp->m_pplaneapp->m_psession                          = m_psession;
         papp->m_pplaneapp->m_pbasesession                      = m_psession;

         /*if(pbaseapp->m_bService)
         {

            App(pbaseapp).m_puiInitialPlaceHolderContainer  = NULL;

         }*/

         if(m_psystem != NULL && m_psystem->m_psession == NULL)
         {

            m_psystem->m_psession = m_psession;

         }

         if(papp != NULL)
         {

            if(strId == "bergedge"
            || strId == "cube")
            {

               papp->m_pplaneapp->m_strAppId = strId;

            }

            if(papp->m_pplaneapp->m_strInstallToken.is_empty())
            {

               papp->m_pplaneapp->m_strInstallToken = papp->m_pplaneapp->m_strAppId;

            }

         }

      }

      //pbaseapp->m_pbaseapp                               = this;
      papp->m_pplaneapp->m_psystem                             = m_psystem;

      papp->m_pbasesystem                                      = m_pbasesystem;

      papp->m_pplaneapp->command_central()->consolidate(command_central());

      papp->m_pplaneapp->m_bSessionSynchronizedCursor = m_bSessionSynchronizedCursor;

      if(pbias != NULL)
      {

         papp->m_pplaneapp->propset().merge(pbias->m_set);

      }
      else
      {

         papp->m_pplaneapp->oprop("SessionSynchronizedInput")   = true;
         papp->m_pplaneapp->oprop("NativeWindowFocus")          = true;

      }

      if((papp == NULL || papp->m_pplaneapp->m_strAppId != strId)
         &&
         (!Application.command()->m_varTopicQuery.has_property("install")
         && !Application.command()->m_varTopicQuery.has_property("uninstall")))
      {

         TRACE("Failed to instantiate %s, going to try installation through ca2_cube_install", strId);

         string strCommandLine;

         strCommandLine    =" : app=" + strId;
         strCommandLine    += " locale=" + string(Application.str_context()->m_plocaleschema->m_idLocale);
         strCommandLine    += " style=" + string(Application.str_context()->m_plocaleschema->m_idSchema);
         strCommandLine    += " install";

         System.install().start(strCommandLine);

         throw installing_exception(get_app());

         return NULL;

      }

      return papp;

   }


   sp(base_application) application::create_application(const char * pszType, const char * pszId, bool bSynch, application_bias * pbias)
   {

      sp(base_application) pbaseapp = instantiate_application(pszType, pszId, pbias);

      if(pbaseapp == NULL)
         return NULL;

      sp(base_application) papp = (pbaseapp);

      if(!papp->m_pplaneapp->start_application(bSynch, pbias))
      {
         try
         {
            pbaseapp.release();
         }
         catch(...)
         {
         }
         return NULL;
      }


      return pbaseapp;

   }


   //////////////////////////////////////////////////////////////////////////////////////////////////
   // System/System
   //
   sp(::user::object) application::place_hold(sp(::user::interaction) pui)
   {

      return NULL;

   }


   count application::get_monitor_count()
   {

      return 0;

   }

   bool application::get_monitor_rect(index i, LPRECT lprect)
   {

      return false;

   }

   count application::get_desk_monitor_count()
   {

      return 0;

   }

   bool application::get_desk_monitor_rect(index i, LPRECT lprect)
   {

      return false;

   }



      void application::set_title(const char * pszTitle)
   {

      Session.set_app_title(m_strInstallType, m_strAppName, pszTitle);

   }


//////////////////////////////////////////////////////////////////////////////////////////////////
   // Session/Session
   //
   sp(::bergedge::view) application::get_view()
   {

      return NULL;

   }

   sp(::bergedge::document) application::get_document()
   {

      return NULL;

   }



   bool application::update_appmatter(::sockets::socket_handler & h, ::sockets::http_session * & psession,const char * pszRoot, const char * pszRelative)
   {

      ::str::international::locale_schema localeschema(this);

      fill_locale_schema(localeschema);

      bool bIgnoreStdStd = string(pszRoot) == "app" && (string(pszRelative) == "main" || string(pszRelative) == "bergedge");

      //update_appmatter(h, psession, pszRoot, pszRelative, localeschema.m_idLocale, localeschema.m_idSchema);

      for(int32_t i = 0; i < localeschema.m_idaLocale.get_count(); i++)
      {
         if(localeschema.m_idaLocale[i] == __id(std) && localeschema.m_idaSchema[i] == __id(std) && bIgnoreStdStd)
            continue;
         update_appmatter(h, psession, pszRoot, pszRelative, localeschema.m_idaLocale[i], localeschema.m_idaSchema[i]);
         progress();
      }


      return true;

   }

   bool application::update_appmatter(::sockets::socket_handler & h, ::sockets::http_session * & psession,const char * pszRoot, const char * pszRelative, const char * pszLocale, const char * pszStyle)
   {

      string strLocale;
      string strSchema;
      TRACE("update_appmatter(root=%s, relative=%s, locale=%s, style=%s)", pszRoot, pszRelative, pszLocale, pszStyle);
      string strRelative = System.dir().path(System.dir().path(pszRoot, "appmatter", pszRelative), App(this).get_locale_schema_dir(pszLocale, pszStyle)) + ".zip";
      string strFile = System.dir().element(strRelative);
      string strUrl;
      if(_ca_is_basis())
      {
         strUrl = "http://basis.spaignition.api.server.ca2.cc/download?authnone&version=basis&stage=";
      }
      else
      {
         strUrl = "http://stage.spaignition.api.server.ca2.cc/download?authnone&version=stage&stage=";
      }

      strUrl += System.url().url_encode(strRelative);

      primitive::memory mem(get_app());

      if(psession == NULL)
      {

         while(true)
         {

            property_set setEmpty(get_app());

            psession = System.http().open(h, System.url().get_server(strUrl), System.url().get_protocol(strUrl), setEmpty, NULL, NULL);

            if(psession != NULL)
               break;

            Sleep(184);

         }

      }

      psession = System.http().get(h, psession, strUrl, mem);

      ::file::memory_buffer file(get_app(), &mem);

      if(mem.get_size() > 0)
      {

         zip::Util util;

         string strDir = strFile;

         ::str::ends_eat_ci(strDir, ".zip");

         try
         {

            util.extract_all(strDir, &file);

         }
         catch(...)
         {

            // spa app-install.exe would recover by retrying or someone would fix the resource packaging problem and then zip extraction at least should work.

            return false;

         }

         //System.compress().extract_all(strFile, this);

      }

      return true;

   }


   bool application::add_library(::core::library * plibrary)
   {

      plibrary->set_app(this);

      System.add_library(plibrary);

      return true;

   }


   count g_iCountProgress;
   index g_iStepProgress;

   void trace_progress(index iStep)
   {
      double dProgressStart   = 0.8;
      double dProgressEnd     = 1.0;
      double dProgress = dProgressStart + (dProgressEnd - dProgressStart) * ((double) iStep / (double) g_iCountProgress);
      ::trace_progress(dProgress);
   }

   void progress()
   {
      trace_progress(++g_iStepProgress);
   }



   bool application::initialize()
   {

      if (!::application::initialize())
         return false;

      if(!is_installing() && !is_uninstalling() && !is_system())
      {

         simpledb().set_keyboard_layout(NULL, false);

      }


/*      if(m_bIfs)
      {
		  if(m_psession != NULL && &Session != NULL)
         {
            if(m_spfsdata.is_null())
               m_spfsdata = new ::fs::set(this);
            ::fs::set * pset = dynamic_cast < ::fs::set * > ((class ::fs::data *) m_spfsdata);
            pset->m_spafsdata.add(Session.m_pifs);
            pset->m_spafsdata.add(Session.m_prfs);
            stringa stra;
            pset->root_ones(stra);
         }
      }*/

      m_dwAlive = ::get_tick_count();

      if(!is_system())
      {
         System.register_bergedge_application(this);
      }




      if(!m_spuserfs->initialize())
         return false;


      if(!m_simpledb.initialize())
         return false;


      if (!m_spuserex->initialize())
         return false;

      if (!m_phtml->initialize())
         return false;

      if(!is_system() && !is_session() &&  !is_installing() && !is_uninstalling())
      {

         string str;
         // if system locale has changed (compared to last recorded one by core)
         // use the system locale
         if(data_get("system_locale", str))
         {
            if(str.has_char())
            {
               if(str != get_locale())
               {
                  try
                  {
                     data_set("system_locale", get_locale());
                     data_set("locale", get_locale());
                  }
                  catch(...)
                  {
                  }
               }
            }
         }
         else
         {
            data_set("system_locale", get_locale());
         }

         if(command()->m_varTopicQuery["locale"].get_string().has_char())
         {
            str = command()->m_varTopicQuery["locale"];
            data_set("system_locale", str);
            data_set("locale", str);
            set_locale(str, false);
         }
         else if(command()->m_varTopicQuery["lang"].get_string().has_char())
         {
            str = command()->m_varTopicQuery["lang"];
            data_set("system_locale", str);
            data_set("locale", str);
            set_locale(str, false);
         }
         else if(data_get("locale", str))
         {
            if(str.has_char())
            {
               set_locale(str, false);
            }
         }
         // if system schema has changed (compared to last recorded one by core)
         // use the system schema
         if(data_get("system_schema", str))
         {
            if(str.has_char())
            {
               if(str != get_schema())
               {
                  try
                  {
                     data_set("system_schema", get_schema());
                     data_set("schema", get_schema());
                  }
                  catch(...)
                  {
                  }
               }
            }
         }
         else
         {
            data_set("system_schema", get_schema());
         }

         if(command()->m_varTopicQuery["schema"].get_string().has_char())
         {
            str = command()->m_varTopicQuery["schema"];
            data_set("system_schema", str);
            data_set("schema", str);
            set_schema(str, false);
         }
         else if(data_get("schema", str))
         {
            if(str.has_char())
            {
               set_schema(str, false);
            }
         }

         // keyboard layout
         if(data_get("keyboard_layout", str) && str.has_char())
         {
            user()->set_keyboard_layout(str, false);
         }
         else
         {
            user()->set_keyboard_layout(NULL, false);
         }

         data_pulse_change("ca2", "savings", NULL);


         App(this).fill_locale_schema(*str_context()->m_plocaleschema);


         Sys(this).appa_load_string_table();

   }


      return true;

   }

   bool application::process_initialize()
   {

      if(!::application::process_initialize())
         return false;

      m_spuserex = create_userex();

      if (m_spuserex == NULL)
         return false;

      m_spuserex->construct(this);

      m_spuserfs = create_userfs();

      if(m_spuserfs == NULL)
         return false;

      m_spuserfs->construct(this);

      m_phtml = create_html();

      if(m_phtml == NULL)
         return false;

      m_phtml->construct(this);

      return true;

   }

   bool application::initialize1()
   {



      m_splicense = new class ::fontopus::license(this);



      /*if(!is_system())
      {
         if(m_spfsdata.is_null())
            m_spfsdata = new ::fs::set(this);
         ::fs::set * pset = dynamic_cast < ::fs::set * > ((class ::fs::data *) m_spfsdata);
         pset->m_spafsdata.add(new ::fs::native(this));
         stringa stra;
         pset->root_ones(stra);
      }*/


/*      if(fontopus()->m_puser == NULL &&
        (Application.directrix()->m_varTopicQuery.has_property("install")
      || Application.directrix()->m_varTopicQuery.has_property("uninstall")))
      {

         if(fontopus()->create_system_user("system") == NULL)
            return false;

      }*/

      if(!::application::initialize1())
         return false;

      /*if(!m_spuser->initialize1())
         return false;
      if(!m_spuser->initialize2())
         return false;*/

      if (!m_spuserex->initialize1())
         return false;
      if (!m_spuserex->initialize2())
         return false;

      m_simpledb.construct(this);

      if(!m_simpledb.initialize2())
         return false;


      return true;

   }

   bool application::initialize2()
   {

      if(!::application::initialize2())
         return false;



      fill_locale_schema(*str_context()->m_plocaleschema);




      return true;

   }


   bool application::initialize_instance()
   {



      if(!::application::initialize_instance())
         return false;

      //if(!m_pfontopus->initialize_instance())
        // return false;


      return true;


   }


   int32_t session::main()
   {


      return ::platform::application::main();


   }

  int32_t application::exit_instance()
   {

      try
      {

         m_iReturnCode = ::application::exit_instance();

      }
      catch(...)
      {

         m_iReturnCode = -1;

      }

      try
      {

         System.unregister_bergedge_application(this);

      }
      catch(...)
      {

         m_iReturnCode = -1;

      }

      try
      {

         if(System.appptra().get_count() <= 1)
         {

             if(System.thread::get_os_data() != NULL)
              {
              System.post_thread_message(WM_QUIT);

              }

         }

      }
      catch(...)
      {

         m_iReturnCode = -1;

      }

      return m_iReturnCode;

   }



   service_base * application::get_service()
   {
      return m_pservice;
   }

   void application::data_on_after_change(signal_details * pobj)
   {
      SCAST_PTR(::database::change_event, pchange, pobj);
      if(pchange->m_key.m_idKey == "ca2")
      {
         if(pchange->m_key.m_idIndex  == "savings")
         {
            pchange->data_get(savings().m_eresourceflagsShouldSave);
         }
      }
   }


   int32_t application::simple_message_box(sp(::user::interaction) puiOwner, const char * pszMessage, UINT fuStyle)
   {

      if (!user().is_set())
         return ::application::simple_message_box(puiOwner, pszMessage, fuStyle);

      return userex()->simple_message_box(puiOwner, pszMessage, fuStyle);

   }


   int32_t application::simple_message_box_timeout(sp(::user::interaction) pwndOwner, const char * pszMessage, ::duration durationTimeOut, UINT fuStyle)
   {

      if (!user().is_set())
         return ::application::simple_message_box_timeout(pwndOwner, pszMessage, durationTimeOut, fuStyle);

      return userex()->simple_message_box_timeout(pwndOwner, pszMessage, durationTimeOut, fuStyle);

   }


   void application::assert_valid() const
   {

     ::application::assert_valid();
      //::database::server::assert_valid();

   }


   void application::dump(dump_context & context) const
   {

      ::application::dump(context);
      //::database::server::dump(context);

   }


} //namespace plane





