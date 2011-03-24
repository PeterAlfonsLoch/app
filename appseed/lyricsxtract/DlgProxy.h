// DlgProxy.h : header file
//

#if !defined(AFX_DLGPROXY_H__C0E2C4F2_A3E2_409B_B34E_1781BC86047A__INCLUDED_)
#define AFX_DLGPROXY_H__C0E2C4F2_A3E2_409B_B34E_1781BC86047A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLyricsXtractDlg;

/////////////////////////////////////////////////////////////////////////////
// CLyricsXtractDlgAutoProxy command target

class CLyricsXtractDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CLyricsXtractDlgAutoProxy)

	CLyricsXtractDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CLyricsXtractDlg* m_pDialog;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLyricsXtractDlgAutoProxy)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CLyricsXtractDlgAutoProxy();

	// Generated message map functions
	//{{AFX_MSG(CLyricsXtractDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CLyricsXtractDlgAutoProxy)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CLyricsXtractDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROXY_H__C0E2C4F2_A3E2_409B_B34E_1781BC86047A__INCLUDED_)
