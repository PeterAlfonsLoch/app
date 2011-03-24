// vmsaudioprofile.h : main header file for the VMSAUDIOPROFILE application
//

#if !defined(AFX_VMSAUDIOPROFILE_H__24997464_995B_46DE_99F2_D1C59F901603__INCLUDED_)
#define AFX_VMSAUDIOPROFILE_H__24997464_995B_46DE_99F2_D1C59F901603__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// AudioProfileApp:
// See vmsaudioprofile.cpp for the implementation of this class
//

class AudioProfileApp : public CWinApp
{
public:
	AudioProfileApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AudioProfileApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	//{{AFX_MSG(AudioProfileApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VMSAUDIOPROFILE_H__24997464_995B_46DE_99F2_D1C59F901603__INCLUDED_)
