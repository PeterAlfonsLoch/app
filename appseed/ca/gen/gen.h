#pragma once


#include "app/appseed/ca/ca/ca.h"


// former gen

// Since ca2 API itself is built with wchar_t as a native type, it will not have
// the correct type info for types built with wchar_t typedef'd to uint32_t
// int16_t.  Make sure that the ::fontopus::user's cast builds this type info in this case.
#ifndef _NATIVE_WCHAR_T_DEFINED
#define ___FULLTYPEINFO
#endif


#ifdef __DBGMEM_H__
#error <atldbgmem.h> cannot be used in ca2 API projects. See __enable_memory_tracking
#endif

#if defined(_MFC_DLL_BLD) && defined(DEBUG)
#ifndef _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC
#endif
#endif


#ifdef WINDOWS
#include <new.h>
#endif





/////////////////////////////////////////////////////////
// Forward declations
namespace gen
{
   class object;
}
class base_exception;
class simple_exception;
class memory_exception;
class not_supported_exception;
class invalid_argument_exception;
namespace gen
{
   class file_exception;
   class file;
}
class stdio_file;
namespace primitive
{
   class memory_file;
}
namespace gen
{
   struct file_status;
}
struct memory_state;
class dump_context;


/////////////////////////////////////////////////////////////////////////////
// Basic types
// abstract iteration position
//struct __POSITION {};
//typedef __POSITION* POSITION;

// Standard constants
#undef FALSE
#undef TRUE
#undef NULL

#define FALSE   0
#define TRUE    1
#define NULL    0


/////////////////////////////////////////////////////////////////////////////
// Turn off warnings for /W4
// To resume any of these warning: #pragma warning(default: 4xxx)
// which should be placed after the _ include files

#pragma warning(disable: 4505)  // unreferenced local function has been removed
#pragma warning(disable: 4511)  // private copy constructors are good to have
#pragma warning(disable: 4512)  // private operator= are good to have
#pragma warning(disable: 4514)  // unreferenced inlines are common
#pragma warning(disable: 4710)  // function not inlined
#pragma warning(disable: 4660)  // template is already instantiated
#pragma warning(disable: 4127)  // constant expression used in macros do while(0);

#pragma warning(disable: 4275)  // deriving exported class from non-exported
#pragma warning(disable: 4251)  // using non-exported as public in exported


#ifdef ___ALL_WARNINGS
#pragma warning( push )
#endif

// warnings generated with common ca2 API/Windows code
#pragma warning(disable: 4134)  // message ::collection::map member fxn casts
#pragma warning(disable: 4201)  // nameless unions are part of C++
#pragma warning(disable: 4320)  // structs with uuid handled as interfaces
#pragma warning(disable: 4705)  // statement has no effect in optimized code
#pragma warning(disable: 4191)  // pointer-to-function casting
// warnings caused by normal optimizations
#ifndef DEBUG
#pragma warning(disable: 4701)  // local var *may* be used without init
#pragma warning(disable: 4702)  // unreachable code caused by optimizations
#pragma warning(disable: 4791)  // loss of debugging info in release version
#pragma warning(disable: 4189)  // initialized but unused var
#pragma warning(disable: 4390)  // is_empty controlled statement
#endif
#pragma warning(disable: 4204)  // non-constant aggregate initializer
#pragma warning(disable: 4263 4264)  // base class method is hidden


/////////////////////////////////////////////////////////////////////////////
// Other implementation helpers

#define BEFORE_START_POSITION ((POSITION)-1L)


#undef __DATA
#define __DATA __CORE_DATA


#ifndef _OLEAUTO_H_
   typedef wchar_t * BSTR;// must (semantically) match typedef in oleauto.h
#endif

#undef new



#define new DEBUG_NEW


#include "ca/exception/exception.h"




#include "ca/primitive/primitive_numeric_info.h"
#include "gen_c_number.h"

#include "ca/multithreading/multithreading_wait_result.h"
#include "ca/primitive/datetime/datetime_duration.h"
#include "gen_request_interface.h"
#include "ca/multithreading/multithreading_waitable.h"
#include "ca/primitive/primitive.h"


#include "gen_object.h"


#include "gen_definition.h"
#include "gen_common.h"
#include "gen_core.h"


