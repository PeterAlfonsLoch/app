#pragma once



/////////////////////////////////////////////////////////////////////////////
// Global implementation helpers

// window creation hooking
CLASS_DECL_LINUX void AfxHookWindowCreate(sp(::user::interaction) pWnd);
CLASS_DECL_LINUX WINBOOL AfxUnhookWindowCreate();
CLASS_DECL_LINUX void AfxResetMsgcache();

// for backward compatibility to previous versions
#define _AfxHookWindowCreate    AfxHookWindowCreate
#define _AfxUnhookWindowCreate  AfxUnhookWindowCreate


#include "implementation.h"
#include "linux_factory_exchange.h"
#include "linux_window_draw.h"
#include "linux_interaction_impl.h"
#include "linux_copydesk.h"

#define AfxWndProc (*AfxGetAfxWndProc())

#define LNX_WINDOW(pwnd) (dynamic_cast < ::linux::interaction_impl * > (((sp(::user::interaction_impl))(pwnd)).m_p))
#define LNX_DC(pgraphics) (dynamic_cast < ::linux::graphics * > (dynamic_cast < ::draw2d::graphics * > (pgraphics)))
#define SP_DC(pgraphics) (dynamic_cast < ::linux::graphics * > (( ::draw2d::graphics * )(pgraphics)))
#define LNX_HDC(pgraphics) ((HDC)*(dynamic_cast < ::linux::graphics * > (dynamic_cast < ::draw2d::graphics * > (pgraphics))))
#define SP_HDC(pgraphics) ((HDC)*(dynamic_cast < ::linux::graphics * > ((::draw2d::graphics *)(pgraphics))))
#define LNX_DIB(pdib) (dynamic_cast < ::linux::dib * > (dynamic_cast < ::draw2d::dib * >(pdib)))

#include "linux_shell.h"

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




#include "linux_internal.h"
