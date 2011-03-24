// npvmpView.h : interface of the CNpvmpView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NPVMPVIEW_H__E5D8F263_CFFB_4512_9EC1_ECBD44002FD5__INCLUDED_)
#define AFX_NPVMPVIEW_H__E5D8F263_CFFB_4512_9EC1_ECBD44002FD5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "npvmpLightDoc.h"

class CNpvmpCntrItem;

class CNpvmpView : public CView
{
protected: // create from serialization only
	CNpvmpView();
	DECLARE_DYNCREATE(CNpvmpView)

// Attributes
public:
	CNpvmpDoc* GetDocument();
	// m_pSelection holds the selection to the current CNpvmpCntrItem.
	// For many applications, such a member variable isn't adequate to
	//  represent a selection, such as a multiple selection or a selection
	//  of objects that are not CNpvmpCntrItem objects.  This selection
	//  mechanism is provided just to help you get started.

	// TODO: replace this selection mechanism with one appropriate to your app.
	CNpvmpCntrItem* m_pSelection;
	

	void InsertObject(LPCTSTR lpcsz = NULL);
	BOOL CreateItem(COleClientItem* pNewItem);
	BOOL CreateItemFromFile(COleClientItem* pNewItem, LPCTSTR lpcsz);


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNpvmpView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL IsSelected(const base_object* pDocItem) const;// Container support
	//}}AFX_VIRTUAL

// Implementation
public:
	void Layout();
	void SetDocument(CDocument * pdoc);
	virtual ~CNpvmpView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNpvmpView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	afx_msg void OnDestroy();
	afx_msg void OnSetFocus(base_wnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCancelEditCntr();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in npvmpView.cpp
inline CNpvmpDoc* CNpvmpView::GetDocument()
   { return (CNpvmpDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NPVMPVIEW_H__E5D8F263_CFFB_4512_9EC1_ECBD44002FD5__INCLUDED_)
