#pragma once

class CXfplayerOpenFileDialog : public CFileDialog
{
public:
	CXfplayerOpenFileDialog(//BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		base_wnd* pParentWnd = NULL);

public:
	bool DoPromptFileName(string& fileName, UINT nIDSTitle, DWORD lFlags);

protected:
};
