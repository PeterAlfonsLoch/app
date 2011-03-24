// OSZipShell.h : main header file for the OSZIPSHELL DLL
//

#if !defined(AFX_OSZIPSHELL_H__7305D84C_9171_4AD3_B7C8_66EB5AC70169__INCLUDED_)
#define AFX_OSZIPSHELL_H__7305D84C_9171_4AD3_B7C8_66EB5AC70169__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// COSZipShellApp
// See OSZipShell.cpp for the implementation of this class
//

class COSZipShellApp : public CWinApp
{
public:
	COSZipShellApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COSZipShellApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(COSZipShellApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OSZIPSHELL_H__7305D84C_9171_4AD3_B7C8_66EB5AC70169__INCLUDED_)
