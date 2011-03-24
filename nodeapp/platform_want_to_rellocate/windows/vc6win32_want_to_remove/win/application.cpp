#include "StdAfx.h"

extern thread_slot_data* _afxThreadData;

namespace win
{

   application::application(::ca::application * papp) :
      ::ca::ca(papp)
   {
      ::ca::thread_sp::create(papp);
      WIN_THREAD(smart_pointer < ::ca::thread >::m_p)->m_pAppThread = this;

      m_pfilemanager = NULL;


      // initialize thread state
      AFX_MODULE_STATE* pModuleState = AfxGetModuleState();
      ENSURE(pModuleState);
      if(pModuleState->m_pCurrentWinApp == NULL)
      {
         AFX_MODULE_THREAD_STATE* pThreadState = pModuleState->m_thread;
         ENSURE(pThreadState);
//         ASSERT(Application.GetThread() == NULL);
         pThreadState->m_pCurrentWinThread = dynamic_cast < class ::win::thread * > (::ca::thread_sp::m_p);
  //       ASSERT(Application.GetThread() == this);
         dynamic_cast < class ::win::thread * > (::ca::thread_sp::m_p)->m_hThread = ::GetCurrentThread();
         dynamic_cast < class ::win::thread * > (::ca::thread_sp::m_p)->m_nThreadID = ::GetCurrentThreadId();

         // initialize application state
         //ASSERT(afxCurrentWinApp == NULL); // only one application object please
         pModuleState->m_pCurrentWinApp = dynamic_cast < application * > (this);
         //ASSERT(&Application == this);
      }

      // in non-running state until WinMain
      m_hInstance = NULL;
//      m_hLangResourceDLL = NULL;
      m_pszHelpFilePath = NULL;
      m_pszProfileName = NULL;
      m_pszRegistryKey = NULL;
      m_pszExeName = NULL;
      m_pRecentFileList = NULL;
      m_pdocmanager = NULL;
      m_atomApp = m_atomSystemTopic = NULL;
      m_lpCmdLine = NULL;
//      m_pCmdInfo = NULL;

      // initialize wait cursor state
      m_nWaitCursorCount = 0;
      m_hcurWaitCursorRestore = NULL;

      // initialize current printer state
      m_hDevMode = NULL;
      m_hDevNames = NULL;
      m_nNumPreviewPages = 0;     // not specified (defaults to 1)

      // other initialization
      m_bHelpMode = FALSE;
      m_eHelpType = afxWinHelp;
      m_nSafetyPoolSize = 512;        // default size

      WindowsShell::theWindowsShell.Initialize();
   }

   application::~application()
   {
      if(m_pszCmdLine != NULL)
      {
         delete[] m_pszCmdLine;
      }
      if(m_argv != NULL)
      {
         delete[] m_argv;
      }

   }

   void application::_001ParseCommandLine(gen::command_line& rCmdInfo)
   {
      wchar_t * lpwstr = ::GetCommandLineW();
      int numargs;
      int numchars;
      wparse_cmdline(
         lpwstr, 
         NULL, 
         NULL,
         &numargs,
         &numchars);

      m_pszCmdLine = new WCHAR[numchars];
      m_argv = new WCHAR*[numargs];

      wparse_cmdline(
         lpwstr, 
         m_argv, 
         m_pszCmdLine,
         &numargs,
         &numchars);

      m_argc = numargs - 1;

      int iStart = 1;
      if(gen::str::ends(gen::international::unicode_to_utf8(m_argv[0]), "ca2app.exe"))
         iStart++;

      bool bTwoDots = false;
      for (int i = iStart; i < m_argc; i++)
      {
         const wchar_t * pszParam = m_argv[i];
         BOOL bFlag = bTwoDots;
         BOOL bLast = ((i + 1) == m_argc);
         if(bFlag)
         {
         }
         else if (pszParam[0] == '-' || pszParam[0] == '/')
         {
            // remove flag specifier
            bFlag = TRUE;
            ++pszParam;
         }
         else if (wcscmp(pszParam, L":") == 0)
         {
            bTwoDots = true;
            continue;
         }
         string strParam;
         gen::international::unicode_to_utf8(strParam, pszParam);
         rCmdInfo.ParseParam(strParam, bFlag, bLast);
      }

      string strCmdLine;
      gen::international::unicode_to_utf8(strCmdLine, lpwstr);
      rCmdInfo.m_setParameters._008Parse(strCmdLine);
   }

