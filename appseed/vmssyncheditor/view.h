#pragma once

namespace vmssyncheditor
{

class view : public BaseView
{
public:
   view(::ca::application * papp);
	
	document* get_document();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(view)
	public:
	virtual void _001OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~view();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

#ifndef _DEBUG  // debug version in view.cpp
inline document* view::get_document()
   { return (document*)m_pDocument; }
#endif


} // namespace vmssyncheditor