#include "framework.h" // from "axis/user/user.h"




namespace axis
{


   UINT application::APPM_LANGUAGE = WM_APP + 117;
   WPARAM application::WPARAM_LANGUAGE_UPDATE = 1;


   application::application():
      m_framea(this)
   {

      m_peventReady = NULL;


#ifdef WINDOWS

      m_hinstance                = NULL;

#endif

      if(m_pauraapp != NULL)
      {

         m_paxisapp              = m_pauraapp->m_paxisapp;

      }

      m_paxisapp                 = this;

      if(m_pauraapp != NULL)
      {

         m_paxissystem           = m_pauraapp->m_paxissystem;

         if(m_pauraapp->m_paxissession == NULL && m_paxissystem != NULL)
         {

            m_paxissession       = m_paxissystem->m_paxissession;

         }
         else
         {

            m_paxissession       = m_pauraapp->m_paxissession;

         }

#ifdef WINDOWS

         m_hinstance             = m_pauraapp->m_hinstance;

#endif

      }
      else
      {

         m_paxissystem           = NULL;

      }

//      m_pcoreapp                 = NULL;

      



      m_psignal                  = canew(class signal());


      m_bLicense                 = true;

      // initialize wait cursor state
      m_iWaitCursorCount         = 0;

      m_bAxisProcessInitialize         = false;
      m_bAxisProcessInitializeResult   = false;

      m_bAxisInitialize1               = false;
      m_bAxisInitialize1Result         = false;

      m_bAxisInitialize                = false;
      m_bAxisInitializeResult          = false;

      m_bAxisInitializeInstance        = false;
      m_bAxisInitializeInstanceResult  = false;


      m_bShouldInitializeGTwf = true;
      m_bInitializeProDevianMode = true;

      m_pinitmaindata = NULL;


   }

   application::~application()
   {
   }


   void application::assert_valid() const
   {

      thread::assert_valid();


   }

   void application::dump(dump_context & dumpcontext) const
   {

      thread::dump(dumpcontext);

#ifdef WINDOWS

      dumpcontext << "m_hinstance = " << (void *)m_hinstance;

#endif

      //dumpcontext << "\nm_strCmdLine = " << m_strCmdLine;
      //dumpcontext << "\nm_nCmdShow = " << m_nCmdShow;
      dumpcontext << "\nm_bHelpMode = " << m_strAppName;

      dumpcontext << "\n";

   }




   bool application::is_system()
   {

      return false;

   }

   bool application::is_session()
   {

      return false;

   }


   bool application::is_serviceable()
   {

      return false;

   }




   void application::process_message_filter(int32_t code,signal_details * pobj)
   {

      if(pobj == NULL)
         return;   // not handled

      SCAST_PTR(::message::base,pbase,pobj);

      sp(::user::frame_window) pTopFrameWnd;
      //::user::interaction * pMainWnd;
      ::user::interaction * pMsgWnd;
      switch(code)
      {
      //case MSGF_DDEMGR:
         // Unlike other WH_MSGFILTER codes, MSGF_DDEMGR should
         //  never call the next hook.
         // By returning FALSE, the message will be dispatched
         //  instead (the default behavior).
         //return;

      case MSGF_MENU:
         pMsgWnd = pbase->m_pwnd;
         if(pMsgWnd != NULL)
         {
            pTopFrameWnd = pMsgWnd->GetTopLevelFrame();
            if(pTopFrameWnd != NULL && pTopFrameWnd->IsTracking() &&
               pTopFrameWnd->m_bHelpMode)
            {
               //pMainWnd = __get_main_window();
               //if((m_puiMain != NULL) && (IsEnterKey(pbase) || IsButtonUp(pbase)))
               //{
               //   //                  pMainWnd->SendMessage(WM_COMMAND, ID_HELP);
               //   pbase->m_bRet = true;
               //   return;
               //}
            }
         }
         // fall through...

      case MSGF_DIALOGBOX:    // handles message boxes as well.
         //pMainWnd = __get_main_window();
         if(code == MSGF_DIALOGBOX && m_puiActive != NULL &&
            pbase->m_uiMessage >= WM_KEYFIRST && pbase->m_uiMessage <= WM_KEYLAST)
         {
            //// need to translate messages for the in-place container
            //___THREAD_STATE* pThreadState = __get_thread_state();
            //ENSURE(pThreadState);

            //if (pThreadState->m_bInMsgFilter)
            //   return;
            //pThreadState->m_bInMsgFilter = TRUE;    // avoid reentering this code
            //if (m_puiActive->is_window_enabled())
            //{
            //   pre_translate_message(pobj);
            //   if(pobj->m_bRet)
            //   {
            //      pThreadState->m_bInMsgFilter = FALSE;
            //      return;
            //   }
            //}
            //pThreadState->m_bInMsgFilter = FALSE;    // ok again
         }
         break;
      }
      // default to not handled

   }

   

