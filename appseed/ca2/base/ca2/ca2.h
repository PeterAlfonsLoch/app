#pragma once


#include "app/appseed/ca/ca/ca.h"


#include "nodeapp/operational_system/operational_system.h"

#pragma warning(disable: 4251)  // using non-exported as public in exported


#ifdef _CA2_LIBRARY
   #define CLASS_DECL_ca2  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_ca2  CLASS_DECL_IMPORT
#endif


extern CLASS_DECL_ca2 vsstring g_strNote;


namespace plane
{

   class application;


} // namespace plane


#undef App
#define planeApp(pcaapp) (*pcaapp->m_pappThis)
#define planeApplication (planeApp(m_papp))
#define App(pcaapp) planeApp(pcaapp)
#define Application (App(m_papp))



#if defined(WIN32) && !defined(VC6) && ! defined(VC71)
#include <vadefs.h>
#endif


#include "ca2_enum.h"
#include "ca2_ca2.h"
#include "ca2_live_object.h"
#include "ca2_log.h"


#include "ca2_main_init_data.h"




#pragma warning(disable: 4250)






#include "base/api/api_rotate.h"


#define rgba_get_r(rgba)      ((byte)(rgba & 0xff))
#define rgba_get_g(rgba)      ((byte)((rgba >> 8) & 0xff))
#define rgba_get_b(rgba)      ((byte)((rgba >> 16) & 0xff))
#define rgba_get_a(rgba)      ((byte)((rgba >> 24) & 0xff))

#ifdef WINDOWS
#include <crtdbg.h>
#else
#include "base/api/api_debug.h"
#endif


#if defined(MACOS)

#include "base/macos/macos.h"

#elif defined(METROWIN)

#include "base/metrowin/metrowin.h"

#elif defined(LINUX)

#include "base/linux/os.h"

#endif


#include "primitive/count.h"


#include "base/api/api.h"







// former ca2

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
namespace ca2
{
   class object;
}
class base_exception;
class simple_exception;
class memory_exception;
class not_supported_exception;
class invalid_argument_exception;
namespace ca2
{
   class file_exception;
   class file;
}
class stdio_file;
namespace primitive
{
   class memory_file;
}
namespace ca2
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

#define FALSE   0
#define TRUE    1

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

// warnings caerated with common ca2 API/Windows code
#pragma warning(disable: 4134)  // message map member fxn casts
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


#include "base/exception/exception.h"




#include "primitive/primitive_numeric_info.h"
#include "ca2_c_number.h"

#include "base/multithreading/multithreading_wait_result.h"
#include "primitive/datetime/datetime_duration.h"
#include "ca2_request_interface.h"
#include "base/multithreading/multithreading_waitable.h"
#include "primitive/primitive.h"


#include "ca2_object.h"


#include "ca2_definition.h"
#include "ca2_common.h"
#include "ca2_core.h"


#include "ca2_heap.h"
#include "ca2_plex_heap.h"
#include "ca2_fixed_alloc.h"

#include "primitive/primitive_simple_string.h"

#include "ca2_ch.h"
#include "ca2_str.h"
#include "ca2_strn.h"
#include "ca2_hex.h"


#include "primitive/primitive_id.h"
#include "primitive/primitive_string_format.h"
#include "primitive/primitive_fixed_string.h"
#include "primitive/primitive_string_interface.h"
#include "primitive/primitive_string_composite.h"
#include "primitive/primitive_string.h"
#include "primitive/datetime/datetime_time.h"


#include "primitive/primitive.h"


#include "ca2_object.h"

#include "ca2_hash.h"
#include "ca2_equals.h"
#include "ca2_compare.h"
#include "ca2_less.h"


#include "ca2_template.h"




#include "ca2_smart_pointer_query.h"



