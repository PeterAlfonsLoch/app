#if !defined(AFX_OPTIONSIMAGESDIRECTORIESDIALOG_H__FB6AAEA5_4C1F_482D_9120_58511A82AF45__INCLUDED_)
#define AFX_OPTIONSIMAGESDIRECTORIESDIALOG_H__FB6AAEA5_4C1F_482D_9120_58511A82AF45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsImagesDirectoriesDialog.h : header file
//
//#include "vmsguibase/BaseForm.h"
/////////////////////////////////////////////////////////////////////////////
// COptionsImagesDirectoriesDialog dialog

class COptionsImagesDirectoriesDialog :
	public BaseForm
{
// Construction
public:
	bool IsModified();
	COptionsImagesDirectoriesDialog();   // standard constructor
	//COptionsImagesDirectoriesDialog(CWnd* pParent = NULL);   // standard constructor
	COptionsImagesDirectoriesDialog(CWnd* pParent);   // standard constructor

// Attributes
protected:
	bool			m_bModified;

// Operations
public:
	virtual void _001InitializeFormPreData();
	void SetModifiedFlag(bool bModified = true);
	BOOL Update(BOOL bSaveAndValidate = TRUE);
	BOOL UpdateDatabase(BOOL bSaveAndValidate = TRUE);

// Dialog Data
	//{{AFX_DATA(COptionsImagesDirectoriesDialog)
	enum { IDD = IDD_OPTIONS_IMAGES_DIRECTORIES };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsImagesDirectoriesDialog)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptionsImagesDirectoriesDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnRemove();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSIMAGESDIRECTORIESDIALOG_H__FB6AAEA5_4C1F_482D_9120_58511A82AF45__INCLUDED_)