#include "gen_heap.h"
#include "gen_plex_heap.h"
#include "gen_fixed_alloc.h"

#include "ca/primitive/primitive_simple_string.h"

#include "gen_ch.h"
#include "gen_str.h"

#include "ca/primitive/primitive_id.h"
#include "ca/primitive/primitive_string_format.h"
#include "ca/primitive/primitive_fixed_string.h"
#include "ca/primitive/primitive_string.h"
#include "ca/primitive/datetime/datetime_time.h"


#include "ca/primitive/primitive.h"

#include "gen_object.h"

#include "gen_hash.h"
#include "gen_equals.h"
#include "gen_compare.h"
#include "gen_less.h"
#include "gen.h"


#include "gen_template.h"


#include "ca/collection/collection_base_array.h"

#include "ca/ca/ca_smart_pointer.h"



#define ASSERT_KINDOF(class_name, object) ASSERT(base < class_name > ::bases(object))
#define DYNAMIC_DOWNCAST(class_name, object) (dynamic_cast < class_name * > (object))
#define STATIC_DOWNCAST(class_name, object) (dynamic_cast<class_name*>(object))
#define STATIC_DOWNCAST_T(class_name, T1, object) (static_cast<class_name<T1>*>(gen::StaticDownCast(RUNTIME_CLASS_T(class_name, T1), object)))
#define STATIC_DOWNCAST_T2(class_name, T1, T2, object) (static_cast<class_name<T1, T2>*>(gen::StaticDownCast(RUNTIME_CLASS_T2(class_name, T1, T2), object)))

// optional bit for schema number that enables object versioning
#define VERSIONABLE_SCHEMA  (0x80000000)

/////////////////////////////////////////////////////////////////////////////
// other helpers

// zero fill everything after the vtbl pointer
#define __ZERO_INIT_OBJECT(base_class) memset(((base_class*)this)+1, 0, sizeof(*this) - sizeof(class base_class));



#include "gen.inl"


#undef __DATA
#define __DATA CLASS_DECL_ca


#ifdef ___ALL_WARNINGS
#pragma warning( pop )
#endif



#include "gen_allocate.h"
#include "gen_plex.h"

#include "ca/collection/collection.h"


#include "gen_plex_heap.h"



#include "gen_holder.h"
#include "gen_base.h"


#include "ca/ca/ca_interlocked_long.h"
#include "ca/ca/ca_interlocked_long_pulse.h"

#include "ca/multithreading/multithreading.h"

#include "ca/ca/ca_data.h"
#include "ca/ca/ca_data_container.h"
#include "ca/ca/ca_data_listener.h"

#include "ca/ca/ca_edit.h"

#include "ca/ca/ca_type_info.h"
#include "gen_factory.h"


#include "ca/user/user_str.h"


#pragma once

typedef long VMSRESULT;

/*typedef struct tagVMSNMHDR {
    oswindow oswindowFrom;
    UINT idFrom;
    UINT code;
} VMSNMHDR;

typedef struct tagE17_KEYDOWN {
    VMSNMHDR hdr;
    WORD wVKey;
    UINT flags;
} E17_KEYDOWN;

typedef struct tagE17_SYSKEYDOWN {
    VMSNMHDR hdr;
    WORD wVKey;
    UINT flags;
} E17_SYSKEYDOWN;*/



#define APPM_NOTIFY WM_APP + 1117
#define APPN_CHILDDELETE 1000
#define APPN_OPENLINK 1001
   // lParam is a pointer to a Unicode string
   // that can´t be deleted

#define VMSM_NOTIFY WM_USER + 1117
#define VMSM_TIMER WM_USER + 1119

#define E17N_KEYDOWN 17
#define E17N_SYSKEYDOWN 19
#define E17N_ESCAPE 1
#define E17N_RETURN 0

#define VMS_FAILED(Status) ((VMSRESULT)(Status)<0)
#define VMS_SUCCEEDED(Status) ((VMSRESULT)(Status)>=0)

#define VMSR_SUCCESS          0
#define VMSR_S_NOTFOUND       2000
#define VMSR_S_ENDOFFILE     3000
#define VMSR_S_SKIP         4000
#define VMSR_E_FAIL          -1
#define VMSR_E_NOMEMORY    -13
#define VMSR_E_INVALIDFILE    -15