#define ASSERT_KINDOF(class_name, object) ASSERT(base < class_name > ::bases(object))
#define DYNAMIC_DOWNCAST(class_name, object) (dynamic_cast < class_name * > (object))
#define STATIC_DOWNCAST(class_name, object) (dynamic_cast<class_name*>(object))
#define STATIC_DOWNCAST_T(class_name, T1, object) (static_cast<class_name<T1>*>(::ca2::StaticDownCast(RUNTIME_CLASS_T(class_name, T1), object)))
#define STATIC_DOWNCAST_T2(class_name, T1, T2, object) (static_cast<class_name<T1, T2>*>(::ca2::StaticDownCast(RUNTIME_CLASS_T2(class_name, T1, T2), object)))

// optional bit for schema number that enables object versioning
#define VERSIONABLE_SCHEMA  (0x80000000)

/////////////////////////////////////////////////////////////////////////////
// other helpers

// zero fill everything after the vtbl pointer
#define __ZERO_INIT_OBJECT(base_class) memset(((base_class*)this)+1, 0, sizeof(*this) - sizeof(class base_class));



#include "ca2.inl"


#undef __DATA
#define __DATA CLASS_DECL_ca2


#ifdef ___ALL_WARNINGS
#pragma warning( pop )
#endif



#include "ca2_allocate.h"
#include "ca2_plex.h"

#include "base/collection/collection.h"


#include "ca2_plex_heap.h"



#include "ca2_base.h"


#include "ca2_interlocked_long.h"
#include "ca2_interlocked_long_pulse.h"

#include "base/multithreading/multithreading.h"

#include "ca2_data.h"
#include "ca2_data_container.h"
#include "ca2_data_listener.h"

#include "ca2_edit.h"

#include "ca2_type_info.h"
#include "ca2_factory.h"

#include "ca2_string_buffer.h"
#include "user/user_str.h"


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


#include "ca2_base.h"
#include "ca2_constraint.h"

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

