#pragma once

#include "img/dib.h"

class winservice_1_document;


class CLASS_DECL_CA2_WINSERVICE_1 winservice_1_view :
   virtual public BaseView,
   virtual public uie
{
public:
	winservice_1_view(::ca::application * papp);
	// DECLARE_DYNCREATE(winservice_1_view)


protected:
	virtual ~winservice_1_view();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:

   enum EMessage
   {
      MessageOp = WM_USER + 1123,
   };

   enum EOp
   {
      OpUpdateCurrentArea,
   };

   void GetDateTime(string & strDateTime);

	virtual uie * BackViewGetWnd();
   virtual uie * get_guie();

   virtual void _001OnDraw(CDC * pdc);


	protected:
   virtual void _001InstallMessageHandling(igui::win::message::Dispatch * pinterface);
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
   DECL_GEN_SIGNAL(_001OnInitialUpdate)
   DECL_GEN_SIGNAL(_001OnLButtonDown)
   DECL_GEN_SIGNAL(_001OnLButtonUp)
   DECL_GEN_SIGNAL(_001OnTimer)
   DECL_GEN_SIGNAL(_001OnRButtonUp)
	virtual void OnUpdate(BaseView* pSender, LPARAM lHint, base_object* pHint);

   winservice_1_document * get_document();


protected:
	DECL_GEN_SIGNAL(_001OnDestroy)
	DECL_GEN_SIGNAL(_001OnSize)
	DECL_GEN_SIGNAL(_001OnPaint)
	DECL_GEN_SIGNAL(_001OnCreate)
	DECL_GEN_SIGNAL(_001OnContextMenu)
	DECL_GEN_SIGNAL(_001OnSetCursor)
	DECL_GEN_SIGNAL(_001OnEraseBkgnd)
	DECL_GEN_SIGNAL(_001OnOp)
   DECL_GEN_SIGNAL(_001OnShowWindow)
   virtual void _001OnTabClick(int iTab);
};

