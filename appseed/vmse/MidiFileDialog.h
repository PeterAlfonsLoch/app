#if !defined(AFX_MIDIFILEDIALOG_H__5BAEC82E_2FF8_4C6D_8601_FD2F2E7DEB8B__INCLUDED_)
#define AFX_MIDIFILEDIALOG_H__5BAEC82E_2FF8_4C6D_8601_FD2F2E7DEB8B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XfplayerSaveFileDialog.h : header file
//

#ifdef _VMSE_DLL
    #define CLASS_DECL_VMSE  _declspec(dllexport)
#else
    #define CLASS_DECL_VMSE  _declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////////////////
// CMidiFileDialog dialog

class CLASS_DECL_VMSE CMidiFileDialog : public CFileDialog
{
	DECLARE_DYNAMIC(CMidiFileDialog)

public:
	int GetFileType();
	virtual void OnLBSelChangedNotify( UINT nIDBox, UINT iCurSel, UINT nCode);
    BOOL DoPromptFileName(CString& fileName, UINT nIDSTitle,
			DWORD lFlags, BOOL bOpenFileDialog, CDocTemplate* pTemplate,
            int & iTargetFileType);
	//bool DoPromptFileName(CString& fileName, UINT nIDSTitle, DWORD lFlags);
	CMidiFileDialog(//BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);
    
protected:
    int m_iFileType;
	//{{AFX_MSG(CMidiFileDialog)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIDIFILEDIALOG_H__5BAEC82E_2FF8_4C6D_8601_FD2F2E7DEB8B__INCLUDED_)
