#pragma once

class paint_document;


class CLASS_DECL_CA2_PAINT paint_view :
   public BaseView,
   virtual public Ex1VirtualGuieInterface
{
protected:
	paint_view();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(paint_view)


protected:
	virtual ~paint_view();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
   virtual base_wnd * KaraokeGetWnd();
	virtual base_wnd * BackViewGetWnd();
   virtual base_wnd * _001GetWnd();

   virtual void _001OnDraw(CDC * pdc);


	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(paint_view)
	protected:
   virtual void _001InstallMessageHandling(igui::win::message::Dispatch * pinterface);
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
   virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
   virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
   DECL_GEN_SIGNAL(_001OnInitialUpdate)
	virtual void OnUpdate(BaseView* pSender, LPARAM lHint, base_object* pHint);

   paint_document * GetDocument();

	//}}AFX_VIRTUAL

   // Generated message map functions
protected:
	//{{AFX_MSG(paint_view)
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
	DECLARE_MESSAGE_MAP()

   virtual void _001OnTabClick(int iTab);
   
};