#define VMS_DOC_VERSION_1    1

#define VMS_EVENT_NULL 0
#define VMS_EVENT_MIDI 1
#define VMS_EVENT_MIDI_DELETED 2
#define VMS_EVENT_SYMBOL 3
#define VMS_EVENT_SYMBOL_DELETED 4


#define FOURCC_MShd     mmioFOURCC('M','S','h','d')
#define FOURCC_MStk     mmioFOURCC('M','S','t','k')

#define APP_MAX_STRING_ERROR_CHARS      512
#define APP_MAX_STRING_ERROR_BYTES      (APP_MAX_STRING_ERROR_CHARS * sizeof(TCHAR))

#define VMSM_EXCEPTION WM_APP + 1000
#define EXCEPTION_OLEDB 1000

#define VMSM_RENDER_RECT    WM_USER + 2000
#define VMSM_RENDER_RGN     WM_USER + 2001

#define VMSM_ECONOMODECHANGE WM_USER + 2002

#define VMSM_V001 WM_APP + 1001
#define NOTIFY_BUILDALBUMPROGRESSUPDATE 1000
#define NOTIFY_BUILDALBUMSTATUSUPDATE 1001
#define NOTIFY_BUILDALBUMTASKSUPDATE 1002
#define NOTIFY_BUILDALBUMDELETE 1003
#define NOTIFY_BUILDALBUMFINISHED 1010
#define NOTIFY_TIMERCALLBACKCREATETIMER 1104
#define NOTIFY_TIMERCALLBACKDELETETIMER 1105
#define NOTIFY_CLOSE 1106
#define NOTIFY_BUILDALBUMONHIDETASKDIALOG 120

#define VMSM_COMMAND WM_APP + 1002
#define VMSC_BRINGTOTOP 1000

class CTimerCallback;


typedef struct tag_TimerCallbackCreateTimer
{
    CTimerCallback *    m_pTimerCallback;
    UINT                m_uiElapse;
    UINT                m_uiIDEvent;
} TIMERCALLBACKCREATETIMER, * LPTIMERCALLBACKCREATETIMER;









#define WM_VIEW (WM_USER + 1023)


#include "gen_base.h"
#include "gen_constraint.h"

#ifdef WINDOWS
#ifndef _INC_SHELLAPI
   #include <shellapi.h>
#endif
#endif



namespace user
{


   class document_interface;


} // namespace user


// Avoid mapping GetFileTitle to GetFileTitle[A/W]
#ifdef GetFileTitle
#undef GetFileTitle
inline int16_t APIENTRY GetFileTitle(const char * lpszFile, LPTSTR lpszTitle, WORD cbBuf)
#ifdef UNICODE
   { return ::GetFileTitleW(lpszFile, lpszTitle, cbBuf); }
#else
   { return ::GetFileTitleA(lpszFile, lpszTitle, cbBuf); }
#endif
#endif


#if (_WIN32_WINNT >= 0x501)
#include <uxtheme.h>
#include <vssym32.h>
#endif   // (_WIN32_WINNT >= 0x501)

#ifndef _CA_DLL
#pragma comment(lib, "uuid.lib")
#endif

#ifdef _INC_WINDOWSX
// The following names from WINDOWSX.H collide with names in this header
#undef subclass_window
#undef CopyRgn
#endif

//#include <htmlhelp.h>

#pragma warning( push )
#pragma warning( disable: 4121 )


/////////////////////////////////////////////////////////////////////////////
// Classes declared in this file

