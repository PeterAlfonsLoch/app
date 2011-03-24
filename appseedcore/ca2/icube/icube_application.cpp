#include "StdAfx.h"

namespace icube
{

   CLASS_DECL_ca LPFN_instantiate_application g_lpfn_instantiate_application = NULL;

   application::application()
   {
      m_dir.set_app(this);
      m_file.set_app(this);
      m_http.set_app(this);
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


   ::ca::application * application::instantiate_application(const char * pszId)
   {

      ::ca::application * pcaapp = NULL;
      ::ca2::application * papp = NULL;

      string strId(pszId);

      if(strId.CompareNoCase("bergedge") == 0)
      {
         ::bergedge::bergedge * pbergedge = new ::bergedge::bergedge();
         pcaapp = pbergedge;
         pcaapp->m_pbergedge = pbergedge;
         pbergedge->construct();
      }
      else
      {
         pcaapp                                       = g_lpfn_instantiate_application(this, pszId);
         pcaapp->m_pbergedge                          = m_pbergedge;
         if(pcaapp->m_bService)
         {
            pcaapp->m_puiInitialPlaceHolderContainer  = NULL;
         }
         else
         {
            pcaapp->m_puiInitialPlaceHolderContainer  = m_pbergedge->force_get_document()->get_view();
         }
      }

      pcaapp->m_papp                               = this;
      pcaapp->m_psystem                            = m_psystem;
      
      

      papp = dynamic_cast < ::ca2::application * > (pcaapp);

      papp->m_bSessionSynchronizedCursor = m_bSessionSynchronizedCursor;



      if((papp == NULL || papp->m_strAppName != strId) 
         &&
         (!System.command_line().m_varQuery.has_property("install")
         && !System.command_line().m_varQuery.has_property("uninstall")))
      {
         TRACE("Failed to instantiate %s, going to try installation through ca2_cube_install", strId);
         ::icube::ca2_cube_install(strId);
         return NULL;
      }


      return pcaapp;
   }


   ::ca::application * application::create_application(const char * pszId, bool bSynch, ::ca::application_bias * pbias)
   {

      ::ca::application * pcaapp = instantiate_application(pszId);

      if(pcaapp == NULL)
         return NULL;

      ::ca2::application * papp = dynamic_cast < ::ca2::application * > (pcaapp);

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
         CSingleLock sl(peventReady, TRUE);
      }

      return papp;
   }


   int application::pre_run()
   {

      if(is_system())
      {
         se_translator::attach();
      }

      int nReturnCode            = 0;

      // App global initializations (rare)
      if (!InitApplication())
         goto InitFailure;

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
               nReturnCode = -1;
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
               nReturnCode = exit();
            }
            catch(...)
            {
               nReturnCode = -1;
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
      run:
      return nReturnCode;
   }


   int application::on_run()
   {
      int nReturnCode = 0;
      _001InstallMessageHandling(System.GetThread()->::ca::smart_pointer < ::ca::thread > ::m_p);
      try
      {
         try
         {
            if(m_peventReady != NULL)
               m_peventReady->SetEvent();
         }
         catch(...)
         {
         }
         run:
         try
         {
            nReturnCode = run();
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
               nReturnCode = exit();
            }
            catch(...)
            {
               nReturnCode = -1;
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
      try
      {
         nReturnCode = exit();
      }
      catch(...)
      {
         nReturnCode = -1;
      }
InitFailure:
      try
      {
         if(m_peventReady != NULL)
            m_peventReady->SetEvent();
      }
      catch(...)
      {
      }
      if(is_system())
      {
         se_translator::detach();
      }

      if(!is_system())
      {
         try
         {
            delete this;
         }
         catch(...)
         {
         }
      }

      return nReturnCode;
   }

   int application::main()
   {
      int nReturnCode = pre_run();
      if(nReturnCode != 0)
      {
         TRACE("application::main pre_run failure");
         return nReturnCode;
      }
      if(!os_native_bergedge_start())
      {
         TRACE("application::main os_native_bergedge_start failure");
         return -1;
      }
      nReturnCode = on_run();
      if(nReturnCode != 0)
      {
         TRACE("application::main on_run termination failure");
         return nReturnCode;
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

} //namespace icube


