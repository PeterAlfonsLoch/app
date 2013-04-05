#include "framework.h"


simple_form_list_view::simple_form_list_view(::ca::applicationsp papp) :
   ca(papp),
   ::user::interaction(papp), 
   ::user::form(papp), 
   ::ca::user::form(papp),
   ::user::form_list(papp),
   ::userbase::form_list(papp),
   m_headerctrl(papp),
   ::userbase::view(papp),
   ::user::scroll_view(papp),
   ::user::list(papp)
{
   m_pheaderctrl     = &m_headerctrl;
   m_pheaderctrl->SetBaseListCtrlInterface(this);

}

simple_form_list_view::~simple_form_list_view()
{
}

void simple_form_list_view::install_message_handling(::ca::message::dispatch * pinterface)
{
   ::userbase::view::install_message_handling(pinterface);
   ::user::form_list::install_message_handling(pinterface);
}



#ifdef DEBUG
void simple_form_list_view::assert_valid() const
{
   ::userbase::view::assert_valid();
}

void simple_form_list_view::dump(dump_context & dumpcontext) const
{
   ::userbase::view::dump(dumpcontext);
}
#endif //DEBUG

bool simple_form_list_view::pre_create_window(CREATESTRUCT& cs) 
{
   
   cs.style |= WS_CLIPCHILDREN;
   
   return ::userbase::view::pre_create_window(cs);
}

