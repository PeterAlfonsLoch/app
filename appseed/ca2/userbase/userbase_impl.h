#pragma once

/*#ifdef _ApplicationFrameworkDLL
#define _WSTATIC_SUFFIX
#else
#define _WSTATIC_SUFFIX L"s"
#endif

#define _WUNICODE_SUFFIX L"W"

#ifndef _DEBUG
#define _WDEBUG_SUFFIX
#else
#define _WDEBUG_SUFFIX L"d"
#endif


#define AFX_WWNDCLASS(s) \
   L"Afx" s L"42" _WSTATIC_SUFFIX _WUNICODE_SUFFIX _WDEBUG_SUFFIX

#define AFX_WWND             AFX_WWNDCLASS(L"Wnd")
#define AFX_WWNDCONTROLBAR   AFX_WWNDCLASS(L"ControlBar")
#define AFX_WWNDMDIFRAME     AFX_WWNDCLASS(L"MDIFrame")
#define AFX_WWNDFRAMEORVIEW  AFX_WWNDCLASS(L"FrameOrView")
#define AFX_WWNDOLECONTROL   AFX_WWNDCLASS(L"OleControl")


extern const WCHAR _vfxWWnd[];
extern const WCHAR _vfxWWndControlBar[];
extern const WCHAR _vfxWWndMDIFrame[];
extern const WCHAR _vfxWWndFrameOrView[];
extern const WCHAR _vfxWWndOleControl[];

extern const CHAR _vfxWndFrameOrView[];




//#ifndef NORESOURCE

/*
 * Predefined Resource Types
 */
/*#define RTW_CURSOR           MAKEINTRESOURCEW(1)
#define RTW_BITMAP           MAKEINTRESOURCEW(2)
#define RTW_ICON             MAKEINTRESOURCEW(3)
#define RTW_MENU             MAKEINTRESOURCEW(4)
#define RTW_DIALOG           MAKEINTRESOURCEW(5)
#define RTW_STRING           MAKEINTRESOURCEW(6)
#define RTW_FONTDIR          MAKEINTRESOURCEW(7)
#define RTW_FONT             MAKEINTRESOURCEW(8)
#define RTW_ACCELERATOR      MAKEINTRESOURCEW(9)
#define RTW_RCDATA           MAKEINTRESOURCEW(10)
#define RTW_MESSAGETABLE     MAKEINTRESOURCEW(11)


#define RTW_TOOLBAR  MAKEINTRESOURCEW(241)
*/

namespace userbase
{

   class tool_cmd_ui : 
      public cmd_ui        // class private to this file !
   {
   public: // re-implementations only


      tool_cmd_ui(::ax::application * papp);
      virtual ~tool_cmd_ui();

      virtual void Enable(BOOL bOn);
      virtual void SetCheck(int nCheck);
      virtual void SetText(const char * lpszText);
   };

   struct tool_bar_data
   {
      WORD wVersion;
      WORD wWidth;
      WORD wHeight;
      WORD wItemCount;
      //WORD aItems[wItemCount]

      WORD* items()
         { return (WORD*)(this+1); }
   };

} // namespace userbase

/*

/////////////////////////////////////////////////////////////////////////////
// mirroring support

//WINBUG: some mirroring stuff will be in wingdi.h someday
#ifndef LAYOUT_RTL
#define LAYOUT_LTR                               0x00000000
#define LAYOUT_RTL                         0x00000001
#define NOMIRRORBITMAP                     0x80000000
#endif

//WINBUG: some mirroring stuff will be in winuser.h someday
#ifndef WS_EX_LAYOUTRTL
#define WS_EX_LAYOUTRTL                    0x00400000L
#endif



/////////////////////////////////////////////////////////////////////////////
// Thread global state

// forward references required for _AFX_THREAD_STATE definition
class FrameWnd;
class SimpleView;
class CToolTipCtrl;
class ::userbase::control_bar;


CLASS_DECL_ca UINT PASCAL _AfxGetMouseScrollLines();

*/