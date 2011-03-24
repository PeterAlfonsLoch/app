// MainFrm.h : interface of the MainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__BBA7EFE4_935E_4688_85E3_B494E8C24D45__INCLUDED_)
#define AFX_MAINFRM_H__BBA7EFE4_935E_4688_85E3_B494E8C24D45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "PaneView1.h"


class MainFrame :
   public SimpleFrameWnd
{
	
protected: // create from serialization only
	MainFrame();
	DECLARE_DYNCREATE(MainFrame)

// Attributes
public:
   BaseMenuMessageHandler        m_menuhook;
   CString                    m_strAnimatedStatusBarText;
   int                        m_iAnimateStep;
   ImageList                  m_imagelist;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void ShowControlBars(bool bShow);
	void AnimateStatusBar();
	void SetAnimatedStatusBarText(LPCTSTR lpcsz);
	PaneView * GetPaneView();
	EPaneView GetViewId();
   void ShowView(EPaneView iPane);
	bool IsFullScreen();
	void ToggleFullScreen();
	virtual void WfiOnFullScreen(bool bFullScreen);
	virtual ~MainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	
   CRect             m_FullScreenWindowRect;
//   SimpleMenuBar     m_menubar;
//   SimpleDialogBar   m_dialogbar;
//xxx	SimpleReBar       m_wndReBar;
//	SimpleStatusBar   m_statusbar;
//   SimpleToolBar     m_toolbar;
//   SimpleToolBar     m_toolbarView;


   //bool              m_bFullScreen;

// Generated message map functions
protected:
	//{{AFX_MSG(MainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewFullScreen();
	afx_msg void OnUpdateViewFullScreen(CCmdUI* pCmdUI);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnClose();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnViewKaraoke();
	afx_msg void OnUpdateViewKaraoke(CCmdUI* pCmdUI);
	afx_msg void OnViewPlaylist();
	afx_msg void OnUpdateViewPlaylist(CCmdUI* pCmdUI);
	afx_msg void OnViewAlbum();
	afx_msg void OnUpdateViewAlbum(CCmdUI* pCmdUI);
   afx_msg void OnFileOpenEx();
	afx_msg void OnUpdateFileOpenEx(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent);
   afx_msg void OnShowWindow(BOOL bShow, UINT nStatus) ;
	afx_msg void OnNcPaint();
	afx_msg void OnTogglecustomframe();
	afx_msg void OnUpdateTogglecustomframe(CCmdUI* pCmdUI);
	afx_msg void OnViewOptions();
	afx_msg void OnUpdateViewOptions(CCmdUI* pCmdUI);
	afx_msg void OnViewNextPane();
   afx_msg void OnViewMediaExplorer();
   afx_msg void OnViewAllMedia();
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnInitMenu(CMenu* pMenu);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//}}AFX_MSG
	afx_msg LRESULT OnVmSimple(WPARAM wparam, LPARAM lparam);
	afx_msg BOOL OnCopyData(CWnd * pwnd, COPYDATASTRUCT* pcds);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__BBA7EFE4_935E_4688_85E3_B494E8C24D45__INCLUDED_)
