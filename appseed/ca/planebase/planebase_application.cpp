#include "framework.h"


namespace planebase
{


   CLASS_DECL_ca LPFN_instantiate_application g_lpfn_instantiate_application = NULL;


   application::application()
   {


      m_dir.set_app(this);
      m_file.set_app(this);
      m_http.set_app(this);

      m_bIfs                     = true;
      m_bUpdateMatterOnInstall   = true;

      m_pservice                 = NULL;
   }

   application::~application()
   {
   }

   void application::defer_initialize_twf()
   {
      if(System.m_ptwf == NULL && (System.m_bShouldInitializeGTwf && m_bShouldInitializeGTwf && m_bInitializeProDevianMode))
      {
         System.create_twf();
      }
   }


   ::ca::application * application::instantiate_application(const char * pszType, const char * pszId, ::ca::application_bias * pbias)
   {

      ::ca::application * pcaapp = NULL;
      ::ca2::application * papp = NULL;

      string strId(pszId);

      if(strId.CompareNoCase("session") == 0)
      {
         ::plane::session * psession = new ::plane::session();
         pcaapp = psession;
         psession->construct();
         if(m_psystem != NULL && m_psystem->m_psession == NULL)
         {
            m_psystem->m_psession = psession;
         }
      }
      else
      {


         pcaapp = System.get_new_app(this, pszType, pszId);

         if(pcaapp == NULL)
            return NULL;

         pcaapp->m_psession                          = m_psession;

         /*if(pcaapp->m_bService)
         {
            App(pcaapp).m_puiInitialPlaceHolderContainer  = NULL;
         }*/
         if(m_psystem != NULL && m_psystem->m_psession == NULL)
         {
            m_psystem->m_psession = m_psession;
         }
      }

      //pcaapp->m_papp                               = this;
      pcaapp->m_psystem                            = m_psystem;

      papp = dynamic_cast < ::ca2::application * > (pcaapp);

      papp->command_central().consolidate(dynamic_cast < ::gen::command_thread * > (&command_central()));

      papp->m_bSessionSynchronizedCursor = m_bSessionSynchronizedCursor;

      if(pbias != NULL)
      {
         papp->propset().merge(pbias->m_set);
      }
      else
      {
         papp->oprop("SessionSynchronizedInput")   = true;
         papp->oprop("NativeWindowFocus")          = true;
      }




      if((papp == NULL || papp->m_strAppName != strId)
         &&
         (!Application.command().m_varTopicQuery.has_property("install")
         && !Application.command().m_varTopicQuery.has_property("uninstall")))
      {

         TRACE("Failed to instantiate %s, going to try installation through ca2_cube_install", strId);

         string strCommandLine;

         strCommandLine    =" : app=" + strId;
         strCommandLine    += " locale=" + string(Application.str_context()->m_plocaleschema->m_idLocale);
         strCommandLine    += " style=" + string(Application.str_context()->m_plocaleschema->m_idSchema);
         strCommandLine    += " install";

         System.install().start(strCommandLine);

         throw installing_exception();

         return NULL;

      }


      return pcaapp;
   }


   ::ca::application * application::create_application(const char * pszType, const char * pszId, bool bSynch, ::ca::application_bias * pbias)
   {

      ::ca::application * pcaapp = instantiate_application(pszType, pszId, pbias);

      if(pcaapp == NULL)
         return NULL;

      ::ca2::application * papp = dynamic_cast < ::ca2::application * > (pcaapp);

      if(!papp->start_application(bSynch, pbias))
      {
         try
         {
            delete pcaapp;
         }
         catch(...)
         {
         }
         return NULL;
      }


      return pcaapp;

   }


