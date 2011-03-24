// npvmp.h : main header file for the NPVMP DLL
//

#if !defined(AFX_NPVMP_H__402EDE85_52E7_4D8E_99D4_32145F06B396__INCLUDED_)
#define AFX_NPVMP_H__402EDE85_52E7_4D8E_99D4_32145F06B396__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#ifdef _NPVMP_DLL
    #define CLASS_DECL_NPVMP  _declspec(dllexport)
#else
    #define CLASS_DECL_NPVMP  _declspec(dllimport)
#endif

/////////////////////////////////////////////////////////////////////////////
// CNpvmpApp
// See npvmp.cpp for the implementation of this class
//

class CNpvmpApp : public CWinApp
{
public:
	CNpvmpApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNpvmpApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CNpvmpApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

AFX_EXT_CLASS extern "C" NPError NPP_Initialize();

AFX_EXT_CLASS extern "C" NPError NPP_New(
	NPMIMEType    pluginType,
    NPP instance,
	uint16 mode,
    int16 argc,
	char *argn[],
    char *argv[],
	NPSavedData *saved);

AFX_EXT_CLASS extern "C" NPError NPP_Destroy(NPP instance, NPSavedData **save);

AFX_EXT_CLASS extern "C" void NPP_Shutdown(void);


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NPVMP_H__402EDE85_52E7_4D8E_99D4_32145F06B396__INCLUDED_)
