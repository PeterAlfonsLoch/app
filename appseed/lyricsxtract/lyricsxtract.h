// lyricsxtract.h : main header file for the LYRICSXTRACT application
//

#if !defined(AFX_LYRICSXTRACT_H__87C483B8_03FD_40AA_863A_44BE328253C1__INCLUDED_)
#define AFX_LYRICSXTRACT_H__87C483B8_03FD_40AA_863A_44BE328253C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLyricsXtractApp:
// See lyricsxtract.cpp for the implementation of this class
//

class CLyricsXtractApp : public CWinApp
{
public:
	CLyricsXtractApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLyricsXtractApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLyricsXtractApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LYRICSXTRACT_H__87C483B8_03FD_40AA_863A_44BE328253C1__INCLUDED_)
