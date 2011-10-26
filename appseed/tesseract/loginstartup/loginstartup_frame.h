// MainFrm.h : interface of the loginstartup_frame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__BBA7EFE4_935E_4688_85E3_B494E8C24D45__INCLUDED_)
#define AFX_MAINFRM_H__BBA7EFE4_935E_4688_85E3_B494E8C24D45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CLASS_DECL_CA2_LOGINSTARTUP loginstartup_frame : public SimpleFrameWindow
{
	
public: // create from serialization only
	loginstartup_frame(::ca::application * papp);
	// DECLARE_DYNCREATE(loginstartup_frame)

// Attributes
public:
   string                    m_strAnimatedStatusBarText;
   bool                       m_bAutoHideOnOutClick;
   int                        m_iAnimateStep;
   image_list                  m_imagelist;
   bool                       m_bTimerHide;
   bool                       m_bTimerOn;
   bool                       m_bLControl;
   SimpleToolBar              m_toolbar;
   EPosition                  m_eposition;
   bool                       m_bMoveDrag;
   bool                       m_bLastLWin;
   loginstartup_view *       m_ploginstartupview;

   virtual void _001InstallMessageHandling(igui::win::message::Dispatch * pinterface);

// Operations
public:
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg); 
public:
	void ShowControlBars(bool bShow);
	void AnimateStatusBar();
	void SetAnimatedStatusBarText(const char * lpcsz);
	bool IsFullScreen();
	void ToggleFullScreen();
   void show_task_bar(int nCmdShow);
	virtual void WfiOnFullScreen(bool bFullScreen);
	virtual ~loginstartup_frame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext & dumpcontext) const;
#endif

   bool m_bHoverMouse;
   DWORD m_dwLastHover;


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
	afx_msg void OnActivate(UINT nState, ::ca::window* pWndOther, BOOL bMinimized);
	afx_msg BOOL OnCopyData(::ca::window * pwnd, COPYDATASTRUCT* pcds);

	// DECLARE_MESSAGE_MAP()

   DECL_GEN_SIGNAL(_001OnClose)
   DECL_GEN_SIGNAL(_001OnMove)
   DECL_GEN_SIGNAL(_001OnShowWindow)
   DECL_GEN_SIGNAL(_001OnDestroy)
   DECL_GEN_SIGNAL(_001OnApp2000)
   virtual bool _001OnCommand(id id);
   virtual bool _001OnUpdateCmdUi(CCmdUI * pcmdui);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__BBA7EFE4_935E_4688_85E3_B494E8C24D45__INCLUDED_)
