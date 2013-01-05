#pragma once


#include "ca/radix/radix.h"


#include "ca/radix/radix_os_history.h"


namespace windows
{
   template < class APP >
   inline ::ca::application & cast(APP * papp)
   {
      return *(dynamic_cast < ::ca::application * > (papp));
   }
}



#include "ca/collection/collection_sort_array.h"


#include "ca/primitive/primitive_id_space.h"
#include "ca/primitive/primitive_id_space.h"


#include "ca/gen/gen_international_locale_schema.h"


#include "ca/radix/radix_system.h"


#include "ca/radix/radix_wait_cursor.h"





/////////////////////////////////////////////////////////////////////////////
// Extra diagnostic tracing options

#ifdef DEBUG
extern CLASS_DECL_ca UINT g_uiTraceFlags;
#endif // DEBUG

#ifdef DEBUG
#define DECLARE___TRACE_CATEGORY( name ) extern CLASS_DECL_ca ::gen::trace::category name;
#else
#define DECLARE___TRACE_CATEGORY( name ) const dword_ptr name = 0;
#endif


//////////////////////////////////////////////////////////////////////////////
// MessageBox helpers

//CLASS_DECL_ca void gen::FormatString1(string & rString, UINT nIDS, const char * lpsz1);
//CLASS_DECL_ca void gen::FormatString2(string & rString, UINT nIDS,
//            const char * lpsz1, const char * lpsz2);
/*CLASS_DECL_ca int32_t System.simple_message_box(const char * lpszText, UINT nType = MB_OK,
            UINT nIDHelp = 0);*/
/*CLASS_DECL_ca int32_t System.simple_message_box(UINT nIDPrompt, UINT nType = MB_OK,
            UINT nIDHelp = (UINT)-1);*/

// Implementation string helpers
//CLASS_DECL_ca void __format_strings(string & rString, UINT nIDS,
//            const char * const* rglpsz, int32_t nString);
namespace ex1
{

   CLASS_DECL_ca void format_strings(string & rString, const char * lpszFormat, const char * const* rglpsz, int32_t nString);
   CLASS_DECL_ca bool extract_sub_string(string & rString, const char * lpszFullString, int32_t iSubString, char chSep = '\n');

}



#include "ca/radix/radix_os.h"



#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lp)                        ((int32_t)(short)LOWORD(lp))
#endif
#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lp)                        ((int32_t)(short)HIWORD(lp))
#endif


#include "ca/radix/radix_fixed_alloc.h"
#include "ca/radix/radix_process_data.h"


#include "ca/ca/ca_system.h"



#include "ex1_exception.h"

#include "ex1_request_interface.h"

#include "ex1_tree_item_data.h"
#include "ex1_tree_item.h"
#include "ex1_tree_data.h"
#include "ex1_tree.h"

#include "ex1_fs_interface.h"

#include "ex1_stream_base.h"

#include "ex1_seekable.h"

#include "ex1_reader.h"
#include "ex1_writer.h"
#include "ex1_stream.h"

#include "ex1_byte_serializable.h"
#include "ex1_byte_stream.h"
#include "ex1_plain_text_serializable.h"

#include "ca/gen/gen_base_enum.h"




#include "ex1_plain_text_stream.h"
#include "ex1_output_stream_flush_interface.h"
#include "ex1_stream2.h"


namespace primitive
{


   class memory;


} // namespace primitive


namespace ex1
{


   class file_exception;
   struct file_status;


} // namespace ex1


#include "ex1_file.h"
#include "ex1_file_composite.h"
#include "ex1_file_exception.h"
#include "ex1_file_status.h"



#include "ex1_plain_text_string_stream.h"

#include "ex1_file_stream.h"


// memory primitives
#include "ca/primitive/primitive_memory_base.h"
#include "ca/primitive/primitive_memory.h"
#include "ca/primitive/primitive_virtual_memory.h"
#include "ca/primitive/primitive_shared_memory.h"
#include "ca/primitive/primitive_memory_container.h"
#include "ca/primitive/primitive_memory_file.h"
#include "ca/primitive/primitive_shared_file.h"



