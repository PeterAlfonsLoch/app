// vme.h : main header file for the VME application
//

#if !defined(AFX_VME_H__03558A06_3444_4110_8E11_50C2B7FD5CA3__INCLUDED_)
#define AFX_VME_H__03558A06_3444_4110_8E11_50C2B7FD5CA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "VmsGenApp.h"
#include "_vmsguibaseAppInterface.h"
#include "VmsDBApp.h"
#include "resource.h"

#ifdef _VMSE_DLL
    #define CLASS_DECL_VMSE  _declspec(dllexport)
#else
    #define CLASS_DECL_VMSE  _declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////////////////
// CVmeApp:
// See vme.cpp for the implementation of this class
//

class CLASS_DECL_VMSE CVmeApp :
   public CVmsGenApp,
   public _vmsguibaseAppInterface,
   public _vmssimpledbAppInterface
{
public:
	CVmeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVmeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	//{{AFX_MSG(CVmeApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VME_H__03558A06_3444_4110_8E11_50C2B7FD5CA3__INCLUDED_)
