#pragma once

namespace ihtml
{

class document;


class CLASS_DECL_CA2_IHTML view :
   public BaseView,
   virtual public form
{
protected:
	view();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(view)


protected:
	virtual ~view();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:

   string GetLocationURL();
   bool Refresh2(int i);
   bool Navigate(const char * pszUrl);

   virtual void on_document_complete(const char * pszUrl);

	protected:
   virtual void _001InstallMessageHandling(igui::win::message::Dispatch * pinterface);
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
   virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
   virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(BaseView* pSender, LPARAM lHint, base_object* pHint);

   DECL_GEN_SIGNAL(_001OnInitialUpdate)

   virtual base_wnd * KaraokeGetWnd();
	virtual base_wnd * BackViewGetWnd();
   virtual base_wnd * _001GetWnd();

   virtual void _001OnDraw(CDC * pdc);


   string m_strLocationURL;


	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(view)
	protected:

      document * GetDocument();
	//}}AFX_VIRTUAL

   // Generated message map functions
protected:
	//{{AFX_MSG(view)
	DECL_GEN_SIGNAL(_001OnDestroy)
	DECL_GEN_SIGNAL(_001OnSize)
	DECL_GEN_SIGNAL(_001OnLButtonDown)
	DECL_GEN_SIGNAL(_001OnMouseMove)
	DECL_GEN_SIGNAL(_001OnLButtonUp)
	DECL_GEN_SIGNAL(_001OnPaint)
	DECL_GEN_SIGNAL(_001OnCreate)
	DECL_GEN_SIGNAL(_001OnContextMenu)
	DECL_GEN_SIGNAL(_001OnSetCursor)
	DECL_GEN_SIGNAL(_001OnEraseBkgnd)
	DECL_GEN_SIGNAL(_001OnUpdateViewEncoding)
	DECL_GEN_SIGNAL(_001OnViewEncoding)
	DECL_GEN_SIGNAL(_001OnImageLoaded)
	DECL_GEN_SIGNAL(_001OnKeyDown)
	DECLARE_MESSAGE_MAP()

   virtual void _001OnTabClick(int iTab);
   
};

} // namespace ihtml