#include "ca/zlib/zconf.h"
#include "ca/zlib/zlib.h"
#include "ca/zlib/zutil.h"
#include "ca/sqlite/sqlite.h"



#include "ca/libcharguess/libcharguess.h"





// Implementation structures
struct __SIZEPARENTPARAMS;    // control bar implementationpropergen_property.h

// Classes declared in this file

   //::ca::graphics_sp
      class preview_dc;               // Virtual DC for print preview

   //command_target
      //::ca::window
         //::view
            class CPreviewView;     // Print preview ::view
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
   // E900 -> EEFF standard ::ca::window controls/components
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
// (0x0360 - 0x037F are reserved for ca2 API)

#define WM_QUERYAFXWNDPROC  0x0360  // lResult = 1 if processed by __window_procedure
#define WM_SIZEPARENT       0x0361  // lParam = &__SIZEPARENTPARAMS
#define WM_SETMESSAGESTRING 0x0362  // wParam = nIDS (or 0),
                           // lParam = lpszOther (or NULL)
#define WM_IDLEUPDATECMDUI  0x0363  // wParam == bDisableIfNoHandler
#define WM_INITIALUPDATE    0x0364  // (params unused) - sent to children
#define WM_COMMANDHELP      0x0365  // lResult = TRUE/FALSE,
                           // lParam = dwContext
#define WM_HELPHITTEST      0x0366  // lResult = dwContext,
                           // lParam = MAKELONG(x,y)
#define WM_EXITHELPMODE     0x0367  // (params unused)
#define WM_RECALCPARENT     0x0368  // force layout on frame ::ca::window
                           //  (only for inplace frame windows)
#define WM_SIZECHILD        0x0369  // special notify from COleResizeBar
                           // wParam = ID of child ::ca::window
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
//  some versions of Windows.  To remain compatible, ca2 API does not
//  use messages in that range.
#define WM_RESERVED_0370    0x0370
#define WM_RESERVED_0371    0x0371
#define WM_RESERVED_0372    0x0372

// WM_SOCKET_NOTIFY and WM_SOCKET_DEAD are used internally by ca2 API's
// Windows sockets implementation.  For more information, see sockcore.cpp
#define WM_SOCKET_NOTIFY    0x0373
#define WM_SOCKET_DEAD      0x0374

// same as WM_SETMESSAGESTRING except not popped if IsTracking()
#define WM_POPMESSAGESTRING 0x0375

// WM_HELPPROMPTADDR is used internally to get the address of
//   m_dwPromptContext from the associated frame ::ca::window. This is used
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

// Note: Messages 0x037C - 0x37E reserved for future ca2 API use.
#define WM_RESERVED_037C    0x037C
#define WM_RESERVED_037D    0x037D
#define WM_RESERVED_037E    0x037E

// WM_FORWARDMSG - used by gen to forward a message to another ::ca::window for processing
//   WPARAM - DWORD dwUserData - defined by ::fontopus::user
//   LPARAM - LPMESSAGE pMsg - a pointer to the MESSAGE structure
//   return value - 0 if the message was not processed, nonzero if it was
#define WM_FORWARDMSG      0x037F

// like ON_MESSAGE but no return value
#define ON_MESSAGE_VOID(message, memberFxn) \
   { message, 0, 0, 0, gen::Sig_vv, \
      (__PMSG)(__PMSGW)(void (__MSG_CALL ::ca::window::*)())&memberFxn },

#if defined(LINUX) || defined(MACOS) || defined(METROWIN)

typedef void * HDWP;

#endif


// special struct for WM_SIZEPARENT
struct __SIZEPARENTPARAMS
{
   HDWP hDWP;       // handle for DeferWindowPos
   RECT rect;       // parent client rectangle (trim as appropriate)
   SIZE sizeTotal;  // total size on each side as layout proceeds
   bool bStretch;   // should stretch to fill all space
};

