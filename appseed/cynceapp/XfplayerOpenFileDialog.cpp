// XfplayerOpenFileDialog.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "XfplayerOpenFileDialog.h"
#include "gen/vfxstat_.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// XfplayerOpenFileDialog

IMPLEMENT_DYNAMIC(XfplayerOpenFileDialog, BaseFileDialog)

XfplayerOpenFileDialog::XfplayerOpenFileDialog(
		UINT nIDSTitle,
		DWORD dwFlags, CWnd* pParentWnd)
         : BaseFileDialog(TRUE, NULL, NULL, dwFlags, NULL, pParentWnd)
{


   WString wstrDefExt;
   WString wstrFileName;
   WString wstrFilter;

//   International::Utf8ToUnicode(wstrDefExt      , lpszDefExt);
  // International::Utf8ToUnicode(wstrFileName    , lpszFileName);
   //International::Utf8ToUnicode(wstrFilter      , lpszFilter);

   BOOL bOpenFileDialog = TRUE;
	DISetSection("XfplayerOpenFileDialog");
   DILoad("InitialDir", m_strInitialDir);

   WString wstr;
   International::Utf8ToUnicode(wstr, m_strInitialDir);
   m_ofn.lpstrInitialDir = wstr;

	m_nIDHelp = bOpenFileDialog ? AFX_IDD_FILEOPEN : AFX_IDD_FILESAVE;


	m_ofn.lpstrDefExt = wstrDefExt;
	m_ofn.lpstrFileTitle = m_szFileTitle;
	m_ofn.nMaxFileTitle = _countof(m_szFileTitle);
	m_ofn.Flags |= dwFlags | OFN_ENABLEHOOK | OFN_ENABLESIZING;
//xxx	if (!afxData.bWin4 && AfxHelpEnabled())
//		m_ofn.Flags |= OFN_SHOWHELP;
//	if (afxData.bWin4)
//	{
///		m_ofn.Flags |= OFN_EXPLORER;
	//	m_ofn.hInstance = AfxGetResourceHandle();
	//}
	//m_ofn.lpfnHook = (COMMDLGPROC)_AfxCommDlgProc;

	// setup initial file name
//	if (lpszFileName != NULL)
//		lstrcpynW(m_szFileName, wstrFileName, _countof(m_szFileName));

	// Translate filter into commdlg format (lots of \0)
/*	if (lpszFilter != NULL)
	{
		m_wstrFilter = lpszFilter;
		LPWSTR pch = m_wstrFilter.GetBuffer(0); // modify the buffer in place
		// MFC delimits with '|' not '\0'
		while ((pch = wcschr(pch, '|')) != NULL)
			*pch++ = '\0';
		m_ofn.lpstrFilter = m_wstrFilter;
		// do not call ReleaseBuffer() since the string contains '\0' characters
	}*/

WString title;
	VERIFY(title.LoadString(nIDSTitle));

	m_ofn.Flags |= dwFlags;

	WString strFilter;
	WStrTokenizer strTokenizer;
	WString strToken;

	strTokenizer.LoadString(IDS_XFPLAYER_OPENFILEFILTER2);

	while(strTokenizer.GetNextToken(strToken, L"|", false))
	{
		strFilter += strToken;
		strFilter += (TCHAR)'\0';   // next string please
		m_ofn.nMaxCustFilter++;
	}

	// append the "*.*" all files filter
	CString allFilter;
	VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
	strFilter += allFilter;
	strFilter += (TCHAR)'\0';   // next string please
	strFilter += L"*.*";
	strFilter += (TCHAR)'\0';   // last string
	m_ofn.nMaxCustFilter++;

	m_ofn.lpstrFilter = strFilter;

}


