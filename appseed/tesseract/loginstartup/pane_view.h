#pragma once

#include "pane_view_update_hint.h"
#include "guibase/BaseVirtualTab.h"

namespace loginstartup
{

class CLASS_DECL_CA2_LOGINSTARTUPAPPLICATION pane_view : 
   virtual public guiex::pane_tab_view,
   virtual public FileManagerCallbackInterface,
   virtual public loginstartup::form_callback
{
public:
	pane_view(::ca::application * papp);

   void Rotate();

   void on_create_view(view_data * pviewdata);
   void on_show_view();

   virtual void _001InstallMessageHandling(igui::win::message::Dispatch * pinterface);

	virtual void on_update(BaseView* pSender, LPARAM lHint, base_object* pHint);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);


   void OnFileManagerOpenFile(
      FileManagerDDX & ddx, 
      FileManagerItemArray & itema);

   DECL_GEN_SIGNAL(_001OnMenuMessage)
	virtual ~pane_view();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext & dumpcontext) const;
#endif

	DECL_GEN_SIGNAL(_001OnCreate)
	DECL_GEN_SIGNAL(_001OnSize)
};


} // namespace loginstartup

