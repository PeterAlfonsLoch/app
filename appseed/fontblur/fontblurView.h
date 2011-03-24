// fontblurView.h : interface of the CFontblurView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FONTBLURVIEW_H__AA4920F4_916A_4F5C_986E_7FF88343512D__INCLUDED_)
#define AFX_FONTBLURVIEW_H__AA4920F4_916A_4F5C_986E_7FF88343512D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFontblurView : public CView
{
protected: // create from serialization only
	CFontblurView();
	DECLARE_DYNCREATE(CFontblurView)

// Attributes
public:
	CFontblurDoc* GetDocument();

   CFont       m_font1;
   CDC         m_dc1;
   CBitmap     m_bitmap1;
   CDC         m_dc2;
   CBitmap     m_bitmap2;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFontblurView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFontblurView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFontblurView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in fontblurView.cpp
inline CFontblurDoc* CFontblurView::GetDocument()
   { return (CFontblurDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FONTBLURVIEW_H__AA4920F4_916A_4F5C_986E_7FF88343512D__INCLUDED_)
