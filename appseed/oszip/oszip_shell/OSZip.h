#if !defined(AFX_OSZIP_H__A9CFF55A_5D1D_426B_B12E_9304BD2E4F22__INCLUDED_)
#define AFX_OSZIP_H__A9CFF55A_5D1D_426B_B12E_9304BD2E4F22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OSZip.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// OSZip window

class OSZip : public CWnd
{
	DECLARE_DYNCREATE(OSZip)

// Construction
public:
	OSZip();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(OSZip)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~OSZip();

	// Generated message map functions
protected:
	//{{AFX_MSG(OSZip)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(OSZip)
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(OSZip)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OSZIP_H__A9CFF55A_5D1D_426B_B12E_9304BD2E4F22__INCLUDED_)
