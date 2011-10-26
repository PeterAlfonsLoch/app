#pragma once

#include "pane_view_update_hint.h"

namespace devedge 
{

   class CLASS_DECL_CA2_TESSERACT pane_view : 
      public ::userex::pane_tab_view
   {
   public:
      bool m_bShowDevEdge;

      pane_view(::ca::application * papp);
      virtual ~pane_view();

      virtual void install_message_handling(::user::win::message::dispatch * pinterface);
      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);

      virtual void on_create_view(::user::view_creator_data * pcreatordata);

      void rotate();


      ::document * open_file(::ca::create_context * pcreatecontext);

      void on_show_view();
      DECL_GEN_SIGNAL(_001OnCreate)
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif
   };

} // namespace devedge