// DlgProxy.h : header file
//

#if !defined(AFX_DLGPROXY_H__0F08D45C_D957_4930_9EE3_924B7EFA7981__INCLUDED_)
#define AFX_DLGPROXY_H__0F08D45C_D957_4930_9EE3_924B7EFA7981__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSHChangeNotifyDlg;

/////////////////////////////////////////////////////////////////////////////
// CSHChangeNotifyDlgAutoProxy command target

class CSHChangeNotifyDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CSHChangeNotifyDlgAutoProxy)

	CSHChangeNotifyDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CSHChangeNotifyDlg* m_pDialog;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSHChangeNotifyDlgAutoProxy)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSHChangeNotifyDlgAutoProxy();

	// Generated message map functions
	//{{AFX_MSG(CSHChangeNotifyDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CSHChangeNotifyDlgAutoProxy)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CSHChangeNotifyDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROXY_H__0F08D45C_D957_4930_9EE3_924B7EFA7981__INCLUDED_)
