// oszip_shell.h : main header file for the OSZIP_SHELL DLL
//

#if !defined(AFX_OSZIP_SHELL_H__5AC3212D_1B4E_4465_911E_31E7D637822E__INCLUDED_)
#define AFX_OSZIP_SHELL_H__5AC3212D_1B4E_4465_911E_31E7D637822E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "Oszip_shell_i.h"

/////////////////////////////////////////////////////////////////////////////
// COszip_shellApp
// See oszip_shell.cpp for the implementation of this class
//

class COszip_shellApp : public CWinApp
{
public:
	COszip_shellApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COszip_shellApp)
	public:
	virtual BOOL InitInstance();
		virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(COszip_shellApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL InitATL();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OSZIP_SHELL_H__5AC3212D_1B4E_4465_911E_31E7D637822E__INCLUDED_)
