#if !defined(AFX_PANEVIEW_H__AA089937_9656_4C44_849A_DAD4D293EF96__INCLUDED_)
#define AFX_PANEVIEW_H__AA089937_9656_4C44_849A_DAD4D293EF96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PaneView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PaneView view

class PaneView : public CView
{
protected:
	PaneView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(PaneView)

// Attributes
public:

   

// Operations
public:
   static CWnd* CreateView(CCreateContext* pContext, UINT nID, CWnd * pwndParent);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PaneView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~PaneView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(PaneView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANEVIEW_H__AA089937_9656_4C44_849A_DAD4D293EF96__INCLUDED_)
