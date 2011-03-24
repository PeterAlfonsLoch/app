// HtmlViews.h : main header file for the HTMLVIEWS application
//

#if !defined(AFX_HTMLVIEWS_H__DB2D2F54_1190_11D2_8436_0000B43382FE__INCLUDED_)
#define AFX_HTMLVIEWS_H__DB2D2F54_1190_11D2_8436_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CHtmlViewsApp:
// See HtmlViews.cpp for the implementation of this class
//

class CHtmlViewsApp : public CWinApp
{
public:
	CHtmlViewsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHtmlViewsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHtmlViewsApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HTMLVIEWS_H__DB2D2F54_1190_11D2_8436_0000B43382FE__INCLUDED_)
