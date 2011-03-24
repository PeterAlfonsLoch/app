#if !defined(AFX_ERRORDIALOG_H__B0334111_6B03_4E0D_B6E9_E7AB7D0FAF2F__INCLUDED_)
#define AFX_ERRORDIALOG_H__B0334111_6B03_4E0D_B6E9_E7AB7D0FAF2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ErrorDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CErrorDialog dialog


class CErrorDialog : public CDialog
{
// Construction
public:
	CErrorDialog(base_wnd* pParent = NULL);   // standard constructor

public:

// Dialog Data
protected:
	CBitmap				m_bmpImage;
	//MMRESULT			m_mmrc;
public:
	//{{AFX_DATA(CErrorDialog)
	enum { IDD = IDD_ERROR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CErrorDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CErrorDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERRORDIALOG_H__B0334111_6B03_4E0D_B6E9_E7AB7D0FAF2F__INCLUDED_)
