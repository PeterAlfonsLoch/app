#include "framework.h"


//extern thread_local_storage * gen_ThreadData;


namespace metrowin
{


   application::application(::base::application * papp) :
      element(papp)
   {

      m_pthreadimpl.create(allocer());
      m_pthreadimpl->m_p = this;

      WIN_THREAD(m_pthreadimpl.m_p)->m_pAppThread = this;

      m_pbasesystem = papp->m_pcoreapp->m_pbasesystem;

      m_pfilemanager = NULL;



      // in non-running state until WinMain
//      m_hInstance = NULL;
//      m_hLangResourceDLL = NULL;
      m_pszHelpFilePath = NULL;
      m_pszProfileName = NULL;
      m_pszRegistryKey = NULL;
//      m_pRecentFileList = NULL;
//      m_pdocmanager = NULL;
      m_atomApp = m_atomSystemTopic = NULL;
      //m_lpCmdLine = NULL;
//      m_pCmdInfo = NULL;

      // initialize wait cursor state
//      m_nWaitCursorCount = 0;
      m_hcurWaitCursorRestore = NULL;

      // initialize current printer state
      m_hDevMode = NULL;
      m_hDevNames = NULL;
      m_nNumPreviewPages = 0;     // not specified (defaults to 1)

      // other initialization
      m_bHelpMode = FALSE;
//      m_eHelpType = afxWinHelp;
      m_nSafetyPoolSize = 512;        // default size

      shell::theWindowsShell.Initialize();
   }

   application::~application()
   {

   }


   void application::_001OnFileNew()
   {
      m_pimpl->_001OnFileNew(NULL);
   }

   sp(::user::object) application::_001OpenDocumentFile(var varFile)
   {
      return m_pimpl->_001OpenDocumentFile(varFile);
   }

   void application::_001EnableShellOpen()
   {
      ASSERT(m_atomApp == NULL && m_atomSystemTopic == NULL); // do once
/*
      m_atomApp            = ::GlobalAddAtomW(::str::international::utf8_to_unicode(m_strAppName));
      m_atomSystemTopic    = ::GlobalAddAtomW(L"system");*/
   }

