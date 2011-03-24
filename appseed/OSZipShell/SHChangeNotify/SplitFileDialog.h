#pragma once


// SplitFileDialog dialog

class SplitFileDialog : public CDialog
{
	DECLARE_DYNAMIC(SplitFileDialog)

public:
	SplitFileDialog(LPCTSTR lpcszFile, CWnd* pParent = NULL);   // standard constructor
	virtual ~SplitFileDialog();

// Dialog Data
	enum { IDD = IDHELP };

   CString m_strFile;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
