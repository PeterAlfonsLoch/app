#include "framework.h"
#include <malloc.h>
#ifdef WINDOWS
#include <cderr.h>      // Commdlg Error definitions
#include <winspool.h>
#endif


CLASS_DECL_ca extern fixed_alloc_array * g_pfixedallocaWstring;

CLASS_DECL_ca fixed_alloc_array * new_wstring_manager();





// // BEGIN_MESSAGE_MAP(application, command_target)
   //{{__MSG_MAP(application)
   // Global File commands
//   ON_COMMAND(ID_APP_EXIT, &application::OnAppExit)
   // MRU - most recently used file menu
//   ON_UPDATE_COMMAND_UI(ID_FILE_MRU_FILE1, &application::OnUpdateRecentFileMenu)
//   ON_COMMAND_EX_RANGE(ID_FILE_MRU_FILE1, ID_FILE_MRU_FILE16, &application::OnOpenRecentFile)
   //}}__MSG_MAP
// // END_MESSAGE_MAP()


typedef LANGID (WINAPI*PFNGETUSERDEFAULTUILANGUAGE)();
typedef LANGID (WINAPI*PFNGETSYSTEMDEFAULTUILANGUAGE)();


class CActivationContext
{
protected :
   HANDLE m_hCtxt;
   ulong_ptr m_uCookie;

   // If pointers are NULL then we are on a platform that does not support WinSXS.
   typedef HANDLE (WINAPI * PFNCreateActCtx)(PCACTCTX);
   static PFNCreateActCtx s_pfnCreateActCtx;

   typedef void (WINAPI * PFNReleaseActCtx)(HANDLE);
   static PFNReleaseActCtx s_pfnReleaseActCtx;

   typedef bool (WINAPI * PFNActivateActCtx)(HANDLE, ulong_ptr*);
   static PFNActivateActCtx s_pfnActivateActCtx;

   typedef bool (WINAPI * PFNDeactivateActCtx)(DWORD, ulong_ptr);
   static PFNDeactivateActCtx s_pfnDeactivateActCtx;

   static bool s_bPFNInitialized;

public:
   CActivationContext(HANDLE hCtxt = INVALID_HANDLE_VALUE) : m_hCtxt( hCtxt ), m_uCookie( 0 )
   {
      // Multiple threads initializing is fine since they will initialize the pointers to the
      // same value.
      if (!s_bPFNInitialized)
      {
         HMODULE hKernel = GetModuleHandle("KERNEL32");
         ENSURE (hKernel != NULL);
#ifdef _UNICODE
         s_pfnCreateActCtx = (PFNCreateActCtx) GetProcAddress(hKernel, "CreateActCtxW");
#else
         s_pfnCreateActCtx = (PFNCreateActCtx) GetProcAddress(hKernel, "CreateActCtxA");
#endif
         s_pfnReleaseActCtx = (PFNReleaseActCtx) GetProcAddress(hKernel, "ReleaseActCtx");
         s_pfnActivateActCtx = (PFNActivateActCtx) GetProcAddress(hKernel, "ActivateActCtx");
         s_pfnDeactivateActCtx = (PFNDeactivateActCtx) GetProcAddress(hKernel, "DeactivateActCtx");
         if (s_pfnCreateActCtx != NULL)
         {
            // If one of the functions is present then all the functions have to be present.
            ENSURE( s_pfnReleaseActCtx != NULL &&
               s_pfnActivateActCtx != NULL &&
               s_pfnDeactivateActCtx != NULL);
         }
         else
         {
            // If one of the functions is not present then all the functions should not be present.
            ENSURE( s_pfnReleaseActCtx == NULL &&
               s_pfnActivateActCtx == NULL &&
               s_pfnDeactivateActCtx == NULL);
         }
         s_bPFNInitialized = true;
      }
   };

   ~CActivationContext()
   {
      Release();
   }

   bool create( PCACTCTX pactctx )
   {
      // NULL on a platform that do not support WinSXS
      if (s_pfnCreateActCtx == NULL)
      {
         return true;
      }

      ASSERT( pactctx != NULL );
      if ( pactctx == NULL )
      {
         return false;
      }

      ASSERT( m_hCtxt == INVALID_HANDLE_VALUE );
      if ( m_hCtxt != INVALID_HANDLE_VALUE )
      {
         return false;
      }

      return ( ( m_hCtxt = s_pfnCreateActCtx( pactctx ) ) != INVALID_HANDLE_VALUE );
   }

   void Release()
   {
      // NULL on a platform that do not support WinSXS
      if (s_pfnReleaseActCtx == NULL)
      {
         return;
      }

      if ( m_hCtxt != INVALID_HANDLE_VALUE )
      {
         Deactivate();
         s_pfnReleaseActCtx( m_hCtxt );
      }
   }

   bool Activate()
   {
      // NULL on a platform that do not support WinSXS
      if (s_pfnActivateActCtx == NULL)
      {
         return true;
      }

      ASSERT( m_hCtxt != INVALID_HANDLE_VALUE );
      if ( m_hCtxt == INVALID_HANDLE_VALUE )
      {
         return false;
      }

      ASSERT( m_uCookie == 0 );
      if ( m_uCookie != 0 )
      {
         return false;
      }

      return ( s_pfnActivateActCtx( m_hCtxt, &m_uCookie) == TRUE );
   }

   bool Deactivate()
   {
      // NULL on a platform that do not support WinSXS
      if (s_pfnDeactivateActCtx == NULL)
      {
         return true;
      }

      if ( m_uCookie != 0 )
      {
         ulong_ptr uCookie = m_uCookie;
         m_uCookie = 0;
         return ( s_pfnDeactivateActCtx(0, uCookie) == TRUE );
      }
      return true;
   }
};


CActivationContext::PFNCreateActCtx CActivationContext::s_pfnCreateActCtx = NULL;
CActivationContext::PFNReleaseActCtx CActivationContext::s_pfnReleaseActCtx = NULL;
CActivationContext::PFNActivateActCtx CActivationContext::s_pfnActivateActCtx = NULL;
CActivationContext::PFNDeactivateActCtx CActivationContext::s_pfnDeactivateActCtx = NULL;
bool CActivationContext::s_bPFNInitialized = false;


// HINSTANCE of the module
extern "C" IMAGE_DOS_HEADER __ImageBase;

namespace radix
{

   const char application::gen_FileSection[] = "Recent File List";
   const char application::gen_FileEntry[] = "File%d";
   const char application::gen_PreviewSection[] = "Settings";
   const char application::gen_PreviewEntry[] = "PreviewPages";

   application::application() :
      ::radix::thread(NULL)
   {

      ::ca::profiler::initialize();

      m_pszRegistryKey              = NULL;
      m_pszHelpFilePath             = NULL;
      m_pszProfileName              = NULL;
      m_pframea                     = NULL;


      m_pmutexGlobal                = NULL;
      m_pmutexGlobalId              = NULL;

      m_pmutexLocal                 = NULL;
      m_pmutexLocalId               = NULL;

      m_nSafetyPoolSize             = 512;        // default size

      m_pwndMain                    = NULL;
      m_puserstrcontext             = NULL;
      m_bShouldInitializeGTwf       = true;
      m_bSessionSynchronizedCursor  = true;
      m_bSessionSynchronizedScreen  = true;

      m_nCmdShow                    = -1;

      m_strInstallType              = "application";


   }

   bool application::LoadSysPolicies()
   {
      return _LoadSysPolicies();
   }

   // This function is not exception safe - will leak a registry key if exceptions are thrown from some places
   // To reduce risk of leaks, I've declared the whole function throw(). This despite the fact that its callers have
   // no dependency on non-throwing.
   bool application::_LoadSysPolicies() throw()
   {
      HKEY hkPolicy = NULL;
      DWORD dwValue = 0;
      DWORD dwDataLen = sizeof(dwValue);
      DWORD dwType = 0;

      // clear current policy settings.
      m_dwPolicies = ___SYSPOLICY_NOTINITIALIZED;

      static __system_policy_data rgExplorerData[] =
      {
         {"NoRun", ___SYSPOLICY_NORUN},
         {"NoDrives", ___SYSPOLICY_NODRIVES},
         {"RestrictRun", ___SYSPOLICY_RESTRICTRUN},
         {"NoNetConnectDisconnect", ___SYSPOLICY_NONETCONNECTDISCONNECTD},
         {"NoRecentDocsHistory", ___SYSPOLICY_NORECENTDOCHISTORY},
         {"NoClose", ___SYSPOLICY_NOCLOSE},
         {NULL, NULL}
      };

      static __system_policy_data rgNetworkData[] =
      {
         {"NoEntireNetwork", ___SYSPOLICY_NOENTIRENETWORK},
         {NULL, NULL}
      };

      static __system_policy_data rgComDlgData[] =
      {
         {"NoPlacesBar", ___SYSPOLICY_NOPLACESBAR},
         {"NoBackButton", ___SYSPOLICY_NOBACKBUTTON},
         {"NoFileMru", ___SYSPOLICY_NOFILEMRU},
         {NULL, NULL}
      };

      static __system_policies rgPolicies[] =
      {
         {"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",
            rgExplorerData},
         {"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",
            rgNetworkData},
         {"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Comdlg32",
            rgComDlgData},
         {NULL, NULL}
      };

      __system_policies *pPolicies = rgPolicies;
      __system_policy_data *pData = NULL;

      while (pPolicies->szPolicyKey != NULL)
      {

         if (ERROR_SUCCESS == ::RegOpenKeyEx(
                  HKEY_CURRENT_USER,
                  pPolicies->szPolicyKey,
                  NULL,
                  KEY_QUERY_VALUE,
                  &hkPolicy
                  ))
         {
            pData = pPolicies->pData;
            while (pData->szPolicyName)
            {
               if (ERROR_SUCCESS == ::RegQueryValueEx(
                               hkPolicy,
                               pData->szPolicyName,
                               NULL,
                               &dwType,
                               (BYTE*)&dwValue,
                               &dwDataLen))
               {
                  if (dwType == REG_DWORD)
                  {
                     if (dwValue != 0)
                        m_dwPolicies |= pData->dwID;
                     else
                        m_dwPolicies &= ~pData->dwID;
                  }
               }
               dwValue = 0;
               dwDataLen = sizeof(dwValue);
               dwType = 0;
               pData++;
            }
            ::RegCloseKey(hkPolicy);
            hkPolicy = NULL;
         }
         pPolicies++;
      };
      return TRUE;
   }

   bool application::GetSysPolicyValue(DWORD dwPolicyID, bool *pbValue)
   {
      if (!pbValue)
         return FALSE; // bad pointer
      *pbValue = (m_dwPolicies & dwPolicyID) != 0;
      return TRUE;
   }

