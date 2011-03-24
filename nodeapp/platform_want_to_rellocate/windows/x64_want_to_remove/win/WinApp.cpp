// WinApp.cpp: implementation of the WinApp class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "afxadv.h"
#include "afximpl.h"
#include "winspool.h"

#define WM_KICKIDLE         0x036A  // (params unused) causes idles to kick in



// vmsgen
#include "_vmswinFrameWndInterface.h"
#include "OleFrameHook.h"
#include "vfxstat_.h"
#include "WinApp.h"


#ifdef _CONVERSION_USES_THREAD_LOCALE
	#ifndef _DEBUG
		#define USES_CONVERSION int _convert; _convert; UINT _acp = GetACP(); _acp; LPCWSTR _lpw; _lpw; LPCSTR _lpa; _lpa
	#else
		#define USES_CONVERSION int _convert = 0; _convert; UINT _acp = GetACP(); _acp; LPCWSTR _lpw = NULL; _lpw; LPCSTR _lpa = NULL; _lpa
	#endif
#else
	#ifndef _DEBUG
		#define USES_CONVERSION int _convert; _convert; UINT _acp = CP_ACP; _acp; LPCWSTR _lpw; _lpw; LPCSTR _lpa; _lpa
	#else
		#define USES_CONVERSION int _convert = 0; _convert; UINT _acp = CP_ACP; _acp; LPCWSTR _lpw = NULL; _lpw; LPCSTR _lpa = NULL; _lpa
	#endif
#endif

#ifdef _UNICODE
	#define T2A W2A
	#define A2T A2W
	inline LPWSTR T2W(LPTSTR lp) { return lp; }
	inline LPTSTR W2T(LPWSTR lp) { return lp; }
	#define T2CA W2CA
	#define A2CT A2CW
	inline LPCWSTR T2CW(LPCTSTR lp) { return lp; }
	inline LPCTSTR W2CT(LPCWSTR lp) { return lp; }
#else
	#define T2W A2W
	#define W2T W2A
	inline LPSTR T2A(LPTSTR lp) { return lp; }
	inline LPTSTR A2T(LPSTR lp) { return lp; }
	#define T2CW A2CW
	#define W2CT W2CA
	inline LPCSTR T2CA(LPCTSTR lp) { return lp; }
	inline LPCTSTR A2CT(LPCSTR lp) { return lp; }
#endif


/////////////////////////////////////////////////////////////////////////////
// Context sensitive help support (see Technical note TN028 for more details)

// Help ID bases
#define HID_BASE_COMMAND    0x00010000UL        // ID and IDM
#define HID_BASE_RESOURCE   0x00020000UL        // IDR and IDD
#define HID_BASE_PROMPT     0x00030000UL        // IDP
#define HID_BASE_NCAREAS    0x00040000UL
#define HID_BASE_CONTROL    0x00050000UL        // IDC
#define HID_BASE_DISPATCH   0x00060000UL        // IDispatch help codes

#define WM_HELPPROMPTADDR   0x0376


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void AFXAPI vfxDeleteObject(HGDIOBJ* pObject)
{
	ASSERT(pObject != NULL);
	if (*pObject != NULL)
	{
		DeleteObject(*pObject);
		*pObject = NULL;
	}
}



AFX_STATIC_DATA const TCHAR _afxFileSection[] = _T("Recent File List");
AFX_STATIC_DATA const TCHAR _afxFileEntry[] = _T("File%d");
AFX_STATIC_DATA const TCHAR _afxPreviewSection[] = _T("Settings");
AFX_STATIC_DATA const TCHAR _afxPreviewEntry[] = _T("PreviewPages");

/////////////////////////////////////////////////////////////////////////////
// globals (internal library use)

// CDocManager statics are in this file for granularity reasons
BOOL CDocManager::bStaticInit = TRUE;
CDocManager* CDocManager::pStaticDocManager = NULL;
CPtrList* CDocManager::pStaticList = NULL;

