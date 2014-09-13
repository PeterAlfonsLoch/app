#pragma once


#define SECURITY_WIN32



#define CLASS_DECL_BASE


string get_error_message(DWORD dwError);

::aura::application *     mac_instantiate_application(::aura::application * pappSystem, const char * pszId);

/////////////////////////////////////////////////////////////////////////////
// explicit initialization for general purpose classes

//CLASS_DECL_BASE WINBOOL AfxInitialize(WINBOOL bDLL = FALSE, DWORD dwVersion = _MFC_VER);
CLASS_DECL_BASE WINBOOL AfxInitialize(WINBOOL bDLL = FALSE, DWORD dwVersion = 0);

/////////////////////////////////////////////////////////////////////////////
// stop on a specific primitive::memory request

// Debugger hook on specified allocation request - Obsolete
CLASS_DECL_BASE void AfxSetAllocStop(LONG lRequestNumber);

// Return TRUE if primitive::memory is sane or print out what is wrong
CLASS_DECL_BASE bool __check_memory();

// Return TRUE if valid primitive::memory block of nBytes
CLASS_DECL_BASE WINBOOL AfxIsMemoryBlock(const void * p, UINT nBytes,
                                        LONG* plRequestNumber = NULL);

// helper routines for non-C++ EH implementations
// for THROW_LAST auto-delete backward compatiblity
CLASS_DECL_BASE void AfxThrowLastCleanup();

// other out-of-line helper functions
CLASS_DECL_BASE void AfxTryCleanup();


/////////////////////////////////////////////////////////////////////////////
// Global implementation helpers

// window creation hooking
CLASS_DECL_BASE void AfxHookWindowCreate(::user::interaction * pWnd);
CLASS_DECL_BASE WINBOOL AfxUnhookWindowCreate();
CLASS_DECL_BASE void AfxResetMsgCache();

// for backward compatibility to previous versions
#define _AfxHookWindowCreate    AfxHookWindowCreate
#define _AfxUnhookWindowCreate  AfxUnhookWindowCreate

#include "macos_factory_exchange.h"
#include "macos_window_draw.h"
#include "macos_interaction_impl.h"
#include "macos_copydesk.h"



#define NULL_REF(class) (*((class *) NULL))
// xxx CLASS_DECL_BASE WNDPROC AfxGetAfxWndProc();
#define AfxWndProc (*AfxGetAfxWndProc())

#define MAC_THREAD(pthread) (dynamic_cast < ::macos::thread * > (dynamic_cast < ::thread * >(pthread)))
#define MAC_WINDOW(pwnd) (dynamic_cast < ::macos::interaction_impl * > (dynamic_cast < ::user::interaction_impl * >(pwnd)))

CLASS_DECL_BASE void __trace_message(const char * lpszPrefix, signal_details * pobj);
CLASS_DECL_BASE void __trace_message(const char * lpszPrefix, LPMESSAGE lpmsg);

CLASS_DECL_BASE void AfxProcessWndProcException(::exception::base*, signal_details * pobj);
CLASS_DECL_BASE void __cdecl __pre_translate_message(signal_details * pobj);
#include "macos_printer.h"
#include "macos_message_queue.h"



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



int32_t CLASS_DECL_BASE __mac_main(int32_t argc, char * argv[]);


CLASS_DECL_BASE void vfxThrowFileException(::aura::application * papp, int32_t cause, LONG lOsError, const char * lpszFileName = NULL);




