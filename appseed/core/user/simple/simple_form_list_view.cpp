//#include "framework.h"


simple_form_list_view::simple_form_list_view(::aura::application * papp) :
   element(papp),
   ::user::interaction(papp),
   ::user::form_interface(papp),
   ::user::form(papp), 
   ::user::form_list(papp),
   m_headerctrl(papp),
   
   ::user::scroll_view(papp),
   ::user::list(papp)
{
   m_pheaderctrl     = &m_headerctrl;
   m_pheaderctrl->SetBaseListCtrlInterface(this);

}

simple_form_list_view::~simple_form_list_view()
{
}

void simple_form_list_view::install_message_handling(::message::dispatch * pinterface)
{
   ::aura::impact::install_message_handling(pinterface);
   ::user::form_list::install_message_handling(pinterface);
}



void simple_form_list_view::assert_valid() const
{
   ::aura::impact::assert_valid();
}

void simple_form_list_view::dump(dump_context & dumpcontext) const
{
   ::aura::impact::dump(dumpcontext);
}

bool simple_form_list_view::pre_create_window(::user::create_struct& cs) 
{
   
   cs.style |= WS_CLIPCHILDREN;
   
   return ::aura::impact::pre_create_window(cs);
}

void simple_form_list_view::_001OnInitialUpdate(signal_details * pobj)
{

   ::user::form_list::_001OnInitialUpdate(pobj);

}