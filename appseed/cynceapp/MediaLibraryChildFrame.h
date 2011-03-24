#if !defined(AFX_ALBUMCHILDFRAME_H__D4734949_D283_4F0B_BC88_29FB538C85FF__INCLUDED_)
#define AFX_ALBUMCHILDFRAME_H__D4734949_D283_4F0B_BC88_29FB538C85FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlbumChildFrame.h : header file
//

// vmsguibase
/*#include "vmsguibase/_vmsguiBaseChildFrame.h"
#include "vmsguibase/SimpleMenuBar.h"
#include "vmsguibase/SimpleReBar.h"
#include "vmsguibase/SimpleToolBar.h"
*/
#include "guibase/BaseChildFrame.h"

#include "MediaLibraryViewUpdateHint.h"

class MediaLibraryView;
/////////////////////////////////////////////////////////////////////////////
// MediaLibraryChildFrame frame

class MediaLibraryChildFrame :
   public BaseChildFrame
{
	DECLARE_DYNCREATE(MediaLibraryChildFrame)
protected:
	MediaLibraryChildFrame();           // protected constructor used by dynamic creation

// Attributes
public:
   SimpleToolBar           m_toolbar;
   SimpleDialogBar         m_dialogbar;
//xxx   SimpleReBar             m_rebar;

   BaseMenuMessageHandler  m_menuhook;

   MediaLibraryView * GetMainView();
// Operations
public:
	EMediaLibraryView GetViewId();

   bool CreateBars();
   bool DestroyBars();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MediaLibraryChildFrame)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~MediaLibraryChildFrame();

	// Generated message map functions
	//{{AFX_MSG(MediaLibraryChildFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewAllMedia();
	afx_msg void OnUpdateViewAllMedia(CCmdUI* pCmdUI);
	afx_msg void OnViewMediaExplorer();
	afx_msg void OnUpdateViewMediaExplorer(CCmdUI* pCmdUI);
	afx_msg void OnViewVeriwellkaraokelibraryexplorer();
	afx_msg void OnUpdateViewVeriwellkaraokelibraryexplorer(CCmdUI* pCmdUI);
	//}}AFX_MSG
   afx_msg void OnChangeEditSearch();
   DECL_GEN_SIGNAL(_001OnAppLanguage)
   DECL_GEN_SIGNAL(_001OnInitializeFormPreData)
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALBUMCHILDFRAME_H__D4734949_D283_4F0B_BC88_29FB538C85FF__INCLUDED_)
