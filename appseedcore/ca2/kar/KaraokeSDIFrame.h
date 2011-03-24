// MainFrm.h : interface of the CKaraokeSDIFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_KARAOKESDIFRAME_H__582F7EA6_EB01_423D_8723_74301B16C6EA__INCLUDED_)
#define AFX_KARAOKESDIFRAME_H__582F7EA6_EB01_423D_8723_74301B16C6EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Xfplayerdialogbar.h"
#include "XfplayerFrameWndInterface.h"
#include "MenuBarV033.h"
#include "ToolBarV033.h"
#include "BaseArray.h"
#include "VMSException.h"	// Added by ClassView
#include "TransparentMDIChildWnd.h"
#include "TransparentStatusBar.h"
#include "vmsgui.h"
#include "DBInterface.h"
//#include "KaraokeMainFrame.h"
//#include "d3d8.h"

class CAlbumDialog;
class CMixerDialog;

class CMenuV033;
class CWndFrameworkV033;

class CKaraokeMainChildWnd;

namespace _vmsp
{
   class CDocumentInterface;
}

class CMixerThread;
class CXfplayerView;




class CKaraokeSDIFrame
   :
   public CTransparentMDIChildWnd,
   public CXfplayerFrameWndInterface

{
    DECLARE_DYNCREATE(CKaraokeSDIFrame)
	
protected: // create from serialization only
	CKaraokeSDIFrame();
    virtual ~CKaraokeSDIFrame();
	
	CFont *			m_pEditFont;
 //   CKaraokeMainChildWnd *   m_pkmcwnd;
// Attributes
protected:

	bool		m_bToolbarVisible;
	CMixerThread		* m_pmixerthread;
    
//    CKaraokeMainFrame *     m_pMainFrame;
	//CMenu *		m_pMenu;
//    CKaraokeSDIFrameInPlaceWnd * m_pIPWnd;
    //CRgn	m_rgnWindow;
//    CMenuManagerV003 *     m_pMenuManager;        
    //CMenuV033 *            m_pmenuV033;
//    CComPtr<IDirect3D8>    m_spDirect3D8;
//    bool                   m_bDirectDrawPresenceChecked;
  //  bool                   m_bDirectDrawPresent;
    //bool                   m_bDirectDrawActive;
    
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKaraokeSDIFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
	virtual BOOL DestroyWindow();
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	CXfplayerDialogBar * GetDialogBar();
	CToolBarV033 * GetToolBar();
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CTransparentStatusBar			m_statusbar;

	CToolBarV033        m_toolbarStandard;
    CToolBarV033        m_toolbarView1;
	CToolBarV033        m_toolbarView2;
    CToolBarV033        m_toolbarPlay;

	CXfplayerDialogBar	m_dialogbar;


public:
//	VMSRESULT ViewToolsAlbum();
	VMSRESULT ViewFullScreen();
protected:


//    void OpenToolsAlbum();
public:
   _vmsp::CDocumentInterface * GetActiveDocumentEx();
	virtual void OnCompactModeChange(bool bCompact);
	virtual void WfiOnAfterFullScreen(bool bFullScreen);
	CMDIFrameWnd * TransparentMDIChildWndGetMDIFrameEx();
	virtual bool TransparentFrameWndIsCompactMode();
	virtual bool _000OnPosCreate();
	void OnUpdateLyricsCodePage();
	//CXfplayerView * GetLyricView();


	void LoadBarState();
	void SaveBarState();
	virtual bool TransparentFrameWndShowBars(int nCmdShow);
	//void UpdateToolBarText(CToolBarV033 &toolbar);
	//void UpdateToolBarText(CToolBarCtrlV017 &toolbar);
	virtual void TransparentFrameWndUpdateBars();
	//void UpdateToolBarStyle(CToolBarV033 &toolbar);
	//void UpdateToolBarStyle(CToolBarCtrlV017 &toolbar);
	//bool GetToolButtonText(CWStr &wstr, UINT uiCmd);
	//virtual void TwiOnDraw(CDC * pdc);
	//virtual void TransparentFrameWndFullScreen(bool bFullScreen);
	
	afx_msg LRESULT OnAppLanguage(WPARAM wParam, LPARAM lParam);
	
	//bool IsCompactMode();

	void TwcRenderBackground(CDC *pdc, LPCRECT lpcrect);
//	inline CAlbumDialog * GetAlbumDialog();
	bool IsFullScreen();
	void UpdateReserveList();
//	CAlbumDialog *		m_pAlbumDialog;
    CTypedPtrArray<CPtrArray, CMixerDialog *> m_ptraMixerDialogs;
//	CXfplayerReserveList m_ReserveList;

    
// Generated message map functions
protected:
	virtual void WfiOnNotifyIcon();
	virtual void WfiOnNotiyIcon();
	//{{AFX_MSG(CKaraokeSDIFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnViewFullScreen();
	afx_msg void OnUpdateViewFullScreen(CCmdUI* pCmdUI);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnExitFullScreen();
	afx_msg void OnUpdateExitFullScreen(CCmdUI* pCmdUI);
	afx_msg void OnToolsOptions();
	afx_msg void OnUpdateToolsOptions(CCmdUI* pCmdUI);
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
	afx_msg void OnUpdateToolsSaveMemory(CCmdUI* pCmdUI);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnInitMenu(CMenu* pMenu);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnPaint();
	afx_msg void OnNcPaint();
	afx_msg void OnClose();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnViewCompactSize();
	afx_msg void OnUpdateViewCompactSize(CCmdUI* pCmdUI);
	afx_msg void OnUpdateVmsguiClose(CCmdUI* pCmdUI);
	afx_msg void OnUpdateVmsguiWindowMinimize(CCmdUI* pCmdUI);
	afx_msg void OnHelpFinder();
	//}}AFX_MSG
	afx_msg LRESULT OnFrameworkV033Command(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnEconoModeChange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAppNotify(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//inline CAlbumDialog * CKaraokeSDIFrame::GetAlbumDialog()
//{
//	return m_pAlbumDialog;
//}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KARAOKESDIFRAME_H__582F7EA6_EB01_423D_8723_74301B16C6EA__INCLUDED_)
