#include "framework.h"
#include <VersionHelpers.h>

#include <ddeml.h>


___WIN_STATE gen_WinState;

typedef bool
(WINAPI * LPFN_ChangeWindowMessageFilter)(
    _In_ UINT message,
    _In_ uint32_t dwFlag);


CLASS_DECL_BASE LPFN_ChangeWindowMessageFilter g_pfnChangeWindowMessageFilter = NULL;

typedef  
LSTATUS
( APIENTRY * LPFN_RegGetValueW) (
    HKEY hkey,
    LPCWSTR lpSubKey,
    LPCWSTR lpValue,
    uint32_t dwFlags,
    LPDWORD pdwType,
	 PVOID pvData,
    LPDWORD pcbData
    );

LPFN_RegGetValueW g_pfnRegGetValueW = NULL;



int_bool os_initialize()
{

   __init_threading_count();

   ::os_thread::s_pmutex = new mutex();

   ::os_thread::s_pptra = new comparable_raw_array < os_thread * >::type ();

   ::windows::thread::s_pmutex = new mutex();
   ::windows::thread::s_phaThread = new comparable_array < HANDLE >;
   ::windows::thread::s_pthreadptra = new comparable_array < ::windows::thread * >;

   //Sleep(15 * 1000);

   //if(!psystem->install().trace().initialize())
     // return FALSE;


   HMODULE hmoduleUser32 = ::LoadLibrary("User32");
   g_pfnChangeWindowMessageFilter = (LPFN_ChangeWindowMessageFilter) ::GetProcAddress(hmoduleUser32, "ChangeWindowMessageFilter");


   HMODULE hmoduleAdvApi32 = ::LoadLibrary("AdvApi32");
   g_pfnRegGetValueW = (LPFN_RegGetValueW) ::GetProcAddress(hmoduleAdvApi32, "RegGetValueW");


   return TRUE;

} 


int_bool os_finalize()
{

   delete ::windows::thread::s_pmutex;
   ::windows::thread::s_pmutex = NULL;

   delete ::windows::thread::s_phaThread;
   ::windows::thread::s_phaThread = NULL;
   
   delete ::windows::thread::s_pthreadptra;
   ::windows::thread::s_pthreadptra = NULL;

   //psystem->install().trace().finalize();

   __term_threading_count();

   return TRUE;

}



int WinRegGetValueW(HKEY hkey, LPCWSTR lpSubKey, LPCWSTR lpValue, DWORD dwFlags, LPDWORD pdwType, PVOID pvData, LPDWORD pcbData)
{

   if(g_pfnRegGetValueW != NULL)
   {
      return g_pfnRegGetValueW(hkey, lpSubKey, lpValue, dwFlags, pdwType, pvData, pcbData);
   }
   else
   {
      LSTATUS lstatus = RegQueryValueExW(hkey, lpSubKey, NULL, pdwType, (LPBYTE) pvData, pcbData);
      if(lstatus == ERROR_SUCCESS)
      {
         if(pvData != NULL && (dwFlags & RRF_RT_REG_SZ) != 0 && *pdwType == REG_SZ)
         {
            ((WCHAR *)pvData)[*pcbData] = L'\0';
         }
      }
      return lstatus;
   }
}



Gdiplus::GdiplusStartupInput *   g_pgdiplusStartupInput     = NULL;
Gdiplus::GdiplusStartupOutput *  g_pgdiplusStartupOutput    = NULL;
DWORD_PTR                        g_gdiplusToken             = NULL;
DWORD_PTR                        g_gdiplusHookToken         = NULL;