   bool application::InitApplication()
   {
      /*if(::get_app() == NULL)
      {
         ::set_app(get_system());
         system::application * pApp = dynamic_cast < system::application * > (::get_app());
         thread * pThread = ::get_app();
         // App global initializations (rare)
         if (pApp != NULL && !pApp->InitApplication())
            goto InitFailure;

         pThread->translator::attach();

         // Perform specific initializations
         try
         {
            try
            {
               if(!pApp->process_initialize())
               {
                  if (pThread->GetMainWnd() != NULL)
                  {
                     TRACE(::radix::trace::category_AppMsg, 0, "Warning: Destroying non-NULL GetMainWnd()\n");
                     pThread->GetMainWnd()->DestroyWindow();
                  }
                  goto InitFailure;
               }
            }
            catch(const ::ca::exception &)
            {
               if (pThread->GetMainWnd() != NULL)
               {
                  pThread->GetMainWnd()->DestroyWindow();
                  pThread->SetMainWnd(NULL);
               }
               goto InitFailure;
            }
            try
            {
               if(!pThread->initialize_instance())
               {
                  if (pThread->GetMainWnd() != NULL)
                  {
                     TRACE(::radix::trace::category_AppMsg, 0, "Warning: Destroying non-NULL GetMainWnd()\n");
                     pThread->GetMainWnd()->DestroyWindow();
                  }
                  pThread->exit_instance();
                  goto InitFailure;
               }
            }
            catch(const ::ca::exception & e)
            {
               if(pThread->on_run_exception((::ca::exception &) e))
                  goto run;
               if (pThread->GetMainWnd() != NULL)
               {
                  TRACE(::radix::trace::category_AppMsg, 0, "Warning: Destroying non-NULL GetMainWnd()\n");
                  try
                  {
                     pThread->GetMainWnd()->DestroyWindow();
                  }
                  catch(::ca::exception &)
                  {
                  }
                  pThread->SetMainWnd(NULL);
               }
               if(pApp->final_handle_exception((::ca::exception &) e))
                  goto run;
               if (pThread->GetMainWnd() != NULL)
               {
                  TRACE(::radix::trace::category_AppMsg, 0, "Warning: Destroying non-NULL GetMainWnd()\n");
                  try
                  {
                     pThread->GetMainWnd()->DestroyWindow();
                  }
                  catch(::ca::exception &)
                  {
                  }
                  pThread->SetMainWnd(NULL);
               }
               pThread->exit_instance();
               goto InitFailure;
            }

         }
         catch(...)
         {
         }
      }
   run:*/

      LoadSysPolicies();

      return TRUE;

   /*InitFailure:

      return FALSE;*/

   }

   bool application::initialize_instance()
   {

      if(!is_system() && !is_bergedge())
      {
         if(!check_exclusive())
            return false;
      }

//      InitLibId();


      m_dwAlive = ::GetTickCount();


      if(!initialize1())
         return false;

      string strWindow;
      if(m_strAppName.has_char())
         strWindow = m_strAppName;
      else
         strWindow = typeid(*this).name();

      if(!initialize_message_window(this, strWindow))
      {
         TRACE("Fatal error: could not initialize application message window (name=\"%s\").", strWindow);
         return false;
      }

      m_dwAlive = ::GetTickCount();

      if(!initialize2())
         return false;

      m_dwAlive = ::GetTickCount();

      if(!initialize3())
         return false;

      m_dwAlive = ::GetTickCount();

      try
      {
         if(!initialize())
            return false;
      }
      catch(const char * psz)
      {
         if(!strcmp(psz, "You have not logged in! Exiting!"))
         {
            return false;
         }
         return false;
      }

      return true;
   }


/*   void application::LoadStdProfileSettings(UINT nMaxMRU)
   {
      UNREFERENCED_PARAMETER(nMaxMRU);
      ASSERT_VALID(this);

      // 0 by default means not set
      m_nNumPreviewPages = GetProfileInt(gen_PreviewSection, gen_PreviewEntry, 0);
   }*/

   /*void application::ParseCommandLine(CCommandLineInfo& rCmdInfo)
   {
      for (int i = 1; i < __argc; i++)
      {
         const char * pszParam = __targv[i];
         bool bFlag = FALSE;
         bool bLast = ((i + 1) == __argc);
         if (pszParam[0] == '-' || pszParam[0] == '/')
         {
            // remove flag specifier
            bFlag = TRUE;
            ++pszParam;
         }
         rCmdInfo.ParseParam(pszParam, bFlag, bLast);
      }
   }*/

   /////////////////////////////////////////////////////////////////////////////
   // CCommandLineInfo implementation

   /*CCommandLineInfo::CCommandLineInfo()
   {
      m_bShowSplash = TRUE;
      m_bRunEmbedded = FALSE;
      m_bRunAutomated = FALSE;
      m_nShellCommand = FileNew;
   }

   CCommandLineInfo::~CCommandLineInfo()
   {
   }

   void CCommandLineInfo::ParseParam(const char* pszParam,bool bFlag,bool bLast)
   {
      if (bFlag)
      {
         const astring strParam(pszParam);
         ParseParamFlag(strParam.GetString());
      }
      else
         ParseParamNotFlag(pszParam);

      ParseLast(bLast);
   }*/

   /*
   #ifdef UNICODE
   void CCommandLineInfo::ParseParam(const char* pszParam, bool bFlag, bool bLast)
   {
      if (bFlag)
         ParseParamFlag(pszParam);
      else
         ParseParamNotFlag(pszParam);

      ParseLast(bLast);
   }
   #endif // UNICODE
   */

   /*
   void CCommandLineInfo::ParseParamFlag(const char* pszParam)
   {
      // OLE command switches are case insensitive, while
      // shell command switches are case sensitive

      if (lstrcmpA(pszParam, "pt") == 0)
         m_nShellCommand = FilePrintTo;
      else if (lstrcmpA(pszParam, "p") == 0)
         m_nShellCommand = FilePrint;
       else if (::__invariant_stricmp(pszParam, "Register") == 0 ||
                ::__invariant_stricmp(pszParam, "Regserver") == 0)
         m_nShellCommand = AppRegister;
       else if (::__invariant_stricmp(pszParam, "Unregister") == 0 ||
                ::__invariant_stricmp(pszParam, "Unregserver") == 0)
         m_nShellCommand = AppUnregister;
      else if (lstrcmpA(pszParam, "dde") == 0)
      {
         m_nShellCommand = FileDDE;
      }
       else if (::__invariant_stricmp(pszParam, "Embedding") == 0)
      {
         m_bRunEmbedded = TRUE;
         m_bShowSplash = FALSE;
      }
       else if (::__invariant_stricmp(pszParam, "Automation") == 0)
      {
         m_bRunAutomated = TRUE;
         m_bShowSplash = FALSE;
      }
   }

   void CCommandLineInfo::ParseParamNotFlag(const char* pszParam)
   {
      if (m_strFileName.is_empty())
         m_strFileName = pszParam;
      else if (m_nShellCommand == FilePrintTo && m_strPrinterName.is_empty())
         m_strPrinterName = pszParam;
      else if (m_nShellCommand == FilePrintTo && m_strDriverName.is_empty())
         m_strDriverName = pszParam;
      else if (m_nShellCommand == FilePrintTo && m_strPortName.is_empty())
         m_strPortName = pszParam;
   }

   #ifdef UNICODE
   void CCommandLineInfo::ParseParamNotFlag(const char* pszParam)
   {
      if (m_strFileName.is_empty())
         m_strFileName = pszParam;
      else if (m_nShellCommand == FilePrintTo && m_strPrinterName.is_empty())
         m_strPrinterName = pszParam;
      else if (m_nShellCommand == FilePrintTo && m_strDriverName.is_empty())
         m_strDriverName = pszParam;
      else if (m_nShellCommand == FilePrintTo && m_strPortName.is_empty())
         m_strPortName = pszParam;
   }
   #endif

   void CCommandLineInfo::ParseLast(bool bLast)
   {
      if (bLast)
      {
         if (m_nShellCommand == FileNew && !m_strFileName.is_empty())
            m_nShellCommand = FileOpen;
         m_bShowSplash = !m_bRunEmbedded && !m_bRunAutomated;
      }
   }
   */

   /////////////////////////////////////////////////////////////////////////////
   // App termination

   application::~application()
   {
      // free doc manager
//      if (m_pdocmanager != NULL)
  //       delete m_pdocmanager;



      // free printer info
   /*   if (m_hDevMode != NULL)
         __global_free(m_hDevMode);
      if (m_hDevNames != NULL)
         __global_free(m_hDevNames);*/

      // free atoms if used
      if (m_atomApp != NULL)
         ::GlobalDeleteAtom(m_atomApp);
      if (m_atomSystemTopic != NULL)
         ::GlobalDeleteAtom(m_atomSystemTopic);

      // free cached commandline
   //   if (m_pCmdInfo != NULL)
      //   delete m_pCmdInfo;

      // free various strings allocated with _tcsdup
      if(m_pszRegistryKey != NULL)
         free((void *)m_pszRegistryKey);
      if(m_pszHelpFilePath != NULL)
         free((void *)m_pszHelpFilePath);
      if(m_pszProfileName != NULL)
         free((void *)m_pszProfileName);

   }

   void application::SaveStdProfileSettings()
   {
      ASSERT_VALID(this);


//      if (m_nNumPreviewPages != 0)
  //       WriteProfileInt(gen_PreviewSection, gen_PreviewEntry, m_nNumPreviewPages);
   }




   // Main running routine until application exits
   int application::run()
   {
   /*   if (GetMainWnd() == NULL) // may be a service or console application ::ca::window
      {
         // Not launched /Embedding or /Automation, but has no main ::ca::window!
         TRACE(::radix::trace::category_AppMsg, 0, "Warning: GetMainWnd() is NULL in application::run - quitting application.\n");
         __post_quit_message(0);
      }*/
      return thread::run();
   }


   /////////////////////////////////////////////////////////////////////////////
   // WinHelp Helper


   void application::WinHelp(dword_ptr dwData, UINT nCmd)
   {
      UNREFERENCED_PARAMETER(dwData);
      UNREFERENCED_PARAMETER(nCmd);
      ::user::interaction* pMainWnd = System.GetMainWnd();
      ENSURE_VALID(pMainWnd);

      // return global cast help mode state to FALSE (backward compatibility)
      m_bHelpMode = FALSE;
      // trans pMainWnd->PostMessage(WM_KICKIDLE); // trigger idle update

      //trans pMainWnd->WinHelp(dwData, nCmd);
   }

   /////////////////////////////////////////////////////////////////////////////
   // HtmlHelp Helper

   void application::HtmlHelp(dword_ptr dwData, UINT nCmd)
   {
      UNREFERENCED_PARAMETER(dwData);
      UNREFERENCED_PARAMETER(nCmd);
      ::user::interaction* pMainWnd = System.GetMainWnd();
      ENSURE_VALID(pMainWnd);

      // return global cast help mode state to FALSE (backward compatibility)
      m_bHelpMode = FALSE;
      // trans pMainWnd->PostMessage(WM_KICKIDLE); // trigger idle update

      // trans pMainWnd->HtmlHelp(dwData, nCmd);
   }

   void application::WinHelpInternal(dword_ptr dwData, UINT nCmd)
   {
      UNREFERENCED_PARAMETER(dwData);
      UNREFERENCED_PARAMETER(nCmd);
   //   ::user::interaction* pMainWnd = System.GetMainWnd();
   //   ENSURE_VALID(pMainWnd);

      // return global cast help mode state to FALSE (backward compatibility)
      m_bHelpMode = FALSE;
      // trans pMainWnd->PostMessage(WM_KICKIDLE); // trigger idle update
      // trans pMainWnd->WinHelpInternal(dwData, nCmd);
   }

   /////////////////////////////////////////////////////////////////////////////
   // Special exception handling

