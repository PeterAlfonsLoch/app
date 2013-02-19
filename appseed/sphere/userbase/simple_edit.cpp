#include "framework.h"


simple_edit::simple_edit(::ca::application * papp) :
   ca(papp),
   ::user::interaction(papp),
   ::user::scroll_view(papp),
   ::userbase::edit_plain_text(papp)
{

}

simple_edit::~simple_edit()
{
}


void simple_edit::_001OnDraw(::ca::graphics *pdc)
{
   ::userbase::edit_plain_text::_001OnDraw(pdc);
}


void simple_edit::pre_subclass_window() 
{
   PreSubClassWindow();   
}

void simple_edit::install_message_handling(::gen::message::dispatch * pinterface)
{
   ::userbase::edit_plain_text::install_message_handling(pinterface);
}



