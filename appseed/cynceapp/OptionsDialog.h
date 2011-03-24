#if !defined(AFX_OPTIONSDIALOG_H__67C442B3_8473_4CD7_A4F5_BB577546215A__INCLUDED_)
#define AFX_OPTIONSDIALOG_H__67C442B3_8473_4CD7_A4F5_BB577546215A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsDialog.h : header file
//
#include "guibase/SimpleTabCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// OptionsDialog dialog

class COptionsSongsDirectoriesDialog;
class OptionsGeneralDialog;
class COptionsImagesDirectoriesDialog;
class COptionsImagesDialog;
class COptionsAudioDevicesDialog;
class CFileAssociationForm;

class OptionsDialog :
	public BaseForm,
	public DBInterface
{
// Construction
public:
	bool Apply();
//	OptionsDialog(CWnd* pParent = NULL);   // standard constructor
	OptionsDialog();   // standard constructor
	OptionsDialog(CWnd* pParent);   // standard constructor
	~OptionsDialog();   // standard constructor
// Attributes
	COptionsSongsDirectoriesDialog *	m_pSongsDirsDlg;
   OptionsGeneralDialog *	            m_pdlgGeneral;
	COptionsImagesDirectoriesDialog *	m_pImagesDirsDlg;
	COptionsImagesDialog	*			m_pImagesDlg;
   COptionsAudioDevicesDialog *		m_pAudioDevsDlg;
   CFileAssociationForm *           m_pfileassociationform;
	
   void _001InitializeFormPreData();

// Dialog Data
	//{{AFX_DATA(OptionsDialog)
	enum { IDD = IDD_OPTIONS };
	SimpleTabCtrl	m_Tab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(OptionsDialog)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(OptionsDialog)
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
