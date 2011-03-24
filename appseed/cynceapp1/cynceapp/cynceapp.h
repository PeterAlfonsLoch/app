// cynceapp.h : main header file for the cynceapp application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CcynceappApp:
// See cynceapp.cpp for the implementation of this class
//

class CcynceappApp : public CWinApp
{
public:
	CcynceappApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CcynceappApp theApp;