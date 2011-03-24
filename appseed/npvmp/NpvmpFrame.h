#if !defined(AFX_NPVMPFRAME_H__27D9CD3C_C79C_4C1B_9AAC_8910084338B9__INCLUDED_)
#define AFX_NPVMPFRAME_H__27D9CD3C_C79C_4C1B_9AAC_8910084338B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NpvmpFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNpvmpFrame frame

class CNpvmpFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CNpvmpFrame)
protected:
	CNpvmpFrame();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNpvmpFrame)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CNpvmpFrame();

	// Generated message map functions
	//{{AFX_MSG(CNpvmpFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NPVMPFRAME_H__27D9CD3C_C79C_4C1B_9AAC_8910084338B9__INCLUDED_)