   bool application::_001OnDDECommand(const char * lpcsz)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      return FALSE;
   }

   HINSTANCE application::GetHinstance()
   {
      return NULL;
   }

   string application::get_version()
   {
#ifdef WINDOWSEX
      char lpszModuleFilePath[MAX_PATH + 1];
      GetModuleFileName(NULL, lpszModuleFilePath, MAX_PATH + 1);

      DWORD dw;

      DWORD dwResSize = GetFileVersionInfoSize(      
         lpszModuleFilePath,
         &dw);


      if(dwResSize > 0)
      {
         LPVOID lpdata = new BYTE[dwResSize];
         if(GetFileVersionInfo(      
            lpszModuleFilePath,
            0,
            dwResSize,
            lpdata))
         {
            UINT cbTranslate;
            struct LANGANDCODEPAGE {
               WORD wLanguage;
               WORD wCodePage;
            } *lpTranslate;

            // read the list of languages and code pages.

            VerQueryValue(lpdata, 
               TEXT("\\VarFileInfo\\Translation"),
               (LPVOID*)&lpTranslate,
               &cbTranslate);

            string strKey;
            //for( i=0; i < (cbTranslate/sizeof(struct LANGANDCODEPAGE)); i++ )
            for(int i=0; i < 1; i++ )
            {
               LPTSTR lpsz;
               UINT uiSize;

               strKey.Format(
                  TEXT("\\StringFileInfo\\%04x%04x\\FileDescription"),
                  lpTranslate[i].wLanguage,
                  lpTranslate[i].wCodePage);




               strKey.Format(
                  TEXT("\\StringFileInfo\\%04x%04x\\FileVersion"),
                  lpTranslate[i].wLanguage,
                  lpTranslate[i].wCodePage);

               // Retrieve file description for language and code page "i". 
               VerQueryValue(lpdata, 
                  (LPTSTR) (const char *) strKey, 
                  (LPVOID *)&lpsz, 
                  &uiSize); 


               string strVersion(lpsz, uiSize);

               return strVersion;
            }
         }
         delete [] (LPBYTE) lpdata;
      }


      return "";
#else
      TRACE("returning hard coded default 1.0 version for metrowin::application::get_version");
      return "1.0";
#endif

   }


   bool application::Ex2OnAppInstall()
   {
#ifdef IMPLEMENT_VISTA_TOOLS
      if(VistaTools::IsVista())
      {
         if(VistaTools::IsElevated() != S_OK)
         {
            TRACE0("Error! Installing application ( : (un)install run parameter ) without Elevation (required since Vista Windows version)");
            return false;
         }
      }
#endif 
      return true;
   }


   bool application::Ex2OnAppUninstall()
   {
#ifdef WINDOWSEX
      if(VistaTools::IsVista())
      {
         if(VistaTools::IsElevated() != S_OK)
         {
            TRACE0("Error! Installing application ( : (un)install run parameter ) without Elevation (required since Vista Windows version)");
            return false;
         }
      }
#endif
      return true;
   }

   /*
   bool application::DeferRegisterClass(LONG fToRegister, const char ** ppszClass)
   {
      return __end_defer_register_class(fToRegister, ppszClass);
   }
   */

   void application::LockTempMaps()
   {
      WIN_THREAD(m_pthreadimpl.m_p)->LockTempMaps();
   }

   bool application::UnlockTempMaps(bool bDeleteTemp)
   {
      return WIN_THREAD(m_pthreadimpl.m_p)->UnlockTempMaps(bDeleteTemp);
   }


   void application::TermThread(HINSTANCE hInstTerm)
   {
/*      try
      {
   #ifdef DEBUG
         // check for missing ::ca2::LockTempMap calls
         if (__get_module_thread_state()->m_pCurrentWinThread->m_nTempMapLock != 0)
         {
            TRACE(::core::trace::category_AppMsg, 0, "Warning: Temp ::map lock count non-zero (%ld).\n",
               __get_module_thread_state()->m_pCurrentWinThread->m_nTempMapLock);
         }
   #endif
         ::ca2::LockTempMaps(m_pimpl);
         ::ca2::UnlockTempMaps(m_pimpl, -1);
      }
      catch( ::exception::base* e )
      {
         e->Delete();
      }*/

      try
      {
         // cleanup thread local tooltip ::user::interaction_impl
         if (hInstTerm == NULL)
         {
//            __MODULE_THREAD_STATE* pModuleThreadState = __get_module_thread_state();
         }
      }
      catch( ::exception::base* e )
      {
         e->Delete();
      }

      try
      {
         // cleanup the rest of the thread local data
         if (gen_ThreadData != NULL)
            gen_ThreadData->delete_data();
      }
      catch( ::exception::base* e )
      {
         e->Delete();
      }
   }

   /*
   const char * application::RegisterWndClass(UINT nClassStyle, HCURSOR hCursor, HBRUSH hbrBackground, HICON hIcon)
   {
      return __register_window_class(nClassStyle, hCursor, hbrBackground, hIcon);
   }
   */



   // application
   HCURSOR application::LoadCursor(const char * lpszResourceName) const
   { 
      return NULL;
   }

   HCURSOR application::LoadCursor(UINT nIDResource) const
   { 
      return NULL;
   }

   HCURSOR application::LoadStandardCursor(const char * lpszCursorName) const
   { 
#ifdef WINDOWSEX
      return ::LoadCursor(NULL, lpszCursorName);
#else
      throw todo(get_app());
#endif
   }

   HCURSOR application::LoadOEMCursor(UINT nIDCursor) const
   { 
#ifdef WINDOWSEX
      return ::LoadCursor(NULL, MAKEINTRESOURCE(nIDCursor));
#else
      throw todo(get_app());
#endif
   }

   HICON application::LoadIcon(const char * lpszResourceName) const
   { 
      return NULL;
   }

   HICON application::LoadIcon(UINT nIDResource) const
   { 
      return NULL;
   }

   HICON application::LoadStandardIcon(const char * lpszIconName) const
   { 
#ifdef WINDOWSEX
      return ::LoadIcon(NULL, lpszIconName);
#else
      throw todo(get_app());
#endif
   }
   
   HICON application::LoadOEMIcon(UINT nIDIcon) const
   { 
#ifdef WINDOWSEX
      return ::LoadIcon(NULL, MAKEINTRESOURCE(nIDIcon));
#else
      throw todo(get_app());
#endif
   }





   /*void application::construct(__THREADPROC pfnThreadProc, LPVOID pParam)
   {
      ::metrowin::thread::construct(pfnThreadProc, pParam);
   }

   void * application::get_os_data()
   {
      return ::metrowin::thread::get_os_data();
   }

   int_ptr application::get_os_int()
   {
      return ::metrowin::thread::get_os_int();
   }


   bool application::begin(int nPriority, UINT nStackSize,
                           DWORD dwCreateFlags, LPSECURITY_ATTRIBUTES lpSecurityAttrs)
   {
      return ::metrowin::thread::begin(nPriority, nStackSize, dwCreateFlags, lpSecurityAttrs);
   }

   bool application::CreateThread(DWORD dwCreateFlags, UINT nStackSize,
                                  LPSECURITY_ATTRIBUTES lpSecurityAttrs)
   {
      return ::metrowin::thread::CreateThread(dwCreateFlags, nStackSize, lpSecurityAttrs);
   }



   int application::GetThreadPriority()
   {
      return ::metrowin::thread::GetThreadPriority();
   }
   bool application::SetThreadPriority(int nPriority)
   {
      return ::metrowin::thread::SetThreadPriority(nPriority);
   }

   // Operations
   DWORD application::SuspendThread()
   {
      return ::metrowin::thread::SuspendThread();
   }
   DWORD application::ResumeThread()
   {
      return ::metrowin::thread::ResumeThread();
   }
   bool application::PostThreadMessage(UINT message, WPARAM wParam, LPARAM lParam)
   {
      return ::metrowin::thread::PostThreadMessage(message, wParam, lParam);
   }
   bool application::post_message(::user::interaction * pguie, UINT message, WPARAM wParam, LPARAM lParam)
   {
      return ::metrowin::thread::post_message(pguie, message, wParam, lParam);
   }

   bool application::PreInitInstance()
   {
      return ::metrowin::thread::PreInitInstance();
   }

   // called when occurs an standard_exception exception in run
   // return true to call run again
   bool application::on_run_exception(::exception::exception & e)
   {
      return ::metrowin::thread::on_run_exception(e);
   }

   // Overridables
   // thread initialization
   bool application::initialize_instance()
   {
      return ::metrowin::thread::initialize_instance();
   }

   ::message::e_prototype application::GetMessagePrototype(UINT uiMessage, UINT uiCode)
   {
      return ::metrowin::thread::GetMessagePrototype(uiMessage, uiCode);
   }

   // running and idle processing
   int application::run()
   {
      return ::metrowin::thread::run();
   }
   bool application::pre_translate_message(signal_details * pobj)
   {
      return ::metrowin::thread::pre_translate_message(pMsg);
   }
   bool application::pump_message()    // low level message pump
   {
      return ::metrowin::thread::pump_message();
   }
   bool application::on_idle(LONG lCount) // return TRUE if more idle processing
   {
      return ::metrowin::thread::on_idle(lCount);
   }
   bool application::is_idle_message(MSG* pMsg)  // checks for special messages
   {
      return ::metrowin::thread::is_idle_message(pMsg);
   }
*/
   bool application::process_initialize()
   {
      if(m_pimpl->is_system())
      {
         if(__get_module_state()->m_pmapHWND == NULL)
         {
//            __get_module_state()->m_pmapHWND = new hwnd_map;
            __get_module_state()->m_pmutexHwnd = new mutex(this);
         }
/*         if(__get_module_state()->m_pmapHDC == NULL)
         {
            __get_module_state()->m_pmapHDC = new hdc_map;
         }
         if(__get_module_state()->m_pmapHGDIOBJ == NULL)
         {
            __get_module_state()->m_pmapHGDIOBJ = new hgdiobj_map;
         }*/
/*         if(__get_module_state()->m_pmapHMENU == NULL)
         {
            __get_module_state()->m_pmapHMENU = new hmenu_map;
         }*/
      }


      return true;
   }

   bool application::initialize1()
   {

      WIN_THREAD(m_pthreadimpl.m_p)->set_run();

      return true;

   }

   bool application::initialize2()
   {
      return true;
   }

   bool application::initialize3()
   {
      return true;
   }

   // thread termination
   int application::exit_instance() // default will 'delete this'
   {

      // avoid calling CloseHandle() on our own thread handle
      // during the thread destructor
      m_pthreadimpl->set_os_data(NULL);

      WIN_THREAD(m_pthreadimpl.m_p)->m_bRun = false;

      int32_t iRet = ::application::exit_instance();

      //smart_pointer < application_base >::destroy();

      return iRet;

   }
