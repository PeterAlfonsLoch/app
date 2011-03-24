#if !defined(AFX_PLAYLISTFRAME_H__7F88B041_783F_4EF2_BB50_E029BE7D8362__INCLUDED_)
#define AFX_PLAYLISTFRAME_H__7F88B041_783F_4EF2_BB50_E029BE7D8362__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlaylistFrame.h : header file
//

#include "gen/PaintHook.h"





//class CPlaylistInPlaceWnd;
class CPlaylistView;
class CXfplayerView;

/////////////////////////////////////////////////////////////////////////////
// PlaylistFrame frame

class PlaylistFrame :
   public SimpleFrameWnd
{
   DECLARE_DYNCREATE(PlaylistFrame)
protected:
   PlaylistFrame();           // protected constructor used by dynamic creation

// Attributes
public:
   SimpleToolBar              m_toolbar;
//xxx	SimpleReBar                m_wndReBar;
   BaseMenuMessageHandler     m_menuhook;
	
// Operations
public:
	virtual void TransparentFrameWndOnAfterChild();
	virtual void TransparentFrameWndOnAfterFrame();
	CView * GetParentLyricView();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PlaylistFrame)
	public:
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CreateContext* pContext = NULL);
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL DestroyWindow();
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CreateContext* pContext);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~PlaylistFrame();

	// Generated message map functions
	//{{AFX_MSG(PlaylistFrame)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnClose();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
    
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYLISTFRAME_H__7F88B041_783F_4EF2_BB50_E029BE7D8362__INCLUDED_)