//::ca2::object
   //base_exception
      //simple_exception
         class resource_exception;// Win resource failure exception
         class user_exception;    // Message Box alert and stop operation


      namespace draw2d
      {
         class graphics;                   // a Display Context / HDC wrapper
         class object;            // ::draw2d::graphics_sp drawing tool
         class bitmap;           // a bitmap
         class palette;          // a palette
         class region;
         class font;
         class pen;
         class brush;
         class memory_graphics;         // ::draw2d::graphics_sp for client of ::ca2::window
         class window_graphics;         // ::draw2d::graphics_sp for entire ::ca2::window
         class paint_graphics;          // embeddable BeginPaint struct helper
      }

      namespace ca2
      {
         class window;            // a window
         class job;
      }

   class command_target;            // a target for ::fontopus::user commands

   namespace user
   {
      class menu;                 // a menu
      class interaction;
      class edit_plain_text;            // Edit control
      class view;            // a ::user::view on a document
      class document_manager;      // document_template manager object
      class frame_window;        // standard SDI frame
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
            class CMDIFrameWnd; // standard MDI frame
            class CMDIChildWnd; // standard MDI child
            class CMiniFrameWnd;// half-height caption frame wnd

         // views on a document
            class CScrollView;  // a scrolling ::user::view

            namespace ca2
            {
               class thread;           // thread base class
               class application;          // application base class
            } // namespace ca2

//      class document_template;         // template for document creation
         class single_document_template;// SDI support
         class multiple_document_template; // MDI support

//      class document;            // main document abstraction


// Helper classes
class cmd_ui;           // Menu/button enabling
//class CDataExchange;    // Data exchange and validation context
//class CCommandLineInfo; // CommandLine parsing helper

enum __HELP_TYPE
{
   afxWinHelp = 0,
   afxHTMLHelp = 1
};



#ifdef DEBUG
// Diagnostic Output
CLASS_DECL_ca2 dump_context & operator<<(dump_context & dumpcontext, SIZE size);
CLASS_DECL_ca2 dump_context & operator<<(dump_context & dumpcontext, POINT point);
CLASS_DECL_ca2 dump_context & operator<<(dump_context & dumpcontext, const RECT& rect);
#endif //DEBUG

// Serialization
/*CLASS_DECL_ca2 CArchive& operator<<(CArchive& ar, SIZE size);
CLASS_DECL_ca2 CArchive& operator<<(CArchive& ar, POINT point);
CLASS_DECL_ca2 CArchive& operator<<(CArchive& ar, const RECT& rect);
CLASS_DECL_ca2 CArchive& operator>>(CArchive& ar, SIZE& size);
CLASS_DECL_ca2 CArchive& operator>>(CArchive& ar, POINT& point);
CLASS_DECL_ca2 CArchive& operator>>(CArchive& ar, RECT& rect);
*/






CLASS_DECL_ca2 void __get_gray_bitmap(sp(::ca2::application) papp, const ::draw2d::bitmap &rSrc, ::draw2d::bitmap *pDest, COLORREF crBackground);
CLASS_DECL_ca2 void __draw_gray_bitmap(sp(::ca2::application) papp, ::draw2d::graphics * pgraphics, int32_t x, int32_t y, const ::draw2d::bitmap &rSrc, COLORREF crBackground);
CLASS_DECL_ca2 void __get_dithered_bitmap(sp(::ca2::application) papp, const ::draw2d::bitmap &rSrc, ::draw2d::bitmap *pDest, COLORREF cr1, COLORREF cr2);
CLASS_DECL_ca2 void __draw_dithered_bitmap(sp(::ca2::application) papp, ::draw2d::graphics * pgraphics, int32_t x, int32_t y, const ::draw2d::bitmap &rSrc, COLORREF cr1, COLORREF cr2);


#include "graphics/draw2d/draw2d.h"



#include "ca2_fixed_alloc.h"
#include "ca2_request_signal.h"

#include "graphics/visual/visual_const.h"

#include "ca2_var_array.h"



#include "ca2_command.h"
#include "ca2_command_target.h"


typedef UINT (c_cdecl *__THREADPROC)(LPVOID);




CLASS_DECL_ca2 ::ca2::thread* __begin_thread(sp(::ca2::application) papp, __THREADPROC pfnThreadProc, LPVOID pParam, int32_t epriority = ::ca2::scheduling_priority_normal, UINT nStackSize = 0, uint32_t dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);
/* xxx CLASS_DECL_ca2 thread* __begin_thread(sp(::ca2::type_info) pThreadClass,
   int32_t nPriority = scheduling_priority_normal, UINT nStackSize = 0,
   uint32_t dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL); xxxx */

template < class THREAD_TYPE >
THREAD_TYPE * __begin_thread (sp(::ca2::application) papp, int32_t epriority = ::ca2::scheduling_priority_normal, UINT nStackSize = 0, uint32_t dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL)
{
   THREAD_TYPE * pthread = new THREAD_TYPE(papp);
   pthread->begin(epriority, nStackSize, dwCreateFlags, lpSecurityAttrs);
   return pthread;
}



// Use instead of PostQuitMessage in OLE server applications
CLASS_DECL_ca2 void __post_quit_message(int32_t nExitCode);


class CRecentFileList;          // forward reference (see afxadv.h)


/*class CLASS_DECL_ca2 CCommandLineInfo : public ::ca2::object
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
// ::user::document_manager


/*CLASS_DECL_ca2 bool __delete_reg_key(const char * lpszKey);



CLASS_DECL_ca2 bool _API
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

//#include "ca2_file_manager_interface.h"



namespace user
{

   class user;


} // namespace user


//#include "user_element_2d.h"
#include "user/user_draw_interface.h"
#include "user/user_mouse_focus.h"
#include "user/user_keyboard_focus.h"
#include "user/user_elemental.h"
#include "user/user_window_util.h"
#include "user/user_text_interface.h"
#include "user/user_check_interface.h"
#include "user/user_window_interface.h"
#include "user/user_text_interface.h"
#include "user/user_check_interface.h"
#include "user/user_control_event.h"
#include "user/user_control_property.h"
#include "user/user_window_id.h"
#include "user/user_interaction.h"
#include "user/user_virtual_user_interface.h"


#include "database/database_id.h"
#include "database/database_key.h"

#include "database/database_selection_item.h"
#include "database/database_selection.h"
#include "database/database_update_hint.h"


#include "ca2_window.h"
#include "ca2_message_window.h"









#include "ca2_profiler.h"
#include "ca2_timer.h"
#include "ca2_timer_callback.h"
#include "ca2_timer_window.h"
#include "ca2_timer_listener.h"
#include "ca2_live_signal.h"
#include "ca2_thread.h"
#include "ca2_window_draw.h"
#include "ca2_history.h"
#include "ca2_application_bias.h"
#include "ca2_create_context.h"
#include "ca2_job.h"
#include "ca2_print_job.h"




#include "ca2_section.h"
#include "ca2_section_container.h"


// former ca2

#include "ca2_os_history.h"


namespace windows
{
   template < class APP >
   inline ::ca2::application & cast(APP * papp)
   {
      return *((papp));
   }
}



#include "base/collection/collection_sort_array.h"


#include "primitive/primitive_id_space.h"
#include "primitive/primitive_id_space.h"


#include "ca2_international_locale_schema.h"


#include "ca2_wait_cursor.h"





/////////////////////////////////////////////////////////////////////////////
// Extra diagnostic tracing options

#ifdef DEBUG
extern CLASS_DECL_ca2 UINT g_uiTraceFlags;
#endif // DEBUG

#ifdef DEBUG
#define DECLARE___TRACE_CATEGORY( name ) extern CLASS_DECL_ca2 ::ca2::trace::category name;
#else
#define DECLARE___TRACE_CATEGORY( name ) const uint_ptr name = 0;
#endif


//////////////////////////////////////////////////////////////////////////////
// MessageBox helpers

//CLASS_DECL_ca2 void ::ca2::FormatString1(string & rString, UINT nIDS, const char * lpsz1);
//CLASS_DECL_ca2 void ::ca2::FormatString2(string & rString, UINT nIDS,
//            const char * lpsz1, const char * lpsz2);
/*CLASS_DECL_ca2 int32_t System.simple_message_box(const char * lpszText, UINT nType = MB_OK,
            UINT nIDHelp = 0);*/
/*CLASS_DECL_ca2 int32_t System.simple_message_box(UINT nIDPrompt, UINT nType = MB_OK,
            UINT nIDHelp = (UINT)-1);*/

// Implementation string helpers
//CLASS_DECL_ca2 void __format_strings(string & rString, UINT nIDS,
//            const char * const* rglpsz, int32_t nString);
namespace ca2
{

   CLASS_DECL_ca2 void format_strings(string & rString, const char * lpszFormat, const char * const* rglpsz, int32_t nString);
   CLASS_DECL_ca2 bool extract_sub_string(string & rString, const char * lpszFullString, int32_t iSubString, char chSep = '\n');

}



#include "base/os/os.h"



#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lp)                        ((int32_t)(int16_t)LOWORD(lp))
#endif
#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lp)                        ((int32_t)(int16_t)HIWORD(lp))
#endif


#include "ca2_fixed_alloc.h"
#include "ca2_process_data.h"


#include "ca2_exception.h"

#include "ca2_request_interface.h"

#include "ca2_tree_item_data.h"
#include "ca2_tree_item.h"
#include "ca2_tree_data.h"
#include "ca2_tree.h"

#include "ca2_fs_interface.h"

#include "ca2_stream_base.h"

#include "ca2_seekable.h"

#include "ca2_reader.h"
#include "ca2_writer.h"
#include "ca2_stream.h"

#include "ca2_byte_serializable.h"
#include "ca2_byte_stream.h"
#include "ca2_plain_text_serializable.h"

#include "ca2_base_enum.h"




#include "ca2_plain_text_stream.h"
#include "ca2_output_stream_flush_interface.h"
#include "ca2_stream2.h"


namespace primitive
{


   class memory;


} // namespace primitive


namespace ca2
{


   class file_exception;
   struct file_status;


} // namespace ca2


#include "ca2_file.h"
#include "ca2_file_composite.h"
#include "ca2_file_exception.h"
#include "ca2_file_status.h"



#include "ca2_plain_text_string_stream.h"

#include "ca2_file_stream.h"


// memory primitives
#include "primitive/primitive_memory_base.h"
#include "primitive/primitive_memory.h"
#include "primitive/primitive_virtual_memory.h"
#include "primitive/primitive_shared_memory.h"
#include "primitive/primitive_memory_container.h"
#include "primitive/primitive_memory_file.h"
#include "primitive/primitive_shared_file.h"



#include "zlib/zlib.h"
#include "database/sqlite/sqlite.h"



#include "base/libcharguess/libcharguess.h"





// Implementation structures
struct __SIZEPARENTPARAMS;    // control bar implementationproperca2_property.h

// Classes declared in this file

   //::draw2d::graphics_sp
      class preview_dc;               // Virtual DC for print preview

   //command_target
      //::ca2::window
         //::user::view
            class CPreviewView;     // Print preview ::user::view
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
   // E900 -> EEFF standard ::ca2::window controls/components
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
#define WM_RECALCPARENT     0x0368  // force layout on frame ::ca2::window
                           //  (only for inplace frame windows)
#define WM_SIZECHILD        0x0369  // special notify from COleResizeBar
                           // wParam = ID of child ::ca2::window
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
//   m_dwPromptContext from the associated frame ::ca2::window. This is used
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

// WM_FORWARDMSG - used by ca2 to forward a message to another ::ca2::window for processing
//   WPARAM - uint32_t dwUserData - defined by ::fontopus::user
//   LPARAM - LPMESSAGE pMsg - a pointer to the MESSAGE structure
//   return value - 0 if the message was not processed, nonzero if it was
#define WM_FORWARDMSG      0x037F

// like ON_MESSAGE but no return value
#define ON_MESSAGE_VOID(message, memberFxn) \
   { message, 0, 0, 0, ::ca2::Sig_vv, \
      (__PMSG)(__PMSGW)(void (__MSG_CALL ::ca2::window::*)())&memberFxn },

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

CLASS_DECL_ca2 void __reposition_window(__SIZEPARENTPARAMS* lpLayout, sp(::user::interaction) oswindow, LPCRECT lpRect);

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

// ::ca2::BSTR2ABTSR
// ::ca2::TaskStringA2W
// ::ca2::TaskStringW2A

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
class CLASS_DECL_ca2 CArchiveStream : public IStream
{
public:
   CArchiveStream(CArchive* pArchive);

// Implementation
   CArchive* m_pArchive;

   STDMETHOD_(ULONG, AddRef)();
   STDMETHOD_(ULONG, Release)();
   ::ca2::HRes QueryInterface)(REFIID, LPVOID*);

   ::ca2::HRes read)(void *, ULONG, ULONG*);
   ::ca2::HRes write)(const void *, ::primitive::memory_size cb, ::primitive::memory_size*);
   ::ca2::HRes seek)(LARGE_INTEGER, uint32_t, ULARGE_INTEGER*);
   ::ca2::HRes set_size)(ULARGE_INTEGER);
   ::ca2::HRes CopyTo)(LPSTREAM, ULARGE_INTEGER, ULARGE_INTEGER*,
      ULARGE_INTEGER*);
   ::ca2::HRes Commit)(uint32_t);
   ::ca2::HRes Revert)();
   ::ca2::HRes LockRegion)(ULARGE_INTEGER, ULARGE_INTEGER,uint32_t);
   ::ca2::HRes UnlockRegion)(ULARGE_INTEGER, ULARGE_INTEGER, uint32_t);
   ::ca2::HRes Stat)(STATSTG*, uint32_t);
   ::ca2::HRes Clone)(LPSTREAM*);
};
*/
/////////////////////////////////////////////////////////////////////////////
// Global UNICODE<>ANSI translation helpers

