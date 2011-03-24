#pragma once

class CLASS_DECL_CA2_WINSERVICE_1 winservice_1_frame : public SimpleFrameWindow
{
public:
	winservice_1_frame(::ca::application * papp);
	
   string                     m_strAnimatedStatusBarText;
   bool                       m_bAutoHideOnOutClick;
   int                        m_iAnimateStep;
   image_list *                m_pimagelist;
   bool m_bTimerHide;
   bool m_bTimerOn;
   SimpleToolBar              m_toolbar;
   EPosition                  m_eposition;
   bool                       m_bMoveDrag;
   bool                       m_bLControl;

   virtual void _001InstallMessageHandling(igui::win::message::Dispatch * pinterface);

// Operations
public:
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg); 
public:
	void ShowControlBars(bool bShow);
	void AnimateStatusBar();
	void SetAnimatedStatusBarText(LPCTSTR lpcsz);
	bool IsFullScreen();
	void ToggleFullScreen();
	virtual void WfiOnFullScreen(bool bFullScreen);
	virtual ~winservice_1_frame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

   static LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);
   void MouseMessage(int nCode, WPARAM wParam, LPARAM lParam);
   static LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam);
   void LowLevelMouseMessage(int nCode, WPARAM wParam, LPARAM lParam);
   bool MouseHook();
   bool MouseUnhook();


   bool m_bHoverMouse;
   DWORD m_dwLastHover;

   void OnHoverAction(bool bShowWinActionArea);
   
   void ToFront();

protected:  // control bar embedded members
	
   base_rect             m_FullScreenWindowRect;
protected:


	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewFullScreen();
	afx_msg void OnUpdateViewFullScreen(CCmdUI* pCmdUI);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnClose();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	DECL_GEN_SIGNAL(_001OnTimer);
   afx_msg void OnShowWindow(BOOL bShow, UINT nStatus) ;
	afx_msg void OnNcPaint();
	afx_msg void OnTogglecustomframe();
	afx_msg void OnUpdateTogglecustomframe(CCmdUI* pCmdUI);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnInitMenu(CMenu* pMenu);
	afx_msg void OnActivate(UINT nState, base_wnd* pWndOther, BOOL bMinimized);
	afx_msg BOOL OnCopyData(base_wnd * pwnd, COPYDATASTRUCT* pcds);

   DECL_GEN_SIGNAL(_001OnClose)
   DECL_GEN_SIGNAL(_001OnMove)
   DECL_GEN_SIGNAL(_001OnShowWindow)


};

