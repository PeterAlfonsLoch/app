#pragma once

class CEditV017 : public CEdit
{
// Construction
public:
	CEditV017();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditV017)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEditV017();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditV017)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	//DECLARE_MESSAGE_MAP()
};

