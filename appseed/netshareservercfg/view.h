#pragma once

namespace netshareservercfg
{
   class socket;

class CLASS_DECL_CA2_NETSHARECLIENT view : public BaseView
{
public:
   view(::ca::application * papp);
	virtual ~view();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	virtual uie * BackViewGetWnd();
   virtual uie * get_guie();

   virtual void _001OnDraw(CDC * pdc);

   netshareservercfg::socket * m_psocket;

   netshareservercfg::area * m_parea;
   string m_strServer;

   virtual void _001InstallMessageHandling(igui::win::message::Dispatch * pinterface);
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   DECL_GEN_SIGNAL(_001OnInitialUpdate)
	virtual void OnUpdate(BaseView* pSender, LPARAM lHint, base_object* pHint);

	DECL_GEN_SIGNAL(_001OnDestroy)
	DECL_GEN_SIGNAL(_001OnSize)
	DECL_GEN_SIGNAL(_001OnPaint)
	DECL_GEN_SIGNAL(_001OnCreate)
	DECL_GEN_SIGNAL(_001OnContextMenu)
	DECL_GEN_SIGNAL(_001OnSetCursor)
	DECL_GEN_SIGNAL(_001OnEraseBkgnd)
   DECL_GEN_SIGNAL(_001OnTimer)
   DECL_GEN_SIGNAL(_001OnMouseMove)
   DECL_GEN_SIGNAL(_001OnLButtonDown)
   DECL_GEN_SIGNAL(_001OnLButtonUp)

   virtual void _001OnTabClick(int iTab);
   
};

} // namespace netshareservercfg
