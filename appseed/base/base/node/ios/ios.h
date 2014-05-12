#pragma once


#define SECURITY_WIN32


#include "app/appseed/core/core.h"


#define CLASS_DECL_ios

struct plane_system
{
   
   ::plane::system *    m_psystem;
   
   plane_system(const char * pszId);
   
   UIWindow * init_part_2ex(CGRect rect);
   
   void begin();
   
};



string get_error_message(DWORD dwError);

::base::application *     ios_instantiate_application(::base::application * pappSystem, const char * pszId);

/////////////////////////////////////////////////////////////////////////////
// explicit initialization for general purpose classes

//CLASS_DECL_ios WINBOOL AfxInitialize(WINBOOL bDLL = FALSE, DWORD dwVersion = _MFC_VER);
CLASS_DECL_ios WINBOOL AfxInitialize(WINBOOL bDLL = FALSE, DWORD dwVersion = 0);

/////////////////////////////////////////////////////////////////////////////
// stop on a specific primitive::memory request

// Debugger hook on specified allocation request - Obsolete
CLASS_DECL_ios void AfxSetAllocStop(LONG lRequestNumber);

// Return TRUE if primitive::memory is sane or print out what is wrong
CLASS_DECL_ios bool __check_memory();

// Return TRUE if valid primitive::memory block of nBytes
CLASS_DECL_ios WINBOOL AfxIsMemoryBlock(const void * p, UINT nBytes,
                                        LONG* plRequestNumber = NULL);

// helper routines for non-C++ EH implementations
// for THROW_LAST auto-delete backward compatiblity
CLASS_DECL_ios void AfxThrowLastCleanup();

// other out-of-line helper functions
CLASS_DECL_ios void AfxTryCleanup();


/////////////////////////////////////////////////////////////////////////////
// Global implementation helpers

// window creation hooking
CLASS_DECL_ios void AfxHookWindowCreate(::user::interaction * pWnd);
CLASS_DECL_ios WINBOOL AfxUnhookWindowCreate();
CLASS_DECL_ios void AfxResetMsgCache();

// for backward compatibility to previous versions
#define _AfxHookWindowCreate    AfxHookWindowCreate
#define _AfxUnhookWindowCreate  AfxUnhookWindowCreate

//#include "ios1.h"
#include "ios_implementation.h"
#include "ios_state.h"
//#include "ios_handle.h"
// xxx #include "ios_file_find.h"
#include "ios_dir.h"
// xxx #include "ios_folder_watch.h"
#include "ios_factory_exchange.h"
#include "ios_window_draw.h"
#include "ios_thread.h"
#include "ios_window.h"
#include "ios_os.h"
#include "ios_port_forward.h"
#include "ios_copydesk.h"
#include "ios_crypto.h"
#include "ios_ip_enum.h"

#define NULL_REF(class) (*((class *) NULL))
// xxx CLASS_DECL_ios WNDPROC AfxGetAfxWndProc();
#define AfxWndProc (*AfxGetAfxWndProc())

#define IOS_THREAD(pthread) (dynamic_cast < ::ios::thread * > (dynamic_cast < ::thread * >(pthread)))
#define IOS_WINDOW(pwnd) (dynamic_cast < ::ios::window * > (dynamic_cast < ::window * >(pwnd)))

#include "ios_shell.h"

CLASS_DECL_ios void __trace_message(const char * lpszPrefix, signal_details * pobj);
CLASS_DECL_ios void __trace_message(const char * lpszPrefix, LPMESSAGE lpmsg);

CLASS_DECL_ios WINBOOL __cdecl __is_idle_message(signal_details * pobj);
CLASS_DECL_ios WINBOOL __cdecl __is_idle_message(MESSAGE* pMsg);


CLASS_DECL_ios void AfxProcessWndProcException(::exception::base*, signal_details * pobj);
CLASS_DECL_ios void __cdecl __pre_translate_message(signal_details * pobj);
#include "ios_printer.h"

#include "ios_application.h"



WINBOOL PeekMessage(
                    LPMESSAGE lpMsg,
                    oswindow hWnd,
                    UINT wMsgFilterMin,
                    UINT wMsgFilterMax,
                    UINT wRemoveMsg);

WINBOOL GetMessage(
                   LPMESSAGE lpMsg,
                   oswindow hWnd,
                   UINT wMsgFilterMin,
                   UINT wMsgFilterMax);



int32_t CLASS_DECL_ios __ios_main(int32_t argc, char * argv[]);


CLASS_DECL_ios void vfxThrowFileException(::base::application * papp, int32_t cause, LONG lOsError, const char * lpszFileName = NULL);



