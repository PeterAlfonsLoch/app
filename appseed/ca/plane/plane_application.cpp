#include "StdAfx.h"


namespace plane
{


   CLASS_DECL_ca LPFN_instantiate_application g_lpfn_instantiate_application = NULL;


   application::application()
   {


      m_dir.set_app(this);
      m_file.set_app(this);
      m_http.set_app(this);

      m_bIfs            = true;


   }

   application::~application()
   {
   }

   CLASS_DECL_ca application & app_cast(::ca::ca * papp)
   {
      return *(dynamic_cast < application * > (papp));
   }

   class ::ca::dir::application & application::dir()
   {
      return m_dir;
   }

   class ::ca2::file::application & application::file()
   {
      return m_file;
   }

   class ::ca4::http::application & application::http()
   {
      return m_http;
   }

   void application::defer_initialize_twf()
   {
      if(System.m_ptwf == NULL && (System.m_bShouldInitializeGTwf && m_bShouldInitializeGTwf && m_bInitializeProDevianMode))
      {
         System.create_twf();
      }
   }


   ::ca::application * application::instantiate_application(const char * pszId, ::ca::application_bias * pbias)
   {

      ::ca::application * pcaapp = NULL;
      ::ca2::application * papp = NULL;

      string strId(pszId);

      // xxx webserver
      /*
      if(strId.CompareNoCase("bergedge") == 0)
      {
         ::bergedge::bergedge * pbergedge = new ::bergedge::bergedge();
         pcaapp = pbergedge;
         pbergedge->construct();
         if(m_psystem != NULL && m_psystem->m_pbergedge == NULL)
         {
            m_psystem->m_pbergedge = pbergedge;
         }
      }
      else
      {


         pcaapp = System.get_new_app(this, pszId);

         if(pcaapp == NULL)
            return NULL;

         pcaapp->m_pbergedge                          = m_pbergedge;

         /*if(pcaapp->m_bService)
         {
            App(pcaapp).m_puiInitialPlaceHolderContainer  = NULL;
         }*/
        /* if(m_psystem != NULL && m_psystem->m_pbergedge == NULL)
         {
            m_psystem->m_pbergedge = m_pbergedge;
         }
      }

      pcaapp->m_papp                               = this;
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
         System.install().start(strId);
         throw installing_exception();
         return NULL;
      }


      return pcaapp;*/
      return NULL;
   }


   ::ca::application * application::create_application(const char * pszId, bool bSynch, ::ca::application_bias * pbias)
   {

      ::ca::application * pcaapp = instantiate_application(pszId, pbias);

      if(pcaapp == NULL)
         return NULL;

      ::ca2::application * papp = dynamic_cast < ::ca2::application * > (pcaapp);

/*      try
      {
         if(pbias != NULL)
         {
            papp->m_puiInitialPlaceHolderContainer = pbias->m_puiParent;
         }
      }
      catch(...)
      {
      }*/
      try
      {
         if(pbias != NULL)
         {
            if(pbias->m_pcallback != NULL)
            {
               pbias->m_pcallback->connect_to(papp);
            }
         }
      }
      catch(...)
      {
      }

      manual_reset_event * peventReady = NULL;

      if(bSynch)
      {
         peventReady = new manual_reset_event();
         papp->m_peventReady = peventReady;
         peventReady->ResetEvent();
      }

      papp->::ca::thread_sp::create(this);
      //dynamic_cast < ::radix::thread * > (papp->::ca::thread_sp::m_p)->m_p = papp->::ca::thread_sp::m_p;
      dynamic_cast < ::radix::thread * > (papp->::ca::thread_sp::m_p)->m_p = papp;
      if(pbias != NULL)
      {
         papp->m_biasCalling = *pbias;
      }
      papp->Begin();

      if(bSynch)
      {
         try
         {
            papp->keep_alive();
         }
         catch(...)
         {
         }
         try
         {
            while(true)
            {
               if(!papp->is_alive())
               {
                  delete papp;
                  return NULL;
               }
               if(papp->m_bReady)
               {
                  if(papp->m_iReturnCode == 0)
                     break;
                  delete papp;
                  return NULL;
               }
               Sleep(84);
            }
         }
         catch(...)
         {
            try
            {
               delete papp;
            }
            catch(...)
            {
            }
            return NULL;
         }
      }

      return papp;
   }


