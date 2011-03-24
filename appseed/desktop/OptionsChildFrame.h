#if !defined(AFX_OPTIONSCHILDFRAME_H__D4734949_D283_4F0B_BC88_29FB538C85FF__INCLUDED_)
#define AFX_OPTIONSCHILDFRAME_H__D4734949_D283_4F0B_BC88_29FB538C85FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlbumChildFrame.h : header file
//

// vmsguibase
/*#include "vmsguibase/_vmsguiBaseChildFrame.h"
#include "vmsguibase/SimpleDialogBar.h"
#include "vmsguibase/SimpleMenuBar.h"
#include "vmsguibase/SimpleReBar.h"
#include "vmsguibase/SimpleToolBar.h"
*/
#include "guibase/BaseChildFrame.h"

class MediaLibraryView;
/////////////////////////////////////////////////////////////////////////////
// OptionsChildFrame frame

class OptionsChildFrame :
   public BaseChildFrame
{
	DECLARE_DYNCREATE(OptionsChildFrame)
protected:
	OptionsChildFrame();           // protected constructor used by dynamic creation

// Attributes
public:
   SimpleToolBar           m_toolbar;
   SimpleToolBar           m_toolbar1;
   SimpleDialogBar         m_dialogbar;
//xxx   SimpleReBar             m_rebar;

   //BaseMenuMessageHandler  m_menuhook;

   MediaLibraryView * GetMainView();
// Operations
public:
	void LoadToolBar(int iToolBar, UINT uiToolBar);
	void DestroyToolBar(int iToolbar);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(OptionsChildFrame)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~OptionsChildFrame();

	// Generated message map functions
	//{{AFX_MSG(OptionsChildFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewAllMedia();
	afx_msg void OnUpdateViewAllMedia(CCmdUI* pCmdUI);
	afx_msg void OnViewMediaExplorer();
	afx_msg void OnUpdateViewMediaExplorer(CCmdUI* pCmdUI);
	//}}AFX_MSG
   afx_msg void OnChangeEditSearch();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSCHILDFRAME_H__D4734949_D283_4F0B_BC88_29FB538C85FF__INCLUDED_)
