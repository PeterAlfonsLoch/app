#if !defined(AFX_OPTIONSIMAGESDIALOG_H__06912007_CC8C_4F53_86A4_216EDF772857__INCLUDED_)
#define AFX_OPTIONSIMAGESDIALOG_H__06912007_CC8C_4F53_86A4_216EDF772857__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define BACKGROUND_IMAGE_CHANGE_MIN_SECONDS 1
#define BACKGROUND_IMAGE_CHANGE_MAX_SECONDS 10000
#define BACKGROUND_IMAGE_CHANGE_DEFAULT_SECONDS 60

// OptionsImagesDialog.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// COptionsImagesDialog dialog

class COptionsImagesDialog :
	public BaseForm
{
// Construction
public:
	virtual void _001InitializeFormPreData();
	COptionsImagesDialog();   // standard constructor
	//COptionsImagesDialog(CWnd* pParent = NULL);   // standard constructor
	COptionsImagesDialog(CWnd* pParent);   // standard constructor

// Attributes
	long	m_lChangeType;
	int		m_iChangeTime;

// Operations
	BOOL Update(BOOL bSaveAndValidate = TRUE);
	BOOL UpdateDatabase(BOOL bSaveAndValidate = TRUE);

// Dialog Data
	//{{AFX_DATA(COptionsImagesDialog)
	enum { IDD = IDD_OPTIONS_IMAGES };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsImagesDialog)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptionsImagesDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSIMAGESDIALOG_H__06912007_CC8C_4F53_86A4_216EDF772857__INCLUDED_)