//::gen::object
   //base_exception
      //simple_exception
         class resource_exception;// Win resource failure exception
         class user_exception;    // Message Box alert and stop operation


      namespace ca
      {
         class graphics;                   // a Display Context / HDC wrapper
         class graphics_object;            // ::ca::graphics_sp drawing tool
         class bitmap;           // a bitmap
         class palette;          // a palette
         class rgn;
         class font;
         class pen;
         class brush;
         class window;            // a window
         class client_graphics;         // ::ca::graphics_sp for client of ::ca::window
         class window_graphics;         // ::ca::graphics_sp for entire ::ca::window
         class paint_graphics;          // embeddable BeginPaint struct helper
      }

      namespace userbase
      {
         class menu;                 // a menu
      }

   class command_target;            // a target for ::fontopus::user commands

   namespace user
   {
      class interaction;
      class edit_plain_text;            // Edit control
   } // namespace user


      class virtual_user_interface;
         class dialog;          // a dialog

         // standard windows controls
         class CStatic;          // Static control
         class simple_button;          // Button control
         class CListBox;         // ListBox control
            class CCheckListBox;// special listbox with checks
         class simple_combo_box;        // ComboBox control
         class CScrollBar;       // ScrollBar control

         // frame windows
         class frame_window;        // standard SDI frame
            class CMDIFrameWnd; // standard MDI frame
            class CMDIChildWnd; // standard MDI child
            class CMiniFrameWnd;// half-height caption frame wnd

         // views on a document
         class view;            // a ::view on a document
            class CScrollView;  // a scrolling ::view

            namespace gen
            {
               class thread;           // thread base class
               class application;          // application base class
            } // namespace gen

      class document_template;         // template for document creation
         class single_document_template;// SDI support
         class multiple_document_template; // MDI support

      class document;            // main document abstraction


// Helper classes
class cmd_ui;           // Menu/button enabling
//class CDataExchange;    // Data exchange and validation context
//class CCommandLineInfo; // CommandLine parsing helper
class document_manager;      // document_template manager object

enum __HELP_TYPE
{
   afxWinHelp = 0,
   afxHTMLHelp = 1
};



#ifdef DEBUG
// Diagnostic Output
CLASS_DECL_ca dump_context & operator<<(dump_context & dumpcontext, SIZE size);
CLASS_DECL_ca dump_context & operator<<(dump_context & dumpcontext, POINT point);
CLASS_DECL_ca dump_context & operator<<(dump_context & dumpcontext, const RECT& rect);
#endif //DEBUG

// Serialization
/*CLASS_DECL_ca CArchive& operator<<(CArchive& ar, SIZE size);
CLASS_DECL_ca CArchive& operator<<(CArchive& ar, POINT point);
CLASS_DECL_ca CArchive& operator<<(CArchive& ar, const RECT& rect);
CLASS_DECL_ca CArchive& operator>>(CArchive& ar, SIZE& size);
CLASS_DECL_ca CArchive& operator>>(CArchive& ar, POINT& point);
CLASS_DECL_ca CArchive& operator>>(CArchive& ar, RECT& rect);
*/






CLASS_DECL_ca void __get_gray_bitmap(::ca::application * papp, const ::ca::bitmap &rSrc, ::ca::bitmap *pDest, COLORREF crBackground);
CLASS_DECL_ca void __draw_gray_bitmap(::ca::application * papp, ::ca::graphics * pgraphics, int32_t x, int32_t y, const ::ca::bitmap &rSrc, COLORREF crBackground);
CLASS_DECL_ca void __get_dithered_bitmap(::ca::application * papp, const ::ca::bitmap &rSrc, ::ca::bitmap *pDest, COLORREF cr1, COLORREF cr2);
CLASS_DECL_ca void __draw_dithered_bitmap(::ca::application * papp, ::ca::graphics * pgraphics, int32_t x, int32_t y, const ::ca::bitmap &rSrc, COLORREF cr1, COLORREF cr2);


#include "ca/ca/ca_graphic_classes.h"



#include "gen_fixed_alloc.h"
#include "gen_request_signal.h"

#include "ca/visual/visual_const.h"

#include "gen_var_array.h"



#include "gen_command.h"
#include "gen_command_target.h"


typedef UINT (c_cdecl *__THREADPROC)(LPVOID);




CLASS_DECL_ca ::gen::thread* __begin_thread(::ca::application * papp, __THREADPROC pfnThreadProc, LPVOID pParam, ::ca::e_thread_priority epriority = ::ca::thread_priority_normal, UINT nStackSize = 0, uint32_t dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);
/* xxx CLASS_DECL_ca thread* __begin_thread(::ca::type_info pThreadClass,
   int32_t nPriority = THREAD_PRIORITY_NORMAL, UINT nStackSize = 0,
   uint32_t dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL); xxxx */

