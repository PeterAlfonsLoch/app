#pragma once

class CLASS_DECL_CA2_CUBE MediaLibraryExplorerTreeView :
   public ::userbase::view
{
public:
   MediaLibraryExplorerTreeView(::ca::application * papp);

   virtual void OnDraw(::ca::graphics * pgraphics);      // overridden to draw this ::view

   virtual ~MediaLibraryExplorerTreeView();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

};
