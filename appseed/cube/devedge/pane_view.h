#pragma once

#include "pane_view_update_hint.h"

namespace devedge 
{

   class CLASS_DECL_CA2_CUBE pane_view : 
      public ::userex::pane_tab_view
   {
   public:
      bool m_bShowDevEdge;

      pane_view(::ca::application * papp);
      virtual ~pane_view();

      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);

      virtual void on_create_view(view_data * pviewdata);

      void rotate();


      ::document * open_file(const char * lpcsz);

      void on_show_view();
      DECL_GEN_SIGNAL(_001OnCreate)
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif
   };

} // namespace devedge