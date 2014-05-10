#pragma once


namespace user
{

   class tool_cmd_ui :
      public cmd_ui        // class private to this file !
   {
   public: // re-implementations only


      tool_cmd_ui(sp(::base::application) papp);
      virtual ~tool_cmd_ui();

      virtual void Enable(bool bOn);
      virtual void SetCheck(int32_t nCheck);
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

} // namespace user

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

// forward references required for ___THREAD_STATE definition
class FrameWnd;
class SimpleView;
class CToolTipCtrl;
class ::user::control_bar;


CLASS_DECL_CORE UINT _::core::GetMouseScrollLines();

*/