   bool application::verb()
   {

      axiom()->run();

      return true;

   }


   ptr_array < ::user::interaction > application::frames()
   {

      return m_framea.base_ptra();

   }


   void application::add_frame(sp(::user::interaction) pwnd)
   {

      synch_lock sl(&m_framea.m_mutex); // recursive lock (on m_framea.add(pwnd)) but m_puiMain is "cared" by m_frame.m_mutex

      System.defer_create_system_frame_window();

      Session.on_create_frame_window();

      m_framea.add(pwnd);

      //pwnd->get_app()->register_dependent_thread(System.get_twf());

      if(m_puiMain == NULL)
      {

         m_puiMain = pwnd;

      }

   }


   void application::remove_frame(sp(::user::interaction) pwnd)
   {

      synch_lock sl(&m_framea.m_mutex); // recursive lock (on m_framea.remove(pwnd)) but m_puiMain is "cared" by m_frame.m_mutex

      if(m_puiMain == pwnd)
      {

         m_puiMain = NULL;

      }

      m_framea.remove(pwnd);


   }




   ::user::interaction * application::window_from_os_data(void * pdata)
   {

      return window_from_handle((oswindow)pdata);

   }


   void application::DoWaitCursor(int32_t nCode)
   {

      if(nCode < 0)
      {

         m_iWaitCursorCount = 0;
         ShowWaitCursor(false);

      }
      else if(nCode == 0)
      {

         if(m_iWaitCursorCount > 0)
         {
            m_iWaitCursorCount--;
         }

         if(m_iWaitCursorCount > 0)
         {

            ShowWaitCursor(true);

         }

         m_iWaitCursorCount = 0;
         ShowWaitCursor(false);

      }
      else
      {

         if(m_iWaitCursorCount < 0)
         {
            m_iWaitCursorCount = 0;
         }

         m_iWaitCursorCount++;

         ShowWaitCursor(true);

      }



   }

   void application::ShowWaitCursor(bool bShow)
   {

      if(m_pimpl == NULL)
         return;

      m_pimpl->ShowWaitCursor(bShow);

   }



   void application::construct(const char * pszAppId)
   {

   }



   void application::TermThread(HINSTANCE hInstTerm)
   {

      throw interface_only_exception(this);

   }



   sp(::user::interaction) application::FindWindow(const char * lpszClassName,const char * lpszWindowName)
   {

      throw interface_only_exception(this);

   }


   sp(::user::interaction) application::FindWindowEx(oswindow oswindowParent,oswindow oswindowChildAfter,const char * lpszClass,const char * lpszWindow)
   {

      throw interface_only_exception(this);

   }


   string application::get_version()
   {

      throw interface_only_exception(this);

   }


   void application::SetCurrentHandles()
   {

      dappy(string(typeid(*this).name()) + " : SetCurrentHandles 1 : " + ::str::from(m_iReturnCode));
      m_pimpl->set_os_data(::get_current_thread());
      if(m_pthreadimpl->get_os_data() == NULL)
      {
         m_pthreadimpl->set_os_data(m_pimpl->get_os_data());
      }
      dappy(string(typeid(*this).name()) + " : SetCurrentHandles 2 : " + ::str::from(m_iReturnCode));
      m_pimpl->set_os_int(::get_current_thread_id());
      if(m_pthreadimpl->get_os_int() == 0)
      {
         m_pthreadimpl->set_os_int(m_pimpl->get_os_int());
      }

      m_pimpl->SetCurrentHandles();
      dappy(string(typeid(*this).name()) + " : SetCurrentHandles impled : " + ::str::from(m_iReturnCode));



   }


   void application::set_env_var(const string & var,const string & value)
   {

      throw interface_only_exception(this);

   }




   bool application::_001OnDDECommand(const char * lpcsz)
   {

      throw interface_only_exception(this);

   }


   void application::_001EnableShellOpen()
   {

      throw interface_only_exception(this);

   }


   ::user::document * application::_001OpenDocumentFile(var varFile)
   {

      throw interface_only_exception(this);

   }