   int application::pre_run()
   {

      m_dir.m_psystem      = m_psystem;
      m_file.m_psystem     = m_psystem;

#ifdef WINDOWS

      MSG msg;

      // Create Windows Message Queue
      ::PeekMessageA(&msg, NULL, 0, 0xffff, 0);

      if(!is_system() && (bool)oprop("SessionSynchronizedInput"))
      {
         ::AttachThreadInput(GetCurrentThreadId(), (DWORD) System.::ca::thread_sp::m_p->get_os_int(), TRUE);
      }

#endif

      if(is_system())
      {
         translator::attach();
      }

      m_iReturnCode            = 0;

      m_dwAlive = ::GetTickCount();

      // App global initializations (rare)
      if (!InitApplication())
         goto InitFailure;

      m_dwAlive = ::GetTickCount();
      // Perform specific initializations
      try
      {
         try
         {
            if(!process_initialize())
            {
               if (GetMainWnd() != NULL)
               {
                  TRACE(::radix::trace::category_AppMsg, 0, "Warning: Destroying non-NULL GetMainWnd()\n");
                  GetMainWnd()->DestroyWindow();
               }
               goto InitFailure;
            }
         }
         catch(const ::ca::exception &)
         {
            if (GetMainWnd() != NULL)
            {
               GetMainWnd()->DestroyWindow();
               SetMainWnd(NULL);
            }
            goto InitFailure;
         }
         m_dwAlive = ::GetTickCount();
         try
         {
            if(!initialize_instance())
            {
               if (GetMainWnd() != NULL)
               {
                  TRACE(::radix::trace::category_AppMsg, 0, "Warning: Destroying non-NULL GetMainWnd()\n");
                  GetMainWnd()->DestroyWindow();
               }

               try
               {
                  exit();
               }
               catch(...)
               {
               }
               m_iReturnCode = -1;
               goto InitFailure;
            }
         }
         catch(const ::ca::exception & e)
         {
            if(on_run_exception((::ca::exception &) e))
               goto run;
            if(GetMainWnd() != NULL)
            {
               TRACE(::radix::trace::category_AppMsg, 0, "Warning: Destroying non-NULL GetMainWnd()\n");
               try
               {
                  GetMainWnd()->DestroyWindow();
               }
               catch(::ca::exception &)
               {
               }
               SetMainWnd(NULL);
            }
            if(final_handle_exception((::ca::exception &) e))
               goto run;
            if(GetMainWnd() != NULL)
            {
               TRACE(::radix::trace::category_AppMsg, 0, "Warning: Destroying non-NULL GetMainWnd()\n");
               try
               {
                  GetMainWnd()->DestroyWindow();
               }
               catch(::ca::exception &)
               {
               }
               SetMainWnd(NULL);
            }
            try
            {
               m_iReturnCode = exit();
            }
            catch(...)
            {
               m_iReturnCode = -1;
            }
            if(m_iReturnCode == 0)
               m_iReturnCode = -1;
            goto InitFailure;
         }
      }
      catch(...)
      {
         // linux-like exit style on crash, differently from general windows error message approach
         // to prevent or correct from crash, should:
         // - look at dumps - to do;
         // - look at trace and log - always doing;
         // - look at debugger with the visual or other tool atashed - to doing;
         // - fill other possibilities;
         // - restart and send information in the holy back, and stateful or self-heal as feedback from below;
         // - ...
         // - ..
         // - .
         // - .
         // - .
         // - .
         // -  .
         // - ...
         // - ...
         // - ...
         // to pro-activia and overall benefits workaround:
         // - stateful applications:
         //      - browser urls, tabs, entire history, in the ca2computing cloud;
         //      - word - html document to simplify here - with all history of undo and redos per document optimized by cvs, svn, syllomatter;
         //           - not directly related but use date and title to name document;
         //      - save forms after every key press in .undo.redo.form file parallel to appmatter / form/undo.redo.file parity;
         //      - last karaoke song and scoring, a little less motivated at time of writing;
         //
         // - ex-new-revolut-dynamic-news-self-healing
         //      - pre-history, antecendentes
         //            - sometimes we can't recover from the last state
         //            - to start from the beggining can be too heavy, waity, worky, bory(ing)
         //      - try to creativetily under-auto-domain with constrained-learning, or heuristcally recover from restart, shutdown, login, logoff;
         //           - reification :
         //           - if the document is corrupted, try to open the most of it
         //           - if can only detect that the document cannot be opened or damaged, should creatively workarounds as it comes, as could it be
         //              done, for example search in the web for a proper solution?
         //           - karaoke file does not open? can open next? do it... may animate with a temporary icon...
         //           - import a little as pepper for the meal, prodevian technology into estamira, so gaming experience relativity can open ligh
         //               speed into cartesian dimensions of
         //               ca2, estamira and prodevian. Take care not to flood prodevian brand black ink over the floor of the estamira office...
         //               black letters, or colorful and pink are accepted and sometimes desired, for example, hello kity prodevian, pirarucu games,
         //               I think no one likes to be boring, but a entire background in black... I don't know... only for your personal office, may be...
         //           - could an online colaborator investigate crashes promptly in a funny way, and make news and jokes? Like terra and UOL for the real world?
         //               - new crash, two documents lost, weathers fault, too hot, can't think, my mother was angry with me, lead to buggy code;
         //               - new version with bug fixes;
         //      - new versions
         //      - automatic updates
         //      - upgrades
         //      - rearrangemntes
         //      - downgrade in the form of retro
         // - ...
         // - ..
         // - .
         // - .
         // - .
         // - .
         // -  .
         // - ...
         // - ...
         // - ...

      }
InitFailure:
      run:
      return m_iReturnCode;
   }