/*
   // Advanced: exception handling
   LRESULT application::ProcessWndProcException(::exception::base* e, const MSG* pMsg)
   {
      return   ::metrowin::thread::ProcessWndProcException(e, pMsg);
   }


   // Advanced: handling messages sent to message filter hook
   bool application::ProcessMessageFilter(int code, LPMSG lpMsg)
   {
      return  ::metrowin::thread::ProcessMessageFilter(code, lpMsg);
   }


   // Advanced: access to GetMainWnd()
   ::user::interaction* application::GetMainWnd()
   {
      return ::metrowin::thread::GetMainWnd();
   }


   
   void application::assert_valid() const
   {
      ::metrowin::thread::assert_valid();
   }

   void application::dump(dump_context & dumpcontext) const
   {
      ::metrowin::thread::dump(dumpcontext);
   }

   
   void application::CommonConstruct()
   {
      ::metrowin::thread::CommonConstruct();
   }
   void application::Delete()
   {
      ::metrowin::thread::Delete();
   }
   // 'delete this' only if m_bAutoDelete == TRUE

   bool application::DispatchThreadMessageEx(MSG* msg)  // helper
   {
      return ::metrowin::thread::DispatchThreadMessageEx(msg);
   }*/

/*   ::draw2d::graphics * application::graphics_from_os_data(void * pdata)
   {
      return ::metrowin::graphics::from_handle((HDC) pdata);
   }*/
