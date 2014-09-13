#pragma once


#define SECURITY_WIN32



#define CLASS_DECL_mac


string get_error_message(DWORD dwError);

::aura::application *     mac_instantiate_application(::aura::application * pappSystem, const char * pszId);

/////////////////////////////////////////////////////////////////////////////
// explicit initialization for general purpose classes

//CLASS_DECL_mac WINBOOL AfxInitialize(WINBOOL bDLL = FALSE, DWORD dwVersion = _MFC_VER);
CLASS_DECL_mac WINBOOL AfxInitialize(WINBOOL bDLL = FALSE, DWORD dwVersion = 0);

/////////////////////////////////////////////////////////////////////////////
// stop on a specific primitive::memory request

// Debugger hook on specified allocation request - Obsolete
CLASS_DECL_mac void AfxSetAllocStop(LONG lRequestNumber);

// Return TRUE if primitive::memory is sane or print out what is wrong
CLASS_DECL_mac bool __check_memory();

// Return TRUE if valid primitive::memory block of nBytes
CLASS_DECL_mac WINBOOL AfxIsMemoryBlock(const void * p, UINT nBytes,
                                        LONG* plRequestNumber = NULL);

// helper routines for non-C++ EH implementations
// for THROW_LAST auto-delete backward compatiblity
CLASS_DECL_mac void AfxThrowLastCleanup();

// other out-of-line helper functions
CLASS_DECL_mac void AfxTryCleanup();


/////////////////////////////////////////////////////////////////////////////
// Global implementation helpers

// window creation hooking
CLASS_DECL_mac void AfxHookWindowCreate(::user::interaction * pWnd);
CLASS_DECL_mac WINBOOL AfxUnhookWindowCreate();
CLASS_DECL_mac void AfxResetMsgCache();

// for backward compatibility to previous versions
#define _AfxHookWindowCreate    AfxHookWindowCreate
#define _AfxUnhookWindowCreate  AfxUnhookWindowCreate

#include "macos_factory_exchange.h"
#include "macos_window_draw.h"
#include "macos_interaction_impl.h"
#include "macos_copydesk.h"



#define NULL_REF(class) (*((class *) NULL))
// xxx CLASS_DECL_mac WNDPROC AfxGetAfxWndProc();
#define AfxWndProc (*AfxGetAfxWndProc())

#define MAC_THREAD(pthread) (dynamic_cast < ::mac::thread * > (dynamic_cast < ::thread * >(pthread)))
#define MAC_WINDOW(pwnd) (dynamic_cast < ::mac::interaction_impl * > (dynamic_cast < ::user::interaction_impl * >(pwnd)))

CLASS_DECL_mac void __trace_message(const char * lpszPrefix, signal_details * pobj);
CLASS_DECL_mac void __trace_message(const char * lpszPrefix, LPMESSAGE lpmsg);

CLASS_DECL_mac void AfxProcessWndProcException(::exception::aura*, signal_details * pobj);
CLASS_DECL_mac void __cdecl __pre_translate_message(signal_details * pobj);
#include "mac_printer.h"



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



int32_t CLASS_DECL_mac __mac_main(int32_t argc, char * argv[]);


CLASS_DECL_mac void vfxThrowFileException(::aura::application * papp, int32_t cause, LONG lOsError, const char * lpszFileName = NULL);



#include "mac_internal.h"

