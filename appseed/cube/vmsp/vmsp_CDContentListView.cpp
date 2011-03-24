#include "StdAfx.h"
#include "CDContentListView.h"


CDContentListView::CDContentListView(::ca::application * papp) :
   ca(papp),
   ::user::form(papp),
   ::userbase::view(papp),
   ::user::scroll_view(papp),
   ::user::list(papp),
   ::user::form_list(papp),
   ::userbase::form_list(papp),
   simple_list_view(papp)
{
}

CDContentListView::~CDContentListView()
{
}


 
void CDContentListView::OnDraw(::ca::graphics * pgraphics)
{
//   ::userbase::document* pDoc = get_document();
   // TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CDContentListView diagnostics

#ifdef _DEBUG
void CDContentListView::assert_valid() const
{
   simple_list_view::assert_valid();
}

void CDContentListView::dump(dump_context & dumpcontext) const
{
   simple_list_view::dump(dumpcontext);
}
#endif //_DEBUG
