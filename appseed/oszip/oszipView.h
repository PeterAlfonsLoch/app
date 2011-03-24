// oszipView.h : interface of the COszipView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OSZIPVIEW_H__86FB7F54_A9A2_4306_B3F5_7167957AFA61__INCLUDED_)
#define AFX_OSZIPVIEW_H__86FB7F54_A9A2_4306_B3F5_7167957AFA61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class COszipDoc;

class CLASS_DECL_OSZIP COszipView : public CHtmlView
{
protected: // create from serialization only
	COszipView();
	DECLARE_DYNCREATE(COszipView)

// Attributes
public:
	COszipDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COszipView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COszipView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COszipView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in oszipView.cpp
inline COszipDoc* COszipView::GetDocument()
   { return (COszipDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OSZIPVIEW_H__86FB7F54_A9A2_4306_B3F5_7167957AFA61__INCLUDED_)