   void application::_001OnFileNew(signal_details * pobj)
   {

      throw interface_only_exception(this);

   }


   sp(::user::printer) application::get_printer(const char * pszDeviceName)
   {

      throw interface_only_exception(this);

   }


   bool application::update_module_paths()
   {


      if(is_system())
      {

         if(!m_pimpl->update_module_paths())
            return false;


      }

      return true;


   }



   string application::veriwell_multimedia_music_midi_get_default_library_name()
   {

      if(m_pimpl == NULL)
         return "";

      return m_pimpl->veriwell_multimedia_music_midi_get_default_library_name();

   }



   string application::multimedia_audio_mixer_get_default_library_name()
   {

      if(m_pimpl == NULL)
         return "";

      return m_pimpl->multimedia_audio_mixer_get_default_library_name();

   }



   string application::multimedia_audio_get_default_library_name()
   {

      if(m_pimpl == NULL)
         return "";

      return m_pimpl->multimedia_audio_get_default_library_name();

   }



   string application::draw2d_get_default_library_name()
   {

      if(m_pimpl == NULL)
         return "draw2d_cairo";

      return m_pimpl->draw2d_get_default_library_name();

   }


   void application::_001CloseApplication()
   {

      throw todo(get_app());

   }


   sp(::user::interaction) application::release_capture_uie()
   {

#if defined(LINUX)

      oswindow oswindowCapture = ::GetCapture();
      if (oswindowCapture == NULL)
         return NULL;
      return oswindowCapture->get_user_interaction()->ReleaseCapture();

#elif defined(WINDOWS)

      oswindow oswindowCapture = ::GetCapture();
      if(oswindowCapture == NULL)
         return NULL;
      return System.window_from_os_data(oswindowCapture)->ReleaseCapture();

#elif defined(APPLEOS)

      oswindow oswindowCapture = ::GetCapture();
      if (oswindowCapture == NULL)
         return NULL;
      return oswindowCapture->get_user_interaction()->ReleaseCapture();

#else

      throw not_implemented(get_app());

#endif

   }


   sp(::user::interaction) application::get_capture_uie()
   {

#if defined(METROWIN)

      oswindow oswindowCapture = ::GetCapture();

      if (oswindowCapture == NULL)
         return NULL;

      ::user::interaction * pui = oswindowCapture->window();

      if (pui == NULL)
         return NULL;

      return pui->GetCapture();

#elif defined(WINDOWS) || defined(APPLE_IOS)

      oswindow oswindowCapture = ::GetCapture();

      if(oswindowCapture == NULL)
         return NULL;

      sp(::user::interaction) pui = System.window_from_os_data(oswindowCapture);

      if(pui == NULL)
         return NULL;

      return pui->GetCapture();

#else

      //      throw not_implemented(get_app());

      oswindow oswindowCapture = ::GetCapture();

      if (oswindowCapture == NULL)
         return NULL;

      return ::GetCapture()->get_user_interaction()->m_pimpl->GetCapture();

#endif

   }







   uint32_t application::get_thread_id()
   {
      return m_pimpl->get_thread_id();
   }





#ifndef METROWIN

   void application::get_time(timeval *p)
   {
      m_pimpl->get_time(p);
   }

#endif


   bool application::do_prompt_file_name(var & varFile,UINT nIDSTitle,uint32_t lFlags,bool bOpenFileDialog,sp(::user::impact_system) ptemplate,sp(::user::document) pdocument)
   {

      UNREFERENCED_PARAMETER(varFile);
      UNREFERENCED_PARAMETER(nIDSTitle);

      return false;

   }


   string CLASS_DECL_AXIS application::get_cred(const string & strRequestUrl,const RECT & rect,string & strUsername,string & strPassword,string strToken,string strTitle,bool bInteractive)
   {

      throw not_implemented(this);

   }




   bool application::get_temp_file_name_template(string & strRet,const char * pszName,const char * pszExtension,const char * pszTemplate)
   {

      throw not_implemented(this);

      return false;

   }


   bool application::get_temp_file_name(string & strRet,const char * pszName,const char * pszExtension)
   {

      return get_temp_file_name_template(strRet,pszName,pszExtension,NULL);

   }








   ::visual::icon * application::set_icon(object * pobject,::visual::icon * picon,bool bBigIcon)
   {

      ::visual::icon * piconOld = get_icon(pobject,bBigIcon);

      if(bBigIcon)
      {

         pobject->oprop("big_icon").operator =((sp(element)) picon);

      }
      else
      {

         pobject->oprop("small_icon").operator =((sp(element)) picon);

      }

      return piconOld;

   }


