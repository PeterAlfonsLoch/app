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



class CLASS_DECL_ca frame_window :
   virtual public ::user::frame_window_interface
{
public:


   static const rect rectDefault;
   int m_nWindow;  // general purpose ::ca::window number - display as ":n"
               // -1 => unknown, 0 => only ::ca::window viewing ::user::document_interface
               // 1 => first of many windows viewing ::user::document_interface, 2=> second

   HMENU m_hMenuDefault;       // default menu resource for this frame
   HACCEL m_hAccelTable;       // accelerator table
   DWORD m_dwPromptContext;    // current help prompt context for message box
   BOOL m_bHelpMode;           // if TRUE, then Shift+F1 help mode is active
   frame_window* m_pNextFrameWnd; // next frame_window in cast global list
   rect m_rectBorder;         // for OLE border space negotiation

   pointer_list m_listControlBars; // base_array of all control bars that have this
                        // ::ca::window as their dock site
   int m_nShowDelay;           // SW_ command for delay show/hide

   bool m_bFrameMoveEnable;


   string m_strMatterHelp;             // Help ID (0 for none, see HID_BASE_RESOURCE)
   UINT m_nIDTracking;         // tracking command ID or string IDS
   UINT m_nIDLastMessage;      // last displayed message string IDS
   ph(::view) m_pViewActive;       // current active ::view
   BOOL (CALLBACK* m_lpfnCloseProc)(frame_window* pFrameWnd);
   UINT m_cModalStack;         // BeginModalState depth
   ::user::interaction ** m_phWndDisable;       // windows disabled because of BeginModalState
   HMENU m_hMenuAlt;           // menu to update to (NULL means default)
   string m_strTitle;         // default title (original)
   BOOL m_bInRecalcLayout;     // avoid recursion in layout
   ::ca::type_info m_pFloatingFrameClass;
   static const DWORD dwDockBarMap[4][2];


   frame_window();
   virtual ~frame_window();


   BOOL LoadAccelTable(const char * lpszResourceName);
   using user::frame_window_interface::create;
   virtual BOOL create(const char * lpszClassName,
            const char * lpszWindowName,
            DWORD dwStyle = WS_OVERLAPPEDWINDOW,
            const RECT& rect = rectDefault,
            ::user::interaction* pParentWnd = NULL,        // != NULL for popups
            const char * lpszMenuName = NULL,
            DWORD dwExStyle = 0,
            ::ca::create_context* pContext = NULL);

   // dynamic creation - load frame and associated resources
   virtual BOOL LoadFrame(const char * pszMatter,
            DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,
            ::user::interaction* pParentWnd = NULL,
            ::ca::create_context* pContext = NULL);

   virtual BOOL ShowWindow(int nCmdShow);


// Attributes
   virtual ::user::document_interface * GetActiveDocument();

   // Active child ::view maintenance
   ::view * GetActiveView() const;           // active ::view or NULL
   void SetActiveView(::view * pViewNew, BOOL bNotify = TRUE);
      // active ::view or NULL, bNotify == FALSE if focus should not be set

   // Active frame (for frames within frames -- MDI)
   virtual frame_window* GetActiveFrame();

   // For customizing the default messages on the status bar
   virtual void GetMessageString(UINT nID, string & rMessage) const;

   BOOL m_bAutoMenuEnable;
      // TRUE => menu items without handlers will be disabled

   BOOL IsTracking() const;

// Operations
   virtual void layout();
   virtual void ActivateFrame(int nCmdShow = -1);
   virtual void InitialUpdateFrame(::user::document_interface * pDoc, BOOL bMakeVisible);
   virtual void InitialFramePosition(bool bForceRestore = false);
   void set_title(const char * lpszTitle);
   string get_title() const;

   // to set text of standard status bar
   void SetMessageText(const char * lpszText);
   void SetMessageText(UINT nID);

   ::userbase::control_bar* GetControlBar(UINT nID);

   // frame ::ca::window based modality
   virtual void BeginModalState();
   virtual void EndModalState();
   BOOL InModalState() const;
   void ShowOwnedWindows(BOOL bShow);


// Overridables
   virtual void OnSetPreviewMode(BOOL bPreview, CPrintPreviewState* pState);
   virtual ::user::interaction * GetMessageBar();

   // border space negotiation
   enum BorderCmd { borderGet = 1, borderRequest = 2, borderSet = 3 };
   virtual BOOL NegotiateBorderSpace(UINT nBorderCmd, LPRECT lpRectBorder);
   virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, ::ca::create_context* pContext);
   void OnContextHelp();   // for Shift+F1 help
   void OnUpdateControlBarMenu(cmd_ui* pCmdUI);
   BOOL OnBarCheck(UINT nID);
   virtual void on_delete(::ca::ca * poc);