template < class THREAD_TYPE >
THREAD_TYPE * __begin_thread (::ca::application * papp, ::ca::e_thread_priority epriority = ::ca::thread_priority_normal, UINT nStackSize = 0, uint32_t dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL)
{
   THREAD_TYPE * pthread = new THREAD_TYPE(papp);
   pthread->begin(epriority, nStackSize, dwCreateFlags, lpSecurityAttrs);
   return pthread;
}



// Use instead of PostQuitMessage in OLE server applications
CLASS_DECL_ca void __post_quit_message(int32_t nExitCode);


class CRecentFileList;          // forward reference (see afxadv.h)


/*class CLASS_DECL_ca CCommandLineInfo : public ::gen::object
{
public:
   // Sets default values
   CCommandLineInfo();

   // plain char* version on UNICODE for source-code backwards compatibility
   virtual void ParseParam(const char* pszParam, bool bFlag, bool bLast);
#ifdef _UNICODE
   virtual void ParseParam(const char* pszParam, bool bFlag, bool bLast);
#endif

   bool m_bShowSplash;
   bool m_bRunEmbedded;
   bool m_bRunAutomated;
   enum { FileNew, FileOpen, FilePrint, FilePrintTo, FileDDE, AppRegister,
      AppUnregister, FileNothing = -1 } m_nShellCommand;

   // not valid for FileNew
   string m_strFileName;

   // valid only for FilePrintTo
   string m_strPrinterName;
   string m_strDriverName;
   string m_strPortName;

   ~CCommandLineInfo();
// Implementation
protected:
   void ParseParamFlag(const char* pszParam);
   void ParseParamNotFlag(const char* pszParam);
#ifdef _UNICODE
   void ParseParamNotFlag(const char* pszParam);
#endif
   void ParseLast(bool bLast);
};
*/
/////////////////////////////////////////////////////////////////////////////
// document_manager


/*CLASS_DECL_ca bool __delete_reg_key(const char * lpszKey);



CLASS_DECL_ca bool _API
__set_reg_key(const char * lpszKey, const char * lpszValue, const char * lpszValueName = NULL);

*/



#define ___MRU_COUNT   4      // default support for 4 entries in file MRU
#define ___MRU_MAX_COUNT 16   // currently allocated id range supports 16

#define ___SYSPOLICY_NOTINITIALIZED         0
#define ___SYSPOLICY_NORUN               1
#define ___SYSPOLICY_NODRIVES               2
#define ___SYSPOLICY_RESTRICTRUN            4
#define ___SYSPOLICY_NONETCONNECTDISCONNECTD   8
#define ___SYSPOLICY_NOENTIRENETWORK         16
#define ___SYSPOLICY_NORECENTDOCHISTORY      32
#define ___SYSPOLICY_NOCLOSE               64
#define ___SYSPOLICY_NOPLACESBAR            128
#define ___SYSPOLICY_NOBACKBUTTON            256
#define ___SYSPOLICY_NOFILEMRU            512

struct __system_policy_data
{
   const char * szPolicyName;
   uint32_t dwID;
};

struct __system_policies
{
   const char * szPolicyKey;
   __system_policy_data *pData;
};

#include "gen_file_manager_interface.h"



namespace user
{

   class user;


} // namespace user


#include "ca/ca/ca_graphics.h"


//#include "user_element_2d.h"
#include "ca/user/user_draw_interface.h"
#include "ca/user/user_mouse_focus.h"
#include "ca/user/user_keyboard_focus.h"
#include "ca/user/user_elemental.h"
#include "ca/user/user_window_util.h"
#include "ca/user/user_text_interface.h"
#include "ca/user/user_check_interface.h"
#include "ca/user/user_window_interface.h"
#include "ca/user/user_text_interface.h"
#include "ca/user/user_check_interface.h"
#include "ca/user/user_control_event.h"
#include "ca/user/user_control_property.h"
#include "ca/user/user_window_id.h"
#include "ca/user/user_interaction.h"
#include "ca/user/user_virtual_user_interface.h"


#include "ca/database/database_id.h"
#include "ca/database/database_key.h"

#include "ca/database/database_selection_item.h"
#include "ca/database/database_selection.h"
#include "ca/database/database_update_hint.h"


#include "ca/ca/ca_window.h"
#include "ca/ca/ca_message_window.h"









#include "ca/ca/ca_profiler.h"


#include "ca/ca/ca_window_draw.h"

