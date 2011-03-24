// MediaView.h: interface for the MediaView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEDIAVIEW_H__B60D1BB7_7ADE_488E_83B9_2CC74EA09DFB__INCLUDED_)
#define AFX_MEDIAVIEW_H__B60D1BB7_7ADE_488E_83B9_2CC74EA09DFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


namespace mediaplay
{

class MediaView :
   public BaseView,
   public MediaViewInterface
{
protected:
	MediaView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(MediaView)


protected:
	virtual ~MediaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
   virtual CWnd * KaraokeGetWnd();
	virtual CWnd & BackViewGetWnd();
   virtual CWnd * _001GetWnd();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MediaView)
	protected:
   virtual void _001InstallMessageHandling(igui::win::message::Dispatch * pinterface);
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
   virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
   virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
   DECL_GEN_SIGNAL(_001OnInitialUpdate)
	virtual void OnUpdate(BaseView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

   // Generated message map functions
protected:
	//{{AFX_MSG(MediaView)
	DECL_GEN_SIGNAL(_001OnDestroy)
	DECL_GEN_SIGNAL(_001OnSize)
	DECL_GEN_SIGNAL(_001OnPaint)
	DECL_GEN_SIGNAL(_001OnCreate)
	DECL_GEN_SIGNAL(_001OnContextMenu)
	DECL_GEN_SIGNAL(_001OnSetCursor)
	DECL_GEN_SIGNAL(_001OnEraseBkgnd)
	DECL_GEN_SIGNAL(_001OnUpdateViewEncoding)
   DECL_GEN_SIGNAL(_001OnViewEncoding)
   DECL_GEN_SIGNAL(_001OnWavePlayerEvent)
	
   virtual void _001OnTabClick(int iTab);
   
};

} // namespace mediaplay

#endif // !defined(AFX_MEDIAVIEW_H__B60D1BB7_7ADE_488E_83B9_2CC74EA09DFB__INCLUDED_)
