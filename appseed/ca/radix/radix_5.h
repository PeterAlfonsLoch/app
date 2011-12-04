#pragma once


#include "radix_2.h"







#define WM_VIEW (WM_USER + 1023)


#include "template/base.h"
#include "constraint.h"

#ifdef _WINDOWS
#ifndef _INC_SHELLAPI
   #include <shellapi.h>
#endif
#endif

#include "collection/collection.h"


#include "simple_list.h"

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
#undef SubclassWindow
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

enum AFX_HELP_TYPE
{
   afxWinHelp = 0,
   afxHTMLHelp = 1
};



#ifdef _DEBUG
// Diagnostic Output
CLASS_DECL_ca dump_context& operator<<(dump_context & dumpcontext, SIZE size);
CLASS_DECL_ca dump_context& operator<<(dump_context & dumpcontext, POINT point);
CLASS_DECL_ca dump_context& operator<<(dump_context & dumpcontext, const RECT& rect);
#endif //_DEBUG

// Serialization
/*CLASS_DECL_ca CArchive& operator<<(CArchive& ar, SIZE size);
CLASS_DECL_ca CArchive& operator<<(CArchive& ar, POINT point);
CLASS_DECL_ca CArchive& operator<<(CArchive& ar, const RECT& rect);
CLASS_DECL_ca CArchive& operator>>(CArchive& ar, SIZE& size);
CLASS_DECL_ca CArchive& operator>>(CArchive& ar, POINT& point);
CLASS_DECL_ca CArchive& operator>>(CArchive& ar, RECT& rect);
*/

// Use AfxFindResourceHandle to find resource in chain of extension DLLs
#ifndef _ApplicationFrameworkDLL
#define AfxFindResourceHandle(lpszResource, lpszType) AfxGetResourceHandle()
#else
CLASS_DECL_ca HINSTANCE AfxFindResourceHandle(const char * lpszName, const char * lpszType);
#endif



CLASS_DECL_ca void AfxThrowResourceException();
CLASS_DECL_ca void AfxThrowUserException();


CLASS_DECL_ca void AfxGetGrayBitmap(::ca::application * papp, const ::ca::bitmap &rSrc, ::ca::bitmap *pDest, COLORREF crBackground);
CLASS_DECL_ca void AfxDrawGrayBitmap(::ca::application * papp, ::ca::graphics * pgraphics, int x, int y, const ::ca::bitmap &rSrc, COLORREF crBackground);
CLASS_DECL_ca void AfxGetDitheredBitmap(::ca::application * papp, const ::ca::bitmap &rSrc, ::ca::bitmap *pDest, COLORREF cr1, COLORREF cr2);
CLASS_DECL_ca void AfxDrawDitheredBitmap(::ca::application * papp, ::ca::graphics * pgraphics, int x, int y, const ::ca::bitmap &rSrc, COLORREF cr1, COLORREF cr2);

#include "ca/ca_3_graphics.h"



#include "gen/gen_signal.h"

#include "visual/visual_00.h"

#include "command.h"
#include "command_target.h"


typedef UINT (AFX_CDECL *AFX_THREADPROC)(LPVOID);




CLASS_DECL_ca ::radix::thread* AfxBeginThread(::ca::application * papp, AFX_THREADPROC pfnThreadProc, LPVOID pParam,
   int nPriority = ::ca::thread_priority_normal, UINT nStackSize = 0,
   DWORD dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);
/* xxx CLASS_DECL_ca thread* AfxBeginThread(::ca::type_info pThreadClass,
   int nPriority = THREAD_PRIORITY_NORMAL, UINT nStackSize = 0,
   DWORD dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL); xxxx */

template < class THREAD_TYPE >
THREAD_TYPE * AfxBeginThread (::ca::application * papp, int nPriority = ::ca::thread_priority_normal, UINT nStackSize = 0,
   DWORD dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL)
{
   THREAD_TYPE * pthread = new THREAD_TYPE(papp);
   pthread->Begin(nPriority, nStackSize, dwCreateFlags, lpSecurityAttrs);
   return pthread;
}



// Use instead of PostQuitMessage in OLE server applications
CLASS_DECL_ca void AfxPostQuitMessage(int nExitCode);


class CRecentFileList;          // forward reference (see afxadv.h)


/*class CLASS_DECL_ca CCommandLineInfo : public ::radix::object
{
public:
   // Sets default values
   CCommandLineInfo();

   // plain char* version on UNICODE for source-code backwards compatibility
   virtual void ParseParam(const char* pszParam, BOOL bFlag, BOOL bLast);
#ifdef _UNICODE
   virtual void ParseParam(const char* pszParam, BOOL bFlag, BOOL bLast);
#endif

   BOOL m_bShowSplash;
   BOOL m_bRunEmbedded;
   BOOL m_bRunAutomated;
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
   void ParseLast(BOOL bLast);
};
*/
/////////////////////////////////////////////////////////////////////////////
// document_manager