   int application::pre_run()
   {

      MSG msg;

      ::PeekMessageA(&msg, NULL, 0, 0xffff, 0);

      if(!is_system() && (bool)oprop("SessionSynchronizedInput"))
      {
         ::AttachThreadInput(GetCurrentThreadId(), System.::ca::thread_sp::m_p->get_os_int(), TRUE);
      }

      if(is_system())
      {
         se_translator::attach();
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
         ::SetEvent((HANDLE) pthread->m_peventReady);
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

      // let se_translator run undefinetely
      /*if(is_system())
      {
         se_translator::detach();
      }*/

      return m_iReturnCode;
   }

   bool application::initial_check_directrix()
   {
      if(directrix().m_varTopicQuery.has_property("install"))
      {
         if(::plane::application::on_install())
         {
            if(on_install())
            {
               string strId = m_strId;
               if(strId.is_empty())
                  strId = m_strAppName;
               if(command().m_varTopicQuery.has_property("app") && strId == command().m_varTopicQuery["app"])
               {
                  System.install().remove_spa_start(strId);
                  System.install().add_app_install(strId);
               }
               else if(command().m_varTopicQuery.has_property("bergedge_start") && strId == command().m_varTopicQuery["bergedge_start"])
               {
                  System.install().remove_spa_start(strId);
                  System.install().add_app_install(strId);
               }
               else if(m_strInstallToken.has_char())
               {
                  System.install().remove_spa_start(m_strInstallToken);
                  System.install().add_app_install(m_strInstallToken);
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
         if(::plane::application::on_uninstall())
         {
            if(on_uninstall())
            {
               System.install().remove_spa_start(m_strInstallToken);
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

   ex1::filesp application::get_file(var varFile, UINT nOpenFlags, ex1::file_exception_sp * pe)
   {
      ex1::filesp spfile;
      string strPath;
      if(varFile.get_type() == var::type_string)
      {
         strPath = varFile;
         strPath.trim("\"'");
      }
      if(varFile.get_type() == var::type_propset
      && varFile.propset()["file"].ca2 < ::ex1::file >() != NULL)
      {
         try
         {
            spfile(varFile.propset()["file"].ca2 < ::ex1::file >());
         }
         catch(...)
         {
            return NULL;
         }
      }
      else if(gen::str::find_ci(".zip:", strPath) >= 0)
      {
         zip::InFile * pinfile = new zip::InFile(get_app());
         if(pinfile == NULL)
            return NULL;
         if(!pinfile->unzip_open(strPath, 0, NULL))
         {
            delete pinfile;
            return NULL;
         }
         spfile(pinfile);
      }
      else if(gen::str::begins_ci(strPath, "rtp://")
         || gen::str::begins_ci(strPath, "rtprx://"))
      {
         throw not_implemented_exception();
/*         rtp::file * pfile =  new rtp::file(this);
         if(!pfile->rx_open(
            System.url().get_server(strPath),
            System.url().get_port(varFile)))
         {
            delete pfile;
            return NULL;
         }
         spfile(pfile);
         try
         {
            gen::property_set setQuery(this);
            setQuery.parse_url_query(System.url().get_query(strPath));
            if(setQuery["payload_type"] == "mp3"
            || setQuery["payload_type"].get_string().is_empty())
            {
               pfile->set_payload("mp3", &payload_type_mp3_128);
            }
         }
         catch(...)
         {
            return NULL;
         }*/
      }
      else if(gen::str::begins(strPath, "http://")
         ||   gen::str::begins(strPath, "https://"))
      {
         spfile(new sockets::http::file(get_app()));
         try
         {
            if(!spfile->open(strPath, nOpenFlags, pe))
            {
               spfile.destroy();
            }
         }
         catch(...)
         {
            return NULL;
         }
      }
      else if(gen::str::begins(strPath, "ifs://")
         ||   gen::str::begins(strPath, "uifs://"))
      {
         try
         {
            spfile(ifs(this, "").get_file(strPath, nOpenFlags, pe));
         }
         catch(...)
         {
            return NULL;
         }
      }
      else if(gen::str::begins_eat_ci(strPath, "matter://"))
      {
         try
         {
            spfile.create(this);
            if(!spfile->open(dir().matter(strPath), nOpenFlags, pe))
            {
               spfile.destroy();
            }
         }
         catch(...)
         {
            return NULL;
         }
      }
      else
      {
         spfile.create(this);
         try
         {
            if(!spfile->open(strPath, nOpenFlags, pe))
            {
               spfile.destroy();
            }
         }
         catch(...)
         {
            return NULL;
         }
      }
      return spfile;
   }

   ::ex1::byte_stream application::get_byte_stream(var varFile, UINT nOpenFlags, ex1::file_exception_sp * pe)
   {
      return ::ex1::byte_stream(get_file(varFile, nOpenFlags, pe));
   }

   int application::exit_instance()
   {

      m_iReturnCode = 0;

      try
      {
         m_iReturnCode = ::planebase::application::exit_instance();
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
            System.PostThreadMessageA(WM_QUIT, 0, 0);
         }
      }
      catch(...)
      {
      }



      return m_iReturnCode;
   }

   bool application::is_licensed(const char * pszId, bool bInteractive)
   {
      return license().has(pszId, bInteractive);
   }

   class ::fontopus::license & application::license()
   {
      return m_splicense;
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
         if((!is_system() && !is_bergedge()) || (is_bergedge() && System.directrix().m_varTopicQuery["show_platform"].get_integer() == 1))
         {
            if(m_spfsdata.is_null())
               m_spfsdata(new ::fs::set(this));
            ::fs::set * pset = dynamic_cast < ::fs::set * > ((class ::fs::data *) m_spfsdata);
            pset->m_spafsdata.add(new ::ifs(this, ""));
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



      if(!planebase::application::initialize())
         return false;

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

      if(!planebase::application::initialize1())
         return false;


      return true;

   }


   class ::fs::data * application::fs()
   {
      return m_spfsdata;
   }


   void application::set_title(const char * pszTitle)
   {

      Bergedge.set_app_title(m_strAppName, pszTitle);

   }


   bool application::on_install()
   {
      return ::planebase::application::on_install();
   }

   bool application::on_uninstall()
   {
      return ::planebase::application::on_uninstall();
   }

   bool application::is_serviceable()
   {
      return ::planebase::application::is_serviceable();
   }

   service_base * application::allocate_new_service()
   {
      return ::planebase::application::allocate_new_service();
   }


} //namespace plane