int_bool main_initialize()
{

   //Sleep(15 * 1000);

   g_pgdiplusStartupInput     = new Gdiplus::GdiplusStartupInput();
   g_pgdiplusStartupOutput    = new Gdiplus::GdiplusStartupOutput();
   g_gdiplusToken             = NULL;
   g_gdiplusHookToken         = NULL;

   //MessageBox(NULL, "Gdiplus Failed to Startup. ca cannot continue.", "Gdiplus Failure", MB_ICONERROR);

   g_pgdiplusStartupInput->SuppressBackgroundThread = TRUE;

   // Initialize GDI+.
   Gdiplus::Status statusStartup = GdiplusStartup(&g_gdiplusToken, g_pgdiplusStartupInput, g_pgdiplusStartupOutput);

   if(statusStartup != Gdiplus::Ok)
   {
      
      MessageBox(NULL, "Gdiplus Failed to Startup. ca cannot continue.", "Gdiplus Failure", MB_ICONERROR);
      
      return FALSE;

   }

   statusStartup = g_pgdiplusStartupOutput->NotificationHook(&g_gdiplusHookToken);
   

   if(statusStartup != Gdiplus::Ok)
   {
      
      MessageBox(NULL, "Gdiplus Failed to Hook. ca cannot continue.", "Gdiplus Failure", MB_ICONERROR);
      
      return FALSE;

   }

   

   return TRUE;

} 


int_bool main_finalize()
{

   g_pgdiplusStartupOutput->NotificationUnhook(g_gdiplusHookToken);

   Gdiplus::GdiplusShutdown(g_gdiplusToken);


   return TRUE;

}




string key_to_char(WPARAM wparam, LPARAM lparam)
{



   wchar_t wsz[32];

   BYTE baState[256];

   for(int i = 0; i < 256; i++)
   {
      baState[i] = (BYTE) GetAsyncKeyState(i);
   }

   if((GetAsyncKeyState(VK_SHIFT) & 0x80000000) != 0)
   {
      baState[VK_SHIFT] |= 0x80;
   }


   int32_t iRet = ToUnicodeEx((UINT) wparam, (UINT) lparam, baState, wsz, 32, 0, GetKeyboardLayout(GetCurrentThreadId()));

   if(iRet > 0)
   {

      wsz[iRet] = L'\0';

      string str;

      str = ::str::international::unicode_to_utf8(wsz);

      if((GetAsyncKeyState(VK_CAPITAL) & 0x0001) != 0)
      {
         if((GetAsyncKeyState(VK_SHIFT) & 0x80000000) != 0)
         {
            str.make_lower();
         }
         else
         {
            str.make_upper();
         }
      }
      else
      {
         if((GetAsyncKeyState(VK_SHIFT) & 0x80000000) != 0)
         {
            str.make_upper();
         }
         else
         {
            str.make_lower();
         }
      }

         

      return str;

   }

   return "";

}

 string get_system_error_message(uint32_t dwError)
{

   LPWSTR lpBuffer;

   HMODULE Hand = NULL;

   if(!FormatMessageW(
      FORMAT_MESSAGE_ALLOCATE_BUFFER |
      FORMAT_MESSAGE_FROM_SYSTEM,
      NULL,
      dwError,
      0,
      (LPWSTR) &lpBuffer,
      1,
      NULL))
   {

      HMODULE Hand = ::LoadLibrary("NTDLL.DLL");

      if(!FormatMessageW(
         FORMAT_MESSAGE_ALLOCATE_BUFFER |
         FORMAT_MESSAGE_FROM_SYSTEM |
         FORMAT_MESSAGE_FROM_HMODULE,
         Hand,
         dwError,
         0,
         (LPWSTR) &lpBuffer,
         1,
         NULL))
      {
         FreeLibrary(Hand);
         return "";
      }

   }

   string str(lpBuffer);

   LocalFree(lpBuffer);
   
   if(Hand != NULL)
   {
      FreeLibrary(Hand);
   }

   return str;

}





void output_debug_string(const char * psz)
{
   ::OutputDebugStringW(wstring(psz));
}