BEGIN_MESSAGE_MAP(XfplayerOpenFileDialog, BaseCommonDialog)
	//{{AFX_MSG_MAP(XfplayerOpenFileDialog)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/*bool XfplayerOpenFileDialog::DoPrompt(UINT nIDSTitle, DWORD lFlags)
{
	MusicalPlayerLightApp * papp = (MusicalPlayerLightApp *) AfxGetApp();

	m_straFile.RemoveAll();

	WString title;
	VERIFY(title.LoadString(nIDSTitle));

	m_ofn.Flags |= lFlags;

	WString strFilter;
	WStrTokenizer strTokenizer;
	WString strToken;

	strTokenizer.LoadString(IDS_XFPLAYER_OPENFILEFILTER2);

	while(strTokenizer.GetNextToken(strToken, L"|", false))
	{
		strFilter += strToken;
		strFilter += (TCHAR)'\0';   // next string please
		m_ofn.nMaxCustFilter++;
	}

	// append the "*.*" all files filter
	CString allFilter;
	VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
	strFilter += allFilter;
	strFilter += (TCHAR)'\0';   // next string please
	strFilter += L"*.*";
	strFilter += (TCHAR)'\0';   // last string
	m_ofn.nMaxCustFilter++;

	m_ofn.Flags |= OFN_ENABLEHOOK;
	if(!DILoad("InitialDir", m_strInitialDir))
	{
//xxx		papp->GetDefaultSongFolderPath(m_strInitialDir);
	}

	WString str;
   WString strInitialDir;
   strInitialDir = m_strInitialDir;
	m_ofn.lpstrFilter = strFilter;
	m_ofn.lpstrTitle = title;
	m_ofn.lpstrFile = str.GetBuffer(1024 * 1024);
	m_ofn.nMaxFile = 1024 * 1024;
	m_ofn.lpstrInitialDir = strInitialDir;
	m_ofn.lCustData = (UINT) (BaseCommonDialog *) this;
	//m_ofn.lpfnHook = _AfxCommDlgProc;

	int nResult = DoModal();
	if(nResult == IDCANCEL)
	{

		CString strFileName = GetPathName();

		if(!strFileName.IsEmpty())
		{
			m_straFile.Add(m_strFile);

	      CString strFilePath(m_strFile);
	      int i = strFilePath.GetLength();
	      bool b = false;
	      while(i > 0)
	      {
		      i--;
		      if(strFilePath[i] == '/' ||
			      strFilePath[i] == '\\')
		      {
			      b = true;
			      break;
		      }
	      }
	      m_strInitialDir = strFilePath.Left(i);

//			m_wstrInitialDir.ExtractFolderPath();	
			DISave("InitialDir", m_strFile);
		}
		
		return false;
	}
	//fileName.ReleaseBuffer();
	return nResult == IDOK;

}*/


BOOL XfplayerOpenFileDialog::OnFileNameOK()
{
	POSITION pos = GetStartPosition();
	
	while(pos != NULL)
	{
		m_straFile.Add(GetNextPathName(pos));
	}
	
	      CString strFilePath(m_strFile);
	      int i = strFilePath.GetLength();
	      bool b = false;
	      while(i > 0)
	      {
		      i--;
		      if(strFilePath[i] == '/' ||
			      strFilePath[i] == '\\')
		      {
			      b = true;
			      break;
		      }
	      }
	      m_strInitialDir = strFilePath.Left(i);
	
	DISave("InitialDir", m_strInitialDir);
	
	return false;
}

BOOL XfplayerOpenFileDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	return BaseCommonDialog::OnNotify(wParam, lParam, pResult);
}

BOOL XfplayerOpenFileDialog::OnCommand(WPARAM wParam, LPARAM lParam)
{
	return BaseCommonDialog::OnCommand(wParam, lParam);
}

void XfplayerOpenFileDialog::OnFileNameChange()
{
	m_strFile = GetPathName();
}

