#if !defined(AFX_WELCOMEDIALOG_H__5FE1F7EE_35AD_46BD_8C50_497DB143E7AF__INCLUDED_)
#define AFX_WELCOMEDIALOG_H__5FE1F7EE_35AD_46BD_8C50_497DB143E7AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WelcomeDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWelcomeDialog dialog

class CWelcomeDialog : public CDialog
{
// Construction
public:
	CWelcomeDialog(base_wnd* pParent = NULL);   // standard constructor

public:
    CBrush      m_brushBackground;
    COLORREF    m_crBackground;
    COLORREF    m_crForeground;


// Dialog Data
	//{{AFX_DATA(CWelcomeDialog)
	enum { IDD = IDD_WELCOME };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWelcomeDialog)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWelcomeDialog)
	afx_msg void OnToolsAlbum();
	afx_msg void OnPlayer();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, base_wnd* pWnd, UINT nCtlColor);
	afx_msg void OnClose();
	//}}AFX_MSG
	//DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WELCOMEDIALOG_H__5FE1F7EE_35AD_46BD_8C50_497DB143E7AF__INCLUDED_)
