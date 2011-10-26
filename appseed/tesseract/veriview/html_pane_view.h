#pragma once

#include "html_pane_view_update_hint.h"

#include "guibase/BaseVirtualTab.h"

class CLASS_DECL_CA2_VERIVIEW html_pane_view : 
   virtual public guiex::pane_tab_view
{
public:
	html_pane_view(::ca::application * papp);

   virtual void Rotate();

   virtual void on_create_view(view_data * pviewdata);

   virtual void OnUpdate(view * pSender, LPARAM lHint, base_object * pHint);
   virtual void OnViewUpdateHint(view* pSender, LPARAM lHint, view_update_hint * pHint);

   void _001InstallMessageHandling(igui::win::message::Dispatch * pinterface);

   html_document * get_html_document();
   html::document * get_document();

   DECL_GEN_SIGNAL(_001OnMenuMessage)

	virtual ~html_pane_view();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	DECL_GEN_SIGNAL(_001OnCreate)
};