/*

// This example checks if the operating system is of "NT-type"
// (which means Windows NT, 2000, XP).
int GetVersion_ex1()
{
   DWORD    dwVersion = GetVersion();
   // Get major and minor version numbers of Windows
   WORD loword = LOWORD(dwVersion);
   int lowbyte = LOBYTE(loword);
   int hibyte = HIBYTE(loword);

   printf("Window major version = %d and minor version = %d\n", lowbyte, hibyte);

   if (!(dwVersion & 0x80000000))                // Windows NT, 2000, XP
      return 1;
   else         // Windows 95, 98, ME
      return 0;
}


*/


BEGIN_EXTERN_C


int_bool is_windows_98_or_lesser()
{

//#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WIN7) // Windows 7 or greater
#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_LONGHORN) // Windows 7 or greater

   return FALSE;

#else

   OSVERSIONINFO osversioninfo;

   osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

   if (!GetVersionEx(&osversioninfo))
      return 0;

   return
      osversioninfo.dwPlatformId == VER_PLATFORM_WIN32s
      || (osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS && ((osversioninfo.dwMajorVersion == 4 && osversioninfo.dwMinorVersion <= 10) || osversioninfo.dwMajorVersion < 4));

#endif

}

int_bool is_windows_nt()
{

#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater

   return IsWindowsXPOrGreater();

#else

   return !(GetVersion() & 0x80000000);

#endif

}


int_bool is_windows_vista_or_greater()
{

#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater

   return IsWindowsVistaOrGreater();

#else

   OSVERSIONINFO osversioninfo;

   osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

   if (!GetVersionEx(&osversioninfo))
      return 0;

   return osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_NT && osversioninfo.dwMajorVersion >= 6;

#endif

}


int_bool is_windows_xp_or_greater()
{

#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater

   return IsWindowsXPOrGreater();

#else

   OSVERSIONINFO osversioninfo;

   osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

   if (!GetVersionEx(&osversioninfo))
      return 0;

   return osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_NT && (osversioninfo.dwMajorVersion > 5 || (osversioninfo.dwMajorVersion == 5 && osversioninfo.dwMinorVersion >= 1);

#endif

}


int_bool is_windows_2000_or_greater()
{

#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater

   return IsWindowsXPOrGreater();

#else

   OSVERSIONINFO osversioninfo;

   osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

   if (!GetVersionEx(&osversioninfo))
      return 0;

   return osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_NT && osversioninfo.dwMajorVersion >= 5;

#endif

}


int_bool is_windows_nt_lesser_than_2000()
{

#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater

   return FALSE;

#else

   OSVERSIONINFO osversioninfo;
   
   osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

   if (!GetVersionEx(&osversioninfo))
      return 0;

   return osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_NT && osversioninfo.dwMajorVersion < 5;

#endif

}

int_bool is_windows_native_unicode()
{

#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater

   return TRUE;

#else

   static int_bool s_bNativeUnicode = -1;

   if (bNativeUnicode == -1)
   {

      DWORD dwVersion = GetVersion();

      // get the Windows version.

      DWORD dwWindowsMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
      DWORD dwWindowsMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));

      // get the build number.

      DWORD dwBuild;

      if (dwVersion < 0x80000000)              // Windows NT
         dwBuild = (DWORD)(HIWORD(dwVersion));
      else if (dwWindowsMajorVersion < 4)      // Win32s
         dwBuild = (DWORD)(HIWORD(dwVersion) & ~0x8000);
      else                                     // Windows Me/98/95
         dwBuild = 0;

      if (dwVersion < 0x80000000)              // Windows NT
         s_bNativeUnicode = TRUE;
      else if (dwWindowsMajorVersion < 4)      // Win32s
         s_bNativeUnicode = FALSE;
      else                                     // Windows Me/98/95
         s_bNativeUnicode = FALSE;

   }

   return bNativeUnicode;

#endif

}

///////////////////////////////////////////////////