   void application::ProcessWndProcException(base_exception* e, gen::signal_object * pobj)
   {
      ENSURE_ARG(e != NULL);
      ENSURE_ARG(pobj != NULL);
      SCAST_PTR(::gen::message::base, pbase, pobj);
      // handle certain messages in thread
      switch (pbase->m_uiMessage)
      {
      case WM_CREATE:
      case WM_PAINT:
         return thread::ProcessWndProcException(e, pobj);
      }

      // handle all the rest
      //linux UINT nIDP = __IDP_INTERNAL_FAILURE;   // generic message string
      const char * nIDP = "Internal Failure";
      pbase->set_lresult(0);        // sensible default
      if (pbase->m_uiMessage == WM_COMMAND)
      {
         if ((HWND)pbase->m_lparam == NULL)
            //linux nIDP = __IDP_COMMAND_FAILURE; // command (not from a control)
            nIDP = "Command Failure";
         pbase->set_lresult((LRESULT)TRUE);        // pretend the command was handled
      }
      if (base < memory_exception >::bases(e))
      {
         e->ReportError(MB_ICONEXCLAMATION|MB_SYSTEMMODAL, nIDP);
      }
      else if (base < user_exception >::bases(e))
      {
         // ::fontopus::user has not been alerted yet of this catastrophic problem
         e->ReportError(MB_ICONSTOP, nIDP);
      }
      //return lResult; // sensible default return from most WndProc functions
   }

   /////////////////////////////////////////////////////////////////////////////
   // application idle processing

   bool application::on_idle(LONG lCount)
   {
/*      if (lCount <= 0)
      {
         thread::on_idle(lCount);

         // call doc-template idle hook
         count count = 0;
         if (m_pdocmanager != NULL)
            count = m_pdocmanager->get_template_count();

         for(index index = 0; index < count; index++)
         {
            document_template * ptemplate = m_pdocmanager->get_template(index);
            ASSERT_KINDOF(document_template, ptemplate);
            ptemplate->on_idle();
         }
      }
      else if (lCount == 1)
      {
         VERIFY(!thread::on_idle(lCount));
      }
      return lCount < 1;  // more to do if lCount < 1*/
      return 0;
   }

   /////////////////////////////////////////////////////////////////////////////
   // application idle processing

   void application::DevModeChange(__in LPTSTR lpDeviceName)
   {
      UNREFERENCED_PARAMETER(lpDeviceName);
      if (m_hDevNames == NULL)
         return;

   }

   ///////////////////////////////////////////////////////////////////////////
   // application diagnostics

   void application::assert_valid() const
   {
      thread::assert_valid();


      if (System.GetThread() != (thread*)this)
         return;     // only do subset if called from different thread

      ASSERT(System.GetThread() == this);
      //ASSERT(afxCurrentInstanceHandle == m_hInstance);

/*      if (m_pdocmanager != NULL)
         ASSERT_VALID(m_pdocmanager);*/
   }

   void application::dump(dump_context & dumpcontext) const
   {
      thread::dump(dumpcontext);

      dumpcontext << "m_hInstance = " << (void *)m_hInstance;
      dumpcontext << "\nm_lpCmdLine = " << m_strCmdLine;
      dumpcontext << "\nm_nCmdShow = " << m_nCmdShow;
      dumpcontext << "\nm_pszAppName = " << m_strAppName;
      dumpcontext << "\nm_bHelpMode = " << m_bHelpMode;
      dumpcontext << "\nm_pszHelpFilePath = " << m_pszHelpFilePath;
      dumpcontext << "\nm_pszProfileName = " << m_pszProfileName;
      dumpcontext << "\nm_hDevMode = " << (void *)m_hDevMode;
      dumpcontext << "\nm_hDevNames = " << (void *)m_hDevNames;
      dumpcontext << "\nm_dwPromptContext = " << m_dwPromptContext;
//      dumpcontext << "\nm_eHelpType = " << m_eHelpType;


/*      if (m_pdocmanager != NULL)
         m_pdocmanager->dump(dumpcontext);*/

      dumpcontext << "\nm_nWaitCursorCount = " << m_nWaitCursorCount;
      dumpcontext << "\nm_hcurWaitCursorRestore = " << (void *)m_hcurWaitCursorRestore;
      dumpcontext << "\nm_nNumPreviewPages = " << m_nNumPreviewPages;

   /*   ___THREAD_STATE* pState = __get_thread_state();
      dumpcontext << "\nm_msgCur = {";
      dumpcontext << "\n\thwnd = " << (void *)pState->m_msgCur.hwnd;
      dumpcontext << "\n\tmessage = " << (UINT)pState->m_msgCur.message;
      dumpcontext << "\n\twParam = " << (UINT)pState->m_msgCur.wParam;
      dumpcontext << "\n\tlParam = " << (void *)pState->m_msgCur.lParam;
      dumpcontext << "\n\ttime = " << pState->m_msgCur.time;
      dumpcontext << "\n\tpt = " << point(pState->m_msgCur.pt);
      dumpcontext << "\n}";
   */
      dumpcontext << "\n";
   }

   ::ca::application * application::get_app() const
   {
      return ::ca::application::get_app();
   }




   string application::load_string(id id)
   {
      return (const char * ) id;
   }

   bool application::on_run_exception(::ca::exception & e)
   {
      UNREFERENCED_PARAMETER(e);
      TRACE("An unexpected error has occurred and no special exception handling is available.");
      //simple_message_box_timeout("An unexpected error has occurred and no special exception handling is available.<br>Timeout: $simple_message_box_timeout", 5000);
      return false; // re-run? by default: doesn't
   }

   void application::pre_translate_message(::gen::signal_object * pobj)
   {

      ::radix::thread::pre_translate_message(pobj);

   }


   HCURSOR application::LoadStandardCursor(const char * lpszCursorName) const
   {
      return ::LoadCursor(NULL, lpszCursorName);
   }


   bool application::ca_process_initialize()
   {
      application_signal_object signal(this, &m_signal, ::ca::application_signal_process_initialize);
      m_signal.emit(&signal);
      return true;
   }

   bool application::ca_initialize1()
   {
      application_signal_object signal(this, &m_signal, ::ca::application_signal_initialize1);
      m_signal.emit(&signal);
      return signal.m_bOk;
   }

   bool application::initialize2()
   {
      application_signal_object signal(this, &m_signal, ::ca::application_signal_initialize2);
      m_signal.emit(&signal);
      return signal.m_bOk;
   }

   bool application::initialize3()
   {
      application_signal_object signal(this, &m_signal, ::ca::application_signal_initialize3);
      m_signal.emit(&signal);
      return signal.m_bOk;
   }

   bool application::initialize()
   {
      application_signal_object signal(this, &m_signal, ::ca::application_signal_initialize);
      m_signal.emit(&signal);
      return signal.m_bOk;
   }

   bool application::ca_finalize()
   {
      application_signal_object signal(this, &m_signal, ::ca::application_signal_finalize);
      try
      {
         m_signal.emit(&signal);
      }
      catch(...)
      {
      }




      return signal.m_bOk;
   }



   bool application::final_handle_exception(::ca::exception & e)
   {
      UNREFERENCED_PARAMETER(e);
//linux      exit(-1);
      return false;
   }


   bool application::open_link(const char * pszLink, const char * pszTarget)
   {
      UNREFERENCED_PARAMETER(pszLink);
      UNREFERENCED_PARAMETER(pszTarget);
      return false;
   }

   bool application::process_initialize()
   {

      m_pframea = new ::user::LPWndArray;

      if(!ca_process_initialize())
         return false;

      if(is_system())
      {
         System.factory().cloneable_large < int_array > ();
         System.factory().cloneable_large < raw_pointer > ();
      }

      return true;
   }




   bool application::check_exclusive()
   {
      SECURITY_ATTRIBUTES MutexAttributes;
      ZeroMemory( &MutexAttributes, sizeof(MutexAttributes) );
      MutexAttributes.nLength = sizeof( MutexAttributes );
      MutexAttributes.bInheritHandle = FALSE; // object uninheritable
      // declare and initialize a security descriptor
      SECURITY_DESCRIPTOR SD;
      bool bInitOk = InitializeSecurityDescriptor(&SD, SECURITY_DESCRIPTOR_REVISION) != FALSE;
      if ( bInitOk )
      {
         // give the security descriptor a Null Dacl
         // done using the  "TRUE, (PACL)NULL" here
         bool bSetOk = SetSecurityDescriptorDacl( &SD,
                                               TRUE,
                                               (PACL)NULL,
                                               FALSE ) != FALSE;
         bool bResourceException;
         if ( bSetOk )
         {
            // Make the security attributes point
            // to the security descriptor
            MutexAttributes.lpSecurityDescriptor = &SD;
            bResourceException = false;
            try
            {
               m_pmutexGlobal = new mutex(FALSE, get_global_mutex_name(), &MutexAttributes);
            }
            catch(resource_exception &)
            {
               try
               {
                  m_pmutexGlobal = new mutex(FALSE, get_global_mutex_name());
               }
               catch(resource_exception &)
               {
                  bResourceException = true;
               }
            }

            if(m_eexclusiveinstance == ExclusiveInstanceGlobal
               && (::GetLastError() == ERROR_ALREADY_EXISTS || bResourceException))
            {
               // Should in some way activate the other instance, but this is global, what to do? do not know yet.
               //System.simple_message_box("A instance of the application:<br><br>           - " + string(m_strAppName) + "<br><br>seems to be already running at the same machine<br>Only one instance of this application can run globally: at the same machine.<br><br>Exiting this new instance.");
               TRACE("A instance of the application:<br><br>           - " + string(m_strAppName) + "<br><br>seems to be already running at the same machine<br>Only one instance of this application can run globally: at the same machine.<br><br>Exiting this new instance.");
               on_exclusive_instance_conflict(ExclusiveInstanceGlobal);
               return false;
            }
            if(m_eexclusiveinstance == ExclusiveInstanceGlobalId)
            {
               bResourceException = false;
               try
               {
                  m_pmutexGlobalId = new mutex(FALSE, get_global_id_mutex_name(), &MutexAttributes);
               }
               catch(resource_exception &)
               {
                  try
                  {
                     m_pmutexGlobalId = new mutex(FALSE, get_global_id_mutex_name());
                  }
                  catch(resource_exception &)
                  {
                     bResourceException = true;
                  }
               }
               if(::GetLastError() == ERROR_ALREADY_EXISTS || bResourceException)
               {
                  // Should in some way activate the other instance
                  //System.simple_message_box("A instance of the application:<br><br>           - " + string(m_strAppName) + "<br><br>seems to be already running at the same account.<br>Only one instance of this application can run locally: at the same account.<br><br>Exiting this new instance.");
                  TRACE("A instance of the application:<br><br>           - " + string(m_strAppName)+ "with the id \"" + get_local_mutex_id() + "\" <br><br>seems to be already running at the same machine<br>Only one instance of this application can run globally: at the same machine with the same id.<br><br>Exiting this new instance.");
                  on_exclusive_instance_conflict(ExclusiveInstanceGlobalId);
                  return false;
               }
            }
            bResourceException = false;
            try
            {
               m_pmutexLocal = new mutex(FALSE, get_local_mutex_name(), &MutexAttributes);
            }
            catch(resource_exception &)
            {
               try
               {
                  m_pmutexLocal = new mutex(FALSE, get_local_mutex_name());
               }
               catch(resource_exception & )
               {
                  bResourceException = true;
               }
            }
            if(m_eexclusiveinstance == ExclusiveInstanceLocal && (::GetLastError() == ERROR_ALREADY_EXISTS || bResourceException))
            {
               // Should in some way activate the other instance
               //System.simple_message_box("A instance of the application:<br><br>           - " + string(m_strAppName) + "<br><br>seems to be already running at the same account.<br>Only one instance of this application can run locally: at the same account.<br><br>Exiting this new instance.");
               TRACE("A instance of the application:<br><br>           - " + string(m_strAppName) + "<br><br>seems to be already running at the same account.<br>Only one instance of this application can run locally: at the same account.<br><br>Exiting this new instance.");
               on_exclusive_instance_conflict(ExclusiveInstanceLocal);
               return false;
            }
            if(m_eexclusiveinstance == ExclusiveInstanceLocalId)
            {
               bResourceException = false;
               try
               {
                  m_pmutexLocalId = new mutex(FALSE, get_local_id_mutex_name(), &MutexAttributes);
               }
               catch(resource_exception &)
               {
                  try
                  {
                     m_pmutexLocalId = new mutex(FALSE, get_local_id_mutex_name());
                  }
                  catch(resource_exception &)
                  {
                     bResourceException = true;
                  }
               }
               if(::GetLastError() == ERROR_ALREADY_EXISTS || bResourceException)
               {
                  // Should in some way activate the other instance
                  //System.simple_message_box("A instance of the application:<br><br>           - " + string(m_strAppName) + "<br><br>seems to be already running at the same account.<br>Only one instance of this application can run locally: at the same account.<br><br>Exiting this new instance.");
                  TRACE("A instance of the application:<br><br>           - " + string(m_strAppName) + "with the id \"" + get_local_mutex_id() + "\" <br><br>seems to be already running at the same account.<br>Only one instance of this application can run locally: at the same account with the same id.<br><br>Exiting this new instance.");
                  on_exclusive_instance_conflict(ExclusiveInstanceLocalId);
                  return false;
               }
            }
         }
         else
         {
            return false;
         }
      }
      else
      {
         return false;
      }
      return true;
   }

