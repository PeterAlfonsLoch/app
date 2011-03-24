#pragma once

#include "pane_view_update_hint.h"

namespace veiev
{

   class CLASS_DECL_CA2_VEIEV pane_view : 
      virtual public ::userex::pane_tab_view,
      virtual public FileManagerCallbackInterface,
      virtual public veiev::form_callback
   {
   public:
	   pane_view(::ca::application * papp);
      
      void on_create_view(view_data * pviewdata);
      void on_show_view();

      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

	   virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);

      void OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema);

	   virtual ~pane_view();
   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif

	   DECL_GEN_SIGNAL(_001OnCreate)
   };


} // namespace veiev

