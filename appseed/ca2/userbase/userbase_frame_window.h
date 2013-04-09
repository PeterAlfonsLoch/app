#pragma once


namespace userbase
{
   class view;
   class frame_window;
   class mdi_child_window;
   class control_bar;
   class document;
   class document_template;

} // namespace userbase



// Frame ::ca::window styles
#define FWS_ADDTOTITLE  0x00008000L // modify title based on content
#define FWS_PREFIXTITLE 0x00004000L // show document name before cast name
#define FWS_SNAPTOBARS  0x00002000L // snap size to size of contained bars

struct PrintPreviewState;  // forward reference (see afxext.h)
class CReBar;               // forward reference (see afxext.h)

class BaseDockBar;             // forward reference (see afxpriv.h)
class mini_dock_frame_window;    // forward reference (see afxpriv.h)
class CDockState;           // forward reference (see afxpriv.h)

class OleFrameHook;        // forward reference (see ..\src\oleimpl2.h)

/*struct create_context   // Creation information structure
   // All fields are optional and may be ::null()
{
   // for creating new views
   sp(::ca::type_info) m_typeinfoNewView; // runtime class of ::view to create or ::null()
   sp(::userbase::document) m_pCurrentDoc;

   // for creating MDI children (mdi_child_window::LoadFrame)
   ::userbase::document_template* m_pNewDocTemplate;

   // for sharing ::view/frame state from the original ::view/frame
   sp(::userbase::view) m_pLastView;
   sp(frame_window) m_pCurrentFrame;

// Implementation
   create_context();
};*/


namespace userbase
{

   class CLASS_DECL_ca2 frame_window :
      virtual public ::frame_window,
      virtual public frame_window_interface
   {
   public:


      frame_window();
      virtual ~frame_window();


      void CommonConstruct();


      virtual void on_delete(sp(::ca::ca) pca);


      virtual void _000OnDraw(::ca::graphics * pdc);


      virtual bool BaseOnControlEvent(::user::control_event * pevent);


      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);

      void OnUpdateControlBarMenu(cmd_ui * pcmdui);
      bool OnBarCheck(UINT nID);
      virtual void install_message_handling(::ca::message::dispatch * pinterface);

      using ::uinteraction::frame::WorkSetListener::attach;

   //#ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   //#endif


      // idle update of frame ::fontopus::user interface
      enum IdleFlags
         { idleMenu = 1, idleTitle = 2, idleNotify = 4, idleLayout = 8 };
      UINT m_nIdleFlags;          // set of bit flags for idle processing
      virtual void DelayUpdateFrameMenu(HMENU hMenuAlt);
      void DelayUpdateFrameTitle();
      void DelayRecalcLayout(bool bNotify = TRUE);



      sp(::user::interaction) WindowDataGetWnd();
      virtual bool pre_create_window(CREATESTRUCT& cs);


      friend class ::user::interaction;  // for access to m_bModalDisable
      friend class BaseReBar; // for access to m_bInRecalcLayout

      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnIdleUpdateCmdUI)
      DECL_GEN_SIGNAL(_001OnSetFocus)
      DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(_001OnQueryEndSession)
      friend class userbase;

      mini_dock_frame_window* CreateFloatingFrame(uint32_t dwStyle);
      uint32_t CanDock(rect rect, uint32_t dwDockStyle, BaseDockBar** ppDockBar = ::null()); // called by CDockContext
      void AddControlBar(::userbase::control_bar *pBar);
      void RemoveControlBar(::userbase::control_bar *pBar);
      void DockControlBar(::userbase::control_bar* pBar, BaseDockBar* pDockBar, LPCRECT lpRect = ::null());
      void ReDockControlBar(::userbase::control_bar* pBar, BaseDockBar* pDockBar, LPCRECT lpRect = ::null());
      virtual void NotifyFloatingWindows(uint32_t dwFlags);

   };



} // namepsce userbase