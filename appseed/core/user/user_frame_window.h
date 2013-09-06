#pragma once


/////////////////////////////////////////////////////////////////////////////
// General style bits etc

// ControlBar styles
#define CBRS_ALIGN_LEFT     0x1000L
#define CBRS_ALIGN_TOP      0x2000L
#define CBRS_ALIGN_RIGHT    0x4000L
#define CBRS_ALIGN_BOTTOM   0x8000L
#define CBRS_ALIGN_ANY      0xF000L

#define CBRS_BORDER_LEFT    0x0100L
#define CBRS_BORDER_TOP     0x0200L
#define CBRS_BORDER_RIGHT   0x0400L
#define CBRS_BORDER_BOTTOM  0x0800L
#define CBRS_BORDER_ANY     0x0F00L

#define CBRS_TOOLTIPS       0x0010L
#define CBRS_FLYBY          0x0020L
#define CBRS_FLOAT_MULTI    0x0040L
#define CBRS_BORDER_3D      0x0080L
#define CBRS_HIDE_INPLACE   0x0008L
#define CBRS_SIZE_DYNAMIC   0x0004L
#define CBRS_SIZE_FIXED     0x0002L
#define CBRS_FLOATING       0x0001L

#define CBRS_GRIPPER        0x00400000L

#define CBRS_ORIENT_HORZ    (CBRS_ALIGN_TOP|CBRS_ALIGN_BOTTOM)
#define CBRS_ORIENT_VERT    (CBRS_ALIGN_LEFT|CBRS_ALIGN_RIGHT)
#define CBRS_ORIENT_ANY     (CBRS_ORIENT_HORZ|CBRS_ORIENT_VERT)

//#define CBRS_ALL            0x0040FFFFL
#define CBRS_ALL            0x0140FFFFL

// the CBRS_ style is made up of an alignment style and a draw border style
//  the alignment styles are mutually exclusive
//  the draw border styles may be combined
#define CBRS_NOALIGN        0x00000000L
#define CBRS_LEFT           (CBRS_ALIGN_LEFT|CBRS_BORDER_RIGHT)
#define CBRS_TOP            (CBRS_ALIGN_TOP|CBRS_BORDER_BOTTOM)
#define CBRS_RIGHT          (CBRS_ALIGN_RIGHT|CBRS_BORDER_LEFT)
#define CBRS_BOTTOM         (CBRS_ALIGN_BOTTOM|CBRS_BORDER_TOP)


// Frame ::ca2::window styles
#define FWS_ADDTOTITLE  0x00008000L // modify title based on content
#define FWS_PREFIXTITLE 0x00004000L // show document name before cast name
#define FWS_SNAPTOBARS  0x00002000L // snap size to size of contained bars


namespace user
{


   class view;
   class frame_window;
   class mdi_child_window;
   class control_bar;
   class document;
   class document_template;




   struct PrintPreviewState;  // forward reference (see afxext.h)
   class CReBar;               // forward reference (see afxext.h)

   class BaseDockBar;             // forward reference (see afxpriv.h)
   class mini_dock_frame_window;    // forward reference (see afxpriv.h)
   class CDockState;           // forward reference (see afxpriv.h)

   class OleFrameHook;        // forward reference (see ..\src\oleimpl2.h)

   /*struct create_context   // Creation information structure
   // All fields are optional and may be NULL
   {
   // for creating new views
   sp(type) m_typeinfoNewView; // runtime class of ::user::view to create or NULL
   sp(::user::document) m_pCurrentDoc;

   // for creating MDI children (mdi_child_window::LoadFrame)
   ::user::document_template* m_pNewDocTemplate;

   // for sharing ::user::view/frame state from the original ::user::view/frame
   sp(::user::view) m_pLastView;
   sp(::user::frame_window) m_pCurrentFrame;

   // Implementation
   create_context();
   };*/





