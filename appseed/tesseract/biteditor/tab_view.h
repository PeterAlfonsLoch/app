#pragma once

#include "pane_view_update_hint.h"

namespace biteditor
{

   class _declspec(dllexport) tab_view : 
      virtual public ::userex::pane_tab_view
   {
   public:
      tab_view(::ca::application * papp);

      void on_create_view(::user::view_creator_data * pcreatordata);

      void install_message_handling(::user::win::message::dispatch * pinterface);
      
      virtual ~tab_view();
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

   protected:
      DECL_GEN_SIGNAL(_001OnCreate)
   };


} // namespace biteditor