CLASS_DECL_ca2 void ::ca2::BSTR2String(string* pStr, BSTR bstr);

#if !defined(_UNICODE)
CLASS_DECL_ca2 BSTR ::ca2::BSTR2ABSTR(BSTR bstrW);
CLASS_DECL_ca2 wchar_t * ::ca2::TaskStringA2W(const char * lpa);
CLASS_DECL_ca2 char * ::ca2::TaskStringW2A(const wchar_t * lpw);
#endif

#endif // __AFXPRIV2_H__DISP__
#endif // __AFXDISP_H__

/////////////////////////////////////////////////////////////////////////////






#include "ca2_definition.h"
#include "ca2_types.h"

#include "ca2_match.h"

// interfaces
#include "ca2_progress_interface.h"


// from 7-zip
#include "ca2_system_exception.h"
#include "ca2_buffer.h"
#include "ca2_dynamic_buffer.h"
#include "ca2_in_buffer.h"
#include "ca2_out_buffer.h"
#include "ca2_circular_buffer.h"
#include "ca2_bitl_decoder.h"
#include "ca2_bitl_encoder.h"
#include "ca2_bitm_decoder.h"
#include "ca2_bitm_encoder.h"
#include "ca2_limited_reader.h"
#include "ca2_limited_input_stream.h"
#include "ca2_clustered_input_stream.h"
#include "ca2_limited_writer.h"

