// util_dup.h : main header file for the util_dup application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// DupApp:
// See util_dup.cpp for the implementation of this class
//

class DupApp :
   public CWinApp,
   public CFontCentral
{
public:
	DupApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern DupApp theApp;