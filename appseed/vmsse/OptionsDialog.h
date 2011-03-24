#if !defined(AFX_OPTIONSDIALOG_H__67C442B3_8473_4CD7_A4F5_BB577546215A__INCLUDED_)
#define AFX_OPTIONSDIALOG_H__67C442B3_8473_4CD7_A4F5_BB577546215A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptionsDialog dialog

#include "DBClient.h"

class COptionsSongsDirectoriesDialog;
class COptionsImagesDirectoriesDialog;
class COptionsImagesDialog;
class COptionsAudioDevicesDialog;

class COptionsDialog
	: public CDialog,
	public CDBClient

{
// Construction
public:
	BOOL Create(CWnd * pwndParent = NULL);
	void Apply();
//	COptionsDialog(CWnd* pParent = NULL);   // standard constructor
	COptionsDialog();   // standard constructor
	COptionsDialog(CWnd* pParent);   // standard constructor
	~COptionsDialog();   // standard constructor
// Attributes
    COptionsSongsDirectoriesDialog *	m_pSongsDirsDlg;
	//COptionsImagesDirectoriesDialog *	m_pImagesDirsDlg;
	//COptionsImagesDialog	*			m_pImagesDlg;
    //COptionsAudioDevicesDialog *		m_pAudioDevsDlg;
	

// Dialog Data
	//{{AFX_DATA(COptionsDialog)
	enum { IDD = IDD_OPTIONS };
	CTabCtrl	m_Tab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsDialog)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptionsDialog)
	afx_msg void OnSelchangingTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnApply();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSDIALOG_H__67C442B3_8473_4CD7_A4F5_BB577546215A__INCLUDED_)
