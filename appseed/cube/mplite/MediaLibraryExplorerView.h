#pragma once

namespace mplite
{

   class CLASS_DECL_CA2_CUBE MediaLibraryExplorerView :
      public ::userbase::split_view
   {
   public:
      MediaLibraryExplorerView(::ca::application * papp);

      void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

      void CreateViews();

      virtual void OnDraw(::ca::graphics * pgraphics); 

      virtual ~MediaLibraryExplorerView();
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      DECL_GEN_SIGNAL(_001OnCreate)
   };


} // namespace mplite