/*UINT _afxMsgLBSELCHANGE;
UINT		_afxMsgSHAREVI;
UINT		_afxMsgFILEOK;
UINT		_afxMsgCOLOROK;
UINT		_afxMsgHELP;
UINT		_afxMsgSETRGB;
UINT CALLBACK
_AfxCommDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (hWnd == NULL)
		return 0;

	_VFX_THREAD_STATE* pThreadState = _vfxThreadState.GetData();
	if (pThreadState->m_pAlternateWndInit != NULL && CWnd::FromHandlePermanent(hWnd) == NULL)
	{
		ASSERT_KINDOF(BaseFileDialog,pThreadState->m_pAlternateWndInit);
		pThreadState->m_pAlternateWndInit->SubclassWindow(hWnd);
		pThreadState->m_pAlternateWndInit = NULL;
	}

	if (message == WM_INITDIALOG)
	{
		OPENFILENAME * lpofn = (OPENFILENAME *)  lParam;
		BaseCommonDialog * pdlg = (BaseCommonDialog *)lpofn->lCustData;
		pdlg->SubclassWindow(hWnd);
		_afxMsgLBSELCHANGE = ::RegisterWindowMessage(LBSELCHSTRING);
		_afxMsgSHAREVI = ::RegisterWindowMessage(SHAREVISTRING);
		_afxMsgFILEOK = ::RegisterWindowMessage(FILEOKSTRING);
		_afxMsgCOLOROK = ::RegisterWindowMessage(COLOROKSTRING);
		_afxMsgHELP = ::RegisterWindowMessage(HELPMSGSTRING);
		_afxMsgSETRGB = ::RegisterWindowMessage(SETRGBSTRING);
		return (UINT)AfxDlgProc(hWnd, message, wParam, lParam);
	}

//xxx	if (message == _afxMsgHELP ||
	   //(message == WM_COMMAND && LOWORD(wParam) == pshHelp))
	//{
		// just translate the message into the AFX standard help command.
	//	SendMessage(hWnd, WM_COMMAND, ID_HELP, 0);
	//	return 1;
	//}

//	if (message < 0xC000)
//	{
		// not a ::RegisterWindowMessage message
//		return 0;
//	}

	// assume it is already wired up to a permanent one
	CDialog* pDlg = (CDialog*)CWnd::FromHandlePermanent(hWnd);
	if(pDlg == NULL)
		return 0;
//	ASSERT(pDlg != NULL);
//	ASSERT_KINDOF(CDialog, pDlg);

/*	if (pDlg->IsKindOf(RUNTIME_CLASS(BaseCommonDialog)))
	{
		// If we're exploring then we are not interested in the Registered messages
		if (((BaseCommonDialog*)pDlg)->m_ofn.Flags & OFN_EXPLORER)
			return 0;
	}*/

	// RegisterWindowMessage - does not copy to lastState buffer, so
	// CWnd::GetCurrentMessage and CWnd::Default will NOT work
	// while in these handlers

	// Dispatch special commdlg messages through our virtual callbacks
	/*if (message == _afxMsgSHAREVI)
	{
//		ASSERT_KINDOF(XfplayerOpenFileDialog, pDlg);
//		return ((XfplayerOpenFileDialog*)pDlg)->OnShareViolation((LPCTSTR)lParam);
	}
	else if (message == _afxMsgFILEOK)
	{
		ASSERT_KINDOF(XfplayerOpenFileDialog, pDlg);

//xxx		if (afxData.bWin4)
	//xxx		((XfplayerOpenFileDialog*)pDlg)->m_pofnTemp = (OPENFILENAMEW*)lParam;

		BOOL bResult = ((XfplayerOpenFileDialog*)pDlg)->OnFileNameOK();

		((XfplayerOpenFileDialog*)pDlg)->m_pofnTemp = NULL;

		return bResult;
	}
	else if (message == _afxMsgLBSELCHANGE)
	{
		ASSERT_KINDOF(XfplayerOpenFileDialog, pDlg);
		((XfplayerOpenFileDialog*)pDlg)->OnLBSelChangedNotify(wParam, LOWORD(lParam),
				HIWORD(lParam));
		return 0;
	}
	else if (message == _afxMsgCOLOROK)
	{
		ASSERT_KINDOF(CColorDialog, pDlg);
		return ((CColorDialog*)pDlg)->OnColorOK();
	}
	else if (message == _afxMsgSETRGB)
	{
		// nothing to do here, since this is a SendMessage
		return 0;
	}
	else if (message == WM_COMMAND)
	{
		SendMessage(hWnd, WM_COMMAND, wParam, lParam);
	}
	return 0;
}*/

void XfplayerOpenFileDialog::OnOK()
{
	BaseCommonDialog::OnOK();
}


/*int XfplayerOpenFileDialog::DoModal()
{
	ASSERT_VALID(this);
	ASSERT(m_ofn.Flags & OFN_ENABLEHOOK);
	ASSERT(m_ofn.lpfnHook != NULL); // can still be a user hook

	// zero out the file buffer for consistent parsing later
	ASSERT(AfxIsValidAddress(m_ofn.lpstrFile, m_ofn.nMaxFile));
	DWORD nOffset = lstrlenW(m_ofn.lpstrFile)+1;
	ASSERT(nOffset <= m_ofn.nMaxFile);
	memset(m_ofn.lpstrFile+nOffset, 0, (m_ofn.nMaxFile-nOffset)*sizeof(TCHAR));

	// WINBUG: This is a special case for the file open/save dialog,
	//  which sometimes pumps while it is coming up but before it has
	//  disabled the main window.
	HWND hWndFocus = ::GetFocus();
	BOOL bEnableParent = FALSE;
	m_ofn.hwndOwner = PreModal();
	AfxUnhookWindowCreate();
	if (m_ofn.hwndOwner != NULL && ::IsWindowEnabled(m_ofn.hwndOwner))
	{
		bEnableParent = TRUE;
		::EnableWindow(m_ofn.hwndOwner, FALSE);
	}

	_VFX_THREAD_STATE* pThreadState = vfxGetThreadState();
	ASSERT(pThreadState->m_pAlternateWndInit == NULL);

	if (m_ofn.Flags & OFN_EXPLORER)
		pThreadState->m_pAlternateWndInit = this;
	else
		AfxHookWindowCreate(this);

	int nResult;
	if (m_bOpenFileDialog)
		nResult = ::GetOpenFileNameW(&m_ofn);
	else
		nResult = ::GetSaveFileNameW(&m_ofn);

	if (nResult)
		ASSERT(pThreadState->m_pAlternateWndInit == NULL);
	pThreadState->m_pAlternateWndInit = NULL;

	// WINBUG: Second part of special case for file open/save dialog.
	if (bEnableParent)
		::EnableWindow(m_ofn.hwndOwner, TRUE);
	if (::IsWindow(hWndFocus))
		::SetFocus(hWndFocus);

	PostModal();
	return nResult ? nResult : IDCANCEL;
}*/

