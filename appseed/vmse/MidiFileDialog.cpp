// XfplayerSaveFileDialog.cpp : implementation file
//

#include "stdafx.h"
#include "vmsmusresource.h"
#include "resource.h"
#include "VmpApp.h"
#include "MidiFileDialog.h"

#include "StrTokenizer.h"

#include "XfplayerDoc.h"

#include "MidiFile.h"

#include <DLGS.H>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMidiFileDialog

IMPLEMENT_DYNAMIC(CMidiFileDialog, CFileDialog)

CMidiFileDialog::CMidiFileDialog(//BOOL bOpenFileDialog,
        LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(false, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
}


BEGIN_MESSAGE_MAP(CMidiFileDialog, CFileDialog)
	//{{AFX_MSG_MAP(CMidiFileDialog)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CMidiFileDialog::DoPromptFileName(CString& fileName, UINT nIDSTitle,
			DWORD lFlags, BOOL bOpenFileDialog, CDocTemplate* pTemplate, int & iTargetFileType)
{

	CString title;
	VERIFY(title.LoadString(nIDSTitle));

	m_ofn.Flags |= lFlags;

	CString strFilter;
	CStrTokenizer strTokenizer;
	CString strToken;

	strTokenizer.LoadString(IDS_MIDI_SAVEFILEFILTER);

	while(strTokenizer.GetNextToken(strToken, _T("|"), false))
	{
		strFilter += strToken;
		strFilter += (TCHAR)'\0';   // next string please
		m_ofn.nMaxCustFilter++;
	}

	// append the "*.*" all files filter
//	CString allFilter;
//	VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
//	strFilter += allFilter;
//	strFilter += (TCHAR)'\0';   // next string please
//	strFilter += _T("*.*");
//	strFilter += (TCHAR)'\0';   // last string
//	m_ofn.nMaxCustFilter++;

	m_ofn.lpstrFilter = strFilter;
	m_ofn.lpstrTitle = title;
	m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);

	int nResult = DoModal();
	fileName.ReleaseBuffer();
    
    iTargetFileType = GetFileType();

	return nResult == IDOK;

}

void CMidiFileDialog::OnLBSelChangedNotify(UINT nIDBox, UINT iCurSel, UINT nCode)
{
    if(nIDBox == cmb1)
    {
        if(nCode == CD_LBSELCHANGE)
        {
            m_iFileType =  iCurSel;
        }
    }

}

int CMidiFileDialog::GetFileType()
{
    int iFileType = 0;
    if(m_iFileType == 0)
    {
        iFileType = CMidiFile::FileTypeXF;
    }
    else if(m_iFileType == 1)
    {
        iFileType = CMidiFile::FileTypeKar;
    }
    else if(m_iFileType == 2)
    {
        iFileType = CMidiFile::FileTypeTune1000;
    }
    return iFileType;

}
