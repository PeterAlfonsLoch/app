#include "StdAfx.h"


namespace planebase
{


   CLASS_DECL_ca LPFN_instantiate_application g_lpfn_instantiate_application = NULL;


   application::application()
   {


      m_dir.set_app(this);
      m_file.set_app(this);
      m_http.set_app(this);

      m_bIfs            = true;

      m_pservice = NULL;

   }

   application::~application()
   {
   }

   class ::ca::dir::application & application::dir()
   {
      return m_dir;
   }

   class ::ca::file::application & application::file()
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


         pcaapp = System.get_new_app(this, pszId);

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
         System.install().start(strId);
         throw installing_exception();
         return NULL;
      }


      return pcaapp;
   }


   ::ca::application * application::create_application(const char * pszId, bool bSynch, ::ca::application_bias * pbias)
   {

      ::ca::application * pcaapp = instantiate_application(pszId, pbias);

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

      m_dir.m_psystem = m_psystem;
      m_file.m_psystem = m_psystem;

      {
         string strLibraryRoot;
         string strLibraryName;
         if(m_strLibraryName.has_char() && m_strLibraryName != "app_" + m_strAppName
            && gen::str::begins_ci(m_strLibraryName, "app_") && m_strLibraryName.find("_", strlen("app_")) > 4)
         {
            stringa stra2;
            stra2.add_tokens(m_strLibraryName, "_", FALSE);
            strLibraryRoot = stra2[1];
            strLibraryName = stra2.implode("_", 2);
         }
         else
         {
            strLibraryName = m_strLibraryName;
         }

         stringa stra;
         stra.add_tokens(m_strAppName, "_", FALSE);
         for(int i = 1; i < stra.get_upper_bound(); i++)
         {
            stra[i] == "_" + stra[i];
         }
         if(stra.get_size() > 1)
         {
            if(strLibraryRoot.has_char())
            {
               m_strRoot = "app-" + strLibraryRoot;
            }
            else
            {
               m_strRoot = "app-" + stra[0];
            }
            stra.remove_at(0);
            if(strLibraryName.has_char() && strLibraryName != "app_" + m_strAppName)
            {
               stra.insert_at(stra.get_upper_bound(), strLibraryName);
            }
            m_strDomain += stra.implode("/");
         }
         else
         {
            if(strLibraryRoot.has_char())
            {
               m_strRoot = "app-" + strLibraryRoot;
            }
            else
            {
               m_strRoot = "app";
            }
            if(strLibraryName.has_char() && strLibraryName != "app_" + m_strAppName)
            {
               m_strDomain = strLibraryName + "/";
            }
            m_strDomain += m_strAppName;
         }
      }


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
         if(::fontopus::application::on_install())
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
               else if(command().m_varTopicQuery.has_property("session_start") && strId == command().m_varTopicQuery["session_start"])
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
         if(::fontopus::application::on_uninstall())
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
         spfile(varFile.propset()["file"].ca2 < ::ex1::file >());
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
      else if(gen::str::begins(strPath, "http://")
         ||   gen::str::begins(strPath, "https://"))
      {
         spfile(new sockets::http::file(get_app()));
         if(!spfile->open(strPath, nOpenFlags, pe))
         {
            spfile.destroy();
         }
      }
      else if(gen::str::begins(strPath, "ifs://")
         ||   gen::str::begins(strPath, "uifs://"))
      {
         spfile(AppUser(this).m_pifs->get_file(strPath, nOpenFlags, pe));
      }
      else if(gen::str::begins_eat_ci(strPath, "matter://"))
      {
         ::ca::application * papp;
         if(System.url().get_server("matter://" + strPath) == App(m_papp).m_strAppName)
         {
            strPath = System.url().get_object("matter://" + strPath).Mid(1);
         }
         else if(&Session != NULL && Session.m_mapApplication.Lookup(System.url().get_server("matter://" + strPath), papp) && App(papp).m_strAppName.has_char())
         {
            return App(papp).get_file("matter://" + strPath, nOpenFlags, pe);
         }
         spfile.create(this);
         if(!spfile->open(dir().matter(strPath), nOpenFlags, pe))
         {
            spfile.destroy();
         }
      }
      else
      {
         spfile.create(this);
         if(!spfile->open(strPath, nOpenFlags, pe))
         {
            spfile.destroy();
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
         if(&Session != NULL)
         {
            if(m_spfsdata.is_null())
               m_spfsdata(new ::fs::set(this));
            ::fs::set * pset = dynamic_cast < ::fs::set * > ((class ::fs::data *) m_spfsdata);
            pset->m_spafsdata.add(Session.m_pifs);
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


   class ::fs::data * application::fs()
   {
      return m_spfsdata;
   }


   void application::set_title(const char * pszTitle)
   {

      Session.set_app_title(m_strAppName, pszTitle);

   }



   FileManagerTemplate * application::GetStdFileManagerTemplate(void)
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

   bool application::create_service()
   {

      if(m_strAppName.is_empty()
      || m_strAppName.CompareNoCase("bergedge") == 0
      || !is_serviceable())
         return false;

      SC_HANDLE hdlSCM = OpenSCManager(0, 0, SC_MANAGER_CREATE_SERVICE);

      string strCalling = m_strModulePath + " : app=" + m_strAppName + " service usehostlogin";

      if(hdlSCM == 0)
      {
         //::GetLastError()
         return false;
      }
    
      SC_HANDLE hdlServ = ::CreateService(
         hdlSCM,                    // SCManager database 
         "CGCLCSTvotagusCa2FontopusMain-" + m_strAppName,               // name of service 
         "ccvotagus ca2 fontopus " + m_strAppName,        // service name to display 
         STANDARD_RIGHTS_REQUIRED,  // desired access 
         SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS, // service type 
         SERVICE_AUTO_START,      // start type 
         SERVICE_ERROR_NORMAL,      // error control type 
         strCalling,                   // service's binary Path name
         0,                      // no load ordering group 
         0,                      // no tag identifier 
         0,                      // no dependencies 
         0,                      // LocalSystem account 
         0);                     // no password 
    
      if (!hdlServ)
      {
         CloseServiceHandle(hdlSCM);
         //Ret = ::GetLastError();
         return FALSE;
      }
       
      CloseServiceHandle(hdlServ);
      CloseServiceHandle(hdlSCM);

      return true;
   }

   bool application::remove_service()
   {

      if(m_strAppName.is_empty()
      || m_strAppName.CompareNoCase("bergedge") == 0
      || !is_serviceable())
         return false;

      SC_HANDLE hdlSCM = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);

      if(hdlSCM == 0)
      {
         //::GetLastError();
         return false;
      }
    
      SC_HANDLE hdlServ = ::OpenService(
         hdlSCM,                    // SCManager database 
         "CGCLCSTvotagusCa2FontopusMain-" + m_strAppName,               // name of service 
         DELETE);                     // no password 
    
      if (!hdlServ)
      {
         // Ret = ::GetLastError();
         CloseServiceHandle(hdlSCM);
         return false;
      }

      ::DeleteService(hdlServ);

      CloseServiceHandle(hdlServ);

      CloseServiceHandle(hdlSCM);

      return false;
   }


   bool application::start_service()
   {

      if(m_strAppName.is_empty()
      || m_strAppName.CompareNoCase("bergedge") == 0
      || !is_serviceable())
         return false;

      SC_HANDLE hdlSCM = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);

      if(hdlSCM == 0)
      {
         //::GetLastError();
         return false;
      }
    
      SC_HANDLE hdlServ = ::OpenService(
         hdlSCM,                    // SCManager database 
         "CGCLCSTvotagusCa2FontopusMain-" + m_strAppName,               // name of service 
         SERVICE_START);                     // no password 
    
    
      if (!hdlServ)
      {
         CloseServiceHandle(hdlSCM);
         //Ret = ::GetLastError();
         return FALSE;
      }
       
      BOOL bOk = StartService(hdlServ, 0, NULL);

      CloseServiceHandle(hdlServ);
      CloseServiceHandle(hdlSCM);

      return bOk != FALSE;
   }

   bool application::stop_service()
   {

      if(m_strAppName.is_empty()
      || m_strAppName.CompareNoCase("bergedge") == 0
      || !is_serviceable())
         return false;

      SC_HANDLE hdlSCM = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);

      if(hdlSCM == 0)
      {
         //::GetLastError();
         return false;
      }
    
      SC_HANDLE hdlServ = ::OpenService(
         hdlSCM,                    // SCManager database 
         "CGCLCSTvotagusCa2FontopusMain-" + m_strAppName,               // name of service 
         SERVICE_STOP);                     // no password 
    
      if (!hdlServ)
      {
         // Ret = ::GetLastError();
         CloseServiceHandle(hdlSCM);
         return false;
      }

      SERVICE_STATUS ss;

      memset(&ss, 0, sizeof(ss));

      BOOL bOk = ::ControlService(hdlServ, SERVICE_CONTROL_STOP, &ss);

      ::DeleteService(hdlServ);

      CloseServiceHandle(hdlServ);

      CloseServiceHandle(hdlSCM);

      return bOk != FALSE;
   }

  
   BOOL application::run()
   {
      if (command().m_varTopicQuery.has_property("service"))
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

   bool application::on_install()
   {

      if(is_serviceable())
      {
         create_service();
         start_service();
      }

      try
      {
         string strRoot;
         string strDomain;
         if(is_system())
         {
            strRoot     = "app";
            strDomain   = "main";
         }
         else if(is_session())
         {
            return true;
         }
         else if(is_cube())
         {
            return true;
         }
         else if(is_bergedge())
         {
            strRoot     = "app";
            strDomain   = "bergedge";
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

         update_appmatter(strRoot, strDomain);
      }
      catch(...)
      {
         return false;
      }


      return true;

   }


   bool application::update_appmatter(const char * pszRoot, const char * pszRelative)
   {
      
      gen::international::locale_style localestyle(this);


      
      
      string strLocale;
      string strStyle;

      
      if(Application.directrix().m_varTopicQuery["locale"].has_char() && Application.directrix().m_varTopicQuery["locale"].get_string().CompareNoCase("_std") != 0)
      {
         if(Application.directrix().m_varTopicQuery["style"].has_char() && Application.directrix().m_varTopicQuery["style"].get_string().CompareNoCase("_std") != 0)
         {
            localestyle.add_locale_variant(Application.directrix().m_varTopicQuery["locale"], Application.directrix().m_varTopicQuery["style"]);
         }
         localestyle.add_locale_variant(Application.directrix().m_varTopicQuery["locale"], Application.directrix().m_varTopicQuery["locale"]);
      }
      
      
      if(Application.directrix().m_varTopicQuery["lang"].has_char() && Application.directrix().m_varTopicQuery["lang"].get_string().CompareNoCase("_std") != 0)
      {
         if(Application.directrix().m_varTopicQuery["style"].has_char() && Application.directrix().m_varTopicQuery["style"].get_string().CompareNoCase("_std") != 0)
         {
            localestyle.add_locale_variant(Application.directrix().m_varTopicQuery["lang"], Application.directrix().m_varTopicQuery["style"]);
         }
         localestyle.add_locale_variant(Application.directrix().m_varTopicQuery["lang"], Application.directrix().m_varTopicQuery["lang"]);
      }
      
      
      if(Application.directrix().m_varTopicQuery["style"].has_char() && Application.directrix().m_varTopicQuery["style"].get_string().CompareNoCase("_std") != 0)
      {
         localestyle.add_locale_variant(get_locale(), Application.directrix().m_varTopicQuery["style"]);
      }
      if(get_style().has_char() && get_style().CompareNoCase("_std") != 0 && get_style().CompareNoCase(get_locale()) != 0)
      {
         localestyle.add_locale_variant(get_locale(), Application.directrix().m_varTopicQuery["style"]);
      }
      localestyle.add_locale_variant(get_locale(), get_locale());


      localestyle.add_locale_variant("en", get_style());
      localestyle.add_locale_variant("en", get_locale());
      localestyle.add_locale_variant(get_style(), "en");
      localestyle.add_locale_variant(get_locale(), "en");
      localestyle.add_locale_variant("en", "en");

      
      localestyle.add_locale_variant("_std", get_style());
      localestyle.add_locale_variant("_std", get_locale());
      localestyle.add_locale_variant(get_style(), "_std");
      localestyle.add_locale_variant(get_locale(), "_std");
      localestyle.add_locale_variant("_std", "_std");


      localestyle.finalize();

      
      for(int i = 0; i < localestyle.m_straLocale.get_count(); i++)
      {
         update_appmatter(pszRoot, pszRelative, localestyle.m_straLocale[i], localestyle.m_straStyle[i]);
      }


      return true;

   }
   
   bool application::update_appmatter(const char * pszRoot, const char * pszRelative, const char * pszLocale, const char * pszStyle)
   {

      string strLocale;
      string strStyle;
      string strRelative = System.dir().path(System.dir().path(pszRoot, "appmatter", pszRelative), App(this).get_locale_style_dir(pszLocale, pszStyle)) + ".zip";
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

      Application.http().get(strUrl, mem);

      primitive::memory_file file(get_app(), &mem);

      if(mem.get_size() > 0)
      {

         zip::Util util;

         string strDir = strFile;

         gen::str::ends_eat_ci(strDir, ".zip");

         util.extract_all(strDir, &file);

         //System.compress().extract_all(strFile, this);

      }

      return true;

   }


} //namespace planebase