#ifdef METROWIN
   sp(::user::interaction) application::window_from_os_data(void * pdata)
   {
      return ((oswindow) pdata)->window();
   }

   sp(::user::interaction) application::window_from_os_data_permanent(void * pdata)
   {
      return ((oswindow) pdata)->window();
   }
#else
   ::user::interaction_impl * application::window_from_os_data(void * pdata)
   {
      return ::metrowin::window::from_handle((oswindow) pdata);
   }

   ::user::interaction_impl * application::window_from_os_data_permanent(void * pdata)
   {
      ::user::interaction_impl * pwnd = ::metrowin::window::FromHandlePermanent((oswindow) pdata);
      if(pwnd != NULL)
         return pwnd;
      user::interaction_ptr_array wndptra = System.frames();
      for(int i = 0; i < wndptra.get_count(); i++)
      {
         if(wndptra[i]->get_safe_handle() == (oswindow) pdata)
         {
            return wndptra[i]->get_wnd();
         }
      }
      return NULL;
   }
#endif

   ::thread * application::GetThread()
   {
      if(__get_thread() == NULL)
         return NULL;
      else
         return dynamic_cast < ::thread * > (__get_thread()->m_p.m_p);
   }

   void application::set_thread(::thread * pthread)
   {
      __set_thread(pthread);
   }

   ///////////////////////////////////////////////////////////////////////////
   // application Initialization

   void application::SetCurrentHandles()
   {
      //ASSERT(this == afxCurrentWinApp);
      //if(afxCurrentAppName != NULL)
        // return;
      //ASSERT(afxCurrentAppName == NULL);


      // Note: there are a number of _tcsdup (aka _strdup) calls that are
      // made here for the exe path, help file path, etc.  In previous
      // versions of ca2 API, this primitive::memory was never freed.  In this and future
      // versions this primitive::memory is automatically freed during application's
      // destructor.  If you are freeing the primitive::memory yourself, you should
      // either remove the code or set the pointers to NULL after freeing
      // the primitive::memory.

      // get path of executable
   /*   char szBuff[_MAX_PATH];
      DWORD dwRet = ::GetModuleFileName(m_hInstance, szBuff, _MAX_PATH);
      ASSERT( dwRet != 0 && dwRet != _MAX_PATH );
      if( dwRet == 0 || dwRet == _MAX_PATH )
         throw user_exception();*/

      /*
      LPTSTR lpszExt = ::PathFindExtension(szBuff);
      ASSERT(lpszExt != NULL);
      if( lpszExt == NULL )
         throw user_exception();

      ASSERT(*lpszExt == '.');
      *lpszExt = 0;       // no suffix
      */

      string strExeName;
      //string strTitle = System.load_string("System.title");
      // get the exe title from the full path name [no extension]
      strExeName = System.get_module_title();

      __get_module_state()->m_lpszCurrentAppName = strdup(m_strAppName);

      // initialize thread state
      __MODULE_STATE* pModuleState = __get_module_state();
      ENSURE(pModuleState);
      if(pModuleState->m_pCurrentWinApp == NULL)
      {
         __MODULE_THREAD_STATE* pThreadState = pModuleState->m_thread;
         ENSURE(pThreadState);
//         ASSERT(System.GetThread() == NULL);
         pThreadState->m_pCurrentWinThread = dynamic_cast < class ::metrowin::thread * > (m_pthreadimpl.m_p);
  //       ASSERT(System.GetThread() == this);

         // initialize application state
         //ASSERT(afxCurrentWinApp == NULL); // only one application object please
         pModuleState->m_pCurrentWinApp = dynamic_cast < application * > (this);
         //ASSERT(&System == this);
      }


//      dynamic_cast < ::metrowin::thread * > ((smart_pointer < ::application >::m_p->::ca2::thread_sp::m_p))->m_hThread = __get_thread()->m_hThread;
  //    dynamic_cast < ::metrowin::thread * > ((smart_pointer < ::application >::m_p->::ca2::thread_sp::m_p))->m_nThreadID = __get_thread()->m_nThreadID;
      dynamic_cast < class ::metrowin::thread * > (m_pthreadimpl.m_p)->m_hThread      =  ::get_current_thread();
      dynamic_cast < class ::metrowin::thread * > (m_pthreadimpl.m_p)->m_nThreadID    =  ::GetCurrentThreadId();
      

   }

   sp(::user::interaction_impl) application::FindWindow(const char * lpszClassName, const char * lpszWindowName)
   {
      return window::FindWindow(lpszClassName, lpszWindowName);
   }

   sp(::user::interaction_impl) application::FindWindowEx(oswindow hwndParent, oswindow hwndChildAfter, const char * lpszClass, const char * lpszWindow)
   {
      return window::FindWindowEx(hwndParent, hwndChildAfter, lpszClass, lpszWindow);
   }


   void application::get_time(struct timeval *p)
   {
   #ifdef WINDOWS
      FILETIME ft; // Contains a 64-bit value representing the number of 100-nanosecond intervals since January 1, 1601 (UTC).
      GetSystemTimeAsFileTime(&ft);
      uint64_t tt;
      memcpy(&tt, &ft, sizeof(tt));
      tt /= 10; // make it usecs
      p->tv_sec = (long)tt / 1000000;
      p->tv_usec = (long)tt % 1000000;
   #else
      gettimeofday(p, NULL);
   #endif
   }

   void application::set_env_var(const string & var,const string & value)
   {
   #if (defined(SOLARIS8) || defined(SOLARIS))
      {
         static std::map<string, char *> vmap;
         if (vmap.find(var) != vmap.end())
         {
            delete[] vmap[var];
         }
         vmap[var] = new char[var.get_length() + 1 + value.get_length() + 1];
         sprintf(vmap[var], "%s=%s", var, value);
         putenv( vmap[var] );
      }
   #elif defined WINDOWSEX
      {
         string slask = var + "=" + value;
         _putenv( (const char *)slask);
      }
   #elif defined METROWIN


   #else
      setenv(var, value, 1);
   #endif
   }

   uint32_t application::get_thread_id()
   {
      return ::GetCurrentThreadId();
   }



   bool application::set_main_init_data(::core::main_init_data * pdata)
   {

      m_pmaininitdata = (::metrowin::main_init_data *) pdata;

      if(m_pmaininitdata != NULL && m_pimpl->is_system())
      {
         if(!win_init(m_pmaininitdata))
            return false;
      }

      return true;

   }

   bool application::win_init(main_init_data * pdata)
   {
         ASSERT(pdata->m_hPrevInstance == NULL);

         HINSTANCE hInstance        = pdata->m_hInstance;
//         HINSTANCE hPrevInstance    = pdata->m_hPrevInstance;
         string strCmdLine          = pdata->m_vssCommandLine;
         UINT nCmdShow              = pdata->m_nCmdShow;

         // handle critical errors and avoid Windows message boxes
//         SetErrorMode(SetErrorMode(0) | SEM_FAILCRITICALERRORS | SEM_NOOPENFILEERRORBOX);

         // set resource handles
         __MODULE_STATE* pModuleState = __get_module_state();
         pModuleState->m_hCurrentInstanceHandle = hInstance;
         pModuleState->m_hCurrentResourceHandle = hInstance;
         pModuleState->CreateActivationContext();

         // fill in the initial state for the application
         // Windows specific initialization (not done if no application)
//         m_hInstance = hInstance;
//         (dynamic_cast < ::application * >(m_pbaseapp.m_p))->m_hInstance = hInstance;
         //hPrevInstance; // Obsolete.
         m_strCmdLine = strCmdLine;
         m_nCmdShow = nCmdShow;
         //pApp->SetCurrentHandles();
         SetCurrentHandles();

         // initialize thread specific data (for main thread)
         if (!afxContextIsDLL)
            __init_thread();

         // Initialize ::user::interaction_impl::m_pfnNotifyWinEvent
      /*   HMODULE hModule = ::GetModuleHandle("user32.dll");
         if (hModule != NULL)
         {
            ::user::interaction_impl::m_pfnNotifyWinEvent = (::user::interaction_impl::PFNNOTIFYWINEVENT)::GetProcAddress(hModule, "NotifyWinEvent");
         }*/

      return true;

   }


   bool application::update_module_paths()
   {

      m_strModuleFolder = "";
      m_strCa2ModuleFolder = "";

      return true;

   }

   ::user::printer * application::get_printer(const char * pszDeviceName)
   {
      ::metrowin::printer * pprinter = new ::metrowin::printer(get_app());
      if(!pprinter->open(pszDeviceName))
      {
         delete pprinter;
         return NULL;
      }
      return pprinter;
   }


   void application::ShowWaitCursor(bool bShow)
   {
   }


   string application::draw2d_get_default_library_name()
   {
      return "draw2d_direct2d";
   }

   string application::veriwell_multimedia_music_midi_get_default_library_name()
   {

      return "";
   }



   string application::multimedia_audio_mixer_get_default_library_name()
   {

      return "";

   }



   string application::multimedia_audio_get_default_library_name()
   {
      return "audio_xaudio2";
   }
} // namespace metrowin




