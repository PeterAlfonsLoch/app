// MainFrm.h : interface of the syllomatter_frame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__BBA7EFE4_935E_4688_85E3_B494E8C24D45__INCLUDED_)
#define AFX_MAINFRM_H__BBA7EFE4_935E_4688_85E3_B494E8C24D45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CLASS_DECL_CA2_SYLLOMATTER syllomatter_frame : public SimpleFrameWnd
{
	
protected: // create from serialization only
	syllomatter_frame();
	DECLARE_DYNCREATE(syllomatter_frame)

// Attributes
public:
   //BaseMenuMessageHandler        m_menuhook;
   string                    m_strAnimatedStatusBarText;
   int                        m_iAnimateStep;
   ImageList                  m_imagelist;
   bool m_bTimerOn;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(syllomatter_frame)
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
	virtual ~syllomatter_frame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

static LRESULT CALLBACK MouseProc(          int nCode,
    WPARAM wParam,
    LPARAM lParam
);

void MouseMessage(          int nCode,
    WPARAM wParam,
    LPARAM lParam
);
   bool MouseHook();
   bool MouseUnhook();


   bool m_bHoverMouse;
   DWORD m_dwLastHover;

   void OnHoverAction();


protected:  // control bar embedded members
	
   BaseRect             m_FullScreenWindowRect;
//   SimpleMenuBar     m_menubar;
//   SimpleDialogBar   m_dialogbar;
//xxx	SimpleReBar       m_wndReBar;
//	SimpleStatusBar   m_statusbar;
//   SimpleToolBar     m_toolbar;
//   SimpleToolBar     m_toolbarView;


   //bool              m_bFullScreen;

// Generated message map functions
protected:


	//{{AFX_MSG(syllomatter_frame)
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

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__BBA7EFE4_935E_4688_85E3_B494E8C24D45__INCLUDED_)