// flags for wParam in the WM_FLOATSTATUS message
enum {  FS_SHOW = 0x01, FS_HIDE = 0x02,
      FS_ACTIVATE = 0x04, FS_DEACTIVATE = 0x08,
      FS_ENABLE = 0x10, FS_DISABLE = 0x20,
      FS_SYNCACTIVE = 0x40 };

CLASS_DECL_ca void __reposition_window(__SIZEPARENTPARAMS* lpLayout, ::user::interaction * oswindow, LPCRECT lpRect);

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

// gen::BSTR2ABTSR
// gen::TaskStringA2W
// gen::TaskStringW2A

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
class CLASS_DECL_ca CArchiveStream : public IStream
{
public:
   CArchiveStream(CArchive* pArchive);

// Implementation
   CArchive* m_pArchive;

   STDMETHOD_(ULONG, AddRef)();
   STDMETHOD_(ULONG, Release)();
   ex1::HRes QueryInterface)(REFIID, LPVOID*);

   ex1::HRes read)(void *, ULONG, ULONG*);
   ex1::HRes write)(const void *, ::primitive::memory_size cb, ::primitive::memory_size*);
   ex1::HRes seek)(LARGE_INTEGER, DWORD, ULARGE_INTEGER*);
   ex1::HRes set_size)(ULARGE_INTEGER);
   ex1::HRes CopyTo)(LPSTREAM, ULARGE_INTEGER, ULARGE_INTEGER*,
      ULARGE_INTEGER*);
   ex1::HRes Commit)(DWORD);
   ex1::HRes Revert)();
   ex1::HRes LockRegion)(ULARGE_INTEGER, ULARGE_INTEGER,DWORD);
   ex1::HRes UnlockRegion)(ULARGE_INTEGER, ULARGE_INTEGER, DWORD);
   ex1::HRes Stat)(STATSTG*, DWORD);
   ex1::HRes Clone)(LPSTREAM*);
};
*/
/////////////////////////////////////////////////////////////////////////////
// Global UNICODE<>ANSI translation helpers

CLASS_DECL_ca void gen::BSTR2String(string* pStr, BSTR bstr);

#if !defined(_UNICODE)
CLASS_DECL_ca BSTR gen::BSTR2ABSTR(BSTR bstrW);
CLASS_DECL_ca wchar_t * gen::TaskStringA2W(const char * lpa);
CLASS_DECL_ca char * gen::TaskStringW2A(const wchar_t * lpw);
#endif

#endif // __AFXPRIV2_H__DISP__
#endif // __AFXDISP_H__

/////////////////////////////////////////////////////////////////////////////






#include "ex1_definition.h"
#include "ex1_types.h"

#include "ex1_match.h"

// interfaces
#include "ex1_progress_interface.h"


// from 7-zip
#include "ex1_system_exception.h"
#include "ex1_buffer.h"
#include "ex1_dynamic_buffer.h"
#include "ex1_in_buffer.h"
#include "ex1_out_buffer.h"
#include "ex1_circular_buffer.h"
#include "ex1_bitl_decoder.h"
#include "ex1_bitl_encoder.h"
#include "ex1_bitm_decoder.h"
#include "ex1_bitm_encoder.h"
#include "ex1_limited_reader.h"
#include "ex1_limited_input_stream.h"
#include "ex1_clustered_input_stream.h"
#include "ex1_limited_writer.h"

#include "ex1_stream_binder.h"
#include "ex1_locked_in_stream.h"
#include "ex1_io_temp_buffer.h"
#include "ex1_size_count_writer.h"
#include "ex1_dynamic_buffered_writer.h"


#include "ex1_buffered_file.h"
#include "ex1_timeout_file.h"
#include "ex1_edit_file.h"
#include "ex1_text_file.h"
#include "ex1_file_system.h"
#include "ex1_resource.h"
#include "ex1_application.h"

#include "ex1_simple_tree_item_data.h"
#include "ex1_simple_tree_data.h"