//
//_PNH CLASS_DECL_BASE __set_new_handler(_PNH pfnNewHandler)
//{
//   __MODULE_THREAD_STATE* pState = __get_module_thread_state();
//   _PNH pfnOldHandler = pState->m_pfnNewHandler;
//   pState->m_pfnNewHandler = pfnNewHandler;
//   return pfnOldHandler;
//}



/////////////////////////////////////////////////////////////////////////////
// stop on a specific primitive::memory request

// Obsolete API
/*
void CLASS_DECL_BASE __set_alloc_stop(LONG lRequestNumber)
{
_CrtSetBreakAlloc(lRequestNumber);
}
*/

/*
// -- true if block of exact size, allocated on the heap
// -- set *plRequestNumber to request number (or 0)
bool CLASS_DECL_BASE __is_memory_block(const void * pData, UINT nBytes,
LONG* plRequestNumber)
{
return _CrtIsMemoryBlock(pData, nBytes, plRequestNumber, NULL, NULL);
}

*/
END_EXTERN_C

#ifdef DEBUG

CLASS_DECL_BASE bool  __check_memory()
{

   return _CrtCheckMemory() != FALSE;

}

#endif





// Note: in separate module so it can be replaced if needed

void CLASS_DECL_BASE __abort()
{
   //   TRACE(::core::trace::category_AppMsg, 0, "__abort called.\n");

   __win_term();
   abort();
}



/////////////////////////////////////////////////////////////////////////////
// export WinMain to force linkage to this module
extern int32_t CLASS_DECL_BASE __win_main(HINSTANCE hInstance,HINSTANCE hPrevInstance,
__in LPTSTR lpCmdLine,int32_t nCmdShow);


/////////////////////////////////////////////////////////////////////////////
// initialize cast state such that it points to this module's core state

CLASS_DECL_BASE bool __initialize(bool bDLL,DWORD dwVersion)
{
   //   __MODULE_STATE* pModuleState = __get_module_state();
   //   pModuleState->m_bDLL = (BYTE)bDLL;
   ASSERT(dwVersion <= _MFC_VER);
   UNUSED(dwVersion);  // not used in release build
   //   pModuleState->m_dwVersion = dwVersion;
#ifdef _MBCS
   // set correct multi-byte code-page for Win32 apps
   //   if (!bDLL)
   //    _setmbcp(_MB_CP_ANSI);
#endif //_MBCS
   return TRUE;
}

// force initialization early
//#pragma warning(disable: 4074)
//#pragma init_seg(lib)


char gen_InitAppState = (char)(__initialize(FALSE,_MFC_VER));





extern CLASS_DECL_BASE oswindow_map * g_pwindowmap;


/////////////////////////////////////////////////////////////////////////////
// other globals (internal library use)

/////////////////////////////////////////////////////////////////////////////
// Standard cleanup called by WinMain and __abort

//void CLASS_DECL_BASE __gen_unregister_window_classes(sp(::base::application) papp)
//{
//   
//   // unregister Window classes
//   __MODULE_STATE* pModuleState = __get_module_state();
//
//   single_lock sl(&pModuleState->m_mutexRegClassList, TRUE);
//
//   if(pModuleState->m_pstrUnregisterList != NULL) 
//   {
//      strsize start = 0;
//      string className = pModuleState->m_pstrUnregisterList->Tokenize("\n",start);
//      while (!className.is_empty())
//      {
////         UnregisterClass(static_cast<const char *>(className), System.m_hInstance);
//         className = pModuleState->m_pstrUnregisterList->Tokenize("\n",start);
//      }
//      pModuleState->m_pstrUnregisterList->Empty();
//      pModuleState->m_pstrUnregisterList = NULL;
//   }
//
//}

extern __declspec(thread) HHOOK t_hHookOldMsgFilter;
extern __declspec(thread) HHOOK t_hHookOldCbtFilter;