#pragma once


namespace ios
{


   class thread;

   class IOS
   {
      int32_t function();
   };



} // namespace ios



// Placed on frame for EXCEPTION linkage, or ::exception::base cleanup
struct CLASS_DECL_ios __exception_link
{
   __exception_link* m_pLinkPrev;    // previous top, next in handler chain
   ::exception::base * m_pException;   // current exception (NULL in try block)

   __exception_link();       // for initialization and linking
   ~__exception_link()       // for cleanup and unlinking
   {
      //__try_cleanup();
   };
};

// Exception global state - never access directly
struct CLASS_DECL_ios __EXCEPTION_CONTEXT
{
   __exception_link* m_pLinkTop;

   // Note: most of the exception context is now in the __exception_link
};

#ifndef _PNH_DEFINED
typedef int32_t(__cdecl * _PNH)(size_t);
#define _PNH_DEFINED
#endif

_PNH CLASS_DECL_ios __get_new_handler();
_PNH CLASS_DECL_ios __set_new_handler(_PNH pfnNewHandler);
CLASS_DECL_ios int32_t c_cdecl __new_handler(size_t nSize);

void CLASS_DECL_ios __abort();

//typedef void * HICON;


// helpers for registering your own WNDCLASSes
CLASS_DECL_ios const char * __register_window_class(UINT nClassStyle,HCURSOR hCursor = 0,HBRUSH hbrBackground = 0,HICON hIcon = 0);

// xxx CLASS_DECL_ios bool __register_class(WNDCLASS* lpWndClass);


CLASS_DECL_ios LRESULT CALLBACK __window_procedure(oswindow hWnd,UINT nMsg,WPARAM wParam,LPARAM lParam);
// xxx CLASS_DECL_ios WNDPROC __get_window_procedure();
// xxx #define __window_procedure (*__get_window_procedure())

typedef void (__MSG_CALL ::window::*__PMSGW)();
// like '__PMSG' but for ::window derived classes only

typedef void (__MSG_CALL ::thread::*__PMSGT)();
// like '__PMSG' but for thread-derived classes only




// xxx CLASS_DECL_ios LONG delete_registry_tree_helper(HKEY hParentKey, const string & strKeyName);


// Advanced initialization: for overriding default diagnostics
//CLASS_DECL_ios bool __diagnostic_init();

namespace ios
{
   CLASS_DECL_ios ::thread * __get_thread();
   CLASS_DECL_ios void __set_thread(::thread * pthread);
}
CLASS_DECL_ios MESSAGE * __get_current_message();

CLASS_DECL_ios void __end_thread(::base::application * papp,UINT nExitCode,bool bDelete = TRUE);

CLASS_DECL_ios void __init_thread();
CLASS_DECL_ios void __term_thread(::base::application * papp,HINSTANCE hInstTerm = NULL);

/////////////////////////////////////////////////////////////////////////////
// Global functions for access to the one and only application

#define afxCurrentWinApp    __get_module_state()->m_pCurrentWinApp
#define afxCurrentInstanceHandle    __get_module_state()->m_hCurrentInstanceHandle
#define afxCurrentResourceHandle    __get_module_state()->m_hCurrentResourceHandle
#define afxCurrentAppName   __get_module_state()->m_lpszCurrentAppName
#define afxContextIsDLL     __get_module_state()->m_bDLL
#define afxRegisteredClasses    __get_module_state()->m_fRegisteredClasses
#define afxAmbientActCtx    __get_module_state()->m_bSetAmbientActCtx


// Advanced initialization: for overriding default WinMain
//CLASS_DECL_ios bool ::ca2::WinInit(__in HINSTANCE hInstance, __in HINSTANCE hPrevInstance,
// __in_z LPTSTR lpCmdLine, __in int32_t nCmdShow);
CLASS_DECL_ios void __ios_term();

CLASS_DECL_ios ::base::application * __get_app();
CLASS_DECL_ios sp(::user::interaction) __get_main_window();
//CLASS_DECL_ios HINSTANCE CLASS_DECL_ios System.m_hInstance;
CLASS_DECL_ios HINSTANCE __get_resource_handle();
CLASS_DECL_ios void __set_resource_handle(HINSTANCE hInstResource);
CLASS_DECL_ios const char * __get_app_name();

CLASS_DECL_ios HINSTANCE __get_resource_handle();
CLASS_DECL_ios HINSTANCE __find_string_resource_handle(UINT nID);

CLASS_DECL_ios void __delete_object(HGDIOBJ* pObject);

void CLASS_DECL_ios __global_free(HGLOBAL hGlobal);
