#if !defined(AFX_DDEFRAMEWND_H__BBE9043D_2071_4E38_AE3A_600C788230EE__INCLUDED_)
#define AFX_DDEFRAMEWND_H__BBE9043D_2071_4E38_AE3A_600C788230EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DDEFrameWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDDEFrameWnd frame

class CDDEFrameWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CDDEFrameWnd)
public:
	CDDEFrameWnd();           // protected constructor used by dynamic creation
protected:
	

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDDEFrameWnd)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDDEFrameWnd();

	// Generated message map functions
	//{{AFX_MSG(CDDEFrameWnd)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DDEFRAMEWND_H__BBE9043D_2071_4E38_AE3A_600C788230EE__INCLUDED_)
