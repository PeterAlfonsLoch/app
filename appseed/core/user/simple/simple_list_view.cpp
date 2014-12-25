//#include "framework.h"

simple_list_view::simple_list_view(::aura::application * papp) :
   element(papp),
   ::user::scroll_view(papp),
   ::user::list(papp),
   ::user::form_interface(papp),
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

void simple_list_view::install_message_handling(::message::dispatch * pinterface)
{
   ::aura::impact::install_message_handling(pinterface);
   ::user::list::install_message_handling(pinterface);
}



/////////////////////////////////////////////////////////////////////////////
// simple_list_view drawing

void simple_list_view::OnDraw(::draw2d::graphics * pgraphics)
{
   UNREFERENCED_PARAMETER(pgraphics);
   ASSERT(FALSE);
}

void simple_list_view::assert_valid() const
{
   ::aura::impact::assert_valid();
}

void simple_list_view::dump(dump_context & dumpcontext) const
{
   ::aura::impact::dump(dumpcontext);
}

bool simple_list_view::pre_create_window(::user::create_struct& cs)
{
   cs.style |= WS_CLIPCHILDREN;

   return ::aura::impact::pre_create_window(cs);
}


sp(::user::interaction) simple_list_view::OnDrawInterfaceGetWnd()
{
   return this;
}

