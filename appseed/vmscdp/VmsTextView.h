#if !defined(AFX_VMSTEXTVIEW_H__50DA2586_1A70_432E_A291_3787B8C874A7__INCLUDED_)
#define AFX_VMSTEXTVIEW_H__50DA2586_1A70_432E_A291_3787B8C874A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VmsTextView.h : header file
//
#include <afxrich.h>
/////////////////////////////////////////////////////////////////////////////
// CVmsTextView view

class CVmsTextView : public CRichEditView
{
protected:
	CVmsTextView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CVmsTextView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVmsTextView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CVmsTextView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CVmsTextView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VMSTEXTVIEW_H__50DA2586_1A70_432E_A291_3787B8C874A7__INCLUDED_)