   int application::on_run()
   {
      int m_iReturnCode = 0;

      try
      {
         ::radix::application_signal_object signal(this, &m_signal, ::ca::application_signal_start);
         m_signal.emit(&signal);
      }
      catch(...)
      {
      }


      install_message_handling(System.GetThread()->::ca::smart_pointer < ::ca::thread > ::m_p);
      try
      {
         try
         {
            m_bReady = true;
            if(m_peventReady != NULL)
               m_peventReady->SetEvent();
         }
         catch(...)
         {
         }
         run:
         try
         {
            m_iReturnCode = run();
         }
         catch(const ::ca::exception & e)
         {
            if(on_run_exception((::ca::exception &) e))
               goto run;
            if (GetMainWnd() != NULL)
            {
               TRACE(::radix::trace::category_AppMsg, 0, "Warning: Destroying non-NULL GetMainWnd()\n");
               try
               {
                  GetMainWnd()->DestroyWindow();
               }
               catch(::ca::exception &)
               {
               }
               SetMainWnd(NULL);
            }
            if(final_handle_exception((::ca::exception &) e))
               goto run;
            if (GetMainWnd() != NULL)
            {
               TRACE(::radix::trace::category_AppMsg, 0, "Warning: Destroying non-NULL GetMainWnd()\n");
               try
               {
                  GetMainWnd()->DestroyWindow();
               }
               catch(::ca::exception &)
               {
               }
               SetMainWnd(NULL);
            }
            try
            {
               m_iReturnCode = exit();
            }
            catch(...)
            {
               m_iReturnCode = -1;
            }
            goto InitFailure;
         }
      }
      catch(...)
      {
         // linux-like exit style on crash, differently from general windows error message approach
         // to prevent or correct from crash, should:
         // - look at dumps - to do;
         // - look at trace and log - always doing;
         // - look at debugger with the visual or other tool atashed - to doing;
         // - fill other possibilities;
         // - restart and send information in the holy back, and stateful or self-heal as feedback from below;
         // - ...
         // - ..
         // - .
         // - .
         // - .
         // - .
         // -  .
         // - ...
         // - ...
         // - ...
         // to pro-activia and overall benefits workaround:
         // - stateful applications:
         //      - browser urls, tabs, entire history, in the ca2computing cloud;
         //      - word - html document to simplify here - with all history of undo and redos per document optimized by cvs, svn, syllomatter;
         //           - not directly related but use date and title to name document;
         //      - save forms after every key press in .undo.redo.form file parallel to appmatter / form/undo.redo.file parity;
         //      - last karaoke song and scoring, a little less motivated at time of writing;
         //
         // - ex-new-revolut-dynamic-news-self-healing
         //      - pre-history, antecendentes
         //            - sometimes we can't recover from the last state
         //            - to start from the beggining can be too heavy, waity, worky, bory(ing)
         //      - try to creativetily under-auto-domain with constrained-learning, or heuristcally recover from restart, shutdown, login, logoff;
         //           - reification :
         //           - if the document is corrupted, try to open the most of it
         //           - if can only detect that the document cannot be opened or damaged, should creatively workarounds as it comes, as could it be
         //              done, for example search in the web for a proper solution?
         //           - karaoke file does not open? can open next? do it... may animate with a temporary icon...
         //           - import a little as pepper for the meal, prodevian technology into estamira, so gaming experience relativity can open ligh
         //               speed into cartesian dimensions of
         //               ca2, estamira and prodevian. Take care not to flood prodevian brand black ink over the floor of the estamira office...
         //               black letters, or colorful and pink are accepted and sometimes desired, for example, hello kity prodevian, pirarucu games,
         //               I think no one likes to be boring, but a entire background in black... I don't know... only for your personal office, may be...
         //           - could an online colaborator investigate crashes promptly in a funny way, and make news and jokes? Like terra and UOL for the real world?
         //               - new crash, two documents lost, weathers fault, too hot, can't think, my mother was angry with me, lead to buggy code;
         //               - new version with bug fixes;
         //      - new versions
         //      - automatic updates
         //      - upgrades
         //      - rearrangemntes
         //      - downgrade in the form of retro
         // - ...
         // - ..
         // - .
         // - .
         // - .
         // - .
         // -  .
         // - ...
         // - ...
         // - ...

      }
InitFailure:
      m_bRun = false;
      try
      {
         if(m_peventReady != NULL)
            m_peventReady->SetEvent();
      }
      catch(...)
      {
      }
      try
      {
         ::radix::thread * pthread = dynamic_cast < ::radix::thread * > (::ca::smart_pointer < ::ca::thread >::m_p);
         if(pthread->m_pbReady != NULL)
         {
            *pthread->m_pbReady = true;
         }
      }
      catch(...)
      {
      }
      /*try
      {
         ::radix::thread * pthread = dynamic_cast < ::radix::thread * > (this);
         ::SetEvent((HANDLE) pthread->m_peventReady);
      }
      catch(...)
      {
      }*/

      // let translator run undefinetely
      /*if(is_system())
      {
         translator::detach();
      }*/

      return m_iReturnCode;
   }

