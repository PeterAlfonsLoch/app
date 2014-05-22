#pragma once


string get_error_message(DWORD dwError);

::base::application *     win_instantiate_application(::base::application * pappSystem, const char * pszId);

/////////////////////////////////////////////////////////////////////////////
// explicit initialization for general purpose classes

//CLASS_DECL_BASE BOOL AfxInitialize(BOOL bDLL = FALSE, DWORD dwVersion = _MFC_VER);
CLASS_DECL_BASE BOOL AfxInitialize(BOOL bDLL = FALSE, DWORD dwVersion = 0);

/////////////////////////////////////////////////////////////////////////////
// stop on a specific primitive::memory request

// Debugger hook on specified allocation request - Obsolete
CLASS_DECL_BASE void AfxSetAllocStop(LONG lRequestNumber);

// Return TRUE if primitive::memory is sane or print out what is wrong
CLASS_DECL_BASE BOOL AfxCheckMemory();

// Return TRUE if valid primitive::memory block of nBytes
CLASS_DECL_BASE BOOL AfxIsMemoryBlock(const void * p, UINT nBytes,
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
CLASS_DECL_BASE BOOL AfxUnhookWindowCreate();
CLASS_DECL_BASE void AfxResetMsgCache();

// for backward compatibility to previous versions
#define _AfxHookWindowCreate    AfxHookWindowCreate
#define _AfxUnhookWindowCreate  AfxUnhookWindowCreate

#include "android1.h"
#include "android_implementation.h"
#include "android_dir.h"
#include "android_factory_exchange.h"
#include "android_window_draw.h"
#include "android_thread.h"
#include "android_window.h"
#include "android_os.h"
#include "android_port_forward.h"
#include "android_copydesk.h"
#include "android_crypt.h"
#include "android_ip_enum.h"

#define NULL_REF(class) (*((class *) NULL))
// xxx CLASS_DECL_BASE WNDPROC AfxGetAfxWndProc();
#define AfxWndProc (*AfxGetAfxWndProc())

#define ANDROID_THREAD(pthread) (dynamic_cast < ::android::thread * > (dynamic_cast < ::ca2::thread * >(pthread)))
#define ANDROID_WINDOW(pwnd) (dynamic_cast < ::android::window * > (((sp(::window))(pwnd)).m_p))
#define ANDROID_DC(pgraphics) (dynamic_cast < ::android::graphics * > (dynamic_cast < ::draw2d::graphics * > (pgraphics)))
#define SP_DC(pgraphics) (dynamic_cast < ::android::graphics * > (( ::draw2d::graphics * )(pgraphics)))
#define ANDROID_HDC(pgraphics) ((HDC)*(dynamic_cast < ::android::graphics * > (dynamic_cast < ::draw2d::graphics * > (pgraphics))))
#define SP_HDC(pgraphics) ((HDC)*(dynamic_cast < ::android::graphics * > ((::draw2d::graphics *)(pgraphics))))
#define ANDROID_DIB(pdib) (dynamic_cast < ::android::dib * > (dynamic_cast < ::draw2d::dib * >(pdib)))

#include "android_shell.h"

CLASS_DECL_BASE void __trace_message(const char * lpszPrefix, ::ca2::signal_object * pobj);
CLASS_DECL_BASE void __trace_message(const char * lpszPrefix, LPMESSAGE lpmsg);

CLASS_DECL_BASE WINBOOL __cdecl __is_idle_message(::ca2::signal_object * pobj);
CLASS_DECL_BASE WINBOOL __cdecl __is_idle_message(MESSAGE* pMsg);


CLASS_DECL_BASE void AfxProcessWndProcException(base_exception*, ::ca2::signal_object * pobj);
CLASS_DECL_BASE void __cdecl __pre_translate_message(::ca2::signal_object * pobj);


#include "android_application.h"



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



int32_t CLASS_DECL_BASE __android_main(int32_t argc, char * argv[]);


CLASS_DECL_BASE void vfxThrowFileException(sp(::base::application) papp, int32_t cause, LONG lOsError, const char * lpszFileName = NULL);
