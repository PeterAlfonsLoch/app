#pragma once


namespace aura
{


   class menu_base_item;
   class menu;
   class menu_base;


}

namespace user
{

   class schema;
   class tree;

}


namespace simple_ui
{

   class label;
   class edit_box;
   class password;
   class tap;

}




namespace user
{

   class control_event;
   class create_context;
   class printer;
   class user;
   class frame_window;

   class form_interface;
   class form_list;
   class form_callback;


} // namespace user

namespace user
{

   class interaction;
   class interaction_impl;
   class view_creator_data;
   class schema;
   class tree;
   class str_context;
   class schema_simple_impl;
   class window_draw;
   class str;

}
typedef sp(::user::interaction_impl) window_sp;

namespace user
{

   class interaction;
   class control_event;
   class create_context;
   class user;
   class frame_window;

   class form_interface;
   class form_list;
   class form_callback;


} // namespace user


namespace simple_ui
{

   class label;
   class edit_box;
   class password;
   class tap;

}

namespace user
{


   class interaction;
   class interaction_impl;
   class frame_window;
   class create_struct;


} // namespace user


namespace user
{

   class place_holder;

#if defined METROWIN

   class CLASS_DECL_BASE native_window_initialize
   {
   public:


      Agile<Windows::UI::Core::CoreWindow> window;
      ::axis::system_window ^ pwindow;


   };

#elif defined(APPLE_IOS)

   class CLASS_DECL_BASE native_window_initialize
   {
   public:

      RECT   m_rect;

   };

#else

   class native_window_initialize;

#endif


   class control_event;
   class frame_window;





   CLASS_DECL_BASE bool is_descendant(::user::interaction * puiParent,::user::interaction * puiChild);


} // namespace user



#if defined(__cplusplus) || defined(__cplusplus_winrt)


namespace user
{


   class CLASS_DECL_BASE create_struct:
      public CREATESTRUCTA
   {
   public:


      create_struct & operator = (const RECT & rect)
      {

         x = rect.left;
         y = rect.top;
         cx = rect.right - rect.left;
         cy = rect.bottom - rect.top;

         return *this;

      }


      create_struct & operator = (LPCRECT lpcrect)
      {

         if(lpcrect == NULL)
         {

            x = 0;
            y = 0;
            cx = 0;
            cy = 0;

         }
         else
         {

            operator = (*lpcrect);

         }

         return *this;

      }


   };


} // namespace user


#endif







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
class CLASS_DECL_BASE Ex1FormInterfaceComboBox:
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
//::aura::impact
class CPreviewView;     // Print preview ::aura::impact
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
#define HID_BASE_COMMAND    0x00010000UL        // ID and IDM
#define HID_BASE_RESOURCE   0x00020000UL        // IDR and IDD
#define HID_BASE_PROMPT     0x00030000UL        // IDP
#define HID_BASE_NCAREAS    0x00040000UL
#define HID_BASE_CONTROL    0x00050000UL        // IDC
#define HID_BASE_DISPATCH   0x00060000UL        // IDispatch help codes





// flags for wParam in the WM_FLOATSTATUS message
enum {
   FS_SHOW = 0x01, FS_HIDE = 0x02,
   FS_ACTIVATE = 0x04, FS_DEACTIVATE = 0x08,
   FS_ENABLE = 0x10, FS_DISABLE = 0x20,
   FS_SYNCACTIVE = 0x40
};


namespace user
{


   CLASS_DECL_BASE void __reposition_window(__SIZEPARENTPARAMS* lpLayout,::user::interaction * pui,LPCRECT lpRect);


} // namespace user


#ifndef LAYOUT_LTR
#define LAYOUT_LTR                         0x00000000
#endif


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


#include "user_message.h"

#include "base/base/base_print_job.h"
#include "user_print_job.h"


#include "user_menu_base_item.h"
#include "user_menu_base.h"



#include "user_inline.h"


#include "base/base/hotplugin/hotplugin.h"


#include "base/install/install.h"


#include "base/user/fontopus/fontopus.h"













