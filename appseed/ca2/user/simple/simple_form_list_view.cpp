#include "framework.h"


simple_form_list_view::simple_form_list_view(sp(::ca2::application) papp) :
   ca2(papp),
   ::user::interaction(papp), 
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

void simple_form_list_view::install_message_handling(::ca2::message::dispatch * pinterface)
{
   ::user::view::install_message_handling(pinterface);
   ::user::form_list::install_message_handling(pinterface);
}



#ifdef DEBUG
void simple_form_list_view::assert_valid() const
{
   ::user::view::assert_valid();
}

void simple_form_list_view::dump(dump_context & dumpcontext) const
{
   ::user::view::dump(dumpcontext);
}
#endif //DEBUG

bool simple_form_list_view::pre_create_window(CREATESTRUCT& cs) 
{
   
   cs.style |= WS_CLIPCHILDREN;
   
   return ::user::view::pre_create_window(cs);
}