   ::visual::icon * application::get_icon(object * pobject,bool bBigIcon) const
   {

      if(bBigIcon)
      {

         return const_cast <object *> (pobject)->oprop("big_icon").cast < ::visual::icon >();

      }
      else
      {

         return const_cast <object *> (pobject)->oprop("small_icon").cast < ::visual::icon >();

      }

   }



   bool application::final_handle_exception(::exception::exception & e)
   {
      UNREFERENCED_PARAMETER(e);
      //linux      exit(-1);

      if(!is_system())
      {

         // get_app() may be it self, it is ok...
         if(Sys(get_app()).final_handle_exception((::exception::exception &) e))
            return true;


      }

      return false;
   }





   int32_t application::main()
   {

      TRACE(string(typeid(*this).name()) + " main");;

      dappy(string(typeid(*this).name()) + " : application::main 1");

      try
      {

         TRACE(string(typeid(*this).name()) + " on_run");;
         dappy(string(typeid(*this).name()) + " : going to on_run : " + ::str::from(m_iReturnCode));
         m_iReturnCode = 0;
         m_bReady = true;
         m_bRun = true;
         m_iReturnCode = on_run();
         if(m_iReturnCode != 0)
         {
            dappy(string(typeid(*this).name()) + " : on_run failure : " + ::str::from(m_iReturnCode));
            ::OutputDebugStringW(L"application::main on_run termination failure");
         }

      }
      catch(::exit_exception &)
      {

         dappy(string(typeid(*this).name()) + " : on_run exit_exception");

         System.post_thread_message(WM_QUIT,0,0);

         goto exit_application;

      }
      catch(...)
      {

         dappy(string(typeid(*this).name()) + " : on_run general exception");

         goto exit_application;

      }

      try
      {

         if(is_system())
         {

            dappy(string(typeid(*this).name()) + " : quiting main");

            //post_to_all_threads(WM_QUIT,0,0);

            //Sleep(5000);

         }

      }
      catch(...)
      {

      }

   exit_application:

      try
      {

         m_iReturnCode = exit();

      }
      catch(::exit_exception &)
      {

         post_to_all_threads(WM_QUIT,0,0);

         m_iReturnCode = -1;

      }
      catch(...)
      {

         m_iReturnCode = -1;

      }

      return m_iReturnCode;

   }




   bool application::pre_run()
   {

      TRACE(string(typeid(*this).name()) + " main_start");;
      try
      {

         m_dwAlive = ::get_tick_count();
         TRACE(string(typeid(*this).name()) + "application_pre_run");;
         int32_t m_iReturnCode = application_pre_run();
         if(m_iReturnCode != 0)
         {
            dappy(string(typeid(*this).name()) + " : applicationpre_run failure : " + ::str::from(m_iReturnCode));
            m_bReady = true;
            TRACE("application::main application_pre_run failure");
            return false;
         }

         xxdebug_box("pre_runnned","pre_runnned",MB_ICONINFORMATION);
         dappy(string(typeid(*this).name()) + " : pre_runned : " + ::str::from(m_iReturnCode));
         TRACE(string(typeid(*this).name()) + " initial_check_directrix");;
         if(!initial_check_directrix())
         {
            dappy(string(typeid(*this).name()) + " : initial_check_directrix failure");
            exit();
            m_iReturnCode = -1;
            m_bReady = true;
            ::OutputDebugStringW(L"exiting on check directrix");
            return false;
         }


         TRACE(string(typeid(*this).name()) + " os_native_bergedge_start");;
         m_dwAlive = ::get_tick_count();
         if(!os_native_bergedge_start())
         {
            dappy(string(typeid(*this).name()) + " : os_native_bergedge_start failure");
            exit();
            m_iReturnCode = -1;
            m_bReady = true;
            ::OutputDebugStringW(L"application::main os_native_bergedge_start failure");
            return false;
         }

         return true;
      }
      catch(::exit_exception &)
      {

         dappy(string(typeid(*this).name()) + " : main_start exit_exception");

         post_to_all_threads(WM_QUIT,0,0);

      }

      return false;

   }




