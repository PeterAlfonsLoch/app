#pragma once


#ifndef TBSTYLE_TOOLTIPS
#define TBSTYLE_TOOLTIPS        0x0100
#define TBSTYLE_WRAPABLE        0x0200
#define TBSTYLE_ALTDRAG         0x0400
#define TBSTYLE_FLAT            0x0800
#define TBSTYLE_LIST            0x1000
#define TBSTYLE_CUSTOMERASE     0x2000
#define TBSTYLE_REGISTERDROP    0x4000
#define TBSTYLE_TRANSPARENT     0x8000
#endif


#include "user_windowing.h"



// Note: afxData.cxBorder and afxData.cyBorder aren't used anymore
#define CX_BORDER   1
#define CY_BORDER   1


class Ex1FormInterfaceComboBox;

/*
class CLASS_DECL_AXIS Ex1FormInterfaceComboBox:
   virtual public ::object
{
public:


   ::database::id       m_datakeyFill;
   stringa              m_wstra;
   uint_array          m_dwaData;


};

*/


// Implementation structures
struct __SIZEPARENTPARAMS;    // control bar implementationproperca2_property.h

// Classes declared in this file

//::draw2d::graphics_sp
class preview_dc;               // Virtual DC for print preview

//command_target
//interaction_impl
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
// E900 -> EEFF standard interaction_impl controls/components
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
#define HID_AXIS_COMMAND    0x00010000UL        // ID and IDM
#define HID_AXIS_RESOURCE   0x00020000UL        // IDR and IDD
#define HID_AXIS_PROMPT     0x00030000UL        // IDP
#define HID_AXIS_NCAREAS    0x00040000UL
#define HID_AXIS_CONTROL    0x00050000UL        // IDC
#define HID_AXIS_DISPATCH   0x00060000UL        // IDispatch help codes





// flags for wParam in the WM_FLOATSTATUS message
enum {
   FS_SHOW = 0x01, FS_HIDE = 0x02,
   FS_ACTIVATE = 0x04, FS_DEACTIVATE = 0x08,
   FS_ENABLE = 0x10, FS_DISABLE = 0x20,
   FS_SYNCACTIVE = 0x40
};


namespace user
{


   CLASS_DECL_AXIS void __reposition_window(__SIZEPARENTPARAMS* lpLayout,sp(::user::interaction) oswindow,LPCRECT lpRect);


} // namespace user


#ifndef LAYOUT_LTR
#define LAYOUT_LTR                         0x00000000
#endif


// General OLE features

#if (!defined ___NO_OLE_SUPPORT) && (defined _OBJAXIS_H_)

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

#if (!defined ___NO_OLE_SUPPORT) && (defined _OBJAXIS_H_)
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
#endif //(!defined ___NO_OLE_SUPPORT) && (defined _OBJAXIS_H_)

/////////////////////////////////////////////////////////////////////////////
// OLE Automation features

#ifdef __AFXDISP_H__
#ifndef __AFXPRIV2_H__DISP__
#define __AFXPRIV2_H__DISP__

/////////////////////////////////////////////////////////////////////////////
// CArchiveStream
/*
class CLASS_DECL_AXIS CArchiveStream : public IStream
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

CLASS_DECL_AXIS void ::core::BSTR2String(string* pStr, BSTR bstr);

#if !defined(_UNICODE)
CLASS_DECL_AXIS BSTR::core::BSTR2ABSTR(BSTR bstrW);
CLASS_DECL_AXIS wchar_t * ::core::TaskStringA2W(const char * lpa);
CLASS_DECL_AXIS char * ::core::TaskStringW2A(const wchar_t * lpw);
#endif

#endif // __AFXPRIV2_H__DISP__
#endif // __AFXDISP_H__

/////////////////////////////////////////////////////////////////////////////




#include "user_impact_update_hint.h"
#include "user_job.h"


#include "user_message.h"

#include "user_printer.h"
#include "axis/axis/axis_print_job.h"
#include "user_print_job.h"


#include "user_menu_base_item.h"
#include "user_menu_base.h"



#include "user_inline.h"










