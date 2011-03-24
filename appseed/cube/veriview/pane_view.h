#pragma once

#include "pane_view_update_hint.h"

namespace veriview
{

   class CLASS_DECL_CA2_CUBE pane_view : 
      virtual public ::userex::pane_tab_view
   {
   public:

      
      pane_view(::ca::application * papp);
      virtual ~pane_view();

      void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object * pHint);

      virtual void rotate();

      virtual void on_create_view(view_data * pviewdata);

      virtual void OnViewUpdateHint(::view * pSender, LPARAM lHint, view_update_hint * pHint);


      html_document * get_view_html_document();
      html::data * get_html_data();

      DECL_GEN_SIGNAL(_001OnMenuMessage)
      DECL_GEN_SIGNAL(_001OnCreate)


   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif


   };

} // namespace veriview