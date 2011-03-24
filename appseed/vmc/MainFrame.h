#pragma once

#include "xfplayerdialogbar.h"

class CAlbumDialog;
class CMixerDialog;

class CMenuV033;



class CMainFrame :
	public SimpleMDIFrameWindow
{
public:
   CMainFrame(::ca::application * papp);
	CFont *			m_pEditFont;

   virtual window_frame::FrameSchema * create_frame_schema();
    HRGN                   m_hrgnWindow;
    CMenuV033 *            m_pmenuV033;

	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, base_wnd* pParentWnd = NULL, CreateContext* pContext = NULL);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CreateContext* pContext);

	CXfplayerDialogBar * GetDialogBar();
	CToolBar * GetToolBar();
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar			m_wndStatusBar;
	CToolBar			m_wndToolBar;
	CReBar				m_wndReBar;
	CXfplayerDialogBar	m_wndDlgBar;
	WINDOWPLACEMENT		m_wpPrev;
	CToolBar *			m_pwndFullScrnBar;
	class rect				m_FullScreenWindowRect;
	bool				m_bFullScreen;
   //BaseArray<CFullScreenItem, CFullScreenItem &> m_fullScreenData;

public:
	VMSRESULT ViewFullScreen();
	VMSRESULT OpenPlayerWindow();
	bool IsFullScreen();
	void UpdateReserveList();
    CTypedPtrArray<CPtrArray, CMixerDialog *> m_ptraMixerDialogs;
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnViewFullScreen();
	afx_msg void OnUpdateViewFullScreen(CCmdUI* pCmdUI);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnExitFullScreen();
	afx_msg void OnUpdateExitFullScreen(CCmdUI* pCmdUI);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnToolsMixer();
	afx_msg void OnUpdateToolsMixer(CCmdUI* pCmdUI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnToolsCompactdatabase();
	afx_msg void OnUpdateToolsCompactdatabase(CCmdUI* pCmdUI);
	afx_msg void OnPlayer();
	afx_msg void OnUpdatePlayer(CCmdUI* pCmdUI);
	afx_msg void OnWindowCascade();
	afx_msg void OnToolsSaveMemory();
	afx_msg void OnActivate(UINT nState, base_wnd* pWndOther, BOOL bMinimized);
	afx_msg void OnInitMenu(CMenu* pMenu);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEnterIdle(UINT nWhy, base_wnd* pWho);
	afx_msg void OnUpdateToolsSaveMemory(CCmdUI* pCmdUI);
    afx_msg LRESULT OnEconoModeChange(WPARAM wParam, LPARAM lParam);
};