CLASS_DECL_ca BOOL _AfxDeleteRegKey(const char * lpszKey);



CLASS_DECL_ca BOOL AFXAPI
_AfxSetRegKey(const char * lpszKey, const char * lpszValue, const char * lpszValueName = NULL);




/////////////////////////////////////////////////////////////////////////////
// application - the root of all Windows applications

#define _AFX_MRU_COUNT   4      // default support for 4 entries in file MRU
#define _AFX_MRU_MAX_COUNT 16   // currently allocated id range supports 16

#define _AFX_SYSPOLICY_NOTINITIALIZED         0
#define _AFX_SYSPOLICY_NORUN               1
#define _AFX_SYSPOLICY_NODRIVES               2
#define _AFX_SYSPOLICY_RESTRICTRUN            4
#define _AFX_SYSPOLICY_NONETCONNECTDISCONNECTD   8
#define _AFX_SYSPOLICY_NOENTIRENETWORK         16
#define _AFX_SYSPOLICY_NORECENTDOCHISTORY      32
#define _AFX_SYSPOLICY_NOCLOSE               64
#define _AFX_SYSPOLICY_NOPLACESBAR            128
#define _AFX_SYSPOLICY_NOBACKBUTTON            256
#define _AFX_SYSPOLICY_NOFILEMRU            512

struct _AfxSysPolicyData
{
   const char * szPolicyName;
   DWORD dwID;
};

struct _AfxSysPolicies
{
   const char * szPolicyKey;
   _AfxSysPolicyData *pData;
};

class CLASS_DECL_ca file_manager_interface :
   virtual public ::radix::object
{
public:
   file_manager_interface();
   virtual ~file_manager_interface();
   virtual BOOL do_prompt_file_name(string & fileName, UINT nIDSTitle, DWORD lFlags,
      BOOL bOpenFileDialog, document_template * ptemplate);

   bool initialize(::ca::application * papp);

};


#include "visual/visual_01.h"
#include "user/user_01.h"
#include "ca/ca_2.h"

#include "radix_os_history.h"


namespace windows
{
   template < class APP >
   inline ::ca::application * cast(APP * papp)
   {
      return *(dynamic_cast < ::ca::application * > (papp));
   }
}


#include "radix_application.h"
#include "radix_system.h"


#include "wait_cursor.h"





/////////////////////////////////////////////////////////////////////////////
// Extra diagnostic tracing options

#ifdef _DEBUG
extern CLASS_DECL_ca UINT afxTraceFlags;
#endif // _DEBUG

#ifdef _DEBUG
#define DECLARE_AFX_TRACE_CATEGORY( name ) extern CLASS_DECL_ca _template::CTraceCategory name;
#else
#define DECLARE_AFX_TRACE_CATEGORY( name ) const DWORD_PTR name = 0;
#endif


//////////////////////////////////////////////////////////////////////////////
// MessageBox helpers

//CLASS_DECL_ca void AfxFormatString1(string & rString, UINT nIDS, const char * lpsz1);
//CLASS_DECL_ca void AfxFormatString2(string & rString, UINT nIDS,
//            const char * lpsz1, const char * lpsz2);
/*CLASS_DECL_ca int System.simple_message_box(const char * lpszText, UINT nType = MB_OK,
            UINT nIDHelp = 0);*/
/*CLASS_DECL_ca int System.simple_message_box(UINT nIDPrompt, UINT nType = MB_OK,
            UINT nIDHelp = (UINT)-1);*/

// Implementation string helpers
//CLASS_DECL_ca void AfxFormatStrings(string & rString, UINT nIDS,
//            const char * const* rglpsz, int nString);
CLASS_DECL_ca void AfxFormatStrings(string & rString, const char * lpszFormat,
            const char * const* rglpsz, int nString);
CLASS_DECL_ca BOOL AfxExtractSubString(string & rString, const char * lpszFullString,
            int iSubString, char chSep = '\n');

/////////////////////////////////////////////////////////////////////////////
// Special target variant APIs

#ifdef _ApplicationFrameworkDLL
   #include "dll_.h"
#endif

// Windows Version compatibility (obsolete)
#define AfxEnableWin30Compatibility()
#define AfxEnableWin31Compatibility()
#define AfxEnableWin40Compatibility()


/////////////////////////////////////////////////////////////////////////////
// Use version 1.0 of the RichEdit control

#define _RICHEDIT_VER 0x0210

/////////////////////////////////////////////////////////////////////////////
// Inline function declarations

#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#endif
#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))
#endif


#include "fixed_alloc.h"
#include "process_data.h"


#include "ca/ca_system.h"

#ifndef _AFX_NO_SYNC_SUPPORT
   #include "multithreading/multithreading.h"
#endif

#include "implementation.h"
