#include "framework.h"
#include <X11/cursorfont.h>

#define __USE_GNU
#include <link.h>


namespace linux
{

   application::application(sp(::base::application) papp) :
      element(papp)
   {

      ::thread::m_pimpl.create(allocer());
      ::thread::m_pimpl->m_puser = this;

  m_nSafetyPoolSize = 512;        // default size

      shell::theLinuxShell.Initialize();
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
   return "";

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



   void application::TermThread(HINSTANCE hInstTerm)
   {


   }






   bool application::process_initialize()
   {

      return true;

   }


   bool application::initialize1()
   {

      ::thread::m_pimpl->set_run();

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
      ::thread::m_pimpl->set_os_data(NULL);

      m_pimpl->m_bRun = false;
      //LNX_THREAD(m_pimpl->::thread_sp::m_p)->m_bRun = false;

      int32_t iRet = ::base::application::exit_instance();

      //::ca2::smart_pointer<::ca2::application>::destroy();



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


   // Advanced: access to GetMainWnd()
   sp(::user::interaction) application::GetMainWnd()
   {
      return ::win::thread::GetMainWnd();
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

      single_lock mlUser(&user_mutex(), true);

      single_lock mlOsWindow(::oswindow_data::s_pmutex, true);

      unsigned int uiShape;

      if(bShow)
      {

         uiShape = XC_watch;

      }
      else
      {

         uiShape = XC_arrow;

      }

      for(int i = 0; i < ::oswindow_data::s_pdataptra->get_count(); i++)
      {

         oswindow window = ::oswindow_data::s_pdataptra->element_at(i);

         if(window->m_bMessageOnlyWindow)
            continue;

         if(window->display() == NULL)
            continue;


//         Cursor cursor = XCreateFontCursor(window->display(), uiShape);

  //       XDefineCursor(window->display(), window->window(), cursor);

      }

   }

   sp(::window) application::window_from_os_data(void * pdata)
   {
      return ::linux::user::interaction_impl::from_handle((oswindow) pdata);
   }

   sp(::window) application::window_from_os_data_permanent(void * pdata)
   {
      sp(::window) pwnd = ::linux::user::interaction_impl::FromHandlePermanent((oswindow) pdata);
      if(pwnd != NULL)
         return pwnd;
      user::interaction_ptr_array wndptra = System.frames();
      for(int32_t i = 0; i < wndptra.get_count(); i++)
      {
         if(wndptra[i].get_safe_handle() == (oswindow) pdata)
         {
            return wndptra[i].get_wnd();
         }
      }
      return NULL;
   }

   ::thread * application::GetThread()
   {
      if(::get_thread() == NULL)
         return NULL;
      else
         return ::get_thread();
   }

   void application::set_thread(::thread * pthread)
   {
      ::set_thread(pthread);
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

      ::thread::m_pimpl->m_hthread      =  ::GetCurrentThread();

   }

   sp(::window) application::FindWindow(const char * lpszClassName, const char * lpszWindowName)
   {
      return window::FindWindow(lpszClassName, lpszWindowName);
   }

   sp(::window) application::FindWindowEx(oswindow hwndParent, oswindow hwndChildAfter, const char * lpszClass, const char * lpszWindow)
   {
      return window::FindWindowEx(hwndParent, hwndChildAfter, lpszClass, lpszWindow);
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



   bool application::set_main_init_data(::base::main_init_data * pdata)
   {

      m_pmaininitdata = (::linux::main_init_data *) pdata;

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


         // fill in the initial state for the application
         // Windows specific initialization (not done if no application)
// xxx         m_hInstance = hInstance;
// xxx          (dynamic_cast < sp(::base::application) >(m_papp))->m_hInstance = hInstance;
         //hPrevInstance; // Obsolete.
         m_strCmdLine = strCmdLine;
         m_nCmdShow = nCmdShow;
         //pApp->SetCurrentHandles();
         SetCurrentHandles();

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

            m_strModuleFolder = lpszModuleFolder;

            free(lpszModuleFolder);

         }

         {

            void * handle = dlopen("libca.so", RTLD_NOW);

            if(handle == NULL)
            {

               m_strCa2ModuleFolder = m_strModuleFolder;

            }
            else
            {

                link_map * plm;

                dlinfo(handle, RTLD_DI_LINKMAP, &plm);

                m_strCa2ModuleFolder = ::dir::name(plm->l_name);

                if(m_strCa2ModuleFolder.is_empty() || m_strCa2ModuleFolder[0] != '/')
                {

                    m_strCa2ModuleFolder = m_strModuleFolder;

                }

                dlclose(handle);

            }

         }

		return true;

   }

   string application::draw2d_get_default_library_name()
   {

         return "draw2d_cairo";

   }


   string application::multimedia_audio_get_default_library_name()
   {

        return "audio_alsa";

   }


   string application::multimedia_audio_mixer_get_default_library_name()
   {

        return "audio_mixer_alsa";

   }


   string application::veriwell_multimedia_music_midi_get_default_library_name()
   {

        return "music_midi_alsa";

   }

} // namespace linux