#include "ca2_stream_binder.h"
#include "ca2_locked_in_stream.h"
#include "ca2_io_temp_buffer.h"
#include "ca2_size_count_writer.h"
#include "ca2_dynamic_buffered_writer.h"


#include "ca2_buffered_file.h"
#include "ca2_timeout_file.h"
#include "ca2_edit_file.h"
#include "ca2_text_file.h"
//#include "ca2_file_system.h"
#include "ca2_resource.h"

#include "ca2_simple_tree_item_data.h"
#include "ca2_simple_tree_data.h"



// former ca2 start - former before concatenation of ca2 + ca2 + ca2 + ca2

#include "ca2_debug.h"

#include "math/math_math.h"

#include "ca2_math_rng.h"
#include "ca2_math.h"
#include "ca2_geometry.h"

#include "ca2_equals.h"

#include "ca2_iterator.h"
#include "ca2_insert_iterator.h"
#include "ca2_back_insert_iterator.h"
#include "ca2_std_pair.h"


#include "ca2_c_number.h"




#include "ca2_muldiv32.h"

#define EX1ASSERT_VALID(pobj) ASSERT(pobj->Ex1IsObjValid())


#include "ca2_simple_thread.h"
#include "ca2_go_thread.h"



//#include "ca2_scoped_ptr.h"
#include "ca2_logic.h"