   bool application::_001ProcessShellCommand(gen::command_line& rCmdInfo)
   {
      bool bResult = true;
      switch (rCmdInfo.m_nShellCommand)
      {
      case gen::command_line::FileNew:
         if (!Application._001SendCommand("file::new"))
            _001OnFileNew();
         if (Application.GetMainWnd() == NULL)
            bResult = false;
         break;

         // If we've been asked to open a file, call open_document_file()

      case gen::command_line::FileOpen:
         if (!Application.open_document_file(rCmdInfo.m_strFileName))
            bResult = false;
         break;

         // If the ::user::profile wanted to print, hide our main ::ca::window and
         // fire a message to ourselves to start the printing

      case gen::command_line::FilePrintTo:
      case gen::command_line::FilePrint:
         Application.m_nCmdShow = SW_HIDE;
//         ASSERT(Application.m_pCmdInfo == NULL);
         _001OpenDocumentFile(rCmdInfo.m_strFileName);
//         m_pcmdinfo = &rCmdInfo;
         Application.GetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_PRINT_DIRECT);
  //       m_pcmdinfo = NULL;
         bResult = false;
         break;

         // If we're doing DDE, hide ourselves

      case gen::command_line::FileDDE:
//         m_pcmdinfo = (gen::command_line*)Application.m_nCmdShow;
         Application.m_nCmdShow = SW_HIDE;
         break;

         // If we've been asked to unregister, unregister and then terminate
      case gen::command_line::AppUnregister:
         {
            //((CVmsGenApp *) &Application)->UnregisterShellFileTypes();
            //xxx         Application.UnregisterShellFileTypes();
            //xxx			BOOL bUnregistered = ((CVmsGenApp *) &Application)->Unregister();

            // if you specify /EMBEDDED, we won't make an success/failure box
            // this use of /EMBEDDED is not related to OLE

            /*			if (!rCmdInfo.m_bRunEmbedded)
            {
            if (bUnregistered)
            Application.simple_message_box(AFX_IDP_UNREG_DONE);
            else
            Application.simple_message_box(AFX_IDP_UNREG_FAILURE);
            }
            bResult = FALSE;    // that's all we do

            // If nobody is using it already, we can use it.
            // We'll flag that we're unregistering and not save our state
            // on the way out. This new object gets deleted by the
            // cast object destructor.

            if (m_pcmdinfo == NULL)
            {
            m_pcmdinfo = new command_line;
            m_pcmdinfo->m_nShellCommand = command_line::AppUnregister;
            }*/
         }
         break;
      }
      return bResult;
   }

   void application::_001OnFileNew()
   {
      ::ca::smart_pointer<::ex2::application>::m_p->_001OnFileNew();
   }

   void * application::_001OpenDocumentFile(const char * lpcsz)
   {
      return ::ca::smart_pointer<::ex2::application>::m_p->_001OpenDocumentFile(lpcsz);
   }

   void application::_001EnableShellOpen()
   {
      ASSERT(m_atomApp == NULL && m_atomSystemTopic == NULL); // do once

      m_atomApp = ::GlobalAddAtomW(gen::international::utf8_to_unicode(m_pszExeName));
      m_atomSystemTopic = ::GlobalAddAtomW(L"system");
   }

   BOOL application::_001OnDDECommand(const char * lpcsz)
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

   }


   bool application::Ex2OnAppInstall()
   {
      if(VistaTools::IsVista())
      {
         if(VistaTools::IsElevated() != S_OK)
         {
            TRACE0("Error! Installing application ( : (un)install run parameter ) without Elevation (required since Vista Windows version)");
            return false;
         }
      }
      return true;
   }


   bool application::Ex2OnAppUninstall()
   {
      if(VistaTools::IsVista())
      {
         if(VistaTools::IsElevated() != S_OK)
         {
            TRACE0("Error! Installing application ( : (un)install run parameter ) without Elevation (required since Vista Windows version)");
            return false;
         }
      }
      return true;
   }

   BOOL application::DeferRegisterClass(LONG fToRegister, const char ** ppszClass)
   {
      return AfxEndDeferRegisterClass(fToRegister, ppszClass);
   }


   void application::LockTempMaps()
   {
      AfxLockTempMaps();
   }
   BOOL application::UnlockTempMaps(BOOL bDeleteTemp)
   {
      return AfxUnlockTempMaps(bDeleteTemp);
   }


   void application::TermThread(HINSTANCE hInstTerm)
   {
      try
      {
   #ifdef _DEBUG
         // check for missing AfxLockTempMap calls
         if (AfxGetModuleThreadState()->m_nTempMapLock != 0)
         {
            TRACE(traceAppMsg, 0, "Warning: Temp map lock count non-zero (%ld).\n",
               AfxGetModuleThreadState()->m_nTempMapLock);
         }
   #endif
         AfxLockTempMaps();
         AfxUnlockTempMaps(-1);
      }
      catch( base_exception* e )
      {
         e->Delete();
      }

      try
      {
         // cleanup thread local tooltip ::ca::window
         if (hInstTerm == NULL)
         {
//            AFX_MODULE_THREAD_STATE* pModuleThreadState = AfxGetModuleThreadState();
         }
      }
      catch( base_exception* e )
      {
         e->Delete();
      }

      try
      {
         // cleanup the rest of the thread local data
         if (_afxThreadData != NULL)
            _afxThreadData->DeleteValues(hInstTerm, FALSE);
      }
      catch( base_exception* e )
      {
         e->Delete();
      }
   }


   const char * application::RegisterWndClass(UINT nClassStyle, HCURSOR hCursor, HBRUSH hbrBackground, HICON hIcon)
   {
      return AfxRegisterWndClass(nClassStyle, hCursor, hbrBackground, hIcon);
   }




   // application
   HCURSOR application::LoadCursor(const char * lpszResourceName) const
   { return ::LoadCursor(AfxFindResourceHandle(lpszResourceName,
                         ATL_RT_GROUP_CURSOR), lpszResourceName); }
   HCURSOR application::LoadCursor(UINT nIDResource) const
   { return ::LoadCursor(AfxFindResourceHandle(ATL_MAKEINTRESOURCE(nIDResource),
                         ATL_RT_GROUP_CURSOR), ATL_MAKEINTRESOURCE(nIDResource)); }
   HCURSOR application::LoadStandardCursor(const char * lpszCursorName) const
   { return ::LoadCursor(NULL, lpszCursorName); }
   HCURSOR application::LoadOEMCursor(UINT nIDCursor) const
   { return ::LoadCursor(NULL, ATL_MAKEINTRESOURCE(nIDCursor)); }
   HICON application::LoadIcon(const char * lpszResourceName) const
   { return ::LoadIcon(AfxFindResourceHandle(lpszResourceName,
                       ATL_RT_GROUP_ICON), lpszResourceName); }
   HICON application::LoadIcon(UINT nIDResource) const
   { return ::LoadIcon(AfxFindResourceHandle(ATL_MAKEINTRESOURCE(nIDResource),
                       ATL_RT_GROUP_ICON), ATL_MAKEINTRESOURCE(nIDResource)); }
   HICON application::LoadStandardIcon(const char * lpszIconName) const
   { return ::LoadIcon(NULL, lpszIconName); }
   HICON application::LoadOEMIcon(UINT nIDIcon) const
   { return ::LoadIcon(NULL, ATL_MAKEINTRESOURCE(nIDIcon)); }
   //void application::EnableHtmlHelp()
   //{ SetHelpMode( afxHTMLHelp ); }

   //AFX_HELP_TYPE application::GetHelpMode() 
   //{ return m_eHelpType; }

   //void application::SetHelpMode( AFX_HELP_TYPE eHelpType )
   //{ 
   // ASSERT( eHelpType == afxHTMLHelp || eHelpType == afxWinHelp );
   //m_eHelpType = eHelpType; 
   //}






   /*void application::construct(AFX_THREADPROC pfnThreadProc, LPVOID pParam)
   {
      ::win::thread::construct(pfnThreadProc, pParam);
   }

   void * application::get_os_data()
   {
      return ::win::thread::get_os_data();
   }

   INT_PTR application::get_os_int()
   {
      return ::win::thread::get_os_int();
   }


   bool application::Begin(int nPriority, UINT nStackSize,
                           DWORD dwCreateFlags, LPSECURITY_ATTRIBUTES lpSecurityAttrs)
   {
      return ::win::thread::Begin(nPriority, nStackSize, dwCreateFlags, lpSecurityAttrs);
   }

   BOOL application::CreateThread(DWORD dwCreateFlags, UINT nStackSize,
                                  LPSECURITY_ATTRIBUTES lpSecurityAttrs)
   {
      return ::win::thread::CreateThread(dwCreateFlags, nStackSize, lpSecurityAttrs);
   }



   int application::GetThreadPriority()
   {
      return ::win::thread::GetThreadPriority();
   }
   BOOL application::SetThreadPriority(int nPriority)
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
   BOOL application::PostThreadMessage(UINT message, WPARAM wParam, LPARAM lParam)
   {
      return ::win::thread::PostThreadMessage(message, wParam, lParam);
   }
   bool application::post_message(::user::interaction * pguie, UINT message, WPARAM wParam, LPARAM lParam)
   {
      return ::win::thread::post_message(pguie, message, wParam, lParam);
   }

   bool application::PreInitInstance()
   {
      return ::win::thread::PreInitInstance();
   }

   // called when occurs an se_exception exception in run
   // return true to call run again
   bool application::on_run_exception(::ca::exception & e)
   {
      return ::win::thread::on_run_exception(e);
   }

   // Overridables
   // thread initialization
   bool application::initialize_instance()
   {
      return ::win::thread::initialize_instance();
   }

   ::user::win::message::e_prototype application::GetMessagePrototype(UINT uiMessage, UINT uiCode)
   {
      return ::win::thread::GetMessagePrototype(uiMessage, uiCode);
   }

   // running and idle processing
   int application::run()
   {
      return ::win::thread::run();
   }
   BOOL application::pre_translate_message(gen::signal_object * pobj)
   {
      return ::win::thread::pre_translate_message(pMsg);
   }
   BOOL application::pump_message()    // low level message pump
   {
      return ::win::thread::pump_message();
   }
   BOOL application::on_idle(LONG lCount) // return TRUE if more idle processing
   {
      return ::win::thread::on_idle(lCount);
   }
   BOOL application::is_idle_message(MSG* pMsg)  // checks for special messages
   {
      return ::win::thread::is_idle_message(pMsg);
   }
*/
   bool application::process_initialize()
   {
      return true;
   }

   bool application::initialize1()
   {
      WIN_THREAD(smart_pointer < ::ca::thread >::m_p)->m_ptimera = new ::user::interaction::timer_array;
      WIN_THREAD(smart_pointer < ::ca::thread >::m_p)->m_puiptra = new user::LPWndArray;
      WIN_THREAD(smart_pointer < ::ca::thread >::m_p)->set_run();
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

   bool  application::initialize_log(const char * psz)
   {
      UNREFERENCED_PARAMETER(psz);
      return false;
   }

   // thread termination
   int application::exit_instance() // default will 'delete this'
   {

      // avoid calling CloseHandle() on our own thread handle
      // during the thread destructor
      ::ca::thread_sp::m_p->set_os_data(NULL);

      int iRet = ::gen::application::exit_instance();

      WIN_THREAD(::ca::thread_sp::m_p)->m_bRun = false;
      WIN_THREAD(::ca::smart_pointer<::ex2::application>::m_p->::ca::thread_sp::m_p)->m_bRun = false;
      //::ca::smart_pointer<::ex2::application>::destroy();

      return iRet;
   }
/*
   // Advanced: exception handling
   LRESULT application::ProcessWndProcException(base_exception* e, const MSG* pMsg)
   {
      return   ::win::thread::ProcessWndProcException(e, pMsg);
   }


   // Advanced: handling messages sent to message filter hook
   BOOL application::ProcessMessageFilter(int code, LPMSG lpMsg)
   {
      return  ::win::thread::ProcessMessageFilter(code, lpMsg);
   }


   // Advanced: access to GetMainWnd()
   ::user::interaction* application::GetMainWnd()
   {
      return ::win::thread::GetMainWnd();
   }


   #ifdef _DEBUG
   void application::AssertValid() const
   {
      ::win::thread::AssertValid();
   }

   void application::Dump(CDumpContext & dumpcontext) const
   {
      ::win::thread::Dump(dumpcontext);
   }

   #endif
   void application::CommonConstruct()
   {
      ::win::thread::CommonConstruct();
   }
   void application::Delete()
   {
      ::win::thread::Delete();
   }
   // 'delete this' only if m_bAutoDelete == TRUE

   BOOL application::DispatchThreadMessageEx(MSG* msg)  // helper
   {
      return ::win::thread::DispatchThreadMessageEx(msg);
   }*/

   ::ca::window * application::window_from_os_data(void * pdata)
   {
      return ::win::window::from_handle((HWND) pdata);
   }

   ::ca::window * application::window_from_os_data_permanent(void * pdata)
   {
      ::ca::window * pwnd = ::win::window::FromHandlePermanent((HWND) pdata);
      if(pwnd != NULL)
         return pwnd;
      user::LPWndArray wndptra = App(::get_app()).frames();
      for(int i = 0; i < wndptra.get_count(); i++)
      {
         if(wndptra[i]->get_safe_handle() == (HWND) pdata)
         {
            return wndptra[i]->get_wnd();
         }
      }
      return NULL;
   }

   ::thread * application::GetThread()
   {
      if(AfxGetThread() == NULL)
         return NULL;
      else
         return AfxGetThread()->m_p;
   }

   ///////////////////////////////////////////////////////////////////////////
   // application Initialization

   void application::SetCurrentHandles()
   {
	   //ASSERT(this == afxCurrentWinApp);
      if(afxCurrentAppName != NULL)
         return;
	   ASSERT(afxCurrentAppName == NULL);


	   // Note: there are a number of _tcsdup (aka _strdup) calls that are
	   // made here for the exe path, help file path, etc.  In previous
	   // versions of ca2 API, this memory was never freed.  In this and future
	   // versions this memory is automatically freed during application's
	   // destructor.  If you are freeing the memory yourself, you should
	   // either remove the code or set the pointers to NULL after freeing
	   // the memory.

	   // get path of executable
   /*	char szBuff[_MAX_PATH];
	   DWORD dwRet = ::GetModuleFileName(m_hInstance, szBuff, _MAX_PATH);
	   ASSERT( dwRet != 0 && dwRet != _MAX_PATH );
	   if( dwRet == 0 || dwRet == _MAX_PATH )
		   AfxThrowUserException();*/

      /*
	   LPTSTR lpszExt = ::PathFindExtension(szBuff);
	   ASSERT(lpszExt != NULL);
	   if( lpszExt == NULL )
		   AfxThrowUserException();

	   ASSERT(*lpszExt == '.');
	   *lpszExt = 0;       // no suffix
      */

	   string strExeName;
      string strTitle = Application.load_string("Application.title");
	   // get the exe title from the full path name [no extension]
	   strExeName = Application.get_module_title();

	   if (m_pszExeName == NULL)
	   {
		   BOOL bEnable = AfxEnableMemoryTracking(FALSE);
		   m_pszExeName = _tcsdup(strExeName); // save non-localized name
		   AfxEnableMemoryTracking(bEnable);
		   if(!m_pszExeName)
		   {
			   AfxThrowMemoryException();
		   }
         if(Application.m_pszExeName == NULL)
         {
            Application.m_pszExeName = m_pszExeName;
         }
	   }

	   // m_strAppName is the name used to present to the ::user::profile
	   if (m_strAppName.is_empty())
	   {
         if(Application.m_strAppName.has_char())
         {
            m_strAppName = Application.m_strAppName;
         }
		   else if(strTitle.has_char())
		   {
			   m_strAppName = strTitle;    // human readable title
		   }
		   else
		   {
			   m_strAppName = m_pszExeName;   // same as EXE
		   }
         if(Application.m_strAppName.is_empty())
         {
            Application.m_strAppName = m_strAppName;
         }
	   }

      AfxGetModuleState()->m_lpszCurrentAppName = _tcsdup(m_strAppName);

   }

   ::ca::window * application::FindWindow(const char * lpszClassName, const char * lpszWindowName)
   {
      return window::FindWindow(lpszClassName, lpszWindowName);
   }

   ::ca::window * application::FindWindowEx(HWND hwndParent, HWND hwndChildAfter, const char * lpszClass, const char * lpszWindow)
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
		   static std::map<string, char *> vmap;
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

   unsigned long application::get_thread_id()
   {
      return ::GetCurrentThreadId();
   }

} // namespace win