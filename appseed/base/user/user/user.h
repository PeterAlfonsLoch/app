#pragma once


#define WM_SIZEPARENT       0x0361  // lParam = &__SIZEPARENTPARAMS

// Note: afxData.cxBorder and afxData.cyBorder aren't used anymore
#define CX_BORDER   1
#define CY_BORDER   1



namespace user
{


   CLASS_DECL_BASE sp(::user::interaction) get_parent_owner(sp(::user::interaction) pui);
   CLASS_DECL_BASE bool is_descendant(sp(::user::interaction) puiParent, sp(::user::interaction) puiChild);


} // namespace user





// Implementation structures
struct __SIZEPARENTPARAMS;    // control bar implementationproperca2_property.h

// Classes declared in this file

//::draw2d::graphics_sp
class preview_dc;               // Virtual DC for print preview

//command_target
//::user::window
//::user::impact
class CPreviewView;     // Print preview ::user::impact
//frame_window
class COleCntrFrameWnd;
//CMiniFrameWnd
class mini_dock_frame_window;

class CDockContext;                     // for dragging control bars

/////////////////////////////////////////////////////////////////////////////
// Global ID ranges (see Technical note TN020 for more details)

// 8000 -> FFFF command IDs (used for menu items, accelerators and controls)
#define IS_COMMAND_ID(nID)  ((nID) & 0x8000)

// 8000 -> DFFF : ::fontopus::user commands
// E000 -> EFFF : _ commands and other things
// F000 -> FFFF : standard windows commands and other things etc
// E000 -> E7FF standard commands
// E800 -> E8FF control bars (first 32 are special)
// E900 -> EEFF standard ::user::window controls/components
// EF00 -> EFFF SC_ menu help
// F000 -> FFFF standard strings
#define ID_COMMAND_FROM_SC(sc)  (((sc - 0xF000) >> 4) + __IDS_SCFIRST)

// 0000 -> 7FFF IDR range
// 0000 -> 6FFF : ::fontopus::user resources
// 7000 -> 7FFF : _ (and standard windows) resources
// IDR ranges (NOTE: IDR_ values must be <32768)
#define ASSERT_VALID_IDR(nIDR) ASSERT((nIDR) != 0 && (nIDR) < 0x8000)

/////////////////////////////////////////////////////////////////////////////
// Context sensitive help support (see Technical note TN028 for more details)

// Help ID bases
#define HID_BASE_COMMAND    0x00010000UL        // ID and IDM
#define HID_BASE_RESOURCE   0x00020000UL        // IDR and IDD
#define HID_BASE_PROMPT     0x00030000UL        // IDP
#define HID_BASE_NCAREAS    0x00040000UL
#define HID_BASE_CONTROL    0x00050000UL        // IDC
#define HID_BASE_DISPATCH   0x00060000UL        // IDispatch help codes

/////////////////////////////////////////////////////////////////////////////
// Internal _ Windows messages (see Technical note TN024 for more details)
// (0x0360 - 0x037F are reserved for core API)

#define WM_SETMESSAGESTRING 0x0362  // wParam = nIDS (or 0),
// lParam = lpszOther (or NULL)
#define WM_IDLEUPDATECMDUI  0x0363  // wParam == bDisableIfNoHandler
#define WM_INITIALUPDATE    0x0364  // (params unused) - sent to children
#define WM_COMMANDHELP      0x0365  // lResult = TRUE/FALSE,
// lParam = dwContext
#define WM_HELPHITTEST      0x0366  // lResult = dwContext,
// lParam = MAKELONG(x,y)
#define WM_EXITHELPMODE     0x0367  // (params unused)
#define WM_RECALCPARENT     0x0368  // force layout on frame ::user::window
//  (only for inplace frame windows)
#define WM_SIZECHILD        0x0369  // special notify from COleResizeBar
// wParam = ID of child ::user::window
// lParam = lpRectNew (new position/size)
#define WM_KICKIDLE         0x036A  // (params unused) causes idles to kick in
#define WM_QUERYCENTERWND   0x036B  // lParam = oswindow to use as centering parent
#define WM_DISABLEMODAL     0x036C  // lResult = 0, disable during modal state
// lResult = 1, don't disable
#define WM_FLOATSTATUS      0x036D  // wParam combination of FS_* flags below

// WM_ACTIVATETOPLEVEL is like WM_ACTIVATEAPP but works with hierarchies
//   of mixed processes (as is the case with OLE in-place activation)
#define WM_ACTIVATETOPLEVEL 0x036E  // wParam = nState (like WM_ACTIVATE)
// lParam = pointer to oswindow[2]
//  lParam[0] = oswindow getting WM_ACTIVATE
//  lParam[1] = oswindow_Other