   bool application::initial_check_directrix()
   {
      if(directrix().m_varTopicQuery.has_property("install"))
      {
         if(::fontopus::application::on_install())
         {
            if(on_install())
            {
               
               string strId = m_strId;
               //MessageBox(NULL, "on_install1", strId, 0);
               if(strId.is_empty())
                  strId = m_strAppName;

               if(command().m_varTopicQuery.has_property("app") && strId == command().m_varTopicQuery["app"])
               {
                  
                  System.install().remove_spa_start(m_strInstallType, strId);
                  System.install().add_app_install(m_strInstallType, strId);
               }
               else if(command().m_varTopicQuery.has_property("session_start") && strId == command().m_varTopicQuery["session_start"])
               {
                  //MessageBox(NULL, "on_install2", "on_install2", 0);
                  System.install().remove_spa_start(m_strInstallType, strId);
                  System.install().add_app_install(m_strInstallType, strId);
                  //MessageBox(NULL, "on_install3", "on_install3", 0);
               }
               else if(m_strInstallToken.has_char())
               {
                  System.install().remove_spa_start(m_strInstallType, m_strInstallToken);
                  System.install().add_app_install(m_strInstallType, m_strInstallToken);
               }

            }
            else
            {
               return false;
            }
         }
         return true;
      }
      else if(directrix().m_varTopicQuery.has_property("uninstall"))
      {
         if(::fontopus::application::on_uninstall())
         {
            if(on_uninstall())
            {
               System.install().remove_spa_start(m_strInstallType, m_strInstallToken);
            }
            else
            {
               return false;
            }
         }
         return true;
      }
      return true;
   }

   int application::main()
   {
      m_dwAlive = ::GetTickCount();
      int m_iReturnCode = pre_run();
      if(m_iReturnCode != 0)
      {
         m_bReady = true;
         TRACE("application::main pre_run failure");
         return m_iReturnCode;
      }


      if(!initial_check_directrix())
      {
         exit();
         m_iReturnCode = -1;
         m_bReady = true;
         ::OutputDebugString("exiting on check directrix");
         return m_iReturnCode;
      }


      m_dwAlive = ::GetTickCount();
      if(!os_native_bergedge_start())
      {
         exit();
         m_iReturnCode = -1;
         m_bReady = true;
         ::OutputDebugString("application::main os_native_bergedge_start failure");
         return m_iReturnCode;
      }
      m_iReturnCode = 0;
      m_bReady = true;
      m_iReturnCode = on_run();
      if(m_iReturnCode != 0)
      {
         ::OutputDebugString("application::main on_run termination failure");
      }
      try
      {
         m_iReturnCode = exit();
      }
      catch(...)
      {
         m_iReturnCode = -1;
      }
      return 0;
   }

   bool application::bergedge_start()
   {
      return true;
   }

