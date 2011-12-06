#include "StdAfx.h"

simple_list_view::simple_list_view(::ca::application * papp) :
   ca(papp),
   ::userbase::view(papp),
   ::user::scroll_view(papp),
   ::user::list(papp),
   ::user::form(papp),
   ::ca2::user::form(papp),
   ::user::form_list(papp),
   ::userbase::form_list(papp),
   m_headerctrl(papp)
{
   m_pheaderctrl     = &m_headerctrl;
   m_pheaderctrl->SetBaseListCtrlInterface(this);
}

simple_list_view::~simple_list_view()
{
}

void simple_list_view::install_message_handling(::gen::message::dispatch * pinterface)
{
   ::userbase::view::install_message_handling(pinterface);
   ::user::list::install_message_handling(pinterface);
}



/////////////////////////////////////////////////////////////////////////////
// simple_list_view drawing

void simple_list_view::OnDraw(::ca::graphics * pgraphics)
{
   UNREFERENCED_PARAMETER(pgraphics);
   ASSERT(FALSE);
}

#ifdef _DEBUG
void simple_list_view::assert_valid() const
{
   ::userbase::view::assert_valid();
}

void simple_list_view::dump(dump_context & dumpcontext) const
{
   ::userbase::view::dump(dumpcontext);
}
#endif //_DEBUG

BOOL simple_list_view::PreCreateWindow(CREATESTRUCT& cs)
{
   cs.style |= WS_CLIPCHILDREN;

   return ::userbase::view::PreCreateWindow(cs);
}


::user::interaction* simple_list_view::OnDrawInterfaceGetWnd()
{
   return this;
}

::user::interaction* simple_list_view::_GetWnd()
{
   return this;
}