#define WM_RESERVED_036F   0x036F  // was WM_QUERY3DCONTROLS (now not used)

// Note: Messages 0x0370, 0x0371, and 0x372 were incorrectly used by
//  some versions of Windows.  To remain compatible, core API does not
//  use messages in that range.
#define WM_RESERVED_0370    0x0370
#define WM_RESERVED_0371    0x0371
#define WM_RESERVED_0372    0x0372

// WM_SOCKET_NOTIFY and WM_SOCKET_DEAD are used internally by core API's
// Windows sockets implementation.  For more information, see sockcore.cpp
#define WM_SOCKET_NOTIFY    0x0373
#define WM_SOCKET_DEAD      0x0374

// same as WM_SETMESSAGESTRING except not popped if IsTracking()
#define WM_POPMESSAGESTRING 0x0375

// WM_HELPPROMPTADDR is used internally to get the address of
//   m_dwPromptContext from the associated frame ::user::window. This is used
//   during message boxes to setup for F1 help while that msg box is
//   displayed. lResult is the address of m_dwPromptContext.
#define WM_HELPPROMPTADDR   0x0376

// Constants used in DLGINIT resources for OLE control containers
// NOTE: These are NOT real Windows messages they are simply tags
// used in the control resource and are never used as 'messages'
#define WM_OCC_LOADFROMSTREAM           0x0376
#define WM_OCC_LOADFROMSTORAGE          0x0377
#define WM_OCC_INITNEW                  0x0378
#define WM_OCC_LOADFROMSTREAM_EX        0x037A
#define WM_OCC_LOADFROMSTORAGE_EX       0x037B

// Marker used while rearranging the message queue
#define WM_QUEUE_SENTINEL   0x0379

// Note: Messages 0x037C - 0x37E reserved for future core API use.
#define WM_RESERVED_037C    0x037C
#define WM_RESERVED_037D    0x037D
#define WM_RESERVED_037E    0x037E

// WM_FORWARDMSG - used by core to forward a message to another ::user::window for processing
//   WPARAM - uint32_t dwUserData - defined by ::fontopus::user
//   LPARAM - LPMESSAGE pMsg - a pointer to the MESSAGE structure
//   return value - 0 if the message was not processed, nonzero if it was
#define WM_FORWARDMSG      0x037F

// like ON_MESSAGE but no return value
#define ON_MESSAGE_VOID(message, memberFxn) \
{ message, 0, 0, 0, ::core::Sig_vv, \
   (__PMSG)(__PMSGW)(void (__MSG_CALL::user::window::*)())&memberFxn },




// flags for wParam in the WM_FLOATSTATUS message
enum {
   FS_SHOW = 0x01, FS_HIDE = 0x02,
   FS_ACTIVATE = 0x04, FS_DEACTIVATE = 0x08,
   FS_ENABLE = 0x10, FS_DISABLE = 0x20,
   FS_SYNCACTIVE = 0x40
};

CLASS_DECL_BASE void __reposition_window(__SIZEPARENTPARAMS* lpLayout, sp(::user::interaction) oswindow, LPCRECT lpRect);

#ifndef LAYOUT_LTR
#define LAYOUT_LTR                         0x00000000
#endif


#if defined(LINUX) || defined(MACOS)
struct NMHDR
{

   int32_t nId;
};


#endif



#pragma once

// General OLE features

#if (!defined ___NO_OLE_SUPPORT) && (defined _OBJBASE_H_)

// Implementation structures
struct __EVENT;               // Event sink implementation

// Classes declared in this file
class COleControlLock;

#endif

// OLE Automation features

#ifdef __AFXDISP_H__
// Classes declared in this file

//IStream
class CArchiveStream;

// Functions declared in this file

// ::core::BSTR2ABTSR
// ::core::TaskStringA2W
// ::core::TaskStringW2A

#endif

/////////////////////////////////////////////////////////////////////////////
// General OLE features

#if (!defined ___NO_OLE_SUPPORT) && (defined _OBJBASE_H_)
#ifndef __AFXPRIV2_H__OLE__
#define __AFXPRIV2_H__OLE__

/////////////////////////////////////////////////////////////////////////////
// Implementation of event sink handling

struct __EVENT
{
   enum
   {
      event,
      propRequest, propChanged,
      propDSCNotify
   };