   class CLASS_DECL_ca2 frame_window :
      virtual public ::user::frame_window_interface
   {
   public:



      ::id           m_idHelp;         // xxx mrs


      int32_t m_nWindow;  // general purpose ::ca2::window number - display as ":n"
      // -1 => unknown, 0 => only ::ca2::window viewing ::user::document_interface
      // 1 => first of many windows viewing ::user::document_interface, 2=> second

      HMENU m_hMenuDefault;       // default menu resource for this frame
      HACCEL m_hAccelTable;       // accelerator table
      uint32_t m_dwPromptContext;    // current help prompt context for message box
      bool m_bHelpMode;           // if TRUE, then Shift+F1 help mode is active
      sp(::user::frame_window) m_pNextFrameWnd; // next frame_window in cast global list
      rect m_rectBorder;         // for OLE border space negotiation

      pointer_list m_listControlBars; // array of all control bars that have this
      // ::ca2::window as their dock site
      int32_t m_nShowDelay;           // SW_ command for delay show/hide

      bool m_bFrameMoveEnable;


      string m_strMatterHelp;             // Help ID (0 for none, see HID_BASE_RESOURCE)
      UINT m_nIDTracking;         // tracking command ID or string IDS
      UINT m_nIDLastMessage;      // last displayed message string IDS
      sp(::user::view) m_pViewActive;       // current active ::user::view
      bool (CALLBACK* m_lpfnCloseProc)(sp(::user::frame_window) pFrameWnd);
      UINT m_cModalStack;         // BeginModalState depth
      comparable_array < sp(::user::interaction), sp(::user::interaction) > m_uiptraDisable;       // windows disabled because of BeginModalState
      HMENU m_hMenuAlt;           // menu to update to (NULL means default)
      string m_strTitle;         // default title (original)
      bool m_bInRecalcLayout;     // avoid recursion in layout
      sp(type) m_pFloatingFrameClass;
      static const uint32_t dwDockBarMap[4][2];


      frame_window();
      virtual ~frame_window();



      bool LoadAccelTable(const char * lpszResourceName);
      using ::user::frame_window_interface::create;
      virtual bool create(const char * lpszClassName,
         const char * lpszWindowName,
         uint32_t dwStyle = WS_OVERLAPPEDWINDOW,
         const RECT & rect = ::rect(0, 0, 0, 0),
         sp(::user::interaction) pParentWnd = NULL,        // != NULL for popups
         const char * lpszMenuName = NULL,
         uint32_t dwExStyle = 0,
         sp(create_context) pContext = NULL);

      // dynamic creation - load frame and associated resources
      virtual bool LoadFrame(const char * pszMatter,
         uint32_t dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,
         sp(::user::interaction) pParentWnd = NULL,
         sp(create_context) pContext = NULL);

      virtual bool ShowWindow(int32_t nCmdShow);


      // Attributes
      virtual sp(::user::document_interface) GetActiveDocument();

      // Active child ::user::view maintenance
      sp(::user::view) GetActiveView() const;           // active ::user::view or NULL
      void SetActiveView(sp(::user::view) pViewNew, bool bNotify = TRUE);
      // active ::user::view or NULL, bNotify == FALSE if focus should not be set

      // Active frame (for frames within frames -- MDI)
      virtual sp(::user::frame_window) GetActiveFrame();

      // For customizing the default messages on the status bar
      virtual void GetMessageString(UINT nID, string & rMessage) const;

      bool m_bAutoMenuEnable;
      // TRUE => menu items without handlers will be disabled

      bool IsTracking() const;

      // Operations
      virtual void layout();
      virtual void ActivateFrame(int32_t nCmdShow = -1);
      virtual void InitialUpdateFrame(sp(::user::document_interface) pDoc, bool bMakeVisible);
      virtual void InitialFramePosition(bool bForceRestore = false);
      void set_title(const char * lpszTitle);
      string get_title() const;

      // to set text of standard status bar
      void SetMessageText(const char * lpszText);
      void SetMessageText(UINT nID);

      ::user::control_bar* GetControlBar(UINT nID);

      // frame ::ca2::window based modality
      virtual void BeginModalState();
      virtual void EndModalState();
      bool InModalState() const;
      void ShowOwnedWindows(bool bShow);


      // Overridables
      virtual void OnSetPreviewMode(bool bPreview, CPrintPreviewState* pState);
      virtual sp(::user::interaction) GetMessageBar();

      // border space negotiation
      enum BorderCmd { borderGet = 1, borderRequest = 2, borderSet = 3 };
      virtual bool NegotiateBorderSpace(UINT nBorderCmd, LPRECT lpRectBorder);
      virtual bool OnCreateClient(LPCREATESTRUCT lpcs, sp(create_context) pContext);
      void OnContextHelp();   // for Shift+F1 help
      void OnUpdateControlBarMenu(cmd_ui* pCmdUI);
      bool OnBarCheck(UINT nID);

#ifdef WINDOWSEX
      virtual void LoadToolBar(id idToolBar, const char * pszToolBar, uint32_t dwCtrlStyle = TBSTYLE_FLAT, uint32_t dwStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP);
#else
      virtual void LoadToolBar(id idToolBar, const char * pszToolBar, uint32_t dwCtrlStyle = 0, uint32_t dwStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP);
#endif



      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
      virtual bool is_frame_window();
      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
      virtual void on_update_frame_title(bool bAddToTitle);
      virtual void OnUpdateFrameMenu(HMENU hMenuAlt);
      virtual HACCEL GetDefaultAccelerator();
      virtual void pre_translate_message(signal_details * pobj);

      // idle update of frame ::fontopus::user interface
      enum IdleFlags
      { idleMenu = 1, idleTitle = 2, idleNotify = 4, idleLayout = 8 };
      UINT m_nIdleFlags;          // set of bit flags for idle processing
      virtual void DelayUpdateFrameMenu(HMENU hMenuAlt);
      void DelayUpdateFrameTitle();
      void DelayRecalcLayout(bool bNotify = TRUE);

      // for Shift+F1 help support
      bool CanEnterHelpMode();
      virtual void ExitHelpMode();


      void UpdateFrameTitleForDocument(const char * lpszDocName);
      virtual bool pre_create_window(CREATESTRUCT& cs);
      virtual bool OnCommand(WPARAM wParam, LPARAM lParam);
      virtual void PostNcDestroy();   // default to delete this.
      int32_t OnCreateHelper(LPCREATESTRUCT lpcs, sp(create_context) pContext);
      void BringToTop(int32_t nCmdShow);
      // bring ::ca2::window to top for SW_ commands which affect z-order

      // implementation helpers for Shift+F1 help mode
      bool ProcessHelpMsg(MESSAGE & msg, uint32_t * pContext);
      oswindow SetHelpCapture(POINT point, bool * pbDescendant);

      // frame_window list management
      void AddFrameWnd();
      void RemoveFrameWnd();

      friend class ::ca2::window;  // for access to m_bModalDisable
      friend class CReBar; // for access to m_bInRecalcLayout

      virtual void install_message_handling(::ca2::message::dispatch * pinterface);

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnSysCommand);
      void OnClose();
      LRESULT OnPopMessageString(WPARAM wParam, LPARAM lParam);
      LRESULT OnSetMessageString(WPARAM wParam, LPARAM lParam);
      LRESULT OnHelpPromptAddr(WPARAM wParam, LPARAM lParam);
      void OnIdleUpdateCmdUI();
      void OnEnterIdle(UINT nWhy, sp(::user::interaction) pWho);
      void OnSetFocus(sp(::user::interaction) pOldWnd);
      void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
      void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
      void OnSize(UINT nType, int32_t cx, int32_t cy);
      bool OnEraseBkgnd(::draw2d::graphics * pgraphics);
      //void OnActivate(UINT nState, sp(::user::interaction) pWndOther, bool bMinimized);
      DECL_GEN_SIGNAL(_001OnActivate)
         DECL_GEN_SIGNAL(_001OnNcActivate)
         //bool OnNcActivate(bool bActive);
         void OnSysCommand(UINT nID, LPARAM lParam);
      bool OnQueryEndSession();
      void OnEndSession(bool bEnding);
#ifdef WINDOWSEX
      void OnDropFiles(HDROP hDropInfo);
#endif
      bool OnSetCursor(sp(::user::interaction) pWnd, UINT nHitTest, UINT message);
      //LRESULT OnCommandHelp(WPARAM wParam, LPARAM lParam);
      //LRESULT OnHelpHitTest(WPARAM wParam, LPARAM lParam);
      LRESULT OnActivateTopLevel(WPARAM wParam, LPARAM lParam);
      void OnEnable(bool bEnable);
      void OnPaletteChanged(sp(::user::interaction) pFocusWnd);
      bool OnQueryNewPalette();
      LRESULT OnDDEInitiate(WPARAM wParam, LPARAM lParam);
      LRESULT OnDDEExecute(WPARAM wParam, LPARAM lParam);
      LRESULT OnDDETerminate(WPARAM wParam, LPARAM lParam);
      LRESULT OnRegisteredMouseWheel(WPARAM wParam, LPARAM lParam);