   bool application::os_native_bergedge_start()
   {
      return true;
   }

   ex1::filesp application::friendly_get_file(var varFile, UINT nOpenFlags)
   {
      try
      {
         return get_file(varFile, nOpenFlags);
      }
      catch(...)
      {
         return ::ca::null();
      }
   }

   ex1::filesp application::get_file(var varFile, UINT nOpenFlags)
   {

      ex1::filesp spfile;

      string strPath;

      if(varFile.get_type() == var::type_string)
      {

         strPath = varFile;

         strPath.trim("\"'");

      }
      else if(varFile.get_type() == var::type_propset)
      {

         if(varFile.has_property("url"))
         {

            strPath = varFile["url"];

            strPath.trim("\"'");

         }

      }

      if(varFile.get_type() == var::type_propset && varFile.propset()["file"].ca2 < ::ex1::file >() != NULL)
      {

         spfile(varFile.propset()["file"].ca2 < ::ex1::file >());

      }
      else if(gen::str::find_ci(".zip:", strPath) >= 0)
      {

         zip::InFile * pinfile = new zip::InFile(get_app());

         if(pinfile != NULL)
         {

            if(!pinfile->unzip_open(strPath, 0))
            {

               delete pinfile;

               pinfile = NULL;

            }

         }

         spfile(pinfile);

      }
      else if(gen::str::begins(strPath, "http://") || gen::str::begins(strPath, "https://"))
      {
         
         spfile(new sockets::http::file(get_app()));
         
         if(!spfile->open(strPath, nOpenFlags))
         {

            spfile.destroy();

         }

      }
      else if(gen::str::begins(strPath, "ifs://") || gen::str::begins(strPath, "uifs://"))
      {

         if(&AppUser(this) == NULL)
         {

            spfile = ::ca::null();

         }
         else
         {

            spfile = AppUser(this).m_pifs->get_file(varFile, nOpenFlags);

         }

      }
      else if(gen::str::begins(strPath, "fs://"))
      {
         
         if(&Session == NULL)
         {

            spfile = ::ca::null();

         }
         else
         {

            spfile = Session.m_prfs->get_file(varFile, nOpenFlags);

         }

      }
      else if(gen::str::begins_eat_ci(strPath, "matter://"))
      {

         ::ca::application * papp;

         if(System.url().get_server("matter://" + strPath) ==m_strAppName)
         {
            
            strPath = System.url().get_object("matter://" + strPath).Mid(1);

            spfile.create(this);

            if(!spfile->open(dir().matter(strPath), nOpenFlags))
            {

               spfile.destroy();

            }

         }
         else if(&Session != NULL && Session.m_mapApplication.Lookup(System.url().get_server("matter://" + strPath), papp) && App(papp).m_strAppName.has_char())
         {

            spfile = App(papp).get_file("matter://" + strPath, nOpenFlags);

         }
         else
         {

            spfile.create(this);

            if(!spfile->open(dir().matter(strPath), nOpenFlags))
            {

               spfile.destroy();

            }

         }

      }
      else
      {

         spfile.create(this);

         if(!spfile->open(strPath, nOpenFlags))
         {

            spfile.destroy();

         }

      }

      if(spfile.is_null())
      {

         throw ex1::file_exception(this, ::ex1::file_exception::none, -1, strPath);

      }

      return spfile;

   }

   ::ex1::byte_stream application::get_byte_stream(var varFile, UINT nOpenFlags)
   {

      return ::ex1::byte_stream(get_file(varFile, nOpenFlags));

   }

   int application::exit_instance()
   {

      try
      {

         m_iReturnCode = 0;


         m_iReturnCode = ::fontopus::application::exit_instance();
      }
      catch(...)
      {
      }

      try
      {
         System.unregister_bergedge_application(this);
      }
      catch(...)
      {
      }

      try
      {
         if(System.appptra().get_count() <= 1)
         {
            System.PostThreadMessage(WM_QUIT, 0, 0);
         }
      }
      catch(...)
      {
      }



      return m_iReturnCode;
   }

   bool application::is_licensed(const char * pszId, bool bInteractive)
   {

      if(directrix().m_varTopicQuery.has_property("install"))
         return true;

      if(directrix().m_varTopicQuery.has_property("uninstall"))
         return true;

      return license().has(pszId, bInteractive);

   }

