#pragma once


#include "ca/visual/visual.h"


namespace html
{
   

   class data;


}


#include "user_document_interface.h"
#include "user_document.h"



#include "user_view.h"
#include "user_control.h"

#include "user_place_holder.h"
#include "user_place_holder_container.h"



/////////////////////////////////////////////////////////////////////////////
// frame_window - base class for SDI and other frame windows

// Frame ::ca::window styles
#define FWS_ADDTOTITLE  0x00008000L // modify title based on content
#define FWS_PREFIXTITLE 0x00004000L // show document name before cast name
#define FWS_SNAPTOBARS  0x00002000L // snap size to size of contained bars

struct CPrintPreviewState;  // forward reference (see afxext.h)
namespace userbase
{
   class control_bar;          // forward reference (see afxext.h)
}
class CReBar;               // forward reference (see afxext.h)
class simple_frame_window;
class CDockBar;             // forward reference (see afxpriv.h)
class mini_dock_frame_window;    // forward reference (see afxpriv.h)
class CDockState;           // forward reference (see afxpriv.h)


#include "user_frame_window_interface.h"
#include "user_frame_window.h"



/////////////////////////////////////////////////////////////////////////////
// MDI Support

/*class CLASS_DECL_ca CMDIFrameWnd : public frame_window
{
   // // DECLARE_DYNCREATE(CMDIFrameWnd)

public:
// Constructors
   CMDIFrameWnd();

// Operations
   void MDIActivate(::user::interaction* pWndActivate);
   CMDIChildWnd* MDIGetActive(BOOL* pbMaximized = NULL) const;
   void MDIIconArrange();
   void MDIMaximize(::user::interaction* pWnd);
   void MDINext();
   void MDIPrev();
   void MDIRestore(::user::interaction* pWnd);
   void MDITile();
   void MDICascade();
   void MDITile(int nType);
   void MDICascade(int nType);
   CMDIChildWnd* CreateNewChild(::ca::type_info pClass, const char * pszMatter,
      HMENU hMenu = NULL, HACCEL hAccel = NULL);

// Overridables
   // ca2 API 1.0 backward compatible CreateClient hook (called by OnCreateClient)
   virtual BOOL CreateClient(LPCREATESTRUCT lpCreateStruct);
   // customize if using an 'Window' menu with non-standard IDs
   virtual HMENU GetWindowMenuPopup(HMENU hMenuBar);

// Implementation
public:
   ::user::interaction * m_pguieMdiClient;       // MDI Client ::ca::window handle

#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   virtual BOOL LoadFrame(const char * pszMatter,
            DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,
            ::user::interaction* pParentWnd = NULL,
            ::ca::create_context* pContext = NULL);
   virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, ::ca::create_context* pContext);
   virtual void pre_translate_message(gen::signal_object * pobj);
   virtual void on_update_frame_title(BOOL bAddToTitle);
   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
   virtual void OnUpdateFrameMenu(HMENU hMenuAlt);
   virtual void DelayUpdateFrameMenu(HMENU hMenuAlt);
   virtual frame_window* GetActiveFrame();

protected:
   virtual LRESULT DefWindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam);
   virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

   DECL_GEN_SIGNAL(_001OnDestroy)
   void OnSize(UINT nType, int cx, int cy);
   void OnUpdateMDIWindowCmd(cmd_ui* pCmdUI);
   BOOL OnMDIWindowCmd(UINT nID);
   void OnWindowNew();
   LRESULT OnCommandHelp(WPARAM wParam, LPARAM lParam);
   void OnIdleUpdateCmdUI();
   LRESULT OnMenuChar(UINT nChar, UINT, ::userbase::menu*);
};

class CLASS_DECL_ca CMDIChildWnd : public frame_window
{
public:
   CMDIChildWnd();

   virtual BOOL create(const char * lpszClassName,
            const char * lpszWindowName,
            DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
            const RECT& rect = rectDefault,
            CMDIFrameWnd* pParentWnd = NULL,
            ::ca::create_context* pContext = NULL);

// Attributes
   CMDIFrameWnd* GetMDIFrame();

// Operations
   void MDIDestroy();
   void MDIActivate();
   void MDIMaximize();
   void MDIRestore();
   void SetHandles(HMENU hMenu, HACCEL hAccel);

// Implementation
protected:
   HMENU m_hMenuShared;        // menu when we are active

public:
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   virtual BOOL LoadFrame(const char * pszMatter, DWORD dwDefaultStyle,
               ::user::interaction* pParentWnd, ::ca::create_context* pContext = NULL);
      // 'pParentWnd' parameter is required for MDI Child
   virtual BOOL DestroyWindow();
   virtual void pre_translate_message(gen::signal_object * pobj);
   virtual void ActivateFrame(int nCmdShow = -1);
   virtual void OnUpdateFrameMenu(BOOL bActive, ::user::interaction* pActivateWnd,
      HMENU hMenuAlt);

   BOOL m_bPseudoInactive;     // TRUE if ::ca::window is MDI active according to
                        //  windows, but not according to ca2 API...

protected:
   virtual ::user::interaction* GetMessageBar();
   virtual void on_update_frame_title(BOOL bAddToTitle);
   virtual LRESULT DefWindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam);
   BOOL UpdateClientEdge(LPRECT lpRect = NULL);

   void OnMDIActivate(BOOL bActivate, ::user::interaction*, ::user::interaction*);
   int OnMouseActivate(::ca::window* pDesktopWnd, UINT nHitTest, UINT message);
   int OnCreate(LPCREATESTRUCT lpCreateStruct);
   BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
   void OnSize(UINT nType, int cx, int cy);
   void OnWindowPosChanging(LPWINDOWPOS lpWndPos);
   BOOL OnNcActivate(BOOL bActive);
   void OnDestroy();
};

/////////////////////////////////////////////////////////////////////////////
// CMiniFrameWnd

// MiniFrame ::ca::window styles
#define MFS_SYNCACTIVE      0x00000100L // syncronize activation w/ parent
#define MFS_4THICKFRAME     0x00000200L // thick frame all around (no tiles)
#define MFS_THICKFRAME      0x00000400L // use instead of WS_THICKFRAME
#define MFS_MOVEFRAME       0x00000800L // no sizing, just moving
#define MFS_BLOCKSYSMENU    0x00001000L // block hit testing on system menu

#pragma warning( disable: 4263 )
#pragma warning( disable: 4264 )
class CLASS_DECL_ca CMiniFrameWnd : public frame_window
{
public:


   CMiniFrameWnd();
   ~CMiniFrameWnd();


   virtual BOOL create(const char * lpClassName, const char * lpWindowName,
      DWORD dwStyle, const RECT& rect,
      virtual_user_interface* pParentWnd = NULL, UINT nID = 0);
   virtual BOOL CreateEx(DWORD dwExStyle, const char * lpClassName, const char * lpWindowName,
      DWORD dwStyle, const RECT& rect,
      virtual_user_interface* pParentWnd = NULL, UINT nID = 0);


   BOOL OnNcActivate(BOOL bActive);
   LRESULT OnNcHitTest(point point);
   void OnSysCommand(UINT nID, LPARAM lParam);
   void OnGetMinMaxInfo(MINMAXINFO* pMMI);
   LRESULT OnFloatStatus(WPARAM wParam, LPARAM lParam);
   LRESULT OnQueryCenterWnd(WPARAM wParam, LPARAM lParam);
   BOOL OnNcCreate(LPCREATESTRUCT lpcs);

public:
   static void PASCAL CalcBorders(LPRECT lpClientRect, DWORD dwStyle = 0, DWORD dwExStyle = 0);

protected:
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
   BOOL m_bSysTracking;
   BOOL m_bInSys;
   BOOL m_bActive;
   string m_strCaption;
};
#pragma warning( default: 4263 )
#pragma warning( default: 4264 )


typedef DWORD DROPEFFECT;
class COleDataObject;   // forward reference (see afxole.h)

*/




namespace win
{
   class CLASS_DECL_ca message
   {
   public:
      ::user::interaction *  m_pguie;
      UINT              m_uiMessage;
      WPARAM            m_wparam;
      LPARAM            m_lparam;
      LRESULT send();
      static UINT ThreadProcSendMessage(LPVOID lp);
      static void post(::user::interaction * puie, UINT uiMessage, WPARAM wparam, LPARAM lparam, int nPriority = 0);
   };

} // namespace win


#include "user_window_util.h"


#include "user_wait_message_dialog.h"
#include "user_message_box.h"
#include "user_network_configuration.h"
#include "user_shell.h"
#include "user_keyboard_layout.h"
#include "user_keyboard.h"
#include "user_keyboard_layout_cfg.h"


#include "user_document_template_interface.h"
#include "user_document_template.h"
#include "user_single_document_template.h"
#include "user_multiple_document_template.h"


#include "user_document_manager.h"


#include "user_data_exchange.h"
#include "user_form.h"
#include "user_form_callback.h"


#include "user_view_container.h"
#include "user_view_creator.h"

#include "user_job.h"


#include "user_application.h"



