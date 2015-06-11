//#include "framework.h"


simple_form_list_view::simple_form_list_view(::aura::application * papp) :
   object(papp),
   ::user::interaction(papp)
{

}

simple_form_list_view::~simple_form_list_view()
{
}

void simple_form_list_view::install_message_handling(::message::dispatch * pinterface)
{
   ::user::impact::install_message_handling(pinterface);
   ::user::form_list::install_message_handling(pinterface);
}



void simple_form_list_view::assert_valid() const
{
   ::user::impact::assert_valid();
}

void simple_form_list_view::dump(dump_context & dumpcontext) const
{
   ::user::impact::dump(dumpcontext);
}

bool simple_form_list_view::pre_create_window(::user::create_struct& cs) 
{
   
   cs.style |= WS_CLIPCHILDREN;
   
   return ::user::impact::pre_create_window(cs);
}

void simple_form_list_view::_001OnInitialUpdate()
{

   BASE::_001OnInitialUpdate();

}