CLASS_DECL_BASE int_bool __win_init()
{

   ::CoInitializeEx(NULL,COINIT_MULTITHREADED);

   if(!os_initialize())
      return FALSE;

   if(!main_initialize())
      return FALSE;

   //Sleep(15 * 1000);

   _set_purecall_handler(_ca2_purecall);

   return TRUE;

}


CLASS_DECL_BASE void __win_term()
{

   __wait_threading_count(::millis((1984 + 1977) * 8));

   delete g_pwindowmap;

   g_pwindowmap = NULL;

   main_finalize();

   os_finalize();

   //if (__get_thread_state() != NULL)
   //{
   //   __get_thread_state()->finalize();
   //   gen_ThreadState = NULL;
   //}


   //__gen_unregister_window_classes();
   // cleanup OLE if required
   //   thread* pThread = &System;

   // cleanup thread local tooltip window
   //   __MODULE_THREAD_STATE* pModuleThreadState = __get_module_thread_state();
   /*   if (pModuleThreadState->m_pToolTip != NULL)
   {
   if (pModuleThreadState->m_pToolTip->DestroyToolTipCtrl())
   pModuleThreadState->m_pToolTip = NULL;
   }*/

   //   ___THREAD_STATE* pThreadState = __get_thread_state();
   // if (!afxContextIsDLL)
   //{
   // unhook windows hooks
   if(t_hHookOldMsgFilter != NULL)
   {
      ::UnhookWindowsHookEx(t_hHookOldMsgFilter);
      t_hHookOldMsgFilter = NULL;
   }
   if(t_hHookOldCbtFilter != NULL)
   {
      ::UnhookWindowsHookEx(t_hHookOldCbtFilter);
      t_hHookOldCbtFilter = NULL;
   }
   //}
   // We used to suppress all exceptions here. But that's the wrong thing
   // to do. If this process crashes, we should allow Windows to crash
   // the process and invoke watson.


   //try
   //{
   //   delete __get_module_state()->m_pmapHWND;
   //}
   //catch (...)
   //{
   //}
   /*   try
   {
   delete __get_module_state()->m_pmapHDC;
   }
   catch(...)
   {
   }*/
   /*   try
   {
   delete __get_module_state()->m_pmapHGDIOBJ;
   }
   catch(...)
   {
   }*/
   //      delete __get_module_state()->m_pmapHMENU;

   //try
   //{
   //   __get_module_state()->m_pmapHWND = NULL;
   //}
   //catch (...)
   //{
   //}
   /*   try
   {
   __get_module_state()->m_pmapHDC      = NULL;
   }
   catch(...)
   {
   }*/
   /*   try
   {
   __get_module_state()->m_pmapHGDIOBJ  = NULL;
   }
   catch(...)
   {
   }*/


}

/////////////////////////////////////////////////////////////////////////////


#include "framework.h"


/////////////////////////////////////////////////////////////////////////////
// ___DEBUG_STATE implementation

#ifndef ___NO_DEBUG_CRT
static _CRT_DUMP_CLIENT pfnOldCrtDumpClient = NULL;

#ifdef DEBUG


