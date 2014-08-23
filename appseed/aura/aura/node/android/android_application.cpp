#include "framework.h"
#include <dlfcn.h>
#include <link.h>


namespace android
{



   application::application(sp(::aura::application) papp) :
      element(papp)
   {
      m_pthreadimpl.alloc(allocer());
      m_pthreadimpl->m_pthread = this;

      //ANDROID_THREAD(::thread::m_p.m_p)->m_pAppThread = this;

//      m_pfilemanager = NULL;
//
//
//
//      // in non-running state until WinMain
//// xxx      m_hInstance = NULL;
////      m_hLangResourceDLL = NULL;
//      m_pszHelpFilePath = NULL;
//      m_pszProfileName = NULL;
//      m_pszRegistryKey = NULL;
//      m_pRecentFileList = NULL;
      //m_pdocmanager = NULL;
// xxx       m_atomApp = m_atomSystemTopic = NULL;
      //m_lpCmdLine = NULL;
//      m_pCmdInfo = NULL;


      // initialize current printer state
// xxx       m_hDevMode = NULL;
// xxx       m_hDevNames = NULL;
      //m_nNumPreviewPages = 0;     // not specified (defaults to 1)

      //// other initialization
      //m_bHelpMode = FALSE;
//      m_eHelpType = afxWinHelp;
      //m_nSafetyPoolSize = 512;        // default size

      shell::theLinuxShell.Initialize();
   }

   application::~application()
   {

   }


   void application::_001OnFileNew()
   {
      //::ca2::application_base::m_p->_001OnFileNew(NULL);
   }

   ::user::document *  application::_001OpenDocumentFile(var varFile)
   {
     // return ::ca2::application_base::m_p->_001OpenDocumentFile(varFile);
   }

   void application::_001EnableShellOpen()
   {
// xxx       ASSERT(m_atomApp == NULL && m_atomSystemTopic == NULL); // do once

// xxx       m_atomApp            = ::GlobalAddAtomW(::str::international::utf8_to_unicode(m_strAppName));
// xxx       m_atomSystemTopic    = ::GlobalAddAtomW(L"system");
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

      throw todo(get_app());

/*      char lpszModuleFilePath[MAX_PATH + 1];
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
            for(int32_t i=0; i < 1; i++ )
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
*/

      return "";

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

      throw todo(get_app());

// xxx       if(VistaTools::IsVista())
// xxx       {
// xxx          if(VistaTools::IsElevated() != S_OK)
// xxx          {
// xxx             TRACE0("Error! Installing application ( : (un)install run parameter ) without Elevation (required since Vista Windows version)");
// xxx             return false;
// xxx          }
// xxx       }
      return true;
   }

