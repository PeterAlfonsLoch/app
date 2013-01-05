#pragma once


#include "app/appseed/ca/ca/ca.h"




// Since ca2 API itself is built with wchar_t as a native type, it will not have
// the correct type info for types built with wchar_t typedef'd to unsigned
// short.  Make sure that the ::fontopus::user's cast builds this type info in this case.
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
namespace radix
{
   class object;
}
class base_exception;
class simple_exception;
class memory_exception;
class not_supported_exception;
class invalid_argument_exception;
namespace ex1
{
   class file_exception;
   class file;
}
class stdio_file;
namespace primitive
{
   class memory_file;
}
namespace ex1
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
#include "ca/gen/gen_c_number.h"

#include "ca/multithreading/multithreading_wait_result.h"
#include "ca/primitive/datetime/datetime_duration.h"
#include "ca/ex1/ex1_request_interface.h"
#include "ca/multithreading/multithreading_waitable.h"
#include "ca/primitive/primitive.h"


#include "ca/radix/radix_object.h"


#include "ca/gen/gen_definition.h"
#include "ca/gen/gen_common.h"
#include "ca/gen/gen_core.h"


#include "ca/radix/radix_heap.h"
#include "ca/radix/radix_plex_heap.h"
#include "ca/radix/radix_fixed_alloc.h"

#include "ca/primitive/primitive_simple_string.h"

#include "ca/gen/gen_ch.h"
#include "ca/gen/gen_str.h"

#include "ca/primitive/primitive_id.h"
#include "ca/primitive/primitive_string_format.h"
#include "ca/primitive/primitive_fixed_string.h"
#include "ca/primitive/primitive_string.h"
#include "ca/primitive/datetime/datetime_time.h"


#include "ca/primitive/primitive.h"

#include "ca/radix/radix_object.h"

#include "ca/gen/gen_hash.h"
#include "ca/gen/gen_equals.h"
#include "ca/gen/gen_compare.h"
#include "ca/gen/gen_less.h"
#include "ca/gen/gen.h"


#include "ca/gen/gen_template.h"


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



#include "ca/radix/radix.inl"


#undef __DATA
#define __DATA CLASS_DECL_ca


#ifdef ___ALL_WARNINGS
#pragma warning( pop )
#endif



#include "ca/radix/radix_allocate.h"
#include "ca/radix/radix_plex.h"

#include "ca/collection/collection.h"


#include "ca/radix/radix_plex_heap.h"



#include "ca/gen/gen_holder.h"
#include "ca/radix/radix_base.h"


#include "ca/ca/ca_interlocked_long.h"
#include "ca/ca/ca_interlocked_long_pulse.h"

#include "ca/multithreading/multithreading.h"

#include "ca/ca/ca_data.h"
#include "ca/ca/ca_data_container.h"
#include "ca/ca/ca_data_listener.h"

#include "ca/ca/ca_edit.h"

#include "ca/ca/ca_type_info.h"
#include "radix_factory.h"


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


#include "ca/gen/gen_base.h"
#include "radix_constraint.h"

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
inline short APIENTRY GetFileTitle(const char * lpszFile, LPTSTR lpszTitle, WORD cbBuf)
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

namespace radix
{
   namespace trace
   {
      enum e_category
      {
         category_AppMsg = 500,        // main message pump trace (includes DDE)
         category_WinMsg ,        // Windows message tracing
         category_CmdRouting ,    // Windows command routing trace
         category_Ole ,          // special OLE callback trace
         category_Database ,     // special database trace
         category_Internet ,     // special Internet client trace
         category_dumpContext ,   // traces from dump_context
         category_Memory ,      // generic non-kernel primitive::memory traces
         category_Html ,         // Html traces
         category_Socket ,      // socket traces
      };

   }
}

/////////////////////////////////////////////////////////////////////////////
// Classes declared in this file

//::radix::object
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

            namespace radix
            {
               class thread;           // thread base class
               class application;          // application base class
            } // namespace radix

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
CLASS_DECL_ca dump_context& operator<<(dump_context & dumpcontext, SIZE size);
CLASS_DECL_ca dump_context& operator<<(dump_context & dumpcontext, POINT point);
CLASS_DECL_ca dump_context& operator<<(dump_context & dumpcontext, const RECT& rect);
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



#include "radix_fixed_alloc.h"
#include "ca/gen/gen_request_signal.h"

#include "ca/visual/visual_const.h"

#include "ca/gen/gen_var_array.h"



#include "radix_command.h"
#include "radix_command_target.h"


typedef UINT (c_cdecl *__THREADPROC)(LPVOID);




CLASS_DECL_ca ::radix::thread* __begin_thread(::ca::application * papp, __THREADPROC pfnThreadProc, LPVOID pParam, ::ca::e_thread_priority epriority = ::ca::thread_priority_normal, UINT nStackSize = 0, DWORD dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);
/* xxx CLASS_DECL_ca thread* __begin_thread(::ca::type_info pThreadClass,
   int32_t nPriority = THREAD_PRIORITY_NORMAL, UINT nStackSize = 0,
   DWORD dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL); xxxx */

template < class THREAD_TYPE >
THREAD_TYPE * __begin_thread (::ca::application * papp, ::ca::e_thread_priority epriority = ::ca::thread_priority_normal, UINT nStackSize = 0, DWORD dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL)
{
   THREAD_TYPE * pthread = new THREAD_TYPE(papp);
   pthread->Begin(epriority, nStackSize, dwCreateFlags, lpSecurityAttrs);
   return pthread;
}



// Use instead of PostQuitMessage in OLE server applications
CLASS_DECL_ca void __post_quit_message(int32_t nExitCode);


class CRecentFileList;          // forward reference (see afxadv.h)


/*class CLASS_DECL_ca CCommandLineInfo : public ::radix::object
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
   DWORD dwID;
};

struct __system_policies
{
   const char * szPolicyKey;
   __system_policy_data *pData;
};

class CLASS_DECL_ca file_manager_interface :
   virtual public ::radix::object
{
public:
   file_manager_interface();
   virtual ~file_manager_interface();
   virtual bool do_prompt_file_name(var & varFile, UINT nIDSTitle, DWORD lFlags, bool bOpenFileDialog, document_template * ptemplate, ::user::document_interface * pdocument);

   bool initialize(::ca::application * papp);

};




namespace user
{

   class application;


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

#include "ca/gen/gen_timer.h"
#include "ca/gen/gen_timer_callback.h"
#include "ca/gen/gen_timer_window.h"
#include "ca/gen/gen_timer_listener.h"



#include "ca/ca/ca_live_signal.h"

#include "ca/ca/ca_thread.h"


#include "ca/radix/radix_thread.h"


#include "ca/ca/ca_history.h"
#include "ca/ca/ca_application_bias.h"
#include "ca/ca/ca_create_context.h"
#include "ca/ca/ca_job.h"
#include "ca/ca/ca_print_job.h"





#include "radix_application.h"


#include "ca/ca/ca_application_interface.h"
