#pragma once


string get_error_message(DWORD dwError);

::aura::application *     win_instantiate_application(::aura::application * pappSystem, const char * pszId);

/////////////////////////////////////////////////////////////////////////////
// explicit initialization for general purpose classes

//CLASS_DECL_AXIS BOOL AfxInitialize(BOOL bDLL = FALSE, DWORD dwVersion = _MFC_VER);
CLASS_DECL_AXIS BOOL AfxInitialize(BOOL bDLL = FALSE, DWORD dwVersion = 0);

/////////////////////////////////////////////////////////////////////////////
// stop on a specific primitive::memory request

// Debugger hook on specified allocation request - Obsolete
CLASS_DECL_AXIS void AfxSetAllocStop(LONG lRequestNumber);

// Return TRUE if primitive::memory is sane or print out what is wrong
CLASS_DECL_AXIS BOOL AfxCheckMemory();

// Return TRUE if valid primitive::memory block of nBytes
CLASS_DECL_AXIS BOOL AfxIsMemoryBlock(const void * p, UINT nBytes,
   LONG* plRequestNumber = NULL);

CLASS_DECL_AXIS void AfxResetMsgCache();


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
#include "android_crypto.h"
#include "android_ip_enum.h"

#define NULL_REF(class) (*((class *) NULL))
// xxx CLASS_DECL_AXIS WNDPROC AfxGetAfxWndProc();
#define AfxWndProc (*AfxGetAfxWndProc())

#define ANDROID_THREAD(pthread) (dynamic_cast < ::android::thread * > (dynamic_cast < ::thread * >(pthread)))
#define ANDROID_WINDOW(pwnd) (dynamic_cast < ::android::interaction_impl * > (((sp(::user::interaction))(pwnd)).m_p))
#define ANDROID_DC(pgraphics) (dynamic_cast < ::android::graphics * > (dynamic_cast < ::draw2d::graphics * > (pgraphics)))
#define SP_DC(pgraphics) (dynamic_cast < ::android::graphics * > (( ::draw2d::graphics * )(pgraphics)))
#define ANDROID_HDC(pgraphics) ((HDC)*(dynamic_cast < ::android::graphics * > (dynamic_cast < ::draw2d::graphics * > (pgraphics))))
#define SP_HDC(pgraphics) ((HDC)*(dynamic_cast < ::android::graphics * > ((::draw2d::graphics *)(pgraphics))))
#define ANDROID_DIB(pdib) (dynamic_cast < ::android::dib * > (dynamic_cast < ::draw2d::dib * >(pdib)))

#include "android_shell.h"

CLASS_DECL_AXIS void __trace_message(const char * lpszPrefix, ::signal_details * pobj);
CLASS_DECL_AXIS void __trace_message(const char * lpszPrefix, LPMESSAGE lpmsg);

CLASS_DECL_AXIS void __cdecl __pre_translate_message(::signal_details * pobj);


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



int32_t CLASS_DECL_AXIS __android_main(int32_t argc, char * argv[]);


CLASS_DECL_AXIS void vfxThrowFileException(sp(::aura::application) papp, int32_t cause, LONG lOsError, const char * lpszFileName = NULL);


#include "android_internal.h"