   /*
      ::radix::application * pradixapp = dynamic_cast < ::radix::application * > (papp);
      if(pradixapp != NULL)
      {
         try
         {
            pradixapp->m_dwAlive = ::GetTickCount();
         }
         catch(...)
         {
         }
      }
   */

   bool application::initialize()
   {

      if(m_bIfs)
      {
         if(&Session != NULL)
         {
            if(m_spfsdata.is_null())
               m_spfsdata(new ::fs::set(this));
            ::fs::set * pset = dynamic_cast < ::fs::set * > ((class ::fs::data *) m_spfsdata);
            pset->m_spafsdata.add(Session.m_pifs);
            pset->m_spafsdata.add(Session.m_prfs);
            stringa stra;
            pset->root_ones(stra);
         }
      }

      m_dwAlive = ::GetTickCount();

      m_splicense(new class ::fontopus::license(this));


      if(!is_system())
      {
         System.register_bergedge_application(this);
      }



      if(!fontopus::application::initialize())
         return false;

      if(!is_system() && !is_session() && !is_bergedge() && !is_cube() && !is_installing() && !is_uninstalling())
      {
      
         string str;
         // if system locale has changed (compared to last recorded one by ca2)
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

         if(command().m_varTopicQuery["locale"].get_string().has_char())
         {
            str = command().m_varTopicQuery["locale"];
            data_set("system_locale", str);
            data_set("locale", str);
            set_locale(str, false);
         }
         else if(command().m_varTopicQuery["lang"].get_string().has_char())
         {
            str = command().m_varTopicQuery["lang"];
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
         // if system schema has changed (compared to last recorded one by ca2)
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

         if(command().m_varTopicQuery["schema"].get_string().has_char())
         {
            str = command().m_varTopicQuery["schema"];
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
            set_keyboard_layout(str, false);
         }
         else
         {
            set_keyboard_layout(NULL, false);
         }

         data_pulse_change("ca2_fontopus_votagus", "savings", NULL);


         App(this).fill_locale_schema(*str_context()->m_plocaleschema);


         Sys(this).appa_load_string_table();

   }


      return true;

   }

   bool application::initialize1()
   {

      if(!is_system() && !is_bergedge())
      {
         if(m_spfsdata.is_null())
            m_spfsdata(new ::fs::set(this));
         ::fs::set * pset = dynamic_cast < ::fs::set * > ((class ::fs::data *) m_spfsdata);
         pset->m_spafsdata.add(new ::fs::native(this));
         stringa stra;
         pset->root_ones(stra);
      }


      if(m_puser == NULL &&
        (Application.directrix().m_varTopicQuery.has_property("install")
      || Application.directrix().m_varTopicQuery.has_property("uninstall")))
      {
         m_puser                 = new ::fontopus::user(this);
         m_puser->m_strLogin     = "system";
         create_user(m_puser);
      }

      if(!fontopus::application::initialize1())
         return false;


      return true;

   }


   void application::set_title(const char * pszTitle)
   {

      Session.set_app_title(m_strInstallType, m_strAppName, pszTitle);

   }



   FileManagerTemplate * application::GetStdFileManagerTemplate()
   {
      return NULL;
   }







   //////////////////////////////////////////////////////////////////////////////////////////////////
   // System/Cube
   //
   ::document * application::hold(::user::interaction * pui)
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






   //////////////////////////////////////////////////////////////////////////////////////////////////
   // Session/Bergedge
   //
   ::bergedge::view * application::get_view()
   {

      return NULL;

   }

   ::bergedge::document * application::get_document()
   {

      return NULL;

   }



   bool application::is_serviceable()
   {
      return false;
   }


   bool application::is_installing()
   {

      return directrix().has_property("install");

   }


   bool application::is_uninstalling()
   {

      return directrix().has_property("uninstall");

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


   int application::run()
   {

      if(!is_system() && !is_session() && !is_bergedge() && !is_cube())
      {
         if(command().m_varTopicQuery.has_property("install")
         || command().m_varTopicQuery.has_property("uninstall"))
         {
         }
         else if(command().m_varTopicQuery.has_property("service"))
         {
            create_new_service();
            service_base::run(*m_pservice);
         }
         else if(command().m_varTopicQuery.has_property("run") || is_serviceable())
         {
            create_new_service();
            m_pservice->Start(0);
            return fontopus::application::run();
         }
         else
         {
            return fontopus::application::run();
         }
      }
      else
      {
         return fontopus::application::run();
      }

      return TRUE;

   }

   bool application::on_uninstall()
   {
      if(is_serviceable())
      {
         stop_service();
         remove_service();
      }
      return ::fontopus::application::on_uninstall();
   }


   service_base * application::get_service()
   {
      return m_pservice;
   }


   service_base * application::allocate_new_service()
   {
      if(!is_serviceable())
         throw "only a serviceable application should/can allocate a new service";
      throw "a serviceable application should implement this function returning a newly allocated application service";
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

   void application::on_service_request(::ca::create_context * pcreatecontext)
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


   bool application::on_install()
   {

      bool bOk = true;

      if(m_bUpdateMatterOnInstall)
      {

         try
         {
            string strRoot;
            string strDomain;
            if(is_system())
            {
               return true;
            }
            else if(is_session() && System.directrix().m_varTopicQuery["session_start"] != "session")
            {
               return true;
            }
            else if(is_cube())
            {
               return true;
            }
            else if(is_bergedge())
            {
               return true;
            }
            else
            {

               stringa stra;
               stra.add_tokens(App(this).m_strAppName, "_", FALSE);

               string strLibrary;

               strLibrary = App(this).m_strLibraryName;

               if(strLibrary.has_char() && strLibrary.CompareNoCase("app_" + App(this).m_strAppName) == 0)
                  strLibrary.Empty();

               if(strLibrary.has_char())
               {

                  ::ca2::library library;

                  if(library.open(this, strLibrary))
                  {
                     stringa straAppList;
                     library.get_app_list(straAppList);
                     if(straAppList.get_count() <= 1)
                        strLibrary.Empty();
                  }
                  else
                  {
                     strLibrary.Empty();
                  }

               }

               for(int i = 1; i < stra.get_upper_bound(); i++)
               {
                  stra[i] == "_" + stra[i];
               }
               if(stra.get_size() > 1)
               {
                  strRoot = "app-" + stra[0];
                  stra.remove_at(0);
                  if(strLibrary.has_char())
                     stra.insert_at(stra.get_upper_bound(), strLibrary);
                  strDomain += stra.implode("/");
               }
               else
               {
                  strRoot = "app";
                  if(strLibrary.has_char())
                     strDomain = strLibrary + "/";
                  strDomain += App(this).m_strAppName;
               }
            }


            ::sockets::socket_handler h(get_app());
            ::sockets::http_session * psession = NULL;

            ::ensure_trace_file();

            g_iStepProgress      = 0;

            g_iCountProgress     = 2;


            if(!is_session() && !is_system())
            {
               g_iCountProgress++;
            }

            gen::international::locale_schema localeschema(this);

            fill_locale_schema(localeschema);

            int iStdStdCount = 0;

            for(int i = 0; i < localeschema.m_idaLocale.get_count(); i++)
            {
               if(localeschema.m_idaLocale[i] == __id(std) &&
                  localeschema.m_idaSchema[i] == __id(std))
               {
                  iStdStdCount++; 
               }

            }

            g_iCountProgress *= localeschema.m_idaLocale.get_count();

            g_iCountProgress -= iStdStdCount * (1 + 1); // ('main' + 'bergedge') * StdStd are not downloaded on session install but on spa boot


/*
            double d1 = ::GetTickCount();
            update_appmatter(h, psession, "app", "main"); // update matter of system
            update_appmatter(h, psession, "app", "bergedge"); // update matter of bergedge
            if(!is_session() && !is_system())
            {
               update_appmatter(h, psession, strRoot, strDomain);
            }

*/
//            double d2 = ::GetTickCount();
//            double d = (d2 - d1) / 1000.0;
//            TRACE("update_appmatter seconds %f", d);

            ::trace_progress(1.0);

         }
         catch(...)
         {
            bOk = false;
         }

      }


      if(is_serviceable())
      {
         create_service();
         start_service();
      }


      return bOk;

   }

   void application::fill_locale_schema(gen::international::locale_schema & localeschema)
   {


      localeschema.m_idaLocale.remove_all();
      localeschema.m_idaSchema.remove_all();


      //localeschema.m_bAddAlternateStyle = true;


      string strLocale;
      string strSchema;


      if(Application.directrix().m_varTopicQuery["locale"].has_char() && Application.directrix().m_varTopicQuery["locale"].get_string().CompareNoCase("_std") != 0)
      {
         strLocale = Application.directrix().m_varTopicQuery["locale"];
         if(Application.directrix().m_varTopicQuery["style"].has_char() && Application.directrix().m_varTopicQuery["style"].get_string().CompareNoCase("_std") != 0)
         {
            strSchema = Application.directrix().m_varTopicQuery["style"];
         }
         else
         {
            strSchema = strLocale;
         }
      }
      else if(Application.directrix().m_varTopicQuery["lang"].has_char() && Application.directrix().m_varTopicQuery["lang"].get_string().CompareNoCase("_std") != 0)
      {
         strLocale = Application.directrix().m_varTopicQuery["lang"];
         if(Application.directrix().m_varTopicQuery["style"].has_char() && Application.directrix().m_varTopicQuery["style"].get_string().CompareNoCase("_std") != 0)
         {
            strSchema = Application.directrix().m_varTopicQuery["style"];
         }
         else
         {
            strSchema = strLocale;
         }
      }
      else
      {
         strLocale  = get_locale();
         strSchema  = get_schema();
      }


      localeschema.m_idLocale     = strLocale;
      localeschema.m_idSchema     = strSchema;


      localeschema.add_locale_variant(strLocale, strSchema);


      if(Application.directrix().m_varTopicQuery["style"].has_char() && Application.directrix().m_varTopicQuery["style"].get_string().CompareNoCase("_std") != 0)
      {
         localeschema.add_locale_variant(get_locale(), Application.directrix().m_varTopicQuery["style"]);
      }

      if(get_schema().has_char() && get_schema().CompareNoCase("_std") != 0 && get_schema().CompareNoCase(get_locale()) != 0)
      {
         localeschema.add_locale_variant(get_locale(), Application.directrix().m_varTopicQuery["style"]);
      }

      localeschema.add_locale_variant(get_locale(), get_locale());

      localeschema.add_locale_variant(get_locale(), __id(en));
      localeschema.add_locale_variant(get_locale(), __id(std));

      localeschema.add_locale_variant(__id(en), get_schema());
      localeschema.add_locale_variant(__id(std), get_schema());

      localeschema.add_locale_variant(__id(en), get_locale());
      localeschema.add_locale_variant(__id(std), get_locale());

      localeschema.add_locale_variant(__id(en), __id(en));
      localeschema.add_locale_variant(__id(std), __id(std));


      localeschema.finalize();

   }


   bool application::update_appmatter(::sockets::socket_handler & h, ::sockets::http_session * & psession,const char * pszRoot, const char * pszRelative)
   {

      gen::international::locale_schema localeschema(this);

      fill_locale_schema(localeschema);

      bool bIgnoreStdStd = string(pszRoot) == "app" && (string(pszRelative) == "main" || string(pszRelative) == "bergedge");

      //update_appmatter(h, psession, pszRoot, pszRelative, localeschema.m_idLocale, localeschema.m_idSchema);

      for(int i = 0; i < localeschema.m_idaLocale.get_count(); i++)
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
      string strFile = System.dir().ca2(strRelative);
      string strUrl;
      if(_ca_is_basis())
      {
         strUrl = "http://basis.spaignition.api.laborserver.net/download?authnone&version=basis&stage=";
      }
      else
      {
         strUrl = "http://stage.spaignition.api.laborserver.net/download?authnone&version=stage&stage=";
      }

      strUrl += System.url().url_encode(strRelative);

      primitive::memory mem(get_app());

      if(psession == NULL)
      {

         while(true)
         {

            gen::property_set setEmpty(get_app());

            psession = System.http().open(h, System.url().get_server(strUrl), System.url().get_protocol(strUrl), setEmpty, NULL, NULL);

            if(psession != NULL)
               break;

            Sleep(184);

         }

      }

      psession = System.http().get(h, psession, strUrl, mem);

      primitive::memory_file file(get_app(), &mem);

      if(mem.get_size() > 0)
      {

         zip::Util util;

         string strDir = strFile;

         gen::str::ends_eat_ci(strDir, ".zip");

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


   bool application::add_library(::ca2::library * plibrary)
   {

      plibrary->set_app(this);

      System.add_library(plibrary);

      return true;

   }


} //namespace planebase


