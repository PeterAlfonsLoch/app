// vmsmiditonetView.h : interface of the CVmsmiditonetView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VMSMIDITONETVIEW_H__EA18FE56_7BDE_4B9C_8668_DD3119C655D0__INCLUDED_)
#define AFX_VMSMIDITONETVIEW_H__EA18FE56_7BDE_4B9C_8668_DD3119C655D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CVmsmiditonetView : public CView
{
protected: // create from serialization only
	CVmsmiditonetView();
	DECLARE_DYNCREATE(CVmsmiditonetView)

// Attributes
public:
	CVmsmiditonetDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVmsmiditonetView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void Stop();
	void Go();
	virtual ~CVmsmiditonetView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVmsmiditonetView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in vmsmiditonetView.cpp
inline CVmsmiditonetDoc* CVmsmiditonetView::GetDocument()
   { return (CVmsmiditonetDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VMSMIDITONETVIEW_H__EA18FE56_7BDE_4B9C_8668_DD3119C655D0__INCLUDED_)