   int32_t application::on_run()
   {
      int32_t m_iReturnCode = 0;

      try
      {
         ::aura::application_signal_details signal(this,m_psignal,::aura::application_signal_start);
         m_psignal->emit(&signal);
      }
      catch(...)
      {
      }

      dappy(string(typeid(*this).name()) + " : starting on_run : " + ::str::from(m_iReturnCode));

      thread * pthread = ::get_thread();

      install_message_handling(pthread->m_pthreadimpl);

      dappy(string(typeid(*this).name()) + " : starting on_run 2 : " + ::str::from(m_iReturnCode));

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
         catch(::exit_exception & e)
         {

            throw e;

         }
         catch(const ::exception::exception & e)
         {
            if(on_run_exception((::exception::exception &) e))
               goto run;
            if(final_handle_exception((::exception::exception &) e))
               goto run;
            try
            {
               m_iReturnCode = exit();
            }
            catch(::exit_exception & e)
            {

               throw e;

            }
            catch(...)
            {
               m_iReturnCode = -1;
            }
            goto InitFailure;
         }
      }
      catch(::exit_exception & e)
      {

         throw e;

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
         //      - uint16_t - html document to simplify here - with all history of undo and redos per document optimized by cvs, svn, syllomatter;
         //           - not directly related but use date and title to name document;
         //      - save forms after every key press in .undo.redo.form file parallel to appmatter / form/undo.redo.file parity;
         //      - last ::ikaraoke::karaoke song and scoring, a little less motivated at time of writing;
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
         //           - ::ikaraoke::karaoke file does not open? can open next? do it... may animate with a temporary icon...
         //           - import a little as pepper for the meal, prodevian technology into estamira, so gaming experience relativity can open ligh
         //               speed into cartesian dimensions of
         //               core, estamira and prodevian. Take care not to flood prodevian brand black ink over the floor of the estamira office...
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
         thread * pthread = this;
         if(pthread != NULL && pthread->m_pbReady != NULL)
         {
            *pthread->m_pbReady = true;
         }
      }
      catch(...)
      {
      }
      /*try
      {
      thread * pthread = dynamic_cast < thread * > (this);
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




   int32_t application::application_pre_run()
   {
   
      return ::aura::application::application_pre_run();

   }



   bool application::InitApplication()
   {

      return true;

   }



   bool application::initial_check_directrix()
   {

      return true;

   }


   bool application::on_install()
   {

      return true;

   }


   bool application::on_uninstall()
   {

      return true;

   }


   bool application::system_add_app_install(const char * pszId)
   {

      throw not_implemented(get_app());

      return true;

   }



   bool application::os_native_bergedge_start()
   {

      return true;

   }











   //   void application::construct(const char *pszId)
   //   {
   //      //if(m_strAppName.has_char())
   //      //   return;
   //      //m_strAppName.Empty();
   //      //m_strId.Empty();
   //      if (pszId == NULL)
   //      {
   //#ifdef WINDOWSEX
   //         wstring wstr = ::GetCommandLineW();
   //         string str = ::str::international::unicode_to_utf8(wstr);
   //         strsize iFind = str.find(" : ");
   //         if (iFind >= 0)
   //         {
   //            iFind = str.find("app=", iFind);
   //            if (iFind >= 0)
   //            {
   //               strsize iEnd = str.find(" ", iFind);
   //               if (iEnd < 0)
   //               {
   //                  m_strId = str.Mid(iFind + 4);
   //               }
   //               else
   //               {
   //                  m_strId = str.Mid(iFind + 4, iEnd - iFind - 4);
   //               }
   //               ::str::begins_eat(m_strId, "\"");
   //               ::str::ends_eat(m_strId, "\"");
   //            }
   //         }
   //#endif
   //      }
   //      else
   //      {
   //         m_strId = pszId;
   //      }
   //      if (m_strId.is_empty())
   //         m_strId = "mplite";
   //      construct();
   //      if (m_strAppName.is_empty())
   //      {
   //         if (m_strAppId.has_char())
   //            m_strAppName = m_strAppId;
   //         else if (m_strInstallToken.has_char())
   //            m_strAppName = m_strInstallToken;
   //      }
   //   }


   //void application::construct()
   //{
   //   string strId = m_strId;
   //   char chFirst = '\0';
   //   if (strId.get_length() > 0)
   //   {
   //      chFirst = strId[0];
   //   }

   //   ::core::application::construct();

   //}




   //void application::_001OnFileNew()
   //{
   //   string strId = m_strId;
   //   char chFirst = '\0';
   //   if (strId.get_length() > 0)
   //   {
   //      chFirst = strId[0];
   //   }
   //   ::core::application::_001OnFileNew(NULL);
   //}


   //bool application::bergedge_start()
   //{
   //   string strId = m_strId;
   //   char chFirst = '\0';
   //   if (strId.get_length() > 0)
   //   {
   //      chFirst = strId[0];
   //   }
   //   return ::core::application::bergedge_start();
   //}



   //bool application::on_install()
   //{
   //   string strId = m_strId;
   //   char chFirst = '\0';
   //   if (strId.get_length() > 0)
   //   {
   //      chFirst = strId[0];
   //   }
   //   return ::core::application::on_install();
   //}

   //bool application::on_uninstall()
   //{
   //   string strId = m_strId;
   //   char chFirst = '\0';
   //   if (strId.get_length() > 0)
   //   {
   //      chFirst = strId[0];
   //   }
   //   return ::core::application::on_uninstall();
   //}


   void application::on_request(sp(::create_context) pcreatecontext)
   {

      ::request_interface::on_request(pcreatecontext);

      command()->consolidate(pcreatecontext);

   }


   //bool application::is_serviceable()
   //{


   //   string strId = m_strId;
   //   char chFirst = '\0';
   //   if (strId.get_length() > 0)
   //   {
   //      chFirst = strId[0];
   //   }
   //   return ::core::application::is_serviceable();
   //}

   //service_base * application::allocate_new_service()
   //{

   //   return NULL;

   //}


   //sp(::user::document) application::_001OpenDocumentFile(var varFile)
   //{
   //   string strId = m_strId;
   //   char chFirst = '\0';
   //   if (strId.get_length() > 0)
   //   {
   //      chFirst = strId[0];
   //   }
   //   return ::core::application::_001OpenDocumentFile(varFile);

   //}


   int32_t application::run()
   {

      if(is_system() || is_session())
      {

         return ::thread::run();

      }
      else if((command()->m_varTopicQuery.has_property("install")
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
            return ::thread::run();
         }
         else
         {
            return ::thread::run();
         }
      }
      else
      {
         return ::thread::run();
      }

      return 0;

   }




   bool application::is_installing()
   {

      return directrix()->has_property("install");

   }


   bool application::is_uninstalling()
   {

      return directrix()->has_property("uninstall");

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



   bool application::process_initialize()
   {

      if(m_bAxisProcessInitialize)
         return m_bAxisProcessInitializeResult;

      m_bAxisProcessInitialize = true;
      m_bAxisProcessInitializeResult = false;


      if(!::aura::application::process_initialize())
         return false;
      

      if(is_system())
      {

         draw2d_factory_exchange();

      }

      m_bAxisProcessInitializeResult = true;

      return true;

   }


   bool application::initialize_instance()
   {

      if(!::aura::application::initialize_instance())
         return false;

      return true;

   }


   bool application::initialize1()
   {

      if(m_bAxisInitialize1)
         return m_bAxisInitialize1Result;

      m_bAxisInitialize1 = true;

      m_bAxisInitialize1Result = false;

      if(!::aura::application::initialize1())
         return false;

      m_dwAlive = ::get_tick_count();

      m_bAxisInitialize1Result = true;

      return true;

   }


   bool application::initialize2()
   {

      if(!::aura::application::initialize2())
         return false;

      return true;

   }


   bool application::initialize3()
   {

      if(!::aura::application::initialize3())
         return false;

      return true;

   }


   bool application::initialize()
   {

      if(!::aura::application::initialize())
         return false;
      
      return true;

   }


   int32_t application::exit_instance()
   {


      try
      {

         m_iReturnCode = ::aura::application::exit_instance();

      }
      catch(...)
      {

         m_iReturnCode = -1;

      }


      return m_iReturnCode;

   }


   bool application::finalize()
   {

      bool bOk = false;

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


   void application::on_exclusive_instance_conflict(EExclusiveInstance eexclusive)
   {

      if(eexclusive == ExclusiveInstanceLocal)
      {

         on_exclusive_instance_local_conflict();

      }

   }


   void application::on_exclusive_instance_local_conflict()
   {

   }


   string application::get_mutex_name_gen()
   {
      return m_strAppName;
   }



   bool application::Ex2OnAppInstall()
   {
      return true;
   }

   bool application::Ex2OnAppUninstall()
   {
      return true;
   }


   void application::draw2d_factory_exchange()
   {

#ifdef CUBE

      ::draw2d_factory_exchange(this);

#else

      string strLibrary = draw2d_get_default_library_name();

      if(strLibrary.is_empty())
         strLibrary = "draw2d_cairo";

      ::aura::library & library = System.m_libraryDraw2d;

      if(library.is_opened())
         return;

      if(!library.open(strLibrary))
      {
         if(strLibrary != "draw2d_cairo")
         {
            if(!library.open("draw2d_cairo"))
            {
               throw "failed to do draw2d factory exchange";
            }
         }
         else
         {
            throw "failed to do draw2d factory exchange";
         }
      }


      PFN_ca2_factory_exchange pfn_ca2_factory_exchange = library.get < PFN_ca2_factory_exchange >("ca2_factory_exchange");

      pfn_ca2_factory_exchange(this);

#endif


   }












   int32_t application::simple_message_box_timeout(sp(::user::interaction) pwndOwner,const char * pszMessage,::duration durationTimeOut,UINT fuStyle)
   {
      UNREFERENCED_PARAMETER(durationTimeOut);
      return simple_message_box(pwndOwner,pszMessage,fuStyle);
   }



   string application::get_license_id()
   {

      return m_strAppId;

   }




   ::user::user * application::create_user()
   {

      return canew(::user::user(this));

   }



   bool application::defer_initialize_twf()
   {

      if(System.m_ptwf == NULL && (System.m_bShouldInitializeGTwf && m_bShouldInitializeGTwf && m_bInitializeProDevianMode))
      {

         if(!System.initialize_twf())
            return false;

      }

      return true;

   }


   bool application::assert_user_logged_in()
   {

      return false;

   }


   ::user::interaction * application::get_active_guie()
   {

      return Session.get_active_guie();

   }


   ::user::interaction * application::get_focus_guie()
   {

      return Session.get_focus_guie();

   }


   

   bool application::on_thread_on_idle(::thread_impl * pimpl, LONG lCount)
   {

      ASSERT_VALID(this);

#if defined(WINDOWS) && defined(DEBUG) && !defined(___NO_DEBUG_CRT)
      // check core API's allocator (before idle)
      if(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) & _CRTDBG_CHECK_ALWAYS_DF)
         ASSERT(__check_memory());
#endif

      single_lock sl(&pimpl->m_mutexUiPtra,TRUE);


      if(lCount <= 0 && pimpl->m_spuiptra.is_set())
      {
         for(int32_t i = 0; i <pimpl-> m_spuiptra->get_count();)
         {
            ::user::interaction * pui = pimpl->m_spuiptra->element_at(i);
            bool bOk = false;
            try
            {

               bOk = pui != NULL && pui->IsWindowVisible();
            }
            catch(...)
            {
            }
            if(!bOk)
            {
               pimpl->m_spuiptra->remove_at(i);
            }
            else
            {
               sl.unlock();
               try
               {
                  pui->send_message(WM_IDLEUPDATECMDUI,(WPARAM)TRUE);
               }
               catch(...)
               {

               }
               sl.lock();
               i++;
            }
         }


      }
      else if(lCount >= 0)
      {
      }

#if defined(WINDOWS) && defined(DEBUG) && !defined(___NO_DEBUG_CRT)
      // check core API's allocator (after idle)
      if(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) & _CRTDBG_CHECK_ALWAYS_DF)
         ASSERT(__check_memory());
#endif



      return lCount < 0;  // nothing more to do if lCount >= 0

   }


   bool application::post_user_message(::thread_impl * pimpl,::user::interaction * pui,UINT message,WPARAM wparam,lparam lparam)
   {

      if(pimpl->m_hthread == NULL)
         return false;

      ::user::message * pmessage    = new ::user::message;
      pmessage->m_pui               = pui;
      pmessage->m_uiMessage         = message;
      pmessage->m_wparam            = wparam;
      pmessage->m_lparam            = lparam;

      return pimpl->post_thread_message(WM_APP + 1984,77,(LPARAM)pmessage) != FALSE;

   }



   bool application::is_window(::user::interaction * pui)
   {

      return pui->IsWindow();

   }

   LRESULT application::send_message(::user::interaction * pui,UINT message,WPARAM wparam,lparam lparam)
   {

      return pui->send_message(message, wparam, lparam);

   }

   oswindow application::get_safe_handle(::user::interaction * pui)
   {

      return pui->get_safe_handle();

   }

   void application::dispatch_user_message(::message::base * pbase)
   {

      smart_pointer < ::user::message > spmessage(pbase->m_lparam);
      spmessage->send();
      pbase->m_uiMessage   = 0;    // ssshhhh.... - self-healing - sh...
      pbase->m_wparam      = 0;    // ssshhhh.... - self-healing - sh...
      pbase->m_bRet        = true;
      return;

   }


   ::user::interaction * application::get_parent(::user::interaction * pui)
   {

      return pui->GetParent();

   }


   bool application::enable_window(::user::interaction * pui, bool bEnable)
   {

      return pui->enable_window(bEnable);

   }


   bool application::set_window_text(::user::interaction * pui,const string & strText)
   {

      pui->SetWindowText(strText);

      return true;

   }


   comparable_array < ::thread * > application::get_thread(::user::interaction * pui)
   {

      return pui->m_threadptra;

   }


   void application::add_thread(::user::interaction * pui,::thread * pthread)
   {

      pui->m_threadptra.add_unique(pthread);

   }

   void application::remove_thread(::user::interaction * pui,::thread * pthread)
   {

      pui->m_threadptra.remove(pthread);

   }

   void application::window_graphics_update_window(window_graphics * & pdata,oswindow interaction_impl,COLORREF * pOsBitmapData,const RECT & rect,int cxParam, int cyParam, int iStride)
   {

      window_graphics::update_window(pdata,interaction_impl,pOsBitmapData,rect,cxParam, cyParam, iStride);

   }



   sp(::message::base) application::get_message_base(LPMESSAGE lpmsg)
   {

      ::user::interaction * pwnd = NULL;

#if defined(METROWIN)
      if(pwnd == NULL && lpmsg->oswindow != NULL)
      {
         ::user::interaction * pwindow = lpmsg->oswindow->interaction_impl();
#else
      if(pwnd == NULL && lpmsg->hwnd != NULL)
      {

         if(lpmsg->message == 126)
         {

            TRACE0("WM_DISPLAYCHANGE");

         }

         ::user::interaction * pwindow = System.window_from_os_data(lpmsg->hwnd);
#endif
         if(pwindow != NULL)
         {
            try
            {
               pwnd = pwindow;
            }
            catch(...)
            {
               pwnd = NULL;
            }
         }

         if(pwnd == NULL)
            return NULL;

      }


      if(pwnd != NULL)
         return pwnd->get_base(lpmsg->message,lpmsg->wParam,lpmsg->lParam);

      ::thread * pthread = ::get_thread();

      if(pthread != NULL)
         return pthread->get_base(lpmsg->message,lpmsg->wParam,lpmsg->lParam);

      return get_base(lpmsg->message,lpmsg->wParam,lpmsg->lParam);

   }


   void application::process_message(signal_details * pobj)
   {

      sp(::message::base) pbase = pobj;

      if(pbase.is_null() || pbase->m_pwnd == NULL)
      {

         try
         {

            message_handler(pobj);

         }
         catch(const ::exception::exception & e)
         {

            TRACE("application::process_message : error processing application thread message (const ::exception::exception & )");

            if(App(this).on_run_exception((::exception::exception &) e))
               goto run;

            if(App(this).final_handle_exception((::exception::exception &) e))
               goto run;

            __post_quit_message(-1);

            pbase->set_lresult(-1);

            return;

         }
         catch(::exception::base * pe)
         {

            process_window_procedure_exception(pe,pbase);

            TRACE(::aura::trace::category_AppMsg,0,"Warning: Uncaught exception in message_handler (returning %ld) (application::process_message : error processing application thread message).\n",(int_ptr)pbase->get_lresult());

            pe->Delete();

         }
         catch(...)
         {

            TRACE("application::process_message : error processing application thread message (...)");

         }

         return;

      }

      try
      {

         pbase->m_pwnd->message_handler(pobj);

         
      }
      catch(const ::exception::exception & e)
      {

         TRACE("application::process_message : error processing window message (const ::exception::exception & )");

         if(App(this).on_run_exception((::exception::exception &) e))
            goto run;

         if(App(this).final_handle_exception((::exception::exception &) e))
            goto run;

         __post_quit_message(-1);

         pbase->set_lresult(-1);

         return;

      }
      catch(::exception::base * pe)
      {

         process_window_procedure_exception(pe,pbase);

         TRACE(::aura::trace::category_AppMsg,0,"Warning: Uncaught exception in message_handler (returning %ld) (application::process_message : error processing window message).\n",(int_ptr)pbase->get_lresult());

         pe->Delete();

      }
      catch(...)
      {

         TRACE("application::process_message : error processing window message (...)");

      }

   run:;

   }




} // namespace axis







