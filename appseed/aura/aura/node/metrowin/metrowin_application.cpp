#include "framework.h"
#include "metrowin.h"


//extern thread_local_storage * gen_ThreadData;


namespace metrowin
{


   application::application(::aura::application * papp) :
      element(papp)
   {

      m_pthreadimpl.create(allocer());
      m_pthreadimpl->m_pthread = this;

      m_paxissystem = papp->m_paxissystem;

      m_atomApp = m_atomSystemTopic = NULL;

   }

   application::~application()
   {

   }


   void application::_001OnFileNew()
   {
      m_pimpl->_001OnFileNew(NULL);
   }

   sp(::user::document) application::_001OpenDocumentFile(var varFile)
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

      return true;
   }

   bool application::initialize1()
   {

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
      int32_t iRet = ::aura::application::exit_instance();

      //smart_pointer < application_base >::destroy();

      return iRet;

   }
/*
   // Advanced: exception handling
   LRESULT application::ProcessWndProcException(::exception::aura* e, const MSG* pMsg)
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


   void application::SetCurrentHandles()
   {

      set_os_data(::get_current_thread());
      set_os_int(::GetCurrentThreadId());
      

   }

   sp(::user::interaction) application::FindWindow(const char * lpszClassName, const char * lpszWindowName)
   {
      return interaction_impl::FindWindow(lpszClassName, lpszWindowName);
   }

   sp(::user::interaction) application::FindWindowEx(oswindow hwndParent,oswindow hwndChildAfter,const char * lpszClass,const char * lpszWindow)
   {
      return interaction_impl::FindWindowEx(hwndParent,hwndChildAfter,lpszClass,lpszWindow);
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


   bool application::set_main_init_data(::aura::main_init_data * pdata)
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
      string strCmdLine          = pdata->m_vssCommandLine;
      UINT nCmdShow              = pdata->m_nCmdShow;

      SetCurrentHandles();

      __init_thread();

      return true;

   }


   bool application::update_module_paths()
   {

      System.m_strModuleFolder = "";
      System.m_strCa2ModuleFolder = "";

      return true;

   }

   sp(::user::printer) application::get_printer(const char * pszDeviceName)
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




