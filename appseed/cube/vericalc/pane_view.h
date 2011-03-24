#pragma once

#include "pane_view_update_hint.h"

namespace vericalc
{

   class CLASS_DECL_CA2_CUBE pane_view : 
      public ::userex::pane_tab_view
   {
   public:
      
      
      pane_view(::ca::application * papp);   
      virtual ~pane_view();

      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

      void rotate();

      void on_create_view(view_data * pviewdata);

      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);



      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnMenuMessage)


   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

   };

} // namespace vericalc