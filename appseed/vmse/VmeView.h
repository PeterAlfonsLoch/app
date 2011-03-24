// VmeView.h : interface of the CVmeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VMEVIEW_H__104567AF_E4A2_46CC_97EA_9A06C2CD8E32__INCLUDED_)
#define AFX_VMEVIEW_H__104567AF_E4A2_46CC_97EA_9A06C2CD8E32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVmeCntrItem;
class CMidiTracksEventsView;

class CVmeView : public CView
{
protected: // create from serialization only
	CVmeView();
	DECLARE_DYNCREATE(CVmeView)

// Attributes
public:
    enum EView
    {
        ViewMidiTracksEvents,
    };
    EView m_view;
	CVmeDoc* GetDocument();
    CMidiTracksEventsView * m_pmiditracksview;
    CView * m_pviewCurrent;
	// m_pSelection holds the selection to the current CVmeCntrItem.
	// For many applications, such a member variable isn't adequate to
	//  represent a selection, such as a multiple selection or a selection
	//  of objects that are not CVmeCntrItem objects.  This selection
	//  mechanism is provided just to help you get started.

	// TODO: replace this selection mechanism with one appropriate to your app.
	CVmeCntrItem* m_pSelection;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVmeView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL IsSelected(const CObject* pDocItem) const;// Container support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	void Layout();
	void View(EView view);
	virtual ~CVmeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVmeView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	afx_msg void OnDestroy();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnInsertObject();
	afx_msg void OnCancelEditCntr();
	afx_msg void OnCancelEditSrvr();
	//}}AFX_MSG
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in VmeView.cpp
inline CVmeDoc* CVmeView::GetDocument()
   { return (CVmeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VMEVIEW_H__104567AF_E4A2_46CC_97EA_9A06C2CD8E32__INCLUDED_)