void __cdecl __crt_dump_client(void * pvData,size_t nBytes)
{
   char sz[1024];
   try
   {

      if(_CrtReportBlockType(pvData) != ___CLIENT_BLOCK)
         return;

      //      object * pca = (object * ) pvData;

      object * pobject = NULL;

      /*for(int32_t i = 0; i < 256; i++)
      {
      try
      {
      pobject = dynamic_cast < object * > ((object *)&((int_ptr *)pca)[i]);
      }
      catch(std::__non_rtti_object & e)
      {
      pobject = NULL;
      }
      catch(...)
      {
      pobject = NULL;
      }
      if(pobject != NULL)
      break;
      }*/

      if(pobject == NULL)
      {
         C_RUNTIME_ERRORCHECK_SPRINTF(_snprintf_s(sz,_countof(sz),_countof(sz) - 1,"unknown object at $%p, %u bytes long\n",pvData,nBytes));
      }
      else if(g_dumpcontext.GetDepth() > 0)
      {
         // long form
         pobject->dump(g_dumpcontext);
         g_dumpcontext << "\n";
      }
      if(false) // else
      {
         object & obj = *pobject;
         // int16_t form
         C_RUNTIME_ERRORCHECK_SPRINTF(_snprintf_s(sz,_countof(sz),_countof(sz) - 1,"a %hs object at $%p, %u bytes long\n",typeid(obj).name(),pvData,nBytes));
         g_dumpcontext << sz;
      }
   }
   catch(std::__non_rtti_object & e)
   {
      g_dumpcontext << "_gen::CrtdumpClient __non_rtti_object ";
      g_dumpcontext << e.what();
   }
   catch(...)
   {
      // int16_t form for trashed objects
      sprintf_s(sz,_countof(sz),"faulted while dumping object at $%p, %u bytes long\n",pvData,nBytes);
      g_dumpcontext << sz;
   }
   if(pfnOldCrtDumpClient != NULL)
      (*pfnOldCrtDumpClient)(pvData,nBytes);
}

int32_t __cdecl __crt_report_hook(int32_t nRptType,__in char *szMsg,int32_t* pResult)
{
   // no hook on asserts or when m_pFile is NULL
   if(nRptType == _CRT_ASSERT || g_dumpcontext.m_pfile == NULL)
      return FALSE;

   ASSERT(pResult != NULL);
   if(pResult == NULL)
      throw invalid_argument_exception(get_thread_app());

   ASSERT(szMsg != NULL);
   if(szMsg == NULL)
      throw invalid_argument_exception(get_thread_app());

   // non-NULL m_pFile, so go through g_dumpcontext for the message
   *pResult = FALSE;
   g_dumpcontext << szMsg;
   //Allow other report hooks to be called.
   return FALSE;
}

#endif
#endif // ___NO_DEBUG_CRT


#ifdef DEBUG

___DEBUG_STATE::___DEBUG_STATE()
{
#ifndef ___NO_DEBUG_CRT
   ASSERT(pfnOldCrtDumpClient == NULL);
   pfnOldCrtDumpClient = _CrtSetDumpClient(__crt_dump_client);

   ASSERT(_CrtSetReportHook2(_CRT_RPTHOOK_INSTALL,__crt_report_hook) != -1);
   _CrtSetReportMode(_CRT_ASSERT,_CRTDBG_MODE_WNDW);
#endif // ___NO_DEBUG_CRT
}

___DEBUG_STATE::~___DEBUG_STATE()
{
#ifndef ___NO_DEBUG_CRT
   if(::IsDebuggerPresent() && false)
   {
      try
      {
         _CrtDumpMemoryLeaks();
      }
      catch(std::__non_rtti_object & e)
      {
         ::OutputDebugString("~___DEBUG_STATE _CrtdumpMemoryLeaks std::__non_rtti_object\n");
         ::OutputDebugString(e.what());
         ::OutputDebugString("\n");
      }
      catch(...)
      {
         ::OutputDebugString("~___DEBUG_STATE _CrtdumpMemoryLeaks exception\n");
      }
   }
   int32_t nOldState = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
   _CrtSetDbgFlag(nOldState & ~_CRTDBG_LEAK_CHECK_DF);

   ASSERT(_CrtSetReportHook2(_CRT_RPTHOOK_REMOVE,__crt_report_hook) != -1);
   _CrtSetDumpClient(pfnOldCrtDumpClient);
#endif // ___NO_DEBUG_CRT
}

CLASS_DECL_BASE ___DEBUG_STATE afxDebugState;

bool CLASS_DECL_BASE __diagnostic_init()
{
   // just get the debug state to cause initialization
   ___DEBUG_STATE* pState = &afxDebugState;
   ASSERT(pState != NULL);

   return TRUE;
}

#endif




