// SHChangeNotifyDlg.h : header file
//

#if !defined(AFX_SHCHANGENOTIFYDLG_H__5E29BDAE_156A_40D5_8267_BD8BBB452284__INCLUDED_)
#define AFX_SHCHANGENOTIFYDLG_H__5E29BDAE_156A_40D5_8267_BD8BBB452284__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSHChangeNotifyDlgAutoProxy;

/////////////////////////////////////////////////////////////////////////////
// CSHChangeNotifyDlg dialog

class CSHChangeNotifyDlg : public CDialog
{
	DECLARE_DYNAMIC(CSHChangeNotifyDlg);
	friend class CSHChangeNotifyDlgAutoProxy;

// Construction
public:
	CSHChangeNotifyDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CSHChangeNotifyDlg();

// Dialog Data
	//{{AFX_DATA(CSHChangeNotifyDlg)
	enum { IDD = IDD_SHCHANGENOTIFY_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSHChangeNotifyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CSHChangeNotifyDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// Generated message map functions
	//{{AFX_MSG(CSHChangeNotifyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnFileAssoc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHCHANGENOTIFYDLG_H__5E29BDAE_156A_40D5_8267_BD8BBB452284__INCLUDED_)