#include "ca2_parse.h"


#include "ca2_template.h"


#include "base/collection/collection_base_2array.h"
#include "base/collection/collection_string_array.h"
#include "base/collection/collection_stringa.h"
#include "base/collection/collection_stringl.h"
#include "base/collection/collection_string_sort_array.h"

#include "ca2_string_tokenizer.h"


#include "ca2_base_enum.h"
#include "ca2_base_enum.h"
//#include "ca2_raw_pointer.h"
//#include "ca2_full_pointer.h"
//#include "ca2_time.h"
#include "ca2_byte_serializable.h"
#include "base/collection/collection_stringa.h"
#include "ca2_var.h"
#include "ca2_var_array.h"

#include "ca2_pipe.h"
#include "ca2_process.h"


#include "ca2_savings.h"

#include "ca2_command.h"
#include "ca2_command_line.h"
#include "ca2_command_thread.h"

#include "ca2_base64.h"

#include "ca2_util1.h"




#include "primitive/primitive_int_biunique.h"


//#include "ca2_memory_file.h"
#include "ca2_byte_stream_memory_file.h"


#include "ca2_microtimer.h"

template <class TYPE>
inline bool is_null(const TYPE & ref)
{
   return &ref == NULL;
}

#define NULL_REF(class) (*((class *) NULL))


