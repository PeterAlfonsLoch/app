#pragma once

class CLASS_DECL_CA2_DEVEDGE devedgeFrame : public SimpleFrameWindow
{
	
public:
	devedgeFrame(::ca::application * papp);

   void _001InstallMessageHandling(igui::win::message::Dispatch * pinterface);

   DECL_GEN_SIGNAL(_001OnClose)
// Attributes
public:
   //BaseMenuMessageHandler        m_menuhook;
   string                     m_strAnimatedStatusBarText;
   int                        m_iAnimateStep;
   ImageList *                m_pimagelist;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(screencaptureFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, CAFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void ShowControlBars(bool bShow);
	void AnimateStatusBar();
	void SetAnimatedStatusBarText(LPCTSTR lpcsz);
	bool IsFullScreen();
	void ToggleFullScreen();
	virtual void WfiOnFullScreen(bool bFullScreen);
	virtual ~devedgeFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	
   rect             m_FullScreenWindowRect;
//   SimpleMenuBar     m_menubar;
//   SimpleDialogBar   m_dialogbar;
//xxx	SimpleReBar       m_wndReBar;
//	SimpleStatusBar   m_statusbar;
//   SimpleToolBar     m_toolbar;
//   SimpleToolBar     m_toolbarView;


   //bool              m_bFullScreen;

// Generated message map functions
protected:
	//{{AFX_MSG(screencaptureFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewFullScreen();
	afx_msg void OnUpdateViewFullScreen(CCmdUI* pCmdUI);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnClose();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnTimer(UINT nIDEvent);
   afx_msg void OnShowWindow(BOOL bShow, UINT nStatus) ;
	afx_msg void OnNcPaint();
	afx_msg void OnTogglecustomframe();
	afx_msg void OnUpdateTogglecustomframe(CCmdUI* pCmdUI);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnInitMenu(CMenu* pMenu);
	afx_msg void OnActivate(UINT nState, base_wnd* pWndOther, BOOL bMinimized);
	afx_msg BOOL OnCopyData(base_wnd * pwnd, COPYDATASTRUCT* pcds);
	DECLARE_MESSAGE_MAP()
};