#define _wcsdec(_cpc1, _cpc2) ((_cpc1)>=(_cpc2) ? NULL : (_cpc2)-1)

#define _wcsinc(_pc)    ((_pc)+1)

CString XfplayerOpenFileDialog::GetNextPathName(POSITION& pos) const
{
   CString strRet;
	BOOL bExplorer = m_ofn.Flags & OFN_EXPLORER;
	TCHAR chDelimiter;
	if (bExplorer)
		chDelimiter = '\0';
	else
		chDelimiter = ' ';

	LPWSTR lpsz = (LPWSTR)pos;
	if (lpsz == m_ofn.lpstrFile) // first time
	{
		if ((m_ofn.Flags & OFN_ALLOWMULTISELECT) == 0)
		{
			pos = NULL;
			return m_ofn.lpstrFile;
		}

		// find char pos after first Delimiter
		while(*lpsz != chDelimiter && *lpsz != '\0')
			lpsz = _wcsinc(lpsz);
		lpsz = _wcsinc(lpsz);

		// if single selection then return only selection
		if (*lpsz == 0)
		{
			pos = NULL;
			return m_ofn.lpstrFile;
		}
	}

	WString strPath = m_ofn.lpstrFile;
	if (!bExplorer)
	{
		LPWSTR lpszPath = m_ofn.lpstrFile;
		while(*lpszPath != chDelimiter)
			lpszPath = _wcsinc(lpszPath);
		strPath = strPath.Left(lpszPath - m_ofn.lpstrFile);
	}

	LPWSTR lpszFileName = lpsz;
	WString strFileName = lpsz;

	// find char pos at next Delimiter
	while(*lpsz != chDelimiter && *lpsz != '\0')
		lpsz = _wcsinc(lpsz);

	if (!bExplorer && *lpsz == '\0')
		pos = NULL;
	else
	{
		if (!bExplorer)
			strFileName = strFileName.Left(lpsz - lpszFileName);

		lpsz = _wcsinc(lpsz);
		if (*lpsz == '\0') // if double terminated then done
			pos = NULL;
		else
			pos = (POSITION)lpsz;
	}

	// only add '\\' if it is needed
	if (!strPath.IsEmpty())
	{
		// check for last back-slash or forward slash (handles DBCS)
		LPCWSTR lpsz = wcsrchr(strPath, '\\');
		if (lpsz == NULL)
			lpsz = wcsrchr(strPath, '/');
		// if it is also the last character, then we don't need an extra
		if (lpsz != NULL &&
			(lpsz - (LPCWSTR)strPath) == strPath.GetLength()-1)
		{
			ASSERT(*lpsz == '\\' || *lpsz == '/');
         International::UnicodeToUtf8(strRet, strPath + strFileName);
         return strRet;
		}
	}
   International::UnicodeToUtf8(strRet, strPath + L'\\' + strFileName);
	return strRet;
}

/*BOOL XfplayerOpenFileDialog::OnFileNameOK()
{
	ASSERT_VALID(this);

	// Do not call Default() if you override
	return FALSE;
}*/

void XfplayerOpenFileDialog::OnLBSelChangedNotify(UINT, UINT, UINT)
{
	ASSERT_VALID(this);

	// Do not call Default() if you override
	// no default processing needed
}


WString XfplayerOpenFileDialog::GetPathName() const
{
	if ((m_ofn.Flags & OFN_EXPLORER) && m_hWnd != NULL)
	{
		ASSERT(::IsWindow(m_hWnd));
		WString strResult;
		if (GetParent()->SendMessage(CDM_GETSPEC, (WPARAM)MAX_PATH,
			(LPARAM)strResult.GetBuffer(MAX_PATH)) < 0)
		{
			strResult.Empty();
		}
		else
		{
			strResult.ReleaseBuffer();
		}

		if (!strResult.IsEmpty())
		{
			if (GetParent()->SendMessage(CDM_GETFILEPATH, (WPARAM)MAX_PATH,
				(LPARAM)strResult.GetBuffer(MAX_PATH)) < 0)
				strResult.Empty();
			else
			{
				strResult.ReleaseBuffer();
				return strResult;
			}
		}
	}
	return m_ofn.lpstrFile;
}
