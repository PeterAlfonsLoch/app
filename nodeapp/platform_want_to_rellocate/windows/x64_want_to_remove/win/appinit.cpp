// This is ca2 API library.
// 
// 
//
// 
// 
// 
// 
// 

#include "StdAfx.h"
#include "sal.h"



/////////////////////////////////////////////////////////////////////////////

BOOL CLASS_DECL_VMSWIN AfxWinInit(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	__in LPTSTR lpCmdLine, int nCmdShow)
{
	ASSERT(hPrevInstance == NULL);


	// handle critical errors and avoid Windows message boxes
	SetErrorMode(SetErrorMode(0) |
		SEM_FAILCRITICALERRORS|SEM_NOOPENFILEERRORBOX);

	// set resource handles
	AFX_MODULE_STATE* pModuleState = AfxGetModuleState();
	pModuleState->m_hCurrentInstanceHandle = hInstance;
	pModuleState->m_hCurrentResourceHandle = hInstance;
	pModuleState->CreateActivationContext();

	// fill in the initial state for the application
	application* pApp = &Application;
	if (pApp != NULL)
	{
		// Windows specific initialization (not done if no application)
		pApp->m_hInstance = hInstance;
		hPrevInstance; // Obsolete.
		pApp->m_lpCmdLine = lpCmdLine;
		pApp->m_nCmdShow = nCmdShow;
		//pApp->SetCurrentHandles();
	}

	// initialize thread specific data (for main thread)
	if (!afxContextIsDLL)
		AfxInitThread();

	// Initialize ::ca::window::m_pfnNotifyWinEvent
/*	HMODULE hModule = ::GetModuleHandle("user32.dll");
	if (hModule != NULL)
	{
		::ca::window::m_pfnNotifyWinEvent = (::ca::window::PFNNOTIFYWINEVENT)::GetProcAddress(hModule, "NotifyWinEvent");
	}*/

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// ex1::filesp implementation helpers

#ifdef AfxGetFileName
#undef AfxGetFileName
#endif


UINT CLASS_DECL_VMSWIN AfxGetFileName(const char * lpszPathName, __out_ecount_opt(nMax) LPTSTR lpszTitle, UINT nMax)
{
	ASSERT(lpszTitle == NULL ||
		AfxIsValidAddress(lpszTitle, nMax));
	ASSERT(AfxIsValidString(lpszPathName));

	ENSURE_ARG(lpszPathName != NULL);

	// always capture the complete file name including extension (if present)
	LPTSTR lpszTemp = ::PathFindFileName(lpszPathName);

	// lpszTitle can be NULL which just returns the number of bytes
	if (lpszTitle == NULL)
		return lstrlen(lpszTemp)+1;

	// otherwise copy it into the buffer provided
	_template::checked::tcsncpy_s(lpszTitle, nMax, lpszTemp, _TRUNCATE);
	return 0;
}