      virtual bool on_simple_command(e_simple_command ecommand, lparam lparam, LRESULT & lresult);





      void CommonConstruct();





      virtual void _000OnDraw(::draw2d::graphics * pdc);


      virtual bool BaseOnControlEvent(::user::control_event * pevent);


//      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);

//      void OnUpdateControlBarMenu(cmd_ui * pcmdui);
//      bool OnBarCheck(UINT nID);
//      virtual void install_message_handling(::ca2::message::dispatch * pinterface);

      using ::uinteraction::frame::WorkSetListener::attach;

      //#ifdef DEBUG
//      virtual void assert_valid() const;
//      virtual void dump(dump_context & dumpcontext) const;
      //#endif


      // idle update of frame ::fontopus::user interface
  //    enum IdleFlags
//      { idleMenu = 1, idleTitle = 2, idleNotify = 4, idleLayout = 8 };
//      UINT m_nIdleFlags;          // set of bit flags for idle processing
//      virtual void DelayUpdateFrameMenu(HMENU hMenuAlt);
//      void DelayUpdateFrameTitle();
//      void DelayRecalcLayout(bool bNotify = TRUE);



      sp(::user::interaction) WindowDataGetWnd();
//      virtual bool pre_create_window(CREATESTRUCT& cs);


      friend class ::user::interaction;  // for access to m_bModalDisable
      friend class BaseReBar; // for access to m_bInRecalcLayout

//      DECL_GEN_SIGNAL(_001OnCreate)
         DECL_GEN_SIGNAL(_001OnIdleUpdateCmdUI)
         DECL_GEN_SIGNAL(_001OnSetFocus)
         DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(_001OnQueryEndSession)
         friend class user;

      mini_dock_frame_window* CreateFloatingFrame(uint32_t dwStyle);
      uint32_t CanDock(rect rect, uint32_t dwDockStyle, BaseDockBar** ppDockBar = NULL); // called by CDockContext
      void AddControlBar(::user::control_bar *pBar);
      void RemoveControlBar(::user::control_bar *pBar);
      void DockControlBar(::user::control_bar* pBar, BaseDockBar* pDockBar, LPCRECT lpRect = NULL);
      void ReDockControlBar(::user::control_bar* pBar, BaseDockBar* pDockBar, LPCRECT lpRect = NULL);
      virtual void NotifyFloatingWindows(uint32_t dwFlags);

   };



} // namepsce user