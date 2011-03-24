#pragma once


// SplitFileDialog dialog

class SplitFileDialog : public CDialog
{
	DECLARE_DYNAMIC(SplitFileDialog)

public:
	SplitFileDialog(LPCTSTR lpcszFile, CWnd* pParent = NULL);   // standard constructor
	virtual ~SplitFileDialog();

// Dialog Data
	enum { IDD = IDD_SPLIT_FILE };

   CString m_strFile;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
   virtual void OnOK();
public:
   int m_iValue;
public:
   afx_msg void OnCbnSelchangeCombo1();
public:
   CString m_strMult;
public:
   virtual BOOL OnInitDialog();
};
