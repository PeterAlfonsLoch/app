// vmsmiditonet.h : main header file for the VMSMIDITONET application
//

#if !defined(AFX_VMSMIDITONET_H__F6F8BC6C_F27E_4396_9784_A353657D39D4__INCLUDED_)
#define AFX_VMSMIDITONET_H__F6F8BC6C_F27E_4396_9784_A353657D39D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CVmsmiditonetApp:
// See vmsmiditonet.cpp for the implementation of this class
//

class CVmsmiditonetApp : public CWinApp
{
public:
	CVmsmiditonetApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVmsmiditonetApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CVmsmiditonetApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VMSMIDITONET_H__F6F8BC6C_F27E_4396_9784_A353657D39D4__INCLUDED_)