   __EVENT(int32_t eventKind);

   __EVENT(int32_t eventKind, DISPID dispid, DISPPARAMS* pDispParams = NULL,
      EXCEPINFO* pExcepInfo = NULL, UINT* puArgError = NULL);

   int32_t m_eventKind;
   DISPID m_dispid;
   DISPPARAMS* m_pDispParams;
   EXCEPINFO* m_pExcepInfo;
   UINT* m_puArgError;
   bool m_bPropChanged;
   HRESULT m_hResult;
   DSCSTATE m_nDSCState;
   DSCREASON m_nDSCReason;
};

inline __EVENT::__EVENT(int32_t eventKind)
{
   m_eventKind = eventKind;
   m_dispid = DISPID_UNKNOWN;
   m_pDispParams = NULL;
   m_pExcepInfo = NULL;
   m_puArgError = NULL;
   m_hResult = NOERROR;
   m_nDSCState = dscNoState;
   m_nDSCReason = dscNoReason;
}

inline __EVENT::__EVENT(int32_t eventKind, DISPID dispid,
   DISPPARAMS* pDispParams, EXCEPINFO* pExcepInfo, UINT* puArgError)
{
   m_eventKind = eventKind;
   m_dispid = dispid;
   m_pDispParams = pDispParams;
   m_pExcepInfo = pExcepInfo;
   m_puArgError = puArgError;
   m_hResult = NOERROR;
   m_nDSCState = dscNoState;
   m_nDSCReason = dscNoReason;
}

/////////////////////////////////////////////////////////////////////////////
// COleControlLock

class COleControlLock
{
   // Constructors
public:
   explicit COleControlLock(REFCLSID clsid);

   // Attributes
   CLSID m_clsid;
   LPCLASSFACTORY m_pClassFactory;
   COleControlLock* m_pNextLock;

   // Implementation
public:
   virtual ~COleControlLock();
};

#endif // __AFXPRIV2_H__OLE__
#endif //(!defined ___NO_OLE_SUPPORT) && (defined _OBJBASE_H_)

/////////////////////////////////////////////////////////////////////////////
// OLE Automation features

#ifdef __AFXDISP_H__
#ifndef __AFXPRIV2_H__DISP__
#define __AFXPRIV2_H__DISP__

/////////////////////////////////////////////////////////////////////////////
// CArchiveStream
/*
class CLASS_DECL_BASE CArchiveStream : public IStream
{
public:
CArchiveStream(CArchive* pArchive);

// Implementation
CArchive* m_pArchive;

STDMETHOD_(ULONG, AddRef)();
STDMETHOD_(ULONG, Release)();
HRes QueryInterface)(REFIID, LPVOID*);

HRes read)(void *, ULONG, ULONG*);
HRes write)(const void *, ::primitive::memory_size cb, ::primitive::memory_size*);
HRes seek)(LARGE_INTEGER, uint32_t, ULARGE_INTEGER*);
HRes set_size)(ULARGE_INTEGER);
HRes CopyTo)(LPSTREAM, ULARGE_INTEGER, ULARGE_INTEGER*,
ULARGE_INTEGER*);
HRes Commit)(uint32_t);
HRes Revert)();
HRes LockRegion)(ULARGE_INTEGER, ULARGE_INTEGER,uint32_t);
HRes UnlockRegion)(ULARGE_INTEGER, ULARGE_INTEGER, uint32_t);
HRes Stat)(STATSTG*, uint32_t);
HRes Clone)(LPSTREAM*);
};
*/
/////////////////////////////////////////////////////////////////////////////
// Global UNICODE<>ANSI translation helpers

CLASS_DECL_BASE void ::core::BSTR2String(string* pStr, BSTR bstr);

#if !defined(_UNICODE)
CLASS_DECL_BASE BSTR::core::BSTR2ABSTR(BSTR bstrW);
CLASS_DECL_BASE wchar_t * ::core::TaskStringA2W(const char * lpa);
CLASS_DECL_BASE char * ::core::TaskStringW2A(const wchar_t * lpw);
#endif

#endif // __AFXPRIV2_H__DISP__
#endif // __AFXDISP_H__

/////////////////////////////////////////////////////////////////////////////




#include "user_impact_update_hint.h"
#include "user_job.h"


#include "base/base/base/base_print_job.h"


#include "user_message.h"

#include "user_printer.h"
#include "user_print_job.h"
#include "user_menu_base.h"
#include "user_button.h"
#include "user_menu_button.h"
#include "user_menu_item.h"





