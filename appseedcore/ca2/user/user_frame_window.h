#pragma once

class CLASS_DECL_ca frame_window :
   virtual public user::frame_window_interface
{
public:
   
   
   static const rect rectDefault;


   frame_window();
   virtual ~frame_window();


   BOOL LoadAccelTable(const char * lpszResourceName);
   virtual BOOL create(const char * lpszClassName,
            const char * lpszWindowName,
            DWORD dwStyle = WS_OVERLAPPEDWINDOW,
            const RECT& rect = rectDefault,
            ::user::interaction* pParentWnd = NULL,        // != NULL for popups
            const char * lpszMenuName = NULL,
            DWORD dwExStyle = 0,
            create_context* pContext = NULL);

   // dynamic creation - load frame and associated resources
   virtual BOOL LoadFrame(const char * pszMatter,
            DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,
            ::user::interaction* pParentWnd = NULL,
            create_context* pContext = NULL);

   virtual BOOL ShowWindow(int nCmdShow);


// Attributes
   virtual ::document * GetActiveDocument();

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
   virtual void InitialUpdateFrame(document * pDoc, BOOL bMakeVisible);
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
   enum BorderCmd
      { borderGet = 1, borderRequest = 2, borderSet = 3 };
   virtual BOOL NegotiateBorderSpace(UINT nBorderCmd, LPRECT lpRectBorder);

   virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, create_context* pContext);

   afx_msg void OnContextHelp();   // for Shift+F1 help
   afx_msg void OnUpdateControlBarMenu(cmd_ui* pCmdUI);
   afx_msg BOOL OnBarCheck(UINT nID);
   virtual void on_delete(::ca::ca * poc);

   int m_nWindow;  // general purpose ::ca::window number - display as ":n"
               // -1 => unknown, 0 => only ::ca::window viewing document
               // 1 => first of many windows viewing document, 2=> second

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


protected:
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

public:
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif
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

   // implementation helpers
public:
   void UpdateFrameTitleForDocument(const char * lpszDocName);
protected:
   virtual const char * GetIconWndClass(DWORD dwDefaultStyle, const char * pszMatter);
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
   virtual void PostNcDestroy();   // default to delete this.
   int OnCreateHelper(LPCREATESTRUCT lpcs, create_context* pContext);
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

   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

   DECL_GEN_SIGNAL(_001OnCreate);
   DECL_GEN_SIGNAL(_001OnDestroy);
   DECL_GEN_SIGNAL(_001OnSysCommand);
   afx_msg void OnClose();
   afx_msg LRESULT OnPopMessageString(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnSetMessageString(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnHelpPromptAddr(WPARAM wParam, LPARAM lParam);
   afx_msg void OnIdleUpdateCmdUI();
   afx_msg void OnEnterIdle(UINT nWhy, ::user::interaction* pWho);
   afx_msg void OnSetFocus(::user::interaction* pOldWnd);
   afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
   afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
   afx_msg void OnSize(UINT nType, int cx, int cy);
   afx_msg BOOL OnEraseBkgnd(::ca::graphics * pgraphics);
   //afx_msg void OnActivate(UINT nState, ::user::interaction* pWndOther, BOOL bMinimized);
   DECL_GEN_SIGNAL(_001OnActivate)
   DECL_GEN_SIGNAL(_001OnNcActivate)
   //afx_msg BOOL OnNcActivate(BOOL bActive);
   afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
   afx_msg BOOL OnQueryEndSession();
   afx_msg void OnEndSession(BOOL bEnding);
   afx_msg void OnDropFiles(HDROP hDropInfo);
   afx_msg BOOL OnSetCursor(::user::interaction* pWnd, UINT nHitTest, UINT message);
   //afx_msg LRESULT OnCommandHelp(WPARAM wParam, LPARAM lParam);
   //afx_msg LRESULT OnHelpHitTest(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnActivateTopLevel(WPARAM wParam, LPARAM lParam);
   afx_msg void OnEnable(BOOL bEnable);
   afx_msg void OnPaletteChanged(::user::interaction* pFocusWnd);
   afx_msg BOOL OnQueryNewPalette();
   afx_msg LRESULT OnDDEInitiate(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnDDEExecute(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnDDETerminate(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnRegisteredMouseWheel(WPARAM wParam, LPARAM lParam);

   friend class ::radix::application;
};
