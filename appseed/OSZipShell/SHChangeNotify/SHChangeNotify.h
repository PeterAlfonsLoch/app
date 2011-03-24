// SHChangeNotify.h : main header file for the SHCHANGENOTIFY application
//

#if !defined(AFX_SHCHANGENOTIFY_H__847EAA67_B370_480F_A46E_A5374CC2F56D__INCLUDED_)
#define AFX_SHCHANGENOTIFY_H__847EAA67_B370_480F_A46E_A5374CC2F56D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSHChangeNotifyApp:
// See SHChangeNotify.cpp for the implementation of this class
//

class CSHChangeNotifyApp : public CWinApp
{
public:
	CSHChangeNotifyApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSHChangeNotifyApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSHChangeNotifyApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHCHANGENOTIFY_H__847EAA67_B370_480F_A46E_A5374CC2F56D__INCLUDED_)
