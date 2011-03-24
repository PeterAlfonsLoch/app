// vmsnettomidi.h : main header file for the VMSNETTOMIDI application
//

#if !defined(AFX_VMSNETTOMIDI_H__E672A2A9_D760_4CF2_BF28_3BED08E6699B__INCLUDED_)
#define AFX_VMSNETTOMIDI_H__E672A2A9_D760_4CF2_BF28_3BED08E6699B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CVmsnettomidiApp:
// See vmsnettomidi.cpp for the implementation of this class
//

class CVmsnettomidiApp : public CWinApp
{
public:
	CVmsnettomidiApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVmsnettomidiApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CVmsnettomidiApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VMSNETTOMIDI_H__E672A2A9_D760_4CF2_BF28_3BED08E6699B__INCLUDED_)