   void application::TermThread(HINSTANCE hInstTerm)
   {

//      try
//      {
//         // cleanup thread local tooltip ::interaction_impl
//         if (hInstTerm == NULL)
//         {
////            __MODULE_THREAD_STATE* pModuleThreadState = __get_module_thread_state();
//         }
//      }
//      catch( ::exception::base* e )
//      {
//         e->Delete();
//      }
//
      //try
      //{
      //   // cleanup the rest of the thread local data
      //   if (__thread_data != NULL)
      //      __thread_data->delete_data();
      //}
      //catch( ::exception::base* e )
      //{
      //   e->Delete();
      //}
   }


   
   /*void application::construct(__THREADPROC pfnThreadProc, LPVOID pParam)
   {
      ::win::thread::construct(pfnThreadProc, pParam);
   }

   void * application::get_os_data()
   {
      return ::win::thread::get_os_data();
   }

   int_ptr application::get_os_int()
   {
      return ::win::thread::get_os_int();
   }


   bool application::Begin(int32_t nPriority, UINT nStackSize,
                           DWORD dwCreateFlags, LPSECURITY_ATTRIBUTES lpSecurityAttrs)
   {
      return ::win::thread::Begin(nPriority, nStackSize, dwCreateFlags, lpSecurityAttrs);
   }

   bool application::create_thread(DWORD dwCreateFlags, UINT nStackSize,
                                  LPSECURITY_ATTRIBUTES lpSecurityAttrs)
   {
      return ::win::thread::create_thread(dwCreateFlags, nStackSize, lpSecurityAttrs);
   }



   int32_t application::GetThreadPriority()
   {
      return ::win::thread::GetThreadPriority();
   }
   bool application::SetThreadPriority(int32_t nPriority)
   {
      return ::win::thread::SetThreadPriority(nPriority);
   }

   // Operations
   DWORD application::SuspendThread()
   {
      return ::win::thread::SuspendThread();
   }
   DWORD application::ResumeThread()
   {
      return ::win::thread::ResumeThread();
   }
   bool application::PostThreadMessage(UINT message, WPARAM wParam, LPARAM lParam)
   {
      return ::win::thread::post_thread_message(message, wParam, lParam);
   }
   bool application::post_message(::user::interaction * pguie, UINT message, WPARAM wParam, LPARAM lParam)
   {
      return ::win::thread::post_message(pguie, message, wParam, lParam);
   }

   bool application::PreInitInstance()
   {
      return ::win::thread::PreInitInstance();
   }

   // called when occurs an standard_exception exception in run
   // return true to call run again
   bool application::on_run_exception(::ca2::exception & e)
   {
      return ::win::thread::on_run_exception(e);
   }

   // Overridables
   // thread initialization
   bool application::initialize_instance()
   {
      return ::win::thread::initialize_instance();
   }

   ::message::e_prototype application::GetMessagePrototype(UINT uiMessage, UINT uiCode)
   {
      return ::win::thread::GetMessagePrototype(uiMessage, uiCode);
   }
post_thread_message
   // running and idle processing
   int32_t application::run()
   {
      return ::win::thread::run();
   }
   bool application::pre_translate_message(::signal_details * pobj)
   {
      return ::win::thread::pre_translate_message(pMsg);
   }
   bool application::pump_message()    // low level message pump
   {
      return ::win::thread::pump_message();
   }
   bool application::on_idle(LONG lCount) // return TRUE if more idle processing
   {
      return ::win::thread::on_idle(lCount);
   }
   bool application::is_idle_message(MESSAGE* pMsg)  // checks for special messages
   {
      return ::win::thread::is_idle_message(pMsg);
   }
*/
   bool application::process_initialize()
   {
      //if(::ca2::application_base::m_p->is_system())
      {
/*
if(__get_module_state()->m_pmapHWND == NULL)
         {
            __get_module_state()->m_pmapHWND = new hwnd_map;
            __get_module_state()->m_pmutexHwnd = new mutex();
         }
         if(__get_module_state()->m_pmapHDC == NULL)
         {
            __get_module_state()->m_pmapHDC = new hdc_map;
         }
         if(__get_module_state()->m_pmapHGDIOBJ == NULL)
         {
            __get_module_state()->m_pmapHGDIOBJ = new hgdiobj_map;
         }
         if(__get_module_state()->m_pmapHMENU == NULL)
         {
            __get_module_state()->m_pmapHMENU = new hmenu_map;
         }
*/
      }


      return true;
   }

   bool application::initialize1()
   {

      //m_pthreadimpl->set_run();

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
   int32_t application::exit_instance() // default will 'delete this'
   {

      // avoid calling CloseHandle() on our own thread handle
      // during the thread destructor
      m_pthreadimpl->set_os_data(NULL);

      //ANDROID_THREAD(m_pthreadimpl.m_p)->m_bRun = false;
      //ANDROID_THREAD(::ca2::application_base::m_p->::ca2::thread_sp::m_p)->m_bRun = false;

      int32_t iRet = ::aura::application::exit_instance();

      //::ca2::smart_pointer<::aura::application>::destroy();



      return iRet;
   }
/*
   // Advanced: exception handling
   LRESULT application::ProcessWndProcException(::exception::base* e, const MESSAGE* pMsg)
   {
      return   ::win::thread::ProcessWndProcException(e, pMsg);
   }


   // Advanced: handling messages sent to message filter hook
   bool application::ProcessMessageFilter(int32_t code, LPMESSAGE lpMsg)
   {
      return  ::win::thread::ProcessMessageFilter(code, lpMsg);
   }




   void application::assert_valid() const
   {
      ::win::thread::assert_valid();
   }

   void application::dump(dump_context & dumpcontext) const
   {
      ::win::thread::dump(dumpcontext);
   }


   void application::CommonConstruct()
   {
      ::win::thread::CommonConstruct();
   }
   void application::Delete()
   {
      ::win::thread::Delete();
   }
   // 'delete this' only if m_bAutoDelete == TRUE

   bool application::DispatchThreadMessageEx(MESSAGE* msg)  // helper
   {
      return ::win::thread::DispatchThreadMessageEx(msg);
   }*/

/*   ::draw2d::graphics * application::graphics_from_os_data(void * pdata)
   {
      return ::win::graphics::from_handle((HDC) pdata);
   }*/

   void application::ShowWaitCursor(bool bShow)
   {

      synch_lock mlUser(&user_mutex());

      synch_lock mlOsWindow(::oswindow_data::s_pmutex);

      unsigned int uiShape = 0;

      TRACE("not_implemented android::application::ShowWaitCursor(bool)");

      /*

      if(bShow)
      {

         uiShape = XC_watch;

      }
      else
      {

         uiShape = XC_arrow;

      }

      */

      for(int i = 0; i < ::oswindow_data::s_pdataptra->get_count(); i++)
      {

         oswindow interaction_impl = ::oswindow_data::s_pdataptra->element_at(i);

         if(interaction_impl->m_bMessageOnlyWindow)
            continue;

/*
         if(interaction_impl->display() == NULL)
            continue;

         Cursor cursor = XCreateFontCursor(interaction_impl->display(), uiShape);

         XDefineCursor(interaction_impl->display(), interaction_impl->interaction_impl(), cursor);

*/

      }

   }



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


//      dynamic_cast < ::android::thread * > ((smart_pointer < ::aura::application >::m_p->::ca2::thread_sp::m_p))->m_hThread = __get_thread()->m_hThread;
  //    dynamic_cast < ::android::thread * > ((smart_pointer < ::aura::application >::m_p->::ca2::thread_sp::m_p))->m_nThreadID = __get_thread()->m_nThreadID;
      //m_pimpl->m_hthread      =  ::GetCurrentThread();


   }