   bool application::release_exclusive()
   {
      if(m_pmutexGlobal != NULL)
      {
         gen::sdel(m_pmutexGlobal);
      }
      if(m_pmutexGlobalId != NULL)
      {
         gen::sdel(m_pmutexGlobalId);
      }
      if(m_pmutexLocal != NULL)
      {
         gen::sdel(m_pmutexLocal);
      }
      if(m_pmutexLocalId != NULL)
      {
         gen::sdel(m_pmutexLocalId);
      }
      return true;
   }

   string application::get_mutex_name_radix()
   {
      return m_strAppName;
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

   void application::message_window_message_handler(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   ::user::LPWndArray & application::frames()
   {
      return *m_pframea;
   }

   void application::add_frame(::user::interaction * pwnd)
   {
      m_pframea->add_unique(pwnd);
   }

   void application::remove_frame(::user::interaction * pwnd)
   {
      m_pframea->remove(pwnd);
      if(GetMainWnd() == pwnd)
      {
         if(m_pframea->get_size() > 0)
         {
            SetMainWnd(m_pframea->element_at(0));
         }
         else
         {
            SetMainWnd(NULL);
         }
      }
   }


   void application::delete_temp()
   {

   }

   // This is ca2 API library.
   //
   //
   //
   //
   //
   //
   //
   //


   void application::_001OnFileNew()
   {
/*      if (m_pdocmanager != NULL)
         m_pdocmanager->_001OnFileNew();*/
   }

   void application::on_file_open()
   {
      ENSURE(m_pdocmanager != NULL);
      //m_pdocmanager->on_file_open();
   }

   // prompt for file name - used for open and save as
   bool application::do_prompt_file_name(var & varFile, UINT nIDSTitle, DWORD lFlags, bool bOpenFileDialog, document_template * ptemplate, ::user::document_interface * pdocument)
         // if ptemplate==NULL => all document templates
   {
      if(m_pfilemanager != NULL)
      {
         return m_pfilemanager->do_prompt_file_name(varFile, nIDSTitle, lFlags, bOpenFileDialog, ptemplate, pdocument);
      }
      ENSURE(m_pdocmanager != NULL);
/*      return m_pdocmanager->do_prompt_file_name(fileName, nIDSTitle, lFlags,
                                 bOpenFileDialog, ptemplate);*/
      return FALSE;
   }

   // This is ca2 API library.
   //
   //
   //
   //
   //
   //
   //
   //



   /////////////////////////////////////////////////////////////////////////////
   // Help and other support

   // Strings in format ".....%1 .... %2 ...." etc.

   /*
   void __format_strings(string & rString, UINT nIDS,
         const char * const* rglpsz, int nString)
   {
      string strFormat;
      if (!strFormat.load_string(nIDS) != 0)
      {
         TRACE(::radix::trace::category_AppMsg, 0, "Error: failed to load gen::FormatString string 0x%04x.\n", nIDS);
         ASSERT(FALSE);
         return;
      }
      __format_strings(rString, strFormat, rglpsz, nString);
   }*/

   void __format_strings(string & rString, const char * lpszFormat,
         const char * const* rglpsz, int nString)
   {
      ENSURE_ARG(lpszFormat != NULL);
      ENSURE_ARG(rglpsz != NULL);
      // determine length of destination string, not including null terminator
      int nTotalLen = 0;
      const char * pchSrc = lpszFormat;
      while (*pchSrc != '\0')
      {
         if (pchSrc[0] == '%' &&
             ( (pchSrc[1] >= '1' && pchSrc[1] <= '9') ||
               (pchSrc[1] >= 'A' && pchSrc[1] <= 'Z')) )
         {
            // %A comes after %9 -- we'll need it someday
            int i;
            if (pchSrc[1] > '9')
               i = 9 + (pchSrc[1] - 'A');
            else
               i = pchSrc[1] - '1';
            pchSrc += 2;
            if (i >= nString)
               ++nTotalLen;
            else if (rglpsz[i] != NULL)
               nTotalLen += lstrlen(rglpsz[i]);
         }
         else
         {
            if (_istlead(*pchSrc))
               ++nTotalLen, ++pchSrc;
            ++pchSrc;
            ++nTotalLen;
         }
      }

      pchSrc = lpszFormat;
      LPTSTR pchDest = rString.GetBuffer(nTotalLen);
      while (*pchSrc != '\0')
      {
         if (pchSrc[0] == '%' &&
             ( (pchSrc[1] >= '1' && pchSrc[1] <= '9') ||
               (pchSrc[1] >= 'A' && pchSrc[1] <= 'Z')) )
         {
            // %A comes after %9 -- we'll need it someday
            int i;
            if (pchSrc[1] > '9')
               i = 9 + (pchSrc[1] - 'A');
            else
               i = pchSrc[1] - '1';
            pchSrc += 2;
            if (i >= nString)
            {
//               TRACE(::radix::trace::category_AppMsg, 0, "Error: illegal string index requested %d.\n", i);
               *pchDest++ = '?';
               nTotalLen--;
            }
            else if (rglpsz[i] != NULL)
            {
               int nLen = lstrlen(rglpsz[i]);
               ::gen::strcpy_s(pchDest, nTotalLen + 1, rglpsz[i]);
               nTotalLen -= nLen;
               pchDest += nLen;
            }
         }
         else
         {
            if (_istlead(*pchSrc))
               *pchDest++ = *pchSrc++, nTotalLen--; // copy first of 2 bytes
            *pchDest++ = *pchSrc++;
            nTotalLen--;
         }
      }
      rString.ReleaseBuffer((int)((const char *)pchDest - (const char *)rString));
         // ReleaseBuffer will assert if we went too far
   }

   /*void gen::FormatString1(string & rString, UINT nIDS, const char * lpsz1)
   {
      __format_strings(rString, nIDS, &lpsz1, 1);
   }

   void gen::FormatString2(string & rString, UINT nIDS, const char * lpsz1,
         const char * lpsz2)
   {
      const char * rglpsz[2];
      rglpsz[0] = lpsz1;
      rglpsz[1] = lpsz2;
      __format_strings(rString, nIDS, rglpsz, 2);
   }*/

   /////////////////////////////////////////////////////////////////////////////


   /////////////////////////////////////////////////////////////////////////////
   // Basic Help support (for backward compatibility to ca2 API 2.0)

   void application::OnHelp()  // use context to derive help context
   {
      if (m_dwPromptContext != 0)
      {
         // do not call WinHelp when the error is failing to lauch help
//         if (m_dwPromptContext != HID_BASE_PROMPT+__IDP_FAILED_TO_LAUNCH_HELP)
  //          WinHelpInternal(m_dwPromptContext);
         return;
      }

      // otherwise, use ::ca::window::OnHelp implementation
      /* trans ::ca::window* pWnd = System.GetMainWnd();
      ENSURE_VALID(pWnd);
      if (!pWnd->IsFrameWnd())
         pWnd->OnHelp();
      else
         (dynamic_cast < frame_window * > (pWnd))->OnHelp();*/
   }

   void application::OnHelpIndex()
   {
      WinHelpInternal(0L, HELP_INDEX);
   }

   void application::OnHelpFinder()
   {
      WinHelpInternal(0L, HELP_FINDER);
   }

   void application::OnHelpUsing()
   {
      WinHelpInternal(0L, HELP_HELPONHELP);
   }

   /////////////////////////////////////////////////////////////////////////////
   // Context Help Mode support (backward compatibility to ca2 API 2.0)

   void application::OnContextHelp()
   {
      // just use frame_window::OnContextHelp implementation
   /* trans   m_bHelpMode = HELP_ACTIVE;
      frame_window* pMainWnd = dynamic_cast < frame_window * > (System.GetMainWnd());
      ENSURE_VALID(pMainWnd);
      ENSURE(pMainWnd->IsFrameWnd());
      pMainWnd->OnContextHelp();
      m_bHelpMode = pMainWnd->m_bHelpMode;
      pMainWnd->PostMessage(WM_KICKIDLE); // trigger idle update */
   }

   /////////////////////////////////////////////////////////////////////////////


   // This is ca2 API library.
   //
   //
   //
   //
   //
   //
   //
   //




   /////////////////////////////////////////////////////////////////////////////
   // WinApp support for printing

   /*bool application::GetPrinterDeviceDefaults(PRINTDLG* pPrintDlg)
   {
      UpdatePrinterSelection(m_hDevNames == NULL); //force default if no current
      if (m_hDevNames == NULL)
         return FALSE;               // no printer defaults

      ENSURE_ARG(pPrintDlg != NULL);
      pPrintDlg->hDevNames = m_hDevNames;
      pPrintDlg->hDevMode = m_hDevMode;

      ::GlobalUnlock(m_hDevNames);
      ::GlobalUnlock(m_hDevMode);
      return TRUE;
   }*/

   void application::UpdatePrinterSelection(bool bForceDefaults)
   {
      UNREFERENCED_PARAMETER(bForceDefaults);
   }


   void application::OnFilePrintSetup()
   {
   }

   void application::SelectPrinter(HANDLE hDevNames, HANDLE hDevMode, bool bFreeOld)
   {
      UNREFERENCED_PARAMETER(hDevNames);
      UNREFERENCED_PARAMETER(hDevMode);
      UNREFERENCED_PARAMETER(bFreeOld);
      throw not_implemented_exception();
      /*if (m_hDevNames != hDevNames)
      {
         if (m_hDevNames != NULL && bFreeOld)
            __global_free(m_hDevNames);
         m_hDevNames = hDevNames;
      }
      if (m_hDevMode != hDevMode)
      {
         if (m_hDevMode != NULL && bFreeOld)
            __global_free(m_hDevMode);
         m_hDevMode = hDevMode;
      }*/
   }

   ::ca::graphics * application::CreatePrinterDC()
   {
//      UNREFERENCED_PARAMETER(spgraphics);
      throw not_implemented_exception();
      /*
      HDC hDC = gen::CreateDC(m_hDevNames, m_hDevMode);
      if (hDC != NULL)
      {
         spgraphics->DeleteDC();
         bool bRet = spgraphics->Attach(hDC);
         ASSERT(bRet);
         return bRet;
      }*/
      //return FALSE;
   }

   /////////////////////////////////////////////////////////////////////////////


   // This is ca2 API library.
   //
   //
   //
   //
   //
   //
   //
   //



   /////////////////////////////////////////////////////////////////////////////
   // application User Interface Extensions

   void application::OnAppExit()
   {

      // same as double-clicking on main ::ca::window close box

      ASSERT(GetMainWnd() != NULL);

      GetMainWnd()->send_message(WM_CLOSE);

   }


   void application::HideApplication()
   {
      try
      {
         if(GetMainWnd() == NULL)
            return;

         // hide the application's windows before closing all the documents
         GetMainWnd()->ShowWindow(SW_HIDE);
      // trans    GetMainWnd()->ShowOwnedPopups(FALSE);

         // put the ::ca::window at the bottom of zorder, so it isn't activated
         GetMainWnd()->SetWindowPos(ZORDER_BOTTOM, 0, 0, 0, 0,
            SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
      }
      catch(...)
      {
      }

   }

   void application::DoWaitCursor(int nCode)
   {
      // 0 => restore, 1=> begin, -1=> end
      ENSURE_ARG(nCode == 0 || nCode == 1 || nCode == -1);
//      ENSURE(afxData.hcurWait != NULL);
//      gen::LockGlobals(CRIT_WAITCURSOR);
      m_nWaitCursorCount += nCode;
      if (m_nWaitCursorCount > 0)
      {
         //HCURSOR hcurPrev = ::SetCursor(afxData.hcurWait);
         //if (nCode > 0 && m_nWaitCursorCount == 1)
           // m_hcurWaitCursorRestore = hcurPrev;
      }
      else
      {
         // turn everything off
         m_nWaitCursorCount = 0;     // prevent underflow
         ::SetCursor(m_hcurWaitCursorRestore);
      }
  //    gen::UnlockGlobals(CRIT_WAITCURSOR);
   }


   bool application::save_all_modified()
   {
/*      if (m_pdocmanager != NULL)
         return m_pdocmanager->save_all_modified();*/
      return TRUE;
   }

   void application::on_request(::ca::create_context * pcreatecontext)
   {
      //m_pdocmanager->request(pcreatecontext);
   }

   void application::close_all_documents(bool bEndSession)
   {
      /*if (m_pdocmanager != NULL)
         m_pdocmanager->close_all_documents(bEndSession);*/
   }


   bool application::OnDDECommand(__in LPTSTR lpszCommand)
   {
/*      if (m_pdocmanager != NULL)
         return m_pdocmanager->OnDDECommand(lpszCommand);
      else*/
         return FALSE;
   }



   void application::EnableModeless(bool bEnable)
   {
       DoEnableModeless(bEnable);
   }

   void application::DoEnableModeless(bool bEnable)
   {
      UNREFERENCED_PARAMETER(bEnable);
   #ifdef ___NO_OLE_SUPPORT
      UNUSED(bEnable);
   #endif

      // no-op if main ::ca::window is NULL or not a frame_window
   /*   ::user::interaction* pMainWnd = System.GetMainWnd();
      if (pMainWnd == NULL || !pMainWnd->IsFrameWnd())
         return;*/

   #ifndef ___NO_OLE_SUPPORT
      // check if notify hook installed
   /*xxx
      ASSERT_KINDOF(frame_window, pMainWnd);
      frame_window* pFrameWnd = (frame_window*)pMainWnd;
      if (pFrameWnd->m_pNotifyHook != NULL)
         pFrameWnd->m_pNotifyHook->OnEnableModeless(bEnable);
   */
   #endif
   }

   int application::DoMessageBox(const char * lpszPrompt, UINT nType, UINT nIDPrompt)
   {
       return ShowAppMessageBox(this, lpszPrompt, nType, nIDPrompt);
   }

   int application::simple_message_box_timeout(::user::interaction * pwndOwner, const char * pszMessage, int iTimeOut,  UINT fuStyle)
   {
      UNREFERENCED_PARAMETER(iTimeOut);
      return simple_message_box(pwndOwner, pszMessage, fuStyle);
   }

   int application::simple_message_box(::user::interaction * puiOwner, const char * pszMessage, UINT fuStyle)
   {

      return MessageBox(puiOwner == NULL ? NULL : (puiOwner->get_wnd() == NULL ? NULL : puiOwner->_get_handle()), pszMessage, m_strAppName, fuStyle);

   }

   int application::simple_message_box(::user::interaction * pwndOwner,  UINT fuStyle, const char * pszFormat, ...)
   {
      va_list va;
      va_start(va, pszFormat);
      string str;
      str.FormatV(pszFormat, va);
      va_end(va);
      return simple_message_box(pwndOwner, str, fuStyle);
   }


   // Helper for message boxes; can work when no application can be found
   int application::ShowAppMessageBox(application *pApp, const char * lpszPrompt, UINT nType, UINT nIDPrompt)
   {
      // disable windows for modal dialog
      DoEnableModeless(FALSE);
      HWND hWndTop;
      HWND hWnd = ::ca::window::GetSafeOwner_(NULL, &hWndTop);

      // re-enable the parent ::ca::window, so that focus is restored
      // correctly when the dialog is dismissed.
      if (hWnd != hWndTop)
         EnableWindow(hWnd, TRUE);

      // set help context if possible
      DWORD* pdwContext = NULL;

      DWORD dwWndPid=0;
      GetWindowThreadProcessId(hWnd,&dwWndPid);

      if (hWnd != NULL && dwWndPid==GetCurrentProcessId() )
      {
         // use cast-level context or frame level context
         LRESULT lResult = ::SendMessage(hWnd, WM_HELPPROMPTADDR, 0, 0);
         if (lResult != 0)
            pdwContext = (DWORD*)lResult;
      }
      // for backward compatibility use cast context if possible
      if (pdwContext == NULL && pApp != NULL)
         pdwContext = &pApp->m_dwPromptContext;

      DWORD dwOldPromptContext = 0;
      if (pdwContext != NULL)
      {
         // save old prompt context for restoration later
         dwOldPromptContext = *pdwContext;
         if (nIDPrompt != 0)
            *pdwContext = HID_BASE_PROMPT+nIDPrompt;
      }

      // determine icon based on type specified
      if ((nType & MB_ICONMASK) == 0)
      {
         switch (nType & MB_TYPEMASK)
         {
         case MB_OK:
         case MB_OKCANCEL:
            nType |= MB_ICONEXCLAMATION;
            break;

         case MB_YESNO:
         case MB_YESNOCANCEL:
            nType |= MB_ICONQUESTION;
            break;

         case MB_ABORTRETRYIGNORE:
         case MB_RETRYCANCEL:
            // No default icon for these types, since they are rarely used.
            // The caller should specify the icon.
            break;
         }
      }

   #ifdef DEBUG
  //    if ((nType & MB_ICONMASK) == 0)
//         TRACE(::radix::trace::category_AppMsg, 0, "Warning: no icon specified for message box.\n");
   #endif

      char szAppName[_MAX_PATH];
      szAppName[0] = '\0';
      const char * pszAppName;
      if (pApp != NULL)
         pszAppName = pApp->m_strAppName;
      else
      {
         pszAppName = szAppName;
         DWORD dwLen = GetModuleFileName(NULL, szAppName, _MAX_PATH);
         if (dwLen == _MAX_PATH)
            szAppName[_MAX_PATH - 1] = '\0';
      }

      int nResult;
      if(pApp == NULL)
      {
         nResult = ::MessageBox(hWnd, lpszPrompt, pszAppName, nType);
      }
      else
      {
         nResult = pApp->simple_message_box(pApp->window_from_os_data(hWnd), lpszPrompt, nType);
      }

      // restore prompt context if possible
      if (pdwContext != NULL)
         *pdwContext = dwOldPromptContext;

      // re-enable windows
      if (hWndTop != NULL)
         ::EnableWindow(hWndTop, TRUE);
      DoEnableModeless(TRUE);

      return nResult;
   }

   /* int gen::MessageBox(const char * lpszText, UINT nType, UINT nIDHelp)
   {
      application* papp = &System;
      if (papp != NULL)
      {
         return papp->DoMessageBox(lpszText, nType, nIDHelp);
      }
      else
      {
         return application::ShowAppMessageBox(NULL, lpszText, nType, nIDHelp);
      }
   }
   */

   /*int System.simple_message_box(UINT nIDPrompt, UINT nType, UINT nIDHelp)
   {
      string string;
      if (!string.load_string(nIDPrompt))
      {
         TRACE(::radix::trace::category_AppMsg, 0, "Error: failed to load message box prompt string 0x%04x.\n",
            nIDPrompt);
         ASSERT(FALSE);
      }
      if (nIDHelp == (UINT)-1)
         nIDHelp = nIDPrompt;
      return System.simple_message_box(string, nType, nIDHelp);
   }*/



   /////////////////////////////////////////////////////////////////////////////


   ::user::interaction * application::get_active_guie()
   {
      return window_from_os_data(::GetActiveWindow());
   }


   ::user::interaction * application::get_focus_guie()
   {
      ::ca::window * pwnd = System.window_from_os_data_permanent(::GetFocus());
      if(pwnd != NULL)
      {
         if(System.get_active_guie()->get_safe_handle() == pwnd->get_safe_handle()
         || ::user::WndUtil::IsAscendant(System.get_active_guie()->get_safe_handle(), pwnd->get_safe_handle()))
         {
            return pwnd;
         }
         else
         {
            return NULL;
         }
      }
      pwnd = System.window_from_os_data(::GetFocus());
      if(pwnd != NULL)
      {
         if(System.get_active_guie()->get_safe_handle() == pwnd->get_safe_handle()
         || ::user::WndUtil::IsAscendant(System.get_active_guie()->get_safe_handle(), pwnd->get_safe_handle()))
         {
            return pwnd;
         }
         else
         {
            return NULL;
         }
      }
      return NULL;
   }





   /*bool application::ProcessShellCommand(CCommandLineInfo& rCmdInfo)
   {
      bool bResult = TRUE;
      switch (rCmdInfo.m_nShellCommand)
      {
      case CCommandLineInfo::FileNew:
         if (!System._001SendCommand("file::new"))
            _001OnFileNew();
         if (GetMainWnd() == NULL)
            bResult = FALSE;
         break;

         // If we've been asked to open a file, call open_document_file()

      case CCommandLineInfo::FileOpen:
         if (!open_document_file(rCmdInfo.m_strFileName))
            bResult = FALSE;
         break;

         // If the ::fontopus::user wanted to print, hide our main ::ca::window and
         // fire a message to ourselves to start the printing

      case CCommandLineInfo::FilePrintTo:
      case CCommandLineInfo::FilePrint:
         m_nCmdShow = SW_HIDE;
         ASSERT(m_pCmdInfo == NULL);
         if(open_document_file(rCmdInfo.m_strFileName))
         {
            m_pCmdInfo = &rCmdInfo;
            ENSURE_VALID(GetMainWnd());
            GetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_PRINT_DIRECT);
            m_pCmdInfo = NULL;
         }
         bResult = FALSE;
         break;

         // If we're doing DDE, hide ourselves

      case CCommandLineInfo::FileDDE:
         m_pCmdInfo = (CCommandLineInfo*)(uint_ptr)m_nCmdShow;
         m_nCmdShow = SW_HIDE;
         break;

      // If we've been asked to register, exit without showing UI.
      // Registration was already done in initialize_instance().
      case CCommandLineInfo::AppRegister:
         {
            Register();
            bResult = FALSE;    // that's all we do

            // If nobody is using it already, we can use it.
            // We'll flag that we're unregistering and not save our state
            // on the way out. This new object gets deleted by the
            // cast object destructor.

            if (m_pCmdInfo == NULL)
            {
               m_pCmdInfo = new CCommandLineInfo;
               m_pCmdInfo->m_nShellCommand = CCommandLineInfo::AppUnregister;
            }
            break;
         }

      // If we've been asked to unregister, unregister and then terminate
      case CCommandLineInfo::AppUnregister:
         {
            bool bUnregistered = Unregister();

            // if you specify /EMBEDDED, we won't make an success/failure box
            // this use of /EMBEDDED is not related to OLE

            if (!rCmdInfo.m_bRunEmbedded)
            {
               /* linux
               if (bUnregistered)
                  System.simple_message_box(__IDP_UNREG_DONE);
               else
                  System.simple_message_box(__IDP_UNREG_FAILURE);
                  */

               /*if (bUnregistered)
                  System.simple_message_box("System unregistered");
               else
                  System.simple_message_box("Failed to unregister application");

            }
            bResult = FALSE;    // that's all we do

            // If nobody is using it already, we can use it.
            // We'll flag that we're unregistering and not save our state
            // on the way out. This new object gets deleted by the
            // cast object destructor.

            if (m_pCmdInfo == NULL)
            {
               m_pCmdInfo = new CCommandLineInfo;
               m_pCmdInfo->m_nShellCommand = CCommandLineInfo::AppUnregister;
            }
         }
         break;
      }
      return bResult;
   }*/

/*   void application::InitLibId()
   {
   }

   bool application::Register()
   {
      return TRUE;
   }

   bool application::Unregister()
   {
      HKEY    hKey = 0;
      char   szBuf[_MAX_PATH+1];
      LONG    cSize = 0;
      bool    bRet = TRUE;

      /*xxx POSITION pos = get_template_count();
      while (pos != NULL)
      {
         document_template * pTempl = get_template(pos);
         if (pTempl != NULL)
            pTempl->_001OnCommand(0, CN_OLE_UNREGISTER, NULL, NULL);
      }*/

      // remove profile information -- the registry entries exist if
      // SetRegistryKey() was used.

  /*    if (m_pszRegistryKey)
      {
         ENSURE(m_pszProfileName != NULL);

         string strKey = "Software\\";
         strKey += m_pszRegistryKey;
         string strSubKey = strKey + "\\" + m_pszProfileName;

         DelRegTree(HKEY_CURRENT_USER, strSubKey);

         // If registry key is is_empty then remove it

         DWORD   dwResult;
         if ((dwResult = ::RegOpenKey(HKEY_CURRENT_USER, strKey, &hKey)) ==
            ERROR_SUCCESS)
         {
            if (::RegEnumKey(hKey, 0, szBuf, _MAX_PATH) == ERROR_NO_MORE_ITEMS)
               DelRegTree(HKEY_CURRENT_USER, strKey);
            ::RegCloseKey(hKey);
         }
         if (RegQueryValue(HKEY_CURRENT_USER, strSubKey, szBuf, &cSize) == ERROR_SUCCESS)
            bRet = TRUE;
      }
      return bRet;
   }*/

//   LONG delete_registry_tree_helper(HKEY hParentKey, const string & strKeyName);

   // Under Win32, a reg key may not be deleted unless it is is_empty.
   // Thus, to delete a tree,  one must recursively enumerate and
   // delete all of the sub-keys.

   /*LONG application::DelRegTree(HKEY hParentKey, const string & strKeyName)
   {
      return delete_registry_tree_helper(hParentKey, strKeyName);
   }

   LONG delete_registry_tree_helper(HKEY hParentKey, const string & strKeyName)
   {
      char   szSubKeyName[MAX_PATH + 1];
      HKEY    hCurrentKey;
      DWORD   dwResult;

      if ((dwResult = RegOpenKey(hParentKey, strKeyName, &hCurrentKey)) ==
         ERROR_SUCCESS)
      {
         // remove all subkeys of the key to delete
         while ((dwResult = RegEnumKey(hCurrentKey, 0, szSubKeyName, MAX_PATH)) ==
               ERROR_SUCCESS)
         {
            try
            {
               // temp string constructed from szSubKeyName can throw in Low Memory condition.
               if ((dwResult = delete_registry_tree_helper(hCurrentKey, szSubKeyName)) != ERROR_SUCCESS)
                  break;
            }
            catch(memory_exception* e)
            {
               dwResult = ERROR_NOT_ENOUGH_MEMORY;
               e->Delete();
               break;
            }
         }

         // If all went well, we should now be able to delete the requested key
         if ((dwResult == ERROR_NO_MORE_ITEMS) || (dwResult == ERROR_BADKEY))
         {
            dwResult = RegDeleteKey(hParentKey, strKeyName);
         }
         RegCloseKey(hCurrentKey);
      }

      return dwResult;
   }*/

   void application::EnableShellOpen()
   {
   /*   ASSERT(m_atomApp == NULL && m_atomSystemTopic == NULL); // do once
      if (m_atomApp != NULL || m_atomSystemTopic != NULL)
      {
         return;
      }

      // Win95 & Win98 sends a WM_DDE_INITIATE with an atom that points to the
      // short file name so we need to use the short file name.
      string strShortName;
      __get_module_short_file_name(System.m_hInstance, strShortName);

      // strip out path
      string strFileName = ::PathFindFileName(strShortName);
      // strip out extension
      LPTSTR pszFileName = strFileName.GetBuffer();
      ::PathRemoveExtension(pszFileName);
      strFileName.ReleaseBuffer();

      m_atomApp = ::GlobalAddAtom(strFileName);
      m_atomSystemTopic = ::GlobalAddAtom("system");*/
   }

   void application::RegisterShellFileTypes(bool bCompat)
   {
      ENSURE(m_pdocmanager != NULL);
//      m_pdocmanager->RegisterShellFileTypes(bCompat);
   }

   void application::UnregisterShellFileTypes()
   {
      ENSURE(m_pdocmanager != NULL);
  //    m_pdocmanager->UnregisterShellFileTypes();
   }


   int application::get_open_document_count()
   {
      ENSURE(m_pdocmanager != NULL);
    //  return m_pdocmanager->get_open_document_count();
      return 0;
   }


   // This is ca2 API library.
   //
   //
   //
   //
   //
   //
   //
   //

   /////////////////////////////////////////////////////////////////////////////
   // application Settings Helpers


   void application::SetRegistryKey(const char * lpszRegistryKey)
   {
      ASSERT(m_pszRegistryKey == NULL);
      ASSERT(lpszRegistryKey != NULL);
      ASSERT(m_strAppName.has_char());

      //bool bEnable = __enable_memory_tracking(FALSE);
      free((void *)m_pszRegistryKey);
      m_pszRegistryKey = _tcsdup(lpszRegistryKey);
      free((void *)m_pszProfileName);
      m_pszProfileName = _tcsdup(m_strAppName);
      //__enable_memory_tracking(bEnable);
   }

   void application::SetRegistryKey(UINT nIDRegistryKey)
   {
      UNREFERENCED_PARAMETER(nIDRegistryKey);
      ASSERT(m_pszRegistryKey == NULL);
    throw not_implemented_exception();
      /*char szRegistryKey[256];
      VERIFY(gen::LoadString(nIDRegistryKey, szRegistryKey));
      SetRegistryKey(szRegistryKey);*/
   }

   // returns key for HKEY_CURRENT_USER\"Software"\RegistryKey\ProfileName
   // creating it if it doesn't exist
   // responsibility of the caller to call RegCloseKey() on the returned HKEY
   HKEY application::GetAppRegistryKey()
   {
      ASSERT(m_pszRegistryKey != NULL);
      ASSERT(m_pszProfileName != NULL);

      HKEY hAppKey = NULL;
      HKEY hSoftKey = NULL;
      HKEY hCompanyKey = NULL;
      if (RegOpenKeyEx(HKEY_CURRENT_USER, "software", 0, KEY_WRITE|KEY_READ,
         &hSoftKey) == ERROR_SUCCESS)
      {
         DWORD dw;
         if (RegCreateKeyEx(hSoftKey, m_pszRegistryKey, 0, REG_NONE,
            REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL,
            &hCompanyKey, &dw) == ERROR_SUCCESS)
         {
            RegCreateKeyEx(hCompanyKey, m_pszProfileName, 0, REG_NONE,
               REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL,
               &hAppKey, &dw);
         }
      }
      if (hSoftKey != NULL)
         RegCloseKey(hSoftKey);
      if (hCompanyKey != NULL)
         RegCloseKey(hCompanyKey);

      return hAppKey;
   }

   // returns key for:
   //      HKEY_CURRENT_USER\"Software"\RegistryKey\AppName\lpszSection
   // creating it if it doesn't exist.
   // responsibility of the caller to call RegCloseKey() on the returned HKEY
   HKEY application::GetSectionKey(const char * lpszSection)
   {
      ASSERT(lpszSection != NULL);

      HKEY hSectionKey = NULL;
      HKEY hAppKey = GetAppRegistryKey();
      if (hAppKey == NULL)
         return NULL;

      DWORD dw;
      RegCreateKeyEx(hAppKey, lpszSection, 0, REG_NONE,
         REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL,
         &hSectionKey, &dw);
      RegCloseKey(hAppKey);
      return hSectionKey;
   }

/*   UINT application::GetProfileInt(const char * lpszSection, const char * lpszEntry,
      int nDefault)
   {
      ASSERT(lpszSection != NULL);
      ASSERT(lpszEntry != NULL);
      if (m_pszRegistryKey != NULL) // use registry
      {
         HKEY hSecKey = GetSectionKey(lpszSection);
         if (hSecKey == NULL)
            return nDefault;
         DWORD dwValue;
         DWORD dwType;
         DWORD dwCount = sizeof(DWORD);
         LONG lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType,
            (LPBYTE)&dwValue, &dwCount);
         RegCloseKey(hSecKey);
         if (lResult == ERROR_SUCCESS)
         {
            ASSERT(dwType == REG_DWORD);
            ASSERT(dwCount == sizeof(dwValue));
            return (UINT)dwValue;
         }
         return nDefault;
      }
      else
      {
         ASSERT(m_pszProfileName != NULL);
         return ::GetPrivateProfileInt(lpszSection, lpszEntry, nDefault,
            m_pszProfileName);
      }
   }

   string application::GetProfileString(const char * lpszSection, const char * lpszEntry,
      const char * lpszDefault)
   {
      ASSERT(lpszSection != NULL);
      ASSERT(lpszEntry != NULL);
      if (m_pszRegistryKey != NULL)
      {
         HKEY hSecKey = GetSectionKey(lpszSection);
         if (hSecKey == NULL)
            return lpszDefault;
         string strValue;
         DWORD dwType=REG_NONE;
         DWORD dwCount=0;
         LONG lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType,
            NULL, &dwCount);
         if (lResult == ERROR_SUCCESS)
         {
            ASSERT(dwType == REG_SZ);
            lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType,
               (LPBYTE)strValue.GetBuffer(dwCount/sizeof(char)), &dwCount);
            strValue.ReleaseBuffer();
         }
         RegCloseKey(hSecKey);
         if (lResult == ERROR_SUCCESS)
         {
            ASSERT(dwType == REG_SZ);
            return strValue;
         }
         return lpszDefault;
      }
      else
      {
         ASSERT(m_pszProfileName != NULL);

         if (lpszDefault == NULL)
            lpszDefault = "";   // don't pass in NULL
         char szT[4096];
         DWORD dw = ::GetPrivateProfileString(lpszSection, lpszEntry,
            lpszDefault, szT, _countof(szT), m_pszProfileName);
         ASSERT(dw < 4095);
         return szT;
      }
   }

   bool application::GetProfileBinary(const char * lpszSection, const char * lpszEntry,
      BYTE** ppData, UINT* pBytes)
   {
      ASSERT(lpszSection != NULL);
      ASSERT(lpszEntry != NULL);
      ASSERT(ppData != NULL);
      ASSERT(pBytes != NULL);
      *ppData = NULL;
      *pBytes = 0;
      if (m_pszRegistryKey != NULL)
      {
         HKEY hSecKey = GetSectionKey(lpszSection);
         if (hSecKey == NULL)
         {
            return FALSE;
         }

         // ensure destruction

         // linux ::gen::CRegKey rkSecKey(hSecKey);

         DWORD dwType=0;
         DWORD dwCount=0;
         LONG lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType, NULL, &dwCount);
         *pBytes = dwCount;
         if (lResult == ERROR_SUCCESS)
         {
            ASSERT(dwType == REG_BINARY);
            *ppData = new BYTE[*pBytes];
            lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType,
               *ppData, &dwCount);
         }
         if (lResult == ERROR_SUCCESS)
         {
            ASSERT(dwType == REG_BINARY);
            return TRUE;
         }
         else
         {
            delete [] *ppData;
            *ppData = NULL;
         }
         return FALSE;
      }
      else
      {
         ASSERT(m_pszProfileName != NULL);

         string str = GetProfileString(lpszSection, lpszEntry, NULL);
         if (str.is_empty())
            return FALSE;
         ASSERT(str.get_length()%2 == 0);
         int_ptr nLen = str.get_length();
         *pBytes = UINT(nLen)/2;
         *ppData = new BYTE[*pBytes];
         for (int i=0;i<nLen;i+=2)
         {
            (*ppData)[i/2] = (BYTE)
               (((str[i+1] - 'A') << 4) + (str[i] - 'A'));
         }
         return TRUE;
      }
   }


   bool application::WriteProfileInt(const char * lpszSection, const char * lpszEntry,
      int nValue)
   {
      ASSERT(lpszSection != NULL);
      ASSERT(lpszEntry != NULL);
      if (m_pszRegistryKey != NULL)
      {
         HKEY hSecKey = GetSectionKey(lpszSection);
         if (hSecKey == NULL)
            return FALSE;
         LONG lResult = RegSetValueEx(hSecKey, lpszEntry, NULL, REG_DWORD,
            (LPBYTE)&nValue, sizeof(nValue));
         RegCloseKey(hSecKey);
         return lResult == ERROR_SUCCESS;
      }
      else
      {
         ASSERT(m_pszProfileName != NULL);

         char szT[16];
         _stprintf_s(szT, _countof(szT), "%d", nValue);
         return ::WritePrivateProfileString(lpszSection, lpszEntry, szT,
            m_pszProfileName);
      }
   }

   bool application::WriteProfileString(const char * lpszSection, const char * lpszEntry,
            const char * lpszValue)
   {
      ASSERT(lpszSection != NULL);
      if (m_pszRegistryKey != NULL)
      {
         LONG lResult;
         if (lpszEntry == NULL) //delete whole section
         {
            HKEY hAppKey = GetAppRegistryKey();
            if (hAppKey == NULL)
               return FALSE;
            lResult = ::RegDeleteKey(hAppKey, lpszSection);
            RegCloseKey(hAppKey);
         }
         else if (lpszValue == NULL)
         {
            HKEY hSecKey = GetSectionKey(lpszSection);
            if (hSecKey == NULL)
               return FALSE;
            // necessary to cast away const below
            lResult = ::RegDeleteValue(hSecKey, (LPTSTR)lpszEntry);
            RegCloseKey(hSecKey);
         }
         else
         {
            HKEY hSecKey = GetSectionKey(lpszSection);
            if (hSecKey == NULL)
               return FALSE;
            lResult = RegSetValueEx(hSecKey, lpszEntry, NULL, REG_SZ,
               (LPBYTE)lpszValue, (lstrlen(lpszValue)+1)*sizeof(char));
            RegCloseKey(hSecKey);
         }
         return lResult == ERROR_SUCCESS;
      }
      else
      {
         ASSERT(m_pszProfileName != NULL);
         ASSERT(lstrlen(m_pszProfileName) < 4095); // can't read in bigger
         return ::WritePrivateProfileString(lpszSection, lpszEntry, lpszValue,
            m_pszProfileName);
      }
   }

   bool application::WriteProfileBinary(const char * lpszSection, const char * lpszEntry,
      LPBYTE pData, UINT nBytes)
   {
      ASSERT(lpszSection != NULL);
      if (m_pszRegistryKey != NULL)
      {
         LONG lResult;
         HKEY hSecKey = GetSectionKey(lpszSection);
         if (hSecKey == NULL)
            return FALSE;
         lResult = RegSetValueEx(hSecKey, lpszEntry, NULL, REG_BINARY,
            pData, nBytes);
         RegCloseKey(hSecKey);
         return lResult == ERROR_SUCCESS;
      }

      // convert to string and write out
      LPTSTR lpsz = new char[nBytes*2+1];
      UINT i;
      for (i = 0; i < nBytes; i++)
      {
         lpsz[i*2] = (char)((pData[i] & 0x0F) + 'A'); //low nibble
         lpsz[i*2+1] = (char)(((pData[i] >> 4) & 0x0F) + 'A'); //high nibble
      }
      lpsz[i*2] = 0;

      ASSERT(m_pszProfileName != NULL);

      bool bResult = WriteProfileString(lpszSection, lpszEntry, lpsz);
      delete[] lpsz;
      return bResult;
   }

#include "framework.h"*/




   gen::property_set & application::propset(::radix::object * pobject)
   {
      single_lock sl(&m_mapObjectSet, TRUE);
      return m_mapObjectSet[pobject];
   }

   bool application::bergedge_start()
   {
      return true;
   }


   bool application::does_launch_window_on_startup()
   {
      return true;
   }

   bool application::activate_app()
   {
      if(GetMainWnd() != NULL)
      {
         GetMainWnd()->ShowWindow(SW_SHOWNORMAL);
      }
      return true;
   }






   /*   int application::GetResourceId(const id_space * pspace, int iKey)
   {
      int iId;
      if(!m_imapResource.get(pspace, iKey, iId))
      {
         m_imapResource.Set(pspace, iKey, m_iResourceId);
         m_iResourceId++;
         if(!m_imapResource.get(pspace, iKey, iId))
         {
            return -1;
         }
      }
      return iId;
   }

   int application::GetResourceId(const id_space * pspace, const char * lpcszKey)
   {
      int iId;
      if(!m_strmapResource.get(pspace, lpcszKey, iId))
      {
         m_strmapResource.Set(pspace, lpcszKey, m_iResourceId);
         m_iResourceId++;
         if(!m_strmapResource.get(pspace, lpcszKey, iId))
         {
            return -1;
         }
      }
      return iId;
   }


   int application::GetResourceId(const id_space & space, int iKey)
   {
      return GetResourceId(&space, iKey);
   }

   int application::GetResourceId(const id_space & space, const char * lpcszKey)
   {
      return GetResourceId(&space, lpcszKey);
   }
   */

   string application::matter_as_string(const char * pszMatter, const char * pszMatter2)
   {
      UNREFERENCED_PARAMETER(pszMatter);
      UNREFERENCED_PARAMETER(pszMatter2);
      throw not_implemented_exception();
   }

   string application::dir_matter(const char * pszMatter, const char * pszMatter2)
   {
      UNREFERENCED_PARAMETER(pszMatter);
      UNREFERENCED_PARAMETER(pszMatter2);
      throw not_implemented_exception();
   }

   bool application::is_inside_time_dir(const char * pszPath)
   {
      UNREFERENCED_PARAMETER(pszPath);
      throw not_implemented_exception();
   }

   bool application::file_is_read_only(const char * pszPath)
   {
      UNREFERENCED_PARAMETER(pszPath);
      throw not_implemented_exception();
   }

   string application::file_as_string(const char * pszPath)
   {
      UNREFERENCED_PARAMETER(pszPath);
      throw not_implemented_exception();
   }

   string application::dir_path(const char * psz1, const char * psz2, const char * psz3)
   {
      UNREFERENCED_PARAMETER(psz1);
      UNREFERENCED_PARAMETER(psz2);
      UNREFERENCED_PARAMETER(psz3);
      throw not_implemented_exception();
   }

   string application::dir_name(const char * psz)
   {
      UNREFERENCED_PARAMETER(psz);
      throw not_implemented_exception();
   }

   bool application::dir_mk(const char * psz)
   {
      UNREFERENCED_PARAMETER(psz);
      throw not_implemented_exception();
   }

   string application::file_title(const char * psz)
   {
      return System.file_title(psz);
   }

   string application::file_name(const char * psz)
   {
      return System.file_name(psz);
   }




   HWND application::get_ca2_app_wnd(const char * psz)
   {
      UNREFERENCED_PARAMETER(psz);
      return NULL;
   }

   ::user::interaction * application::uie_from_point(point pt)
   {
      UNREFERENCED_PARAMETER(pt);
      return NULL;
   }




   ::user::interaction * application::release_capture_uie()
   {
      HWND hwndCapture = ::GetCapture();
      if(hwndCapture == NULL)
         return NULL;
      return System.window_from_os_data(hwndCapture)->release_capture();
   }

   ::user::interaction * application::get_capture_uie()
   {
      HWND hwndCapture = ::GetCapture();
      if(hwndCapture == NULL)
         return NULL;
      return System.window_from_os_data(hwndCapture)->get_capture();
   }

   ::user::str_context * application::str_context()
   {
      return m_puserstrcontext;
   }

   bool application::initialize1()
   {

      //Sleep(15 * 1000);

      m_strMatterLocator = System.dir().appmatter_locator(this);


      m_puserstrcontext = new ::user::str_context(this);
      if(m_puserstrcontext == NULL)
         return false;


      if(!ca_initialize1())
            return false;


      return true;


   }


   void application::on_delete(::ca::ca * pobject)
   {
      try
      {
         waitable * pobj = dynamic_cast < waitable * >(pobject);
         if(pobj != NULL)
         {
            mutex * pmutex = get_mutex(pobj);
            if(pmutex != NULL)
            {
               single_lock sl(&m_mutexObjectLock, TRUE);
               delete pmutex;
               m_mapObjectMutex.remove_key(pobj);
            }
         }
      }
      catch(...)
      {
      }
   }

   mutex * application::get_mutex(waitable * pobject)
   {
      single_lock sl(&m_mutexObjectLock, TRUE);
      mutex * pmutex;
      if(!m_mapObjectMutex.Lookup(pobject, pmutex))
      {
         pmutex = new mutex();
         m_mapObjectMutex.set_at(pobject, pmutex);
      }
      return pmutex;
   }

   void application::wait(waitable * pobject)
   {

      mutex * pmutex = get_mutex(pobject);

      if(pmutex == NULL)
         throw resource_exception();

      pmutex->wait();

   }

   wait_result application::wait(waitable * pobject, duration duration)
   {

      mutex * pmutex = get_mutex(pobject);

      if(pmutex == NULL)
         return wait_result(wait_result::Failure);

      return pmutex->wait(duration);

   }

   bool application::lock(waitable * pobject)
   {
      mutex * pmutex = get_mutex(pobject);
      if(pmutex == NULL)
         return false;
      return pmutex->lock() != FALSE;
   }


   bool application::lock(waitable * pobject, duration duration)
   {
      mutex * pmutex = get_mutex(pobject);
      if(pmutex == NULL)
         return false;
      return pmutex->lock(duration) != FALSE;
   }


   bool application::unlock(waitable * pobject)
   {
      mutex * pmutex = get_mutex(pobject);
      if(pmutex == NULL)
         return false;
      return pmutex->unlock() != FALSE;
   }

   event * application::get_event(::radix::object * pobject, int iEvent)
   {
      single_lock sl(&m_mutexObjectEvent, TRUE);
      ::collection::map < int, int, event *, event * > * peventmap;
      if(!m_mapObjectEvent.Lookup(pobject, peventmap))
      {
         peventmap = new ::collection::map < int, int, event *, event * >();
         m_mapObjectEvent.set_at(pobject, peventmap);
      }
      event * pevent;
      if(!peventmap->Lookup(iEvent, pevent))
      {
         pevent = new event();
         peventmap->set_at(iEvent, pevent);
      }
      return pevent;
   }

   bool application::event_lock(::radix::object * pobject, int iEvent, duration duration)
   {
      event * pevent = get_event(pobject, iEvent);
      if(pevent == NULL)
         return false;
      return pevent->wait(duration).signaled();
   }

   bool application::event_unlock(::radix::object * pobject, int iEvent)
   {
      event * pevent = get_event(pobject, iEvent);
      if(pevent == NULL)
         return false;
      return true;
   }

   void application::get_cursor_pos(LPPOINT lppoint)
   {
      if(is_system() || is_cube())
      {
         if(m_bSessionSynchronizedCursor)
         {
            ::GetCursorPos(&m_ptCursor);
         }
         if(lppoint != NULL)
         {
            *lppoint = m_ptCursor;
         }
      }
      else if(is_session() || is_bergedge())
      {
         if(m_bSessionSynchronizedCursor)
         {
            ::GetCursorPos(&m_ptCursor);
         }
         if(lppoint != NULL)
         {
            *lppoint = m_ptCursor;
         }
      }
      else
      {
         Session.get_cursor_pos(lppoint);
      }
   }

   void application::get_screen_rect(LPRECT lprect)
   {
      if(m_bSessionSynchronizedScreen)
      {
         HWND hwndDesktop = ::GetDesktopWindow();
         ::GetWindowRect(hwndDesktop, &m_rectScreen);
      }
      if(lprect != NULL)
      {
         *lprect = m_rectScreen;
      }
   }

   int application::get_document_count()
   {
//      return m_pdocmanager->get_document_count();
      return 0;
   }

   int application::exit()
   {
      int iExit = 0;

      try
      {
         iExit = ::ca::application::exit();
      }
      catch(...)
      {
         iExit = -1;
      }

      try
      {
         ::radix::thread::exit();
      }
      catch(...)
      {
      }

      return iExit;
   }

   int application::exit_instance()
   {

      release_exclusive();

      if(!finalize_message_window())
      {
         TRACE("Could not finalize message window");
      }

      ::radix::application_signal_object signal(this, &m_signal, ::ca::application_signal_exit_instance);
      try
      {
         m_signal.emit(&signal);
      }
      catch(...)
      {
      }

      try
      {
         if(!is_system())
         {
            System.unregister_bergedge_application(this);
         }
      }
      catch(...)
      {
      }

      /*try
      {
         gen::release(smart_pointer <::ca::thread>::m_p);
      }
      catch(...)
      {
      }*/


      return 0;
/*      int nReturnValue=0;
      if(__get_current_message())
      {
         nReturnValue=static_cast<int>(__get_current_message()->wParam);
      }*/
//      return nReturnValue; // returns the value from PostQuitMessage
   }


   // Temporary ::collection::map management (locks temp ::collection::map on current thread)
   void application::LockTempMaps()
   {
   }

   bool application::UnlockTempMaps(bool bDeleteTemps)
   {
      UNREFERENCED_PARAMETER(bDeleteTemps);
      return TRUE;
   }

   void application::TermThread(HINSTANCE hInstTerm)
   {
      UNREFERENCED_PARAMETER(hInstTerm);
   }

/*   ::ca::graphics * application::graphics_from_os_data(void * pdata)
   {
      UNREFERENCED_PARAMETER(pdata);
      return NULL;
   }*/

   ::ca::window * application::window_from_os_data(void * pdata)
   {
      UNREFERENCED_PARAMETER(pdata);
      return NULL;
   }

   ::ca::window * application::window_from_os_data_permanent(void * pdata)
   {
      UNREFERENCED_PARAMETER(pdata);
      return NULL;
   }

   ::ca::window * application::FindWindow(const char * lpszClassName, const char * lpszWindowName)
   {
      UNREFERENCED_PARAMETER(lpszClassName);
      UNREFERENCED_PARAMETER(lpszWindowName);
      throw not_implemented_exception();
   }

   ::ca::window * application::FindWindowEx(HWND hwndParent, HWND hwndChildAfter, const char * lpszClass, const char * lpszWindow)
   {
      UNREFERENCED_PARAMETER(hwndParent);
      UNREFERENCED_PARAMETER(hwndChildAfter);
      UNREFERENCED_PARAMETER(lpszClass);
      UNREFERENCED_PARAMETER(lpszWindow);
      throw not_implemented_exception();
   }

   string application::get_local_mutex_name(const char * pszAppName)
   {
      string strMutex;
      strMutex.Format("Local\\ca2_fontopus_votagus_application_local_mutex:%s", pszAppName);
      return strMutex;
   }

   string application::get_local_id_mutex_name(const char * pszAppName, const char * pszId)
   {
      string strId(pszId);
      string strMutex;
      strMutex.Format("Local\\ca2_fontopus_votagus_application_local_mutex:%s, id:%s", pszAppName, strId);
      return strMutex;
   }

   string application::get_global_mutex_name(const char * pszAppName)
   {
      string strMutex;
      strMutex.Format("Global\\ca2_fontopus_votagus_application_global_mutex:%s", pszAppName);
      return strMutex;
   }

   string application::get_global_id_mutex_name(const char * pszAppName, const char * pszId)
   {
      string strId(pszId);
      string strMutex;
      strMutex.Format("Global\\ca2_fontopus_votagus_application_global_mutex:%s, id:%s", pszAppName,  strId);
      return strMutex;
   }

   string application::get_local_mutex_name()
   {
      return get_local_mutex_name(get_mutex_name_radix());
   }

   string application::get_local_id_mutex_name()
   {
      return get_local_id_mutex_name(get_mutex_name_radix(), get_local_mutex_id());
   }

   string application::get_global_mutex_name()
   {
      return get_global_mutex_name(get_mutex_name_radix());
   }

   string application::get_global_id_mutex_name()
   {
      return get_global_id_mutex_name(get_mutex_name_radix(), get_global_mutex_id());
   }


   application_signal_object::application_signal_object(::ca::application * papp, gen::signal * psignal, ::ca::e_application_signal esignal) :
      ca(papp),
      gen::signal_object(psignal)
   {

      m_esignal         = esignal;
      m_bOk             = true;

   }

   bool application::is_system()
   {
      return false;
   }

   bool application::is_bergedge()
   {
      return false;
   }

   ::ca::ca * application::alloc(::ca::type_info & info)
   {
      return System.alloc(this, info);
   }

   ::ca::ca * application::alloc(const  id & idType)
   {
      return System.alloc(this, idType);
   }








   bool application::finalize()
   {
      bool bFinalize = false;

      try
      {
         bFinalize = ::ca::application::finalize();
      }
      catch(...)
      {
         bFinalize = false;
      }

      try
      {
         ::radix::thread::finalize();
      }
      catch(...)
      {
         bFinalize = false;
      }

      return bFinalize;
   }

   bool application::app_map_lookup(const char * psz, void * & p)
   {
      return m_appmap.Lookup(psz, p) != FALSE;
   }

   void application::app_map_set(const char * psz, void * p)
   {
      m_appmap.set_at(psz, p);
   }

/*   ::user::interaction * application::get_place_holder_container()
   {
      if(m_puiInitialPlaceHolderContainer != NULL)
         return m_puiInitialPlaceHolderContainer;
      if(m_psession != NULL)
      {
         try
         {
            if(m_psession->m_puiInitialPlaceHolderContainer != NULL)
               return m_psession->m_puiInitialPlaceHolderContainer;
         }
         catch(...)
         {
         }
      }
      if(m_psystem != NULL)
      {
         try
         {
            if(m_psystem->m_puiInitialPlaceHolderContainer != NULL)
               return m_psystem->m_puiInitialPlaceHolderContainer;
         }
         catch(...)
         {
         }
      }
      return NULL;
   }
   */


   ::user::interaction * application::get_request_parent_ui(::user::interaction * pinteraction, ::ca::create_context * pcreatecontext)
   {

      ::user::interaction * puiParent = NULL;

/*      if(puiParent == NULL && dynamic_cast < ::userbase::main_frame * > (pinteraction) != NULL)
      {
         puiParent = get_request_parent_ui(dynamic_cast < ::userbase::main_frame * > (pinteraction), pcreatecontext);
      }*/

      if(puiParent == NULL)
      {
         puiParent = pcreatecontext->m_puiParent;
      }

      if(puiParent == NULL && pcreatecontext->m_spApplicationBias.is_set())
      {
         puiParent = pcreatecontext->m_spApplicationBias->m_puiParent;
      }

      if(puiParent == NULL && m_psession != NULL && !pcreatecontext->m_bClientOnly
         && !pcreatecontext->m_bOuterPopupAlertLike && m_psession != this)
      {
         puiParent = Sess(this).get_request_parent_ui(pinteraction, pcreatecontext);
      }

      return puiParent;

   }

   ::user::interaction * application::get_request_parent_ui(::userbase::main_frame * pmainframe, ::ca::create_context * pcreatecontext)
   {

      if(m_psession != NULL)
      {
         return Sess(this).get_request_parent_ui(pmainframe, pcreatecontext);
      }

      return NULL;

   }

} // namespace radix



file_manager_interface::file_manager_interface()
{
}

file_manager_interface::~file_manager_interface()
{
}

bool file_manager_interface::do_prompt_file_name(var & varFile, UINT nIDSTitle, DWORD lFlags, bool bOpenFileDialog, document_template * ptemplate, ::user::document_interface * pdocument)
{
   UNREFERENCED_PARAMETER(varFile);
   UNREFERENCED_PARAMETER(nIDSTitle);
   UNREFERENCED_PARAMETER(lFlags);
   UNREFERENCED_PARAMETER(bOpenFileDialog);
   UNREFERENCED_PARAMETER(ptemplate);
   return FALSE;
}

bool file_manager_interface::initialize(::ca::application * papp)
{
   UNREFERENCED_PARAMETER(papp);
   //set_app(papp);
   return true;
}


void __post_quit_message(int nExitCode)
{

   ::PostQuitMessage(nExitCode);
}