#include "gen_timer.h"
#include "gen_timer_callback.h"
#include "gen_timer_window.h"
#include "gen_timer_listener.h"



#include "ca/ca/ca_live_signal.h"

#include "ca/ca/ca_thread.h"


#include "gen_thread.h"


#include "ca/ca/ca_history.h"
#include "ca/ca/ca_application_bias.h"
#include "ca/ca/ca_create_context.h"
#include "ca/ca/ca_job.h"
#include "ca/ca/ca_print_job.h"





#include "ca/ca/ca_section.h"


#pragma once

// former gen

#include "gen.h"


#include "gen_os_history.h"


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


#include "gen_international_locale_schema.h"


#include "gen_system.h"


#include "gen_wait_cursor.h"





/////////////////////////////////////////////////////////////////////////////
// Extra diagnostic tracing options

#ifdef DEBUG
extern CLASS_DECL_ca UINT g_uiTraceFlags;
#endif // DEBUG

#ifdef DEBUG
#define DECLARE___TRACE_CATEGORY( name ) extern CLASS_DECL_ca ::gen::trace::category name;
#else
#define DECLARE___TRACE_CATEGORY( name ) const uint_ptr name = 0;
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
namespace gen
{

   CLASS_DECL_ca void format_strings(string & rString, const char * lpszFormat, const char * const* rglpsz, int32_t nString);
   CLASS_DECL_ca bool extract_sub_string(string & rString, const char * lpszFullString, int32_t iSubString, char chSep = '\n');

}



#include "gen_os.h"



#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lp)                        ((int32_t)(int16_t)LOWORD(lp))
#endif
#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lp)                        ((int32_t)(int16_t)HIWORD(lp))
#endif


#include "gen_fixed_alloc.h"
#include "gen_process_data.h"


#include "ca/ca/ca_system.h"



#include "gen_exception.h"

#include "gen_request_interface.h"

#include "gen_tree_item_data.h"
#include "gen_tree_item.h"
#include "gen_tree_data.h"
#include "gen_tree.h"

#include "gen_fs_interface.h"

#include "gen_stream_base.h"

#include "gen_seekable.h"

#include "gen_reader.h"
#include "gen_writer.h"
#include "gen_stream.h"

#include "gen_byte_serializable.h"
#include "gen_byte_stream.h"
#include "gen_plain_text_serializable.h"

#include "gen_base_enum.h"




#include "gen_plain_text_stream.h"
#include "gen_output_stream_flush_interface.h"
#include "gen_stream2.h"


namespace primitive
{


   class memory;


} // namespace primitive


namespace gen
{


   class file_exception;
   struct file_status;


} // namespace gen


#include "gen_file.h"
#include "gen_file_composite.h"
#include "gen_file_exception.h"
#include "gen_file_status.h"



#include "gen_plain_text_string_stream.h"

#include "gen_file_stream.h"


// memory primitives
#include "ca/primitive/primitive_memory_base.h"
#include "ca/primitive/primitive_memory.h"
#include "ca/primitive/primitive_virtual_memory.h"
#include "ca/primitive/primitive_shared_memory.h"
#include "ca/primitive/primitive_memory_container.h"
#include "ca/primitive/primitive_memory_file.h"
#include "ca/primitive/primitive_shared_file.h"



#include "zlib/zlib.h"
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
//   WPARAM - uint32_t dwUserData - defined by ::fontopus::user
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
   gen::HRes QueryInterface)(REFIID, LPVOID*);

   gen::HRes read)(void *, ULONG, ULONG*);
   gen::HRes write)(const void *, ::primitive::memory_size cb, ::primitive::memory_size*);
   gen::HRes seek)(LARGE_INTEGER, uint32_t, ULARGE_INTEGER*);
   gen::HRes set_size)(ULARGE_INTEGER);
   gen::HRes CopyTo)(LPSTREAM, ULARGE_INTEGER, ULARGE_INTEGER*,
      ULARGE_INTEGER*);
   gen::HRes Commit)(uint32_t);
   gen::HRes Revert)();
   gen::HRes LockRegion)(ULARGE_INTEGER, ULARGE_INTEGER,uint32_t);
   gen::HRes UnlockRegion)(ULARGE_INTEGER, ULARGE_INTEGER, uint32_t);
   gen::HRes Stat)(STATSTG*, uint32_t);
   gen::HRes Clone)(LPSTREAM*);
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






