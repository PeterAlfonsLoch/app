#if !defined(AFX_PLAYLISTCHILDFRAME_H__7F88B041_783F_4EF2_BB50_E029BE7D8362__INCLUDED_)
#define AFX_PLAYLISTCHILDFRAME_H__7F88B041_783F_4EF2_BB50_E029BE7D8362__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlaylistFrame.h : header file
//

#include "gen/PaintHook.h"


//#include "guibase/BaseMenuWindowHook.h"
#include "guibase/BaseChildFrame.h"


/////////////////////////////////////////////////////////////////////////////
// PlaylistChildFrame frame

class PlaylistChildFrame :
   public BaseChildFrame
        
{
   DECLARE_DYNCREATE(PlaylistChildFrame)
protected:
   PlaylistChildFrame();           // protected constructor used by dynamic creation

// Attributes
public:
   SimpleToolBar              m_toolbar;
//xxx	SimpleReBar                m_wndReBar;
   BaseMenuMessageHandler     m_menuhook;
	
// Operations
public:
	CView * GetParentLyricView();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PlaylistChildFrame)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~PlaylistChildFrame();

	// Generated message map functions
	//{{AFX_MSG(PlaylistChildFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
    
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYLISTCHILDFRAME_H__7F88B041_783F_4EF2_BB50_E029BE7D8362__INCLUDED_)
