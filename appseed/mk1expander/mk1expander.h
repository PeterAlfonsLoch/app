// mk1expander.h : main header file for the MK1EXPANDER application
//

#if !defined(AFX_MK1EXPANDER_H__48D92F79_B309_42FD_96E3_7760772463AD__INCLUDED_)
#define AFX_MK1EXPANDER_H__48D92F79_B309_42FD_96E3_7760772463AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMk1expanderApp:
// See mk1expander.cpp for the implementation of this class
//

class CMk1expanderApp : public CWinApp
{
public:
	CMk1expanderApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMk1expanderApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	//{{AFX_MSG(CMk1expanderApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MK1EXPANDER_H__48D92F79_B309_42FD_96E3_7760772463AD__INCLUDED_)
