// XfplayerOpenFileDialog.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "../vms/Vms.h"
#include "XfplayerOpenFileDialog.h"

CXfplayerOpenFileDialog::CXfplayerOpenFileDialog(
		//BOOL bOpenFileDialog,
		LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, base_wnd* pParentWnd) :
		CFileDialog(true, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
}
/*

BEGIN_MESSAGE_MAP(CXfplayerOpenFileDialog, CFileDialog)
	//{{AFX_MSG_MAP(CXfplayerOpenFileDialog)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

*/

bool CXfplayerOpenFileDialog::DoPromptFileName(string& fileName, UINT nIDSTitle, DWORD lFlags)
{
	string title;
	VERIFY(title.LoadString(nIDSTitle));

	m_ofn.Flags |= lFlags;

	string strFilter;
	AStrTokenizer strTokenizer;
	string strToken;

	strTokenizer.LoadString(IDS_XFPLAYER_OPENFILEFILTER);

	while(strTokenizer.GetNextToken(strToken, _T("|"), false))
	{
		strFilter += strToken;
		strFilter += (TCHAR)'\0';   // next string please
		m_ofn.nMaxCustFilter++;
	}

	// append the "*.*" all files filter
	string allFilter;
	VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
	strFilter += allFilter;
	strFilter += (TCHAR)'\0';   // next string please
	strFilter += _T("*.*");
	strFilter += (TCHAR)'\0';   // last string
	m_ofn.nMaxCustFilter++;

	m_ofn.lpstrFilter = strFilter;
	m_ofn.lpstrTitle = title;
	m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);

	int nResult = DoModal();
	fileName.ReleaseBuffer();
	return nResult == IDOK;

}