//__DATADEF bool g_bTraceEnabled = TRUE;
//__DATADEF UINT g_uiTraceFlags = 0;
static bool gen_DiagnosticInit = __diagnostic_init();



#include "framework.h"

/////////////////////////////////////////////////////////////////////////////
// __EXCEPTION_CONTEXT (thread global state)

//inline __EXCEPTION_CONTEXT* __get_exception_context()
//{
//   DWORD lError = GetLastError();
//   __EXCEPTION_CONTEXT* pContext = &gen_ThreadState->m_exceptionContext;
//   SetLastError(lError);
//   return pContext;
//}

/////////////////////////////////////////////////////////////////////////////
// __exception_link linked 'jmpbuf' and out-of-line helpers

//__exception_link::__exception_link()
//{
//   // setup initial link state
//   m_pException = NULL;    // no current exception yet
//
//   // wire into top of exception link stack
//   __EXCEPTION_CONTEXT* pContext = __get_exception_context();
//   m_pLinkPrev = pContext->m_pLinkTop;
//   pContext->m_pLinkTop = this;
//}


// out-of-line cleanup called from inline __exception_link destructor
CLASS_DECL_BASE void __try_cleanup()
{
   //__EXCEPTION_CONTEXT* pContext = __get_exception_context();
   //__exception_link* pLinkTop = pContext->m_pLinkTop;

   // delete current exception
   //ASSERT(pLinkTop != NULL);
   //if (pLinkTop == NULL)
   //   return;
   //if (pLinkTop->m_pException != NULL)
   //   pLinkTop->m_pException->Delete();

   //// remove ourself from the top of the chain
   //pContext->m_pLinkTop = pLinkTop->m_pLinkPrev;
}

// special out-of-line implementation of THROW_LAST (for auto-delete behavior)
void CLASS_DECL_BASE __throw_last_cleanup()
{
   //__EXCEPTION_CONTEXT* pContext = __get_exception_context();
   //__exception_link* pLinkTop = pContext->m_pLinkTop;

   //// check for THROW_LAST inside of auto-delete block
   //if (pLinkTop != NULL)
   //{
   //   // make sure current exception does not get auto-deleted
   //   pLinkTop->m_pException = NULL;
   //}

   //// THROW_LAST macro will do actual 'throw'
}






namespace core
{

#if defined( _CUSTOM_THROW )  // You can define your own throw hresult_exception to throw a custom exception.

   CLASS_DECL_BASE void WINAPI atl_throw_impl(HRESULT hr)
   {
      TRACE(atlTraceException,0,"throw hresult_exception: hr = 0x%x\n",hr);
#ifdef _AFX
      if(hr == E_OUTOFMEMORY)
      {
         throw memory_exception();
      }
      else
      {
         //      ::core::ThrowOleException( hr );
      }
#else
      throw atl_exception(hr);
#endif
   };

#endif


   // Throw a atl_exception with th given HRESULT
#if !defined( _CUSTOM_THROW )  // You can define your own throw hresult_exception

   //CLASS_DECL_BASE void WINAPI atl_throw_impl(HRESULT hr)
   //{
   //   TRACE("throw hresult_exception: hr = 0x%x\n", hr);
   //  throw hresult_exception(hr);
   /*   ::OutputDebugString("throw hresult_exception");
   char sz[200];
   sprintf(sz, "0x%s", hr);
   ::OutputDebugString(sz);
   ::OutputDebugString("\n");
   //TRACE(trace::category_Exception, 0, "throw hresult_exception: hr = 0x%x\n", hr );
   ASSERT( false );
   DWORD dwExceptionCode;
   switch(hr)
   {
   case E_OUTOFMEMORY:
   dwExceptionCode = STATUS_NO_MEMORY;
   break;
   default:
   dwExceptionCode = EXCEPTION_ILLEGAL_INSTRUCTION;
   }
   atl_raise_exception((DWORD)dwExceptionCode);*/
   //}
#endif


} // namespace core
