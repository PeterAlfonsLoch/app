// lyricsXtractDlg.h : header file
//

#if !defined(AFX_LYRICSXTRACTDLG_H__C193B19B_74A3_42E0_A45B_5EA792530ED4__INCLUDED_)
#define AFX_LYRICSXTRACTDLG_H__C193B19B_74A3_42E0_A45B_5EA792530ED4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WStr.h"
#include "WStrArray.h"

class CLyricsXtractDlgAutoProxy;

/////////////////////////////////////////////////////////////////////////////
// CLyricsXtractDlg dialog

class CLyricsXtractDlg : public CDialog
{
	DECLARE_DYNAMIC(CLyricsXtractDlg);
	friend class CLyricsXtractDlgAutoProxy;

// Construction
public:
	CLyricsXtractDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CLyricsXtractDlg();

// Dialog Data
	//{{AFX_DATA(CLyricsXtractDlg)
	enum { IDD = IDD_LYRICSXTRACT_DIALOG };
	CEdit	m_editFolderPath;
	CEdit	m_editFilePath;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLyricsXtractDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

   void GetPaths(
      CWStrArray & wstra,
      CWStr wstrFolder,
      CWStrArray wstraExtensions);

	CLyricsXtractDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// Generated message map functions
	//{{AFX_MSG(CLyricsXtractDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnExtract();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LYRICSXTRACTDLG_H__C193B19B_74A3_42E0_A45B_5EA792530ED4__INCLUDED_)
