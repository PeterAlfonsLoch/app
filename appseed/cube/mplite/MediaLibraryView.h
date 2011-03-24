#pragma once

#include "MediaLibraryViewUpdateHint.h"

namespace mplite
{

   class CLASS_DECL_CA2_CUBE MediaLibraryView :
      public ::userex::pane_tab_view
   {
   public:

      
      MediaLibraryView(::ca::application * papp);
      virtual ~MediaLibraryView();

      void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

      void on_create_view(view_data * pviewdata);

      void _001InitializeFormPreData();

      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      DECL_GEN_SIGNAL(_001OnCreate)
   };

} // namespace mplite