CLASS_DECL_ca2 ::ca2::byte_input_stream &  operator >>(::ca2::byte_input_stream & istream, string & string);
CLASS_DECL_ca2 ::ca2::byte_output_stream &  operator <<(::ca2::byte_output_stream & ostream, const string & string);

#ifdef WIN32
#include "ca2_file_association.h"
#endif


#include "ca2_signal_thread.h"

#include "ca2_international_locale_schema.h"

#include "ca2_timer.h"

#include "ca2_istring.h"


#include "ca2_cregexp.h"
#include "ca2_cregexp_util.h"





#include "ca2_file_set.h"

#include "ca2_folder_watch.h"

#include "ca2_transfer_file.h"


class document_interface;


class main_frame;


typedef sp(::ca2::application) (* LP_GET_NEW_APP) ();


namespace ca2
{


   class command_line;


} // namespace ca2

namespace visual
{


   class icon;


} // namespace visual



namespace math
{


   class math;


} // namespace math


namespace geometry
{


   class geometry;


} // namespace geometry


#if defined(LINUX) || defined(MACOS)

typedef ::visual::icon * HICON;

#endif




#pragma once


class file_system;
typedef ::ca::smart_pointer < file_system > file_system_sp;
class Ex1FactoryImpl;




namespace lemon
{


   class array;


} // namespace lemon




#include "ca2_trace.h"



#include "math/calculator/calculator.h"
#include "base/xml/xml.h"
#include "net/sockets/sockets.h"
#include "user/colorertake5/colorertake5.h"

#include "graphics/html/html.h"


#include "ca2_definition.h"
#include "ca2_debug.h"



namespace ca2
{


   class application;


} // namespace ca2


#include "base/crypto/crypto.h"


#include "ca2_file_application.h"
#include "ca2_file_system.h"
#include "ca2_dir_application.h"
#include "ca2_dir_system.h"
#include "ca2_edit_file.h"
#include "ca2_stra.h"
#include "ca2_url_domain.h"
#include "ca2_url.h"


#include "ca2_service.h"
#include "ca2_machine_event_central.h"


#include "base/install/install.h"


#include "ca2_os.h"





#include "ca2_datetime.h"




#include "ca2_library.h"


#include "base/xml/xml_data.h"


#include "filesystem/filehandler/filehandler.h"








#include "compress/compress.h"
#include "programming/javascript/javascript.h"

// former ca2 - changed to ca2 on 2013-02-21
////////////////////////////////////////////////////////////////
// ca2api
// Layer level 5
// Project named ca2api002_00002
// Namespace ca8




#include "ca2_compress.h"
#include "ca2_patch.h"
#include "ca2_copydesk.h"
#include "ca2_crypt.h"
#include "ca2_email.h"
#include "ca2_http.h"
#include "ca2_http_application.h"
#include "ca2_http_system.h"
#include "ca2_http_get_socket.h"
#include "ca2_ip_enum.h"
#include "ca2_port_forward.h"


#include "ca2_oauth.h"
#include "ca2_twit.h"

#include "ca2_process_section.h"






#include "programming/dynamic_source/dynamic_source.h"





#include "graphics/html/html2.h"
#include "user/userex/userex.h"



#include "filesystem/filemanager/filemanager.h"

#include "net/usernet/usernet.h"
#include "user/fontopus/fontopus.h"
#include "net/usermail/usermail.h"


#include "net/hi5/hi5_net.h"

#include "ca2_application.h"




#include "ca2_session.h"
#include "ca2_system.h"


