#include "framework.h"

simple_list_view::simple_list_view(sp(::ca2::application) papp) :
   ca2(papp),
   
   ::user::scroll_view(papp),
   ::user::list(papp),
   ::user::form(papp),
   ::user::form_list(papp),
   m_headerctrl(papp)
{
   m_pheaderctrl     = &m_headerctrl;
   m_pheaderctrl->SetBaseListCtrlInterface(this);
}

simple_list_view::~simple_list_view()
{
}

void simple_list_view::install_message_handling(::ca2::message::dispatch * pinterface)
{
   ::user::view::install_message_handling(pinterface);
   ::user::list::install_message_handling(pinterface);
}



/////////////////////////////////////////////////////////////////////////////
// simple_list_view drawing

void simple_list_view::OnDraw(::ca2::graphics * pgraphics)
{
   UNREFERENCED_PARAMETER(pgraphics);
   ASSERT(FALSE);
}

#ifdef DEBUG
void simple_list_view::assert_valid() const
{
   ::user::view::assert_valid();
}

void simple_list_view::dump(dump_context & dumpcontext) const
{
   ::user::view::dump(dumpcontext);
}
#endif //DEBUG

bool simple_list_view::pre_create_window(CREATESTRUCT& cs)
{
   cs.style |= WS_CLIPCHILDREN;

   return ::user::view::pre_create_window(cs);
}


sp(::user::interaction) simple_list_view::OnDrawInterfaceGetWnd()
{
   return this;
}

sp(::user::interaction) simple_list_view::_GetWnd()
{
   return this;
}

