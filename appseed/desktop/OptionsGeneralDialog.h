#if !defined(AFX_OPTIONSGENERALDIALOG_H__0CA7A5F5_2BD3_4ADB_8E8F_2B6019D55C4E__INCLUDED_)
#define AFX_OPTIONSGENERALDIALOG_H__0CA7A5F5_2BD3_4ADB_8E8F_2B6019D55C4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsGeneralDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// OptionsGeneralDialog dialog

class OptionsGeneralDialog :
	public BaseForm
{
// Construction
public:
	OptionsGeneralDialog(base_wnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(OptionsGeneralDialog)
	enum { IDD = IDD_OPTIONS_GENERAL };
	//BOOL	   m_bMRUEnable;
	//int		m_iMRUCount;
	//int		m_iDelay;
	//}}AFX_DATA

   BOOL Update(BOOL bSaveAndValidate = TRUE);
	BOOL UpdateDatabase(BOOL bSaveAndValidate = TRUE);

   virtual void _001InitializeFormPreData();

//    int m_iMRUCount;
//    BOOL m_bMRUEnable;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(OptionsGeneralDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(OptionsGeneralDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSGENERALDIALOG_H__0CA7A5F5_2BD3_4ADB_8E8F_2B6019D55C4E__INCLUDED_)
