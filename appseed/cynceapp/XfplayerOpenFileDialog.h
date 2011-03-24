#if !defined(AFX_XFPLAYEROPENFILEDIALOG_H__480F2A22_60B8_11D5_A9BB_00C0268E5959__INCLUDED_)
#define AFX_XFPLAYEROPENFILEDIALOG_H__480F2A22_60B8_11D5_A9BB_00C0268E5959__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XfplayerOpenFileDialog.h : header file
//
#include "guibase/BaseFileDialog.h"
/////////////////////////////////////////////////////////////////////////////
// CXfplayerOpenFileDialog dialog

class XfplayerOpenFileDialog :
	public BaseFileDialog,
	public DBInterface
{
   //OPENFILENAMEW m_ofn; // open file parameter block

	DECLARE_DYNAMIC(XfplayerOpenFileDialog)

public:
	XfplayerOpenFileDialog(//BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
      UINT uiTitle,
      DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		CWnd* pParentWnd = NULL);

public:
	friend UINT CALLBACK _AfxCommDlgProc(HWND, UINT, WPARAM, LPARAM);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//bool DoPrompt(UINT nIDSTitle, DWORD lFlags);
	AStrArray		m_straFile;	
	AStrTokenizer	m_strInitialDir;
	CString			m_strFile;
	virtual BOOL OnFileNameOK();
	virtual void OnFileNameChange();
	virtual void OnOK();
   void OnLBSelChangedNotify(UINT, UINT, UINT);
   CString GetNextPathName(POSITION& pos) const;
   POSITION GetStartPosition() const;
   //BOOL OnFileNameOK();

   //int DoModal();
protected:
	
   WString GetPathName() const;  // return full path and filename

	//{{AFX_MSG(CXfplayerOpenFileDialog)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
/*	BOOL m_bOpenFileDialog;       // TRUE for file open, FALSE for file save
	WString m_wstrFilter;          // filter string
						// separate fields with '|', terminate with '||\0'
	WCHAR m_szFileTitle[64];       // contains file title after return
	WCHAR m_szFileName[_MAX_PATH]; // contains full path name after return

	OPENFILENAMEW*  m_pofnTemp;*/

	//virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};

   // CFileDialog
/*_AFXDLGS_INLINE BOOL CFileDialog::GetReadOnlyPref() const
	{ return m_ofn.Flags & OFN_READONLY ? TRUE : FALSE; }
_AFXDLGS_INLINE void CFileDialog::SetTemplate(UINT nWin3ID, UINT nWin4ID)
	{ SetTemplate(MAKEINTRESOURCE(nWin3ID), MAKEINTRESOURCE(nWin4ID)); }*/
inline POSITION XfplayerOpenFileDialog::GetStartPosition() const
	{ return (POSITION)m_ofn.lpstrFile; }

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XFPLAYEROPENFILEDIALOG_H__480F2A22_60B8_11D5_A9BB_00C0268E5959__INCLUDED_)
