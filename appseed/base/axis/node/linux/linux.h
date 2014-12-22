#pragma once


#include "aura/node/linux/linux.h"

/////////////////////////////////////////////////////////////////////////////
// Global implementation helpers

// window creation hooking
CLASS_DECL_AXIS void AfxHookWindowCreate(sp(::user::interaction) pWnd);
CLASS_DECL_AXIS WINBOOL AfxUnhookWindowCreate();
CLASS_DECL_AXIS void AfxResetMsgcache();

// for backward compatibility to previous versions
#define _AfxHookWindowCreate    AfxHookWindowCreate
#define _AfxUnhookWindowCreate  AfxUnhookWindowCreate

#pragma once




// from wincore.cpp
extern CLASS_DECL_AXIS const char _afxWnd[];           // simple child windows/controls
extern CLASS_DECL_AXIS const char _afxWndControlBar[]; // controls with gray backgrounds
extern CLASS_DECL_AXIS const char _afxWndMDIFrame[];
extern CLASS_DECL_AXIS const char _afxWndFrameOrView[];
extern CLASS_DECL_AXIS const char _afxWndOleControl[];


/////////////////////////////////////////////////////////////////////////////
// Special helpers

CLASS_DECL_AXIS void AfxcancelModes(oswindow hWndRcvr);
CLASS_DECL_AXIS WINBOOL AfxHelpEnabled();  // determine if ID_HELP handler exists
CLASS_DECL_AXIS WINBOOL AfxCustomLogFont(UINT nIDS, LOGFONT* pLogFont);
CLASS_DECL_AXIS WINBOOL AfxGetPropSheetFont(string & strFace, WORD& wSize, WINBOOL bWizard);

CLASS_DECL_AXIS WINBOOL _AfxIsComboBoxControl(oswindow hWnd, UINT nStyle);
CLASS_DECL_AXIS WINBOOL _AfxCheckCenterDialog(const char * lpszResource);
CLASS_DECL_AXIS WINBOOL _AfxCompareClassName(oswindow hWnd, const char * lpszClassName);
CLASS_DECL_AXIS oswindow _AfxChildWindowFromPoint(oswindow, POINT);

// for determining version of COMCTL32.DLL
#define VERSION_WIN4    MAKELONG(0, 4)
#define VERSION_IE3             MAKELONG(70, 4)
#define VERSION_IE4             MAKELONG(71, 4)
#define VERSION_IE401   MAKELONG(72, 4)
#define VERSION_6      MAKELONG(0, 6)
extern int32_t _afxComCtlVersion;
DWORD _AfxGetComCtlVersion();
#include "linux_factory_exchange.h"
#include "linux_window_draw.h"
#include "linux_interaction_impl.h"
#include "linux_copydesk.h"
#include "linux_message_queue.h"

#define AfxWndProc (*AfxGetAfxWndProc())

#define LNX_WINDOW(pwnd) (dynamic_cast < ::linux::interaction_impl * > (((sp(::user::interaction_impl))(pwnd)).m_p))
#define LNX_DC(pgraphics) (dynamic_cast < ::linux::graphics * > (dynamic_cast < ::draw2d::graphics * > (pgraphics)))
#define SP_DC(pgraphics) (dynamic_cast < ::linux::graphics * > (( ::draw2d::graphics * )(pgraphics)))
#define LNX_HDC(pgraphics) ((HDC)*(dynamic_cast < ::linux::graphics * > (dynamic_cast < ::draw2d::graphics * > (pgraphics))))
#define SP_HDC(pgraphics) ((HDC)*(dynamic_cast < ::linux::graphics * > ((::draw2d::graphics *)(pgraphics))))
#define LNX_DIB(pdib) (dynamic_cast < ::linux::dib * > (dynamic_cast < ::draw2d::dib * >(pdib)))


CLASS_DECL_AXIS void AfxProcessWndProcException(::exception::base*, ::signal_details * pobj);
CLASS_DECL_AXIS void __cdecl __pre_translate_message(::signal_details * pobj);


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