#ifdef WINDOWS
   virtual void LoadToolBar(id idToolBar, const char * pszToolBar, DWORD dwCtrlStyle = TBSTYLE_FLAT, DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP);
#else
   virtual void LoadToolBar(id idToolBar, const char * pszToolBar, DWORD dwCtrlStyle = 0, DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP);
#endif



   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
   virtual BOOL IsFrameWnd();
   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
   virtual void on_update_frame_title(BOOL bAddToTitle);
   virtual void OnUpdateFrameMenu(HMENU hMenuAlt);
   virtual HACCEL GetDefaultAccelerator();
   virtual void pre_translate_message(gen::signal_object * pobj);

   // idle update of frame ::fontopus::user interface
   enum IdleFlags
      { idleMenu = 1, idleTitle = 2, idleNotify = 4, idleLayout = 8 };
   UINT m_nIdleFlags;          // set of bit flags for idle processing
   virtual void DelayUpdateFrameMenu(HMENU hMenuAlt);
   void DelayUpdateFrameTitle();
   void DelayRecalcLayout(BOOL bNotify = TRUE);

   // for Shift+F1 help support
   BOOL CanEnterHelpMode();
   virtual void ExitHelpMode();


   void UpdateFrameTitleForDocument(const char * lpszDocName);
   virtual const char * GetIconWndClass(DWORD dwDefaultStyle, const char * pszMatter);
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
   virtual void PostNcDestroy();   // default to delete this.
   int OnCreateHelper(LPCREATESTRUCT lpcs, ::ca::create_context* pContext);
   void BringToTop(int nCmdShow);
      // bring ::ca::window to top for SW_ commands which affect z-order

   // implementation helpers for Shift+F1 help mode
   BOOL ProcessHelpMsg(MSG& msg, DWORD* pContext);
   HWND SetHelpCapture(POINT point, BOOL* pbDescendant);

   // frame_window list management
   void AddFrameWnd();
   void RemoveFrameWnd();

   friend class ::ca::window;  // for access to m_bModalDisable
   friend class CReBar; // for access to m_bInRecalcLayout

   virtual void install_message_handling(::gen::message::dispatch * pinterface);

   DECL_GEN_SIGNAL(_001OnCreate);
   DECL_GEN_SIGNAL(_001OnDestroy);
   DECL_GEN_SIGNAL(_001OnSysCommand);
   void OnClose();
   LRESULT OnPopMessageString(WPARAM wParam, LPARAM lParam);
   LRESULT OnSetMessageString(WPARAM wParam, LPARAM lParam);
   LRESULT OnHelpPromptAddr(WPARAM wParam, LPARAM lParam);
   void OnIdleUpdateCmdUI();
   void OnEnterIdle(UINT nWhy, ::user::interaction* pWho);
   void OnSetFocus(::user::interaction* pOldWnd);
   void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
   void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
   void OnSize(UINT nType, int cx, int cy);
   BOOL OnEraseBkgnd(::ca::graphics * pgraphics);
   //void OnActivate(UINT nState, ::user::interaction* pWndOther, BOOL bMinimized);
   DECL_GEN_SIGNAL(_001OnActivate)
   DECL_GEN_SIGNAL(_001OnNcActivate)
   //BOOL OnNcActivate(BOOL bActive);
   void OnSysCommand(UINT nID, LPARAM lParam);
   BOOL OnQueryEndSession();
   void OnEndSession(BOOL bEnding);
   void OnDropFiles(HDROP hDropInfo);
   BOOL OnSetCursor(::user::interaction* pWnd, UINT nHitTest, UINT message);
   //LRESULT OnCommandHelp(WPARAM wParam, LPARAM lParam);
   //LRESULT OnHelpHitTest(WPARAM wParam, LPARAM lParam);
   LRESULT OnActivateTopLevel(WPARAM wParam, LPARAM lParam);
   void OnEnable(BOOL bEnable);
   void OnPaletteChanged(::user::interaction* pFocusWnd);
   BOOL OnQueryNewPalette();
   LRESULT OnDDEInitiate(WPARAM wParam, LPARAM lParam);
   LRESULT OnDDEExecute(WPARAM wParam, LPARAM lParam);
   LRESULT OnDDETerminate(WPARAM wParam, LPARAM lParam);
   LRESULT OnRegisteredMouseWheel(WPARAM wParam, LPARAM lParam);

   friend class ::radix::application;


};


