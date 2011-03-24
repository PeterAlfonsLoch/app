// fileren.h : main header file for the FILEREN application
//

#if !defined(AFX_FILEREN_H__1003BD0F_BCE2_4802_B084_53EBA6D292CE__INCLUDED_)
#define AFX_FILEREN_H__1003BD0F_BCE2_4802_B084_53EBA6D292CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// FileRenApp:
// See fileren.cpp for the implementation of this class
//

class FileRenApp :   
   public gen::App,
   public Ex1App
{
public:
	FileRenApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(FileRenApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

   CMultiDocTemplate* m_ptemplate1;
   CMultiDocTemplate* m_ptemplateRemoveTwoDirDuplicates;

// Implementation
	//{{AFX_MSG(FileRenApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

   virtual Ex1FactoryImpl * Ex1AppGetFactoryImpl();

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEREN_H__1003BD0F_BCE2_4802_B084_53EBA6D292CE__INCLUDED_)
