#pragma once

#include "OptionsViewUpdateHint.h"

namespace mplite
{

   class CLASS_DECL_CA2_CUBE OptionsView : 
      public ::userex::pane_tab_view
   {
   public:
      OptionsView(::ca::application * papp);

      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
      virtual void on_show_view();

      void on_create_view(view_data * pviewdata);
      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
      virtual ~OptionsView();
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      DECL_GEN_SIGNAL(_001OnCreate)
   };

} // namespace mplite