#pragma once


#define SECURITY_WIN32


#define CLASS_DECL_LINUX


string get_error_message(DWORD dwError);

sp(::base::application)     linux_instantiate_application(sp(::base::application) pappSystem, const char * pszId);

/////////////////////////////////////////////////////////////////////////////
// explicit initialization for general purpose classes

//CLASS_DECL_LINUX WINBOOL AfxInitialize(WINBOOL bDLL = FALSE, DWORD dwVersion = _MFC_VER);
CLASS_DECL_LINUX WINBOOL AfxInitialize(WINBOOL bDLL = FALSE, DWORD dwVersion = 0);

/////////////////////////////////////////////////////////////////////////////
// stop on a specific primitive::memory request

// Debugger hook on specified allocation request - Obsolete
CLASS_DECL_LINUX void AfxSetAllocStop(LONG lRequestNumber);

// Return TRUE if primitive::memory is sane or print out what is wrong
CLASS_DECL_LINUX bool __check_memory();

// Return TRUE if valid primitive::memory block of nBytes
CLASS_DECL_LINUX WINBOOL AfxIsMemoryBlock(const void * p, UINT nBytes,
   LONG* plRequestNumber = NULL);

// helper routines for non-C++ EH implementations
// for THROW_LAST auto-delete backward compatiblity
CLASS_DECL_LINUX void AfxThrowLastCleanup();

// other out-of-line helper functions
CLASS_DECL_LINUX void AfxTryCleanup();


/////////////////////////////////////////////////////////////////////////////
// Global implementation helpers

// window creation hooking
CLASS_DECL_LINUX void AfxHookWindowCreate(sp(::user::interaction) pWnd);
CLASS_DECL_LINUX WINBOOL AfxUnhookWindowCreate();
CLASS_DECL_LINUX void AfxResetMsgcache();

// for backward compatibility to previous versions
#define _AfxHookWindowCreate    AfxHookWindowCreate
#define _AfxUnhookWindowCreate  AfxUnhookWindowCreate

#include "linux1.h"
#include "implementation.h"
//#include "linux_state.h"
// xxx #include "handle.h"
// xxx #include "linux_file_find.h"
#include "linux_dir.h"
// xxx #include "linux_folder_watch.h"
#include "linux_factory_exchange.h"
#include "linux_window_draw.h"
#include "linux_thread.h"
#include "linux_window.h"
#include "linux_os.h"
#include "linux_port_forward.h"
#include "linux_copydesk.h"
#include "linux_crypt.h"
#include "linux_ip_enum.h"

#define NULL_REF(class) (*((class *) NULL))
// xxx CLASS_DECL_LINUX WNDPROC AfxGetAfxWndProc();
#define AfxWndProc (*AfxGetAfxWndProc())

#define linux_THREAD(pthread) (dynamic_cast < ::linux::thread * > (dynamic_cast < ::thread * >(pthread)))
#define linux_WINDOW(pwnd) (dynamic_cast < ::linux::window * > (((sp(::window))(pwnd)).m_p))
#define linux_DC(pgraphics) (dynamic_cast < ::linux::graphics * > (dynamic_cast < ::draw2d::graphics * > (pgraphics)))
#define SP_DC(pgraphics) (dynamic_cast < ::linux::graphics * > (( ::draw2d::graphics * )(pgraphics)))
#define linux_HDC(pgraphics) ((HDC)*(dynamic_cast < ::linux::graphics * > (dynamic_cast < ::draw2d::graphics * > (pgraphics))))
#define SP_HDC(pgraphics) ((HDC)*(dynamic_cast < ::linux::graphics * > ((::draw2d::graphics *)(pgraphics))))
#define linux_DIB(pdib) (dynamic_cast < ::linux::dib * > (dynamic_cast < ::draw2d::dib * >(pdib)))

#include "linux_shell.h"

CLASS_DECL_LINUX void __trace_message(const char * lpszPrefix, ::signal_details * pobj);
CLASS_DECL_LINUX void __trace_message(const char * lpszPrefix, LPMESSAGE lpmsg);

CLASS_DECL_LINUX WINBOOL __cdecl __is_idle_message(::signal_details * pobj);
CLASS_DECL_LINUX WINBOOL __cdecl __is_idle_message(MESSAGE* pMsg);


CLASS_DECL_LINUX void AfxProcessWndProcException(::exception::base*, ::signal_details * pobj);
CLASS_DECL_LINUX void __cdecl __pre_translate_message(::signal_details * pobj);


#include "linux_application.h"



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



int32_t CLASS_DECL_LINUX __linux_main(int32_t argc, char * argv[]);


CLASS_DECL_LINUX void vfxThrowFileException(sp(::base::application) papp, int32_t cause, LONG lOsError, const char * lpszFileName = NULL);


#include "linux_internal.h"