   void application::get_time(struct timeval *p)
   {
   #ifdef _WIN32
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
         static std::collection::map<string, char *> vmap;
         if (vmap.find(var) != vmap.end())
         {
            delete[] vmap[var];
         }
         vmap[var] = new char[var.get_length() + 1 + value.get_length() + 1];
         sprintf(vmap[var], "%s=%s", var, value);
         putenv( vmap[var] );
      }
   #elif defined _WIN32
      {
         string slask = var + "=" + value;
         _putenv( (const char *)slask);
      }
   #else
      setenv(var, value, 1);
   #endif
   }

   uint32_t application::get_thread_id()
   {
      return ::pthread_self();
   }



   bool application::set_main_init_data(::aura::main_init_data * pdata)
   {

      m_pmaininitdata = (::android::main_init_data *) pdata;

      if(m_pmaininitdata != NULL && is_system())
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
// xxx         SetErrorMode(SetErrorMode(0) | SEM_FAILCRITICALERRORS | SEM_NOOPENFILEERRORBOX);

         // set resource handles
         //__MODULE_STATE* pModuleState = __get_module_state();
         //pModuleState->m_hCurrentInstanceHandle = hInstance;
         //pModuleState->m_hCurrentResourceHandle = hInstance;
         //pModuleState->CreateActivationContext();

         // fill in the initial state for the application
         // Windows specific initialization (not done if no application)
// xxx         m_hInstance = hInstance;
// xxx          (dynamic_cast < sp(::aura::application) >(m_papp))->m_hInstance = hInstance;
         //hPrevInstance; // Obsolete.
         //m_strCmdLine = strCmdLine;
         //m_nCmdShow = nCmdShow;
         //pApp->SetCurrentHandles();
         SetCurrentHandles();

         // initialize thread specific data (for main thread)
         //if (!afxContextIsDLL)
            __init_thread();

         // Initialize ::interaction_impl::m_pfnNotifyWinEvent
      /*   HMODULE hModule = ::GetModuleHandle("user32.dll");
         if (hModule != NULL)
         {
            ::interaction_impl::m_pfnNotifyWinEvent = (::interaction_impl::PFNNOTIFYWINEVENT)::GetProcaddress(hModule, "NotifyWinEvent");
         }*/

      return true;

   }


   bool application::update_module_paths()
   {

         {

            if(!br_init_lib(NULL))
               return false;

            char * lpszModuleFolder = br_find_exe_dir(NULL);

            if(lpszModuleFolder == NULL)
               return false;

            System.m_strModuleFolder = lpszModuleFolder;

            free(lpszModuleFolder);

         }

         {

            //void * handle = dlopen("libca.so", RTLD_NOW);

            //if(handle == NULL)
            {

               System.m_strCa2ModuleFolder = System.m_strModuleFolder;

            }
            /*else
            {

                link_map * plm;

                dlinfo(handle, RTLD_DI_LINKMAP, &plm);

                m_strCa2ModuleFolder = ::dir::name(plm->l_name);

                if(m_strCa2ModuleFolder.is_empty() || m_strCa2ModuleFolder[0] != '/')
                {

                    m_strCa2ModuleFolder = m_strModuleFolder;

                }

                dlclose(handle);

            }*/

         }

		return true;

   }

   string application::draw2d_get_default_library_name()
   {

         return "draw2d_cairo";

   }

} // namespace android
