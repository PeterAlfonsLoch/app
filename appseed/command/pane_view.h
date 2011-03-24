#pragma once

#include "pane_view_update_hint.h"

namespace command
{

   class CLASS_DECL_CA2_COMMAND pane_view : 
      virtual public ::userex::pane_tab_view,
      virtual public FileManagerCallbackInterface,
      virtual public command::form_callback
   {
   public:
	   pane_view(::ca::application * papp);
	   void rotate();
      
      void on_create_view(view_data * pviewdata);
      void on_show_view();

      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

	   virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
	   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);


      void OnFileManagerOpenFile(
         ::filemanager::data * pdata, 
         ::fs::item_array & itema);

      DECL_GEN_SIGNAL(_001OnMenuMessage)
	   virtual ~pane_view();
   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif

	   DECL_GEN_SIGNAL(_001OnCreate)
	   DECL_GEN_SIGNAL(_001OnSize)
   };


} // namespace command