#include "gen_definition.h"
#include "gen_types.h"

#include "gen_match.h"

// interfaces
#include "gen_progress_interface.h"


// from 7-zip
#include "gen_system_exception.h"
#include "gen_buffer.h"
#include "gen_dynamic_buffer.h"
#include "gen_in_buffer.h"
#include "gen_out_buffer.h"
#include "gen_circular_buffer.h"
#include "gen_bitl_decoder.h"
#include "gen_bitl_encoder.h"
#include "gen_bitm_decoder.h"
#include "gen_bitm_encoder.h"
#include "gen_limited_reader.h"
#include "gen_limited_input_stream.h"
#include "gen_clustered_input_stream.h"
#include "gen_limited_writer.h"

#include "gen_stream_binder.h"
#include "gen_locked_in_stream.h"
#include "gen_io_temp_buffer.h"
#include "gen_size_count_writer.h"
#include "gen_dynamic_buffered_writer.h"


#include "gen_buffered_file.h"
#include "gen_timeout_file.h"
#include "gen_edit_file.h"
#include "gen_text_file.h"
#include "gen_file_system.h"
#include "gen_resource.h"

#include "gen_simple_tree_item_data.h"
#include "gen_simple_tree_data.h"



// former gen start - former before concatenation of gen + gen + gen + gen

#include "gen_debug.h"

#include "ca/math/math_math.h"

#include "gen_math_rng.h"
#include "gen_math.h"
#include "gen_geometry.h"

#include "gen_equals.h"

#include "gen_iterator.h"
#include "gen_insert_iterator.h"
#include "gen_back_insert_iterator.h"
#include "gen_std_pair.h"


#include "gen_c_number.h"




#include "gen_muldiv32.h"

#define EX1ASSERT_VALID(pobj) ASSERT(pobj->Ex1IsObjValid())


#include "gen_simple_thread.h"
#include "gen_go_thread.h"



#include "gen_scoped_ptr.h"
#include "gen_logic.h"



#include "gen_parse.h"


#include "gen_template.h"


#include "ca/collection/collection_base_2array.h"
#include "ca/collection/collection_string_array.h"
#include "ca/collection/collection_stringa.h"
#include "ca/collection/collection_stringl.h"
#include "ca/collection/collection_string_sort_array.h"

#include "gen_string_tokenizer.h"


#include "gen_base_enum.h"
#include "gen_base_enum.h"
#include "gen_holder.h"
#include "gen_raw_pointer.h"
#include "gen_full_pointer.h"
#include "gen_time.h"
#include "gen_byte_serializable.h"
#include "ca/collection/collection_stringa.h"
#include "gen_var.h"
#include "gen_var_array.h"

#include "gen_pointer_manager.h"

#include "gen_pipe.h"
#include "gen_process.h"


#include "gen_savings.h"

#include "gen_command.h"
#include "gen_command_line.h"
#include "gen_command_thread.h"

#include "gen_base64.h"
#include "gen_system.h"


#include "gen_util1.h"


#include "gen_str.h"


#include "ca/primitive/primitive_int_biunique.h"


#include "gen_memory_file.h"
#include "gen_byte_stream_memory_file.h"


#include "gen_microtimer.h"

template <class TYPE>
inline bool IsRefNull(const TYPE & ref)
{
   return &ref == NULL;
}

#define NULL_REF(class) (*((class *) NULL))


CLASS_DECL_ca gen::byte_input_stream &  operator >>(gen::byte_input_stream & istream, string & string);
CLASS_DECL_ca gen::byte_output_stream &  operator <<(gen::byte_output_stream & ostream, const string & string);

#ifdef WIN32
#include "gen_file_association.h"
#endif


#include "gen_signal_thread.h"

#include "gen_international_locale_schema.h"

#include "gen_timer.h"

#include "gen_istring.h"


#include "gen_cregexp.h"
#include "gen_cregexp_util.h"



// former gen 



#pragma once


//#include "gen.h"


#include "gen_file_set.h"

#include "gen_folder_watch.h"

#include "gen_transfer_file.h"

#include "gen_application.h"
