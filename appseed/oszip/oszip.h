// oszip.h : main header file for the OSZIP application
//

#if !defined(AFX_OSZIP_H__97D739AC_E2B4_4A5E_ABA5_D50FD7AD244F__INCLUDED_)
#define AFX_OSZIP_H__97D739AC_E2B4_4A5E_ABA5_D50FD7AD244F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// COszipApp:
// See oszip.cpp for the implementation of this class
//

class COszipApp : public gen::App
{
public:
	COszipApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COszipApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
		// Server object for document creation
	//{{AFX_MSG(COszipApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OSZIP_H__97D739AC_E2B4_4A5E_ABA5_D50FD7AD244F__INCLUDED_)
