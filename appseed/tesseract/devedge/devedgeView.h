// screencaptureView.h: interface for the screencaptureView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEDIAVIEW_H__B60D1BB7_7ADE_488E_83B9_2CC74EA09DFB__INCLUDED_)
#define AFX_MEDIAVIEW_H__B60D1BB7_7ADE_488E_83B9_2CC74EA09DFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class devedgeDoc;

namespace devedge
{
	class KeyboardFocus;
	class Element2D;
} // namespace devedge


class CLASS_DECL_CA2_DEVEDGE devedgeView : public base_edit_plain_text_view
{
public:
	devedgeView(::ca::application * papp);           // protected constructor used by dynamic creation
	// DECLARE_DYNCREATE(devedgeView)


protected:
	virtual ~devedgeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	virtual base_wnd * _001GetWnd();

   void OnUpdate(BaseView* pSender, LPARAM lHint, base_object* phint);

   base_wnd * VirtualGetWnd();

	devedgeDoc * GetDocument() const;

protected:
   virtual BOOL PreTranslateMessage(MSG * pMsg);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	
protected:
	//{{AFX_MSG(screencaptureView)
	DECL_GEN_SIGNAL(_001OnDestroy)
	DECL_GEN_SIGNAL(_001OnCreate)
	DECL_GEN_SIGNAL(_001OnContextMenu)
	DECL_GEN_SIGNAL(_001OnSetCursor)
	DECL_GEN_SIGNAL(_001OnEraseBkgnd)

   DECL_GEN_SIGNAL(_001OnUpdateEditUndo)
   DECL_GEN_SIGNAL(_001OnUpdateEditRedo)
   DECL_GEN_SIGNAL(_001OnEditUndo)
   DECL_GEN_SIGNAL(_001OnEditRedo)

	DECLARE_MESSAGE_MAP()

   
};

#endif // !defined(AFX_MEDIAVIEW_H__B60D1BB7_7ADE_488E_83B9_2CC74EA09DFB__INCLUDED_)
