// DupView.h : interface of the DupView class
//


#pragma once


class DupView :
   public CView,
   public Ex1ListInterface,
   public iguimessage::MessageDispatch
{
protected: // create from serialization only
	DupView();
	DECLARE_DYNCREATE(DupView)

// Attributes
public:
	DupDoc* GetDocument() const;

// Operations
public:

   virtual void _001InsertColumns();

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~DupView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
   virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};

#ifndef _DEBUG  // debug version in DupView.cpp
inline DupDoc* DupView::GetDocument() const
   { return reinterpret_cast<DupDoc*>(m_pDocument); }
#endif

