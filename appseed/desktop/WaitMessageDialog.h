#if !defined(AFX_WAITMESSAGEDIALOG_H__2B04893C_75BD_4EAA_9A06_A6EB94A96D98__INCLUDED_)
#define AFX_WAITMESSAGEDIALOG_H__2B04893C_75BD_4EAA_9A06_A6EB94A96D98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WaitMessageDialog.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// WaitMessageDialog dialog

class WaitMessageDialog :
   public BaseForm
{
// Construction
public:
   virtual void _001InitializeFormPreData();
	void UpdateTimeout();
	WaitMessageDialog(base_wnd* pParent = NULL);   // standard constructor
   WaitMessageDialog(LPCWSTR lpcszMessage, UINT uiDelay);

   WString    m_wstrMessage;
   UINT     m_uiDelay;
   UINT     m_uiStartTime;

// Dialog Data
	//{{AFX_DATA(WaitMessageDialog)
	enum { IDD = IDD_WAIT_MESSAGE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(WaitMessageDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(WaitMessageDialog)
	afx_msg void OnContinue();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAITMESSAGEDIALOG_H__2B04893C_75BD_4EAA_9A06_A6EB94A96D98__INCLUDED_)
