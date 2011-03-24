
#if !defined(AFX_AUDIOGEN_H__170D4EA0_9AEE_45D6_8C20_1BC266DE2AC9__INCLUDED_)
#define AFX_AUDIOGEN_H__170D4EA0_9AEE_45D6_8C20_1BC266DE2AC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "_vmsaudioWaveCentralContainer.h"

/////////////////////////////////////////////////////////////////////////////
// CAudiogenApp:
// See audiogen.cpp for the implementation of this class
//

class CAudiogenApp : public CWinApp ,
public _vmsaudio::CWaveCentralContainer
{
public:
	CAudiogenApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAudiogenApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CAudiogenApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUDIOGEN_H__170D4EA0_9AEE_45D6_8C20_1BC266DE2AC9__INCLUDED_)