BEGIN_MESSAGE_MAP(WinApp, CCmdTarget)
	//{{AFX_MSG_MAP(WinApp)
	// Global File commands
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	// MRU - most recently used file menu
	ON_UPDATE_COMMAND_UI(ID_FILE_MRU_FILE1, OnUpdateRecentFileMenu)
	ON_COMMAND_EX_RANGE(ID_FILE_MRU_FILE1, ID_FILE_MRU_FILE16, OnOpenRecentFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// _AFX_WIN_STATE implementation

#ifndef _AFX_NO_GRAYDLG_SUPPORT


_AFX_WIN_STATE::_AFX_WIN_STATE()
{
	// Note: it is only necessary to intialize non-zero data.
}


_AFX_WIN_STATE::~_AFX_WIN_STATE()
{
	vfxDeleteObject((HGDIOBJ*)&m_hDlgBkBrush);
}

#endif //!_AFX_NO_GRAYDLG_SUPPORT


WinApp::WinApp(LPCTSTR lpszAppName)
{
	if (lpszAppName != NULL)
		m_pszAppName = _tcsdup(lpszAppName);
	else
		m_pszAppName = NULL;

	// initialize CWinThread state
	VFX_MODULE_STATE* pModuleState = _VFX_CMDTARGET_GETSTATE();
	VFX_MODULE_THREAD_STATE* pThreadState = pModuleState->m_thread;
	ASSERT(AfxGetThread() == NULL);
	pThreadState->m_pCurrentWinThread = this;
	ASSERT(AfxGetThread() == this);
	m_hThread = ::GetCurrentThread();
	m_nThreadID = ::GetCurrentThreadId();

	// initialize WinApp state
	ASSERT(afxCurrentWinApp == NULL); // only one WinApp object please
	pModuleState->m_pCurrentWinApp = this;
	ASSERT(vfxGetApp() == this);

	// in non-running state until WinMain
	m_hInstance = NULL;
	m_pszHelpFilePath = NULL;
	m_pszProfileName = NULL;
	m_pszRegistryKey = NULL;
	m_pszExeName = NULL;
	m_pRecentFileList = NULL;
	m_pDocManager = NULL;
	m_atomApp = m_atomSystemTopic = NULL;
	m_lpCmdLine = NULL;
	m_pCmdInfo = NULL;

	// initialize wait cursor state
	m_nWaitCursorCount = 0;
	m_hcurWaitCursorRestore = NULL;

	// initialize current printer state
	m_hDevMode = NULL;
	m_hDevNames = NULL;
	m_nNumPreviewPages = 0;     // not specified (defaults to 1)

	// initialize DAO state
	m_lpfnDaoTerm = NULL;   // will be set if AfxDaoInit called

	// other initialization
	m_bHelpMode = FALSE;
	m_nSafetyPoolSize = 512;        // default size
}

BOOL WinApp::InitApplication()
{
	if (CDocManager::pStaticDocManager != NULL)
	{
		if (m_pDocManager == NULL)
			m_pDocManager = CDocManager::pStaticDocManager;
		CDocManager::pStaticDocManager = NULL;
	}

	if (m_pDocManager != NULL)
		m_pDocManager->AddDocTemplate(NULL);
	else
		CDocManager::bStaticInit = FALSE;

	return TRUE;
}

BOOL WinApp::InitInstance()
{
	return TRUE;
}

void WinApp::LoadStdProfileSettings(UINT nMaxMRU)
{
	ASSERT_VALID(this);
	ASSERT(m_pRecentFileList == NULL);

	if (nMaxMRU != 0)
	{
		// create file MRU since nMaxMRU not zero
		m_pRecentFileList = new CRecentFileList(0, _afxFileSection, _afxFileEntry,
			nMaxMRU);
		m_pRecentFileList->ReadList();
	}
	// 0 by default means not set
	m_nNumPreviewPages = GetProfileInt(_afxPreviewSection, _afxPreviewEntry, 0);
}

void WinApp::ParseCommandLine(CCommandLineInfo& rCmdInfo)
{
	for (int i = 1; i < __argc; i++)
	{
		LPCTSTR pszParam = __targv[i];
		BOOL bFlag = FALSE;
		BOOL bLast = ((i + 1) == __argc);
		if (pszParam[0] == '-' || pszParam[0] == '/')
		{
			// remove flag specifier
			bFlag = TRUE;
			++pszParam;
		}
		rCmdInfo.ParseParam(pszParam, bFlag, bLast);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCommandLineInfo implementation

CCommandLineInfo::CCommandLineInfo()
{
	m_bShowSplash = TRUE;
	m_bRunEmbedded = FALSE;
	m_bRunAutomated = FALSE;
	m_nShellCommand = FileNew;
}

CCommandLineInfo::~CCommandLineInfo()
{
}

void CCommandLineInfo::ParseParam(const TCHAR* pszParam,BOOL bFlag,BOOL bLast)
{
	if (bFlag)
	{
		USES_CONVERSION;
		ParseParamFlag(T2CA(pszParam));
	}
	else
		ParseParamNotFlag(pszParam);

	ParseLast(bLast);
}

#ifdef UNICODE
void CCommandLineInfo::ParseParam(const char* pszParam, BOOL bFlag, BOOL bLast)
{
	if (bFlag)
		ParseParamFlag(pszParam);
	else
		ParseParamNotFlag(pszParam);

	ParseLast(bLast);
}
#endif // UNICODE

void CCommandLineInfo::ParseParamFlag(const char* pszParam)
{
	// OLE command switches are case insensitive, while
	// shell command switches are case sensitive

	if (lstrcmpA(pszParam, "pt") == 0)
		m_nShellCommand = FilePrintTo;
	else if (lstrcmpA(pszParam, "p") == 0)
		m_nShellCommand = FilePrint;
	else if (lstrcmpiA(pszParam, "Unregister") == 0 ||
			 lstrcmpiA(pszParam, "Unregserver") == 0)
		m_nShellCommand = AppUnregister;
	else if (lstrcmpA(pszParam, "dde") == 0)
	{
		AfxOleSetUserCtrl(FALSE);
		m_nShellCommand = FileDDE;
	}
	else if (lstrcmpiA(pszParam, "Embedding") == 0)
	{
		AfxOleSetUserCtrl(FALSE);
		m_bRunEmbedded = TRUE;
		m_bShowSplash = FALSE;
	}
	else if (lstrcmpiA(pszParam, "Automation") == 0)
	{
		AfxOleSetUserCtrl(FALSE);
		m_bRunAutomated = TRUE;
		m_bShowSplash = FALSE;
	}
}

void CCommandLineInfo::ParseParamNotFlag(const TCHAR* pszParam)
{
	if (m_strFileName.IsEmpty())
		m_strFileName = pszParam;
	else if (m_nShellCommand == FilePrintTo && m_strPrinterName.IsEmpty())
		m_strPrinterName = pszParam;
	else if (m_nShellCommand == FilePrintTo && m_strDriverName.IsEmpty())
		m_strDriverName = pszParam;
	else if (m_nShellCommand == FilePrintTo && m_strPortName.IsEmpty())
		m_strPortName = pszParam;
}

#ifdef UNICODE
void CCommandLineInfo::ParseParamNotFlag(const char* pszParam)
{
	if (m_strFileName.IsEmpty())
		m_strFileName = pszParam;
	else if (m_nShellCommand == FilePrintTo && m_strPrinterName.IsEmpty())
		m_strPrinterName = pszParam;
	else if (m_nShellCommand == FilePrintTo && m_strDriverName.IsEmpty())
		m_strDriverName = pszParam;
	else if (m_nShellCommand == FilePrintTo && m_strPortName.IsEmpty())
		m_strPortName = pszParam;
}
#endif

void CCommandLineInfo::ParseLast(BOOL bLast)
{
	if (bLast)
	{
		if (m_nShellCommand == FileNew && !m_strFileName.IsEmpty())
			m_nShellCommand = FileOpen;
		m_bShowSplash = !m_bRunEmbedded && !m_bRunAutomated;
	}
}

/////////////////////////////////////////////////////////////////////////////
// App termination

WinApp::~WinApp()
{
	// free doc manager
	if (m_pDocManager != NULL)
		delete m_pDocManager;

	// free recent file list
	if (m_pRecentFileList != NULL)
		delete m_pRecentFileList;

	// free static list of document templates
	if (!afxContextIsDLL)
	{
		if (CDocManager::pStaticList != NULL)
		{
			delete CDocManager::pStaticList;
			CDocManager::pStaticList = NULL;
		}
		if (CDocManager::pStaticDocManager != NULL)
		{
			delete CDocManager::pStaticDocManager;
			CDocManager::pStaticDocManager = NULL;
		}
	}

	// free printer info
	if (m_hDevMode != NULL)
		AfxGlobalFree(m_hDevMode);
	if (m_hDevNames != NULL)
		AfxGlobalFree(m_hDevNames);

	// free atoms if used
	if (m_atomApp != NULL)
		::GlobalDeleteAtom(m_atomApp);
	if (m_atomSystemTopic != NULL)
		::GlobalDeleteAtom(m_atomSystemTopic);

	// free cached commandline
	if (m_pCmdInfo != NULL)
		delete m_pCmdInfo;

	// cleanup module state
	VFX_MODULE_STATE* pModuleState = _VFX_CMDTARGET_GETSTATE();
	if (pModuleState->m_lpszCurrentAppName == m_pszAppName)
		pModuleState->m_lpszCurrentAppName = NULL;
	if (pModuleState->m_pCurrentWinApp == this)
		pModuleState->m_pCurrentWinApp = NULL;

	// free various strings allocated with _tcsdup
	free((void*)m_pszAppName);
	free((void*)m_pszRegistryKey);
	free((void*)m_pszExeName);
	free((void*)m_pszHelpFilePath);
	free((void*)m_pszProfileName);

	// avoid calling CloseHandle() on our own thread handle
	// during the CWinThread destructor
	m_hThread = NULL;
}

void WinApp::SaveStdProfileSettings()
{
	ASSERT_VALID(this);

	if (m_pRecentFileList != NULL)
		m_pRecentFileList->WriteList();

	if (m_nNumPreviewPages != 0)
		WriteProfileInt(_afxPreviewSection, _afxPreviewEntry, m_nNumPreviewPages);
}

int WinApp::ExitInstance()
{
	// if we remember that we're unregistering,
	// don't save our profile settings

	if (m_pCmdInfo == NULL ||
		m_pCmdInfo->m_nShellCommand != CCommandLineInfo::AppUnregister)
	{
		if (!afxContextIsDLL)
			SaveStdProfileSettings();
	}

	// Cleanup DAO if necessary
	if (m_lpfnDaoTerm != NULL)
	{
		// If a DLL, YOU must call AfxDaoTerm prior to ExitInstance
		ASSERT(!afxContextIsDLL);
		(*m_lpfnDaoTerm)();
	}

	return m_msgCur.wParam; // returns the value from PostQuitMessage
}

/////////////////////////////////////////////////////////////////////////////


// Main running routine until application exits
int WinApp::Run()
{
	if (m_pMainWnd == NULL && AfxOleGetUserCtrl())
	{
		// Not launched /Embedding or /Automation, but has no main window!
		TRACE0("Warning: m_pMainWnd is NULL in WinApp::Run - quitting application.\n");
		AfxPostQuitMessage(0);
	}
	return CWinThread::Run();
}


void AFXAPI AfxPostQuitMessage(int nExitCode)
{
	// cleanup OLE libraries
	CWinThread* pThread = AfxGetThread();
	if (pThread != NULL && pThread->m_lpfnOleTermOrFreeLib != NULL)
		(*pThread->m_lpfnOleTermOrFreeLib)(TRUE, TRUE);

	::PostQuitMessage(nExitCode);
}

/////////////////////////////////////////////////////////////////////////////
// WinHelp Helper


void WinApp::WinHelp(DWORD dwData, UINT nCmd)
{
	CWnd* pMainWnd = AfxGetMainWnd();
	ASSERT_VALID(pMainWnd);

	// return global app help mode state to FALSE (backward compatibility)
	m_bHelpMode = FALSE;
	pMainWnd->PostMessage(WM_KICKIDLE); // trigger idle update

	pMainWnd->WinHelp(dwData, nCmd);
}

/////////////////////////////////////////////////////////////////////////////
// Special exception handling

LRESULT WinApp::ProcessWndProcException(CException* e, const MSG* pMsg)
{
	// handle certain messages in CWinThread
	switch (pMsg->message)
	{
	case WM_CREATE:
	case WM_PAINT:
		return CWinThread::ProcessWndProcException(e, pMsg);
	}

	// handle all the rest
	UINT nIDP = AFX_IDP_INTERNAL_FAILURE;   // generic message string
	LRESULT lResult = 0;        // sensible default
	if (pMsg->message == WM_COMMAND)
	{
		if ((HWND)pMsg->lParam == NULL)
			nIDP = AFX_IDP_COMMAND_FAILURE; // command (not from a control)
		lResult = (LRESULT)TRUE;        // pretend the command was handled
	}
	if (e->IsKindOf(RUNTIME_CLASS(CMemoryException)))
	{
		e->ReportError(MB_ICONEXCLAMATION|MB_SYSTEMMODAL, nIDP);
	}
	else if (!e->IsKindOf(RUNTIME_CLASS(CUserException)))
	{
		// user has not been alerted yet of this catastrophic problem
		e->ReportError(MB_ICONSTOP, nIDP);
	}
	return lResult; // sensible default return from most WndProc functions
}

/////////////////////////////////////////////////////////////////////////////
// WinApp idle processing

BOOL WinApp::OnIdle(LONG lCount)
{
	if (lCount <= 0)
	{
		CWinThread::OnIdle(lCount);

		// call doc-template idle hook
		POSITION pos = NULL;
		if (m_pDocManager != NULL)
			pos = m_pDocManager->GetFirstDocTemplatePosition();

		while (pos != NULL)
		{
			CDocTemplate* pTemplate = m_pDocManager->GetNextDocTemplate(pos);
			ASSERT_KINDOF(CDocTemplate, pTemplate);
			pTemplate->OnIdle();
		}
	}
	else if (lCount == 1)
	{
		VERIFY(!CWinThread::OnIdle(lCount));
	}
	return lCount < 1;  // more to do if lCount < 1
}

/////////////////////////////////////////////////////////////////////////////
// WinApp idle processing

void WinApp::DevModeChange(LPTSTR lpDeviceName)
{
	if (m_hDevNames == NULL)
		return;

	LPDEVNAMES lpDevNames = (LPDEVNAMES)::GlobalLock(m_hDevNames);
	ASSERT(lpDevNames != NULL);
	if (lstrcmp((LPCTSTR)lpDevNames + lpDevNames->wDeviceOffset,
		lpDeviceName) == 0)
	{
		HANDLE hPrinter;
		if (!OpenPrinter(lpDeviceName, &hPrinter, NULL))
			return;

		// DEVMODE changed for the current printer
		if (m_hDevMode != NULL)
			AfxGlobalFree(m_hDevMode);

		// A zero for last param returns the size of buffer needed.
		int nSize = DocumentProperties(NULL, hPrinter, lpDeviceName,
			NULL, NULL, 0);
		ASSERT(nSize >= 0);
		m_hDevMode = GlobalAlloc(GHND, nSize);
		LPDEVMODE lpDevMode = (LPDEVMODE)GlobalLock(m_hDevMode);

		// Fill in the rest of the structure.
		if (DocumentProperties(NULL, hPrinter, lpDeviceName, lpDevMode,
			NULL, DM_OUT_BUFFER) != IDOK)
		{
			AfxGlobalFree(m_hDevMode);
			m_hDevMode = NULL;
		}
		ClosePrinter(hPrinter);
	}
}

///////////////////////////////////////////////////////////////////////////
// WinApp diagnostics

#ifdef _DEBUG
void WinApp::AssertValid() const
{
	CWinThread::AssertValid();

	ASSERT(vfxCurrentWinApp == this);
	ASSERT(vfxCurrentInstanceHandle == m_hInstance);

	if (AfxGetThread() != (CWinThread*)this)
		return;     // only do subset if called from different thread

	if (m_pDocManager != NULL)
		ASSERT_VALID(m_pDocManager);
}

void WinApp::Dump(CDumpContext& dc) const
{
	CWinThread::Dump(dc);

	dc << "m_hInstance = " << (UINT)m_hInstance;
	dc << "\nm_hPrevInstance = " << (UINT)m_hPrevInstance;
	dc << "\nm_lpCmdLine = " << m_lpCmdLine;
	dc << "\nm_nCmdShow = " << m_nCmdShow;
	dc << "\nm_pszAppName = " << m_pszAppName;
	dc << "\nm_bHelpMode = " << m_bHelpMode;
	dc << "\nm_pszExeName = " << m_pszExeName;
	dc << "\nm_pszHelpFilePath = " << m_pszHelpFilePath;
	dc << "\nm_pszProfileName = " << m_pszProfileName;
	dc << "\nm_hDevMode = " << (UINT)m_hDevMode;
	dc << "\nm_hDevNames = " << (UINT)m_hDevNames;
	dc << "\nm_dwPromptContext = " << m_dwPromptContext;

	if (m_pRecentFileList != NULL)
	{
		dc << "\nm_strRecentFiles[] = ";
		int nSize = m_pRecentFileList->GetSize();
		for (int i = 0; i < nSize; i++)
		{
			if ((*m_pRecentFileList)[i].GetLength() != 0)
				dc << "\n\tFile: " << (*m_pRecentFileList)[i];
		}
	}

	if (m_pDocManager != NULL)
		m_pDocManager->Dump(dc);

	dc << "\nm_nWaitCursorCount = " << m_nWaitCursorCount;
	dc << "\nm_hcurWaitCursorRestore = " << (UINT)m_hcurWaitCursorRestore;
	dc << "\nm_nNumPreviewPages = " << m_nNumPreviewPages;

	dc << "\nm_msgCur = {";
	dc << "\n\thwnd = " << (UINT)m_msgCur.hwnd;
	dc << "\n\tmessage = " << (UINT)m_msgCur.message;
	dc << "\n\twParam = " << (UINT)m_msgCur.wParam;
	dc << "\n\tlParam = " << (void*)m_msgCur.lParam;
	dc << "\n\ttime = " << m_msgCur.time;
	dc << "\n\tpt = " << CPoint(m_msgCur.pt);
	dc << "\n}";

	dc << "\n";
}
#endif


IMPLEMENT_DYNAMIC(WinApp, CWinThread)


PROCESS_LOCAL(_AFX_WIN_STATE, _afxWinState)

/////////////////////////////////////////////////////////////////////////////


// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"



/////////////////////////////////////////////////////////////////////////////
// WinApp UI related functions

void WinApp::EnableModeless(BOOL bEnable)
{
#ifdef _AFX_NO_OLE_SUPPORT
	UNUSED(bEnable);
#endif

	// no-op if main window is NULL or not a FrameWndInterface
	CWnd* pMainWnd = AfxGetMainWnd();
	if (pMainWnd == NULL || !pMainWnd->IsFrameWnd())
		return;

#ifndef _AFX_NO_OLE_SUPPORT
	// check if notify hook installed
/*	FrameWndInterface* pFrameWnd = dynamic_cast < FrameWndInterface * > (pMainWnd);
   ASSERT(pFrameWnd != NULL);
	if (pFrameWnd->GetNotifyHook() != NULL)
		pFrameWnd->GetNotifyHook()->OnEnableModeless(bEnable);*/
#endif
}

int WinApp::DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt)
{
	// disable windows for modal dialog
	EnableModeless(FALSE);
	HWND hWndTop;
	HWND hWnd = CWnd::GetSafeOwner_(NULL, &hWndTop);

	// set help context if possible
	DWORD* pdwContext = NULL;
	if (hWnd != NULL)
	{
		// use app-level context or frame level context
		LRESULT lResult = ::SendMessage(hWndTop, WM_HELPPROMPTADDR, 0, 0);
		if (lResult != 0)
			pdwContext = (DWORD*)lResult;
	}
	// for backward compatibility use app context if possible
	if (pdwContext == NULL && this != NULL)
		pdwContext = &m_dwPromptContext;

	DWORD dwOldPromptContext = 0;
	if (pdwContext != NULL)
	{
		// save old prompt context for restoration later
		dwOldPromptContext = *pdwContext;
		if (nIDPrompt != 0)
			*pdwContext = HID_BASE_PROMPT+nIDPrompt;
	}

	// determine icon based on type specified
	if ((nType & MB_ICONMASK) == 0)
	{
		switch (nType & MB_TYPEMASK)
		{
		case MB_OK:
		case MB_OKCANCEL:
			nType |= MB_ICONEXCLAMATION;
			break;

		case MB_YESNO:
		case MB_YESNOCANCEL:
			nType |= MB_ICONEXCLAMATION;
			break;

		case MB_ABORTRETRYIGNORE:
		case MB_RETRYCANCEL:
			// No default icon for these types, since they are rarely used.
			// The caller should specify the icon.
			break;
		}
	}

#ifdef _DEBUG
	if ((nType & MB_ICONMASK) == 0)
		TRACE0("Warning: no icon specified for message box.\n");
#endif

	TCHAR szAppName[_MAX_PATH];
	LPCTSTR pszAppName;
	if (this != NULL)
		pszAppName = m_pszAppName;
	else
	{
		pszAppName = szAppName;
		GetModuleFileName(NULL, szAppName, _MAX_PATH);
	}

	int nResult =
		::MessageBox(hWnd, lpszPrompt, pszAppName, nType);

	// restore prompt context if possible
	if (pdwContext != NULL)
		*pdwContext = dwOldPromptContext;

	// re-enable windows
	if (hWndTop != NULL)
		::EnableWindow(hWndTop, TRUE);
	EnableModeless(TRUE);

	return nResult;
}

int AFXAPI vfxMessageBox(LPCTSTR lpszText, UINT nType, UINT nIDHelp)
{
	WinApp* pApp = vfxGetApp();
	if (pApp != NULL)
		return pApp->DoMessageBox(lpszText, nType, nIDHelp);
	else
		return pApp->WinApp::DoMessageBox(lpszText, nType, nIDHelp);
}

int AFXAPI vfxMessageBox(UINT nIDPrompt, UINT nType, UINT nIDHelp)
{
	CString string;
	if (!string.LoadString(nIDPrompt))
	{
		TRACE1("Error: failed to load message box prompt string 0x%04x.\n",
			nIDPrompt);
		ASSERT(FALSE);
	}
	if (nIDHelp == (UINT)-1)
		nIDHelp = nIDPrompt;
	return vfxMessageBox(string, nType, nIDHelp);
}

////////////////////////////////////////////////////////////////////////////
// UI related CWnd functions

HWND PASCAL CWnd::GetSafeOwner_(HWND hParent, HWND* pWndTop)
{
	// get window to start with
	HWND hWnd = hParent;
	if (hWnd == NULL)
	{
/*		FrameWndInterface * pFrame = dynamic_cast < FrameWndInterface * > (CCmdTarget::GetRoutingFrame_());
		if (pFrame != NULL)
			hWnd = pFrame->GetSafeHwnd();
		else
			hWnd = AfxGetMainWnd()->GetSafeHwnd();*/
	}

	// a popup window cannot be owned by a child window
	while (hWnd != NULL && (::GetWindowLong(hWnd, GWL_STYLE) & WS_CHILD))
		hWnd = ::GetParent(hWnd);

	// determine toplevel window to disable as well
	HWND hWndTop = hWnd, hWndTemp = hWnd;
	for (;;)
	{
		if (hWndTemp == NULL)
			break;
		else
			hWndTop = hWndTemp;
		hWndTemp = ::GetParent(hWndTop);
	}

	// get last active popup of first non-child that was found
	if (hParent == NULL && hWnd != NULL)
		hWnd = ::GetLastActivePopup(hWnd);

	// disable and store top level parent window if specified
	if (pWndTop != NULL)
	{
		if (hWndTop != NULL && ::IsWindowEnabled(hWndTop) && hWndTop != hWnd)
		{
			*pWndTop = hWndTop;
			::EnableWindow(hWndTop, FALSE);
		}
		else
			*pWndTop = NULL;
	}

	return hWnd;    // return the owner as HWND
}

/////////////////////////////////////////////////////////////////////////////
// UI related CCmdTarget functions

/*CView* PASCAL CCmdTarget::GetRoutingView_()
{
	CView* pView = AfxGetThreadState()->m_pRoutingView;
	if (pView != NULL)
		ASSERT_VALID(pView);
	return pView;
}*/

/*FrameWndInterface* PASCAL CCmdTarget::GetRoutingFrame_()
{
	FrameWndInterface* pFrame = AfxGetThreadState()->m_pRoutingFrame;
	if (pFrame != NULL)
		ASSERT_VALID(pFrame);
	return pFrame;
}*/

/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// WinApp User Interface Extensions

void WinApp::OnAppExit()
{
	// same as double-clicking on main window close box
	ASSERT(m_pMainWnd != NULL);
	m_pMainWnd->SendMessage(WM_CLOSE);
}


void WinApp::HideApplication()
{
	ASSERT_VALID(m_pMainWnd);

	// hide the application's windows before closing all the documents
	m_pMainWnd->ShowWindow(SW_HIDE);
	m_pMainWnd->ShowOwnedPopups(FALSE);

	// put the window at the bottom of zorder, so it isn't activated
	m_pMainWnd->SetWindowPos(&CWnd::wndBottom, 0, 0, 0, 0,
		SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
}

void WinApp::DoWaitCursor(int nCode)
{
	// 0 => restore, 1=> begin, -1=> end
	ASSERT(nCode == 0 || nCode == 1 || nCode == -1);
	ASSERT(afxData.hcurWait != NULL);
	AfxLockGlobals(CRIT_WAITCURSOR);
	m_nWaitCursorCount += nCode;
	if (m_nWaitCursorCount > 0)
	{
		HCURSOR hcurPrev = ::SetCursor(afxData.hcurWait);
		if (nCode > 0 && m_nWaitCursorCount == 1)
			m_hcurWaitCursorRestore = hcurPrev;
	}
	else
	{
		// turn everything off
		m_nWaitCursorCount = 0;     // prevent underflow
		::SetCursor(m_hcurWaitCursorRestore);
	}
	AfxUnlockGlobals(CRIT_WAITCURSOR);
}


BOOL WinApp::SaveAllModified()
{
	if (m_pDocManager != NULL)
		return m_pDocManager->SaveAllModified();
	return TRUE;
}

void WinApp::AddToRecentFileList(LPCTSTR lpszPathName)
{
	ASSERT_VALID(this);
	ASSERT(lpszPathName != NULL);
	ASSERT(AfxIsValidString(lpszPathName));

	if (m_pRecentFileList != NULL)
		m_pRecentFileList->Add(lpszPathName);
}

CDocument* WinApp::OpenDocumentFile(LPCTSTR lpszFileName)
{
	ASSERT(m_pDocManager != NULL);
	return m_pDocManager->OpenDocumentFile(lpszFileName);
}

void WinApp::CloseAllDocuments(BOOL bEndSession)
{
	if (m_pDocManager != NULL)
		m_pDocManager->CloseAllDocuments(bEndSession);
}

/////////////////////////////////////////////////////////////////////////////
// MRU file list default implementation

void WinApp::OnUpdateRecentFileMenu(CCmdUI* pCmdUI)
{
	ASSERT_VALID(this);
	if (m_pRecentFileList == NULL) // no MRU files
		pCmdUI->Enable(FALSE);
	else
		m_pRecentFileList->UpdateMenu(pCmdUI);
}

/////////////////////////////////////////////////////////////////////////////
// DDE and ShellExecute support

BOOL WinApp::OnDDECommand(LPTSTR lpszCommand)
{
	if (m_pDocManager != NULL)
		return m_pDocManager->OnDDECommand(lpszCommand);
	else
		return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// MRU file list default implementation

BOOL WinApp::OnOpenRecentFile(UINT nID)
{
	ASSERT_VALID(this);
	ASSERT(m_pRecentFileList != NULL);

	ASSERT(nID >= ID_FILE_MRU_FILE1);
	ASSERT(nID < ID_FILE_MRU_FILE1 + (UINT)m_pRecentFileList->GetSize());
	int nIndex = nID - ID_FILE_MRU_FILE1;
	ASSERT((*m_pRecentFileList)[nIndex].GetLength() != 0);

	TRACE2("MRU: open file (%d) '%s'.\n", (nIndex) + 1,
			(LPCTSTR)(*m_pRecentFileList)[nIndex]);

	if (OpenDocumentFile((*m_pRecentFileList)[nIndex]) == NULL)
		m_pRecentFileList->Remove(nIndex);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
