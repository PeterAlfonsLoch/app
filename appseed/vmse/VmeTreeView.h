// VmeTreeView.h : interface of the CVmeTreeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VMETREEVIEW_H__6BF19D25_8D02_4F3B_95D5_DFF64C6D0044__INCLUDED_)
#define AFX_VMETREEVIEW_H__6BF19D25_8D02_4F3B_95D5_DFF64C6D0044__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVmeDoc;

class CVmeTreeView : public CTreeView
{
protected: // create from serialization only
	CVmeTreeView();
	DECLARE_DYNCREATE(CVmeTreeView)

// Attributes
public:
    class CTree
    {
    public:
        HTREEITEM hMidiTracksEvents;
    };
    enum EView
    {
        ViewMidiTracksEvents,
    };
    CTree m_tree;

	CVmeDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVmeTreeView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVmeTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVmeTreeView)
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in VmeTreeView.cpp
inline CVmeDoc* CVmeTreeView::GetDocument()
   { return (CVmeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VMETREEVIEW_H__6BF19D25_8D02_4F3B_95D5_DFF64C6D0044__INCLUDED_)
