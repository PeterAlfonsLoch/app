#include "StdAfx.h"
#include "MediaLibraryExplorerTreeView.h"

MediaLibraryExplorerTreeView::MediaLibraryExplorerTreeView(::ca::application * papp) :
   ca(papp),
   ::userbase::view(papp)
{
}

MediaLibraryExplorerTreeView::~MediaLibraryExplorerTreeView()
{
}


void MediaLibraryExplorerTreeView::OnDraw(::ca::graphics * pgraphics)
{
   UNREFERENCED_PARAMETER(pgraphics);
   //::userbase::document* pDoc = get_document();
   // TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// MediaLibraryExplorerTreeView diagnostics

#ifdef _DEBUG
void MediaLibraryExplorerTreeView::assert_valid() const
{
   ::userbase::view::assert_valid();
}

void MediaLibraryExplorerTreeView::dump(dump_context & dumpcontext) const
{
   ::userbase::view::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// MediaLibraryExplorerTreeView message handlers
