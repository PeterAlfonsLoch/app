#include "StdAfx.h"
#include "VmsTextView.h"

CVmsTextView::CVmsTextView(::ca::application * papp) :
   ca(papp),
   ::ca::data_container(papp),
   ::user::interaction(papp),
   ::userbase::view(papp),
   ::user::scroll_view(papp),
   colorertake5::base_editor(papp),
   ::user::edit_plain_text(papp),
   ::userbase::edit_plain_text(papp),
   ::userbase::edit_plain_text_view(papp),
   ex1::tree(papp),
   ::ca::data_listener(papp)
{
}

CVmsTextView::~CVmsTextView()
{
}



void CVmsTextView::OnDraw(::ca::graphics * pgraphics)
{
}

/////////////////////////////////////////////////////////////////////////////
// CVmsTextView diagnostics

#ifdef _DEBUG
void CVmsTextView::assert_valid() const
{
   ::userbase::edit_plain_text_view::assert_valid();
}

void CVmsTextView::dump(dump_context & dumpcontext) const
{
   ::userbase::edit_plain_text_view::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVmsTextView message handlers
