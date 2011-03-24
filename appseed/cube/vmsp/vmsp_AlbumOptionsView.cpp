#include "StdAfx.h"
#include "AlbumOptionsView.h"


AlbumOptionsView::AlbumOptionsView(::ca::application * papp) :
   ca(papp),
   ::user::interaction(papp),
   ::user::form(papp),
   ::user::scroll_view(papp),
   ::userbase::view(papp),
   ::userbase::scroll_view(papp),
   ::userbase::form_view(papp),
   html_form(papp),
   html_form_view(papp),
   form_view(papp)
{
}

AlbumOptionsView::~AlbumOptionsView()
{
}

/*void AlbumOptionsView::DoDataExchange(CDataExchange* pDX)
{
//   form_view::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(AlbumOptionsView)
      // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}
*/


/////////////////////////////////////////////////////////////////////////////
// AlbumOptionsView diagnostics

#ifdef _DEBUG
void AlbumOptionsView::assert_valid() const
{
   form_view::assert_valid();
}

void AlbumOptionsView::dump(dump_context & dumpcontext) const
{
   form_view::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// AlbumOptionsView message handlers
