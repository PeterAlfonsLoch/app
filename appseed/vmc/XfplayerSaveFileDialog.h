#pragma once

class CXfplayerSaveFileDialog : public CFileDialog
{
public:
    BOOL DoPromptFileName(string& fileName, UINT nIDSTitle,
			DWORD lFlags, BOOL bOpenFileDialog, DocumentTemplate* pTemplate);
	//bool DoPromptFileName(string& fileName, UINT nIDSTitle, DWORD lFlags);
	CXfplayerSaveFileDialog(//BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		base_wnd* pParentWnd = NULL);

protected:
	//{{AFX_MSG(CXfplayerSaveFileDialog)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
