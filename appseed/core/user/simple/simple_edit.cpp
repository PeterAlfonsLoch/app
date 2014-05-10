#include "framework.h"


simple_edit::simple_edit(sp(::base::application) papp) :
   element(papp),
   ::user::interaction(papp),
   ::user::scroll_view(papp),
   ::data::data_listener(papp),
   ::colorertake5::base_editor(papp),
   ::user::edit_plain_text(papp)
{

}


simple_edit::~simple_edit()
{

}


void simple_edit::_001OnDraw(::draw2d::graphics *pdc)
{
   ::user::edit_plain_text::_001OnDraw(pdc);
}


void simple_edit::pre_subclass_window() 
{
   PreSubClassWindow();   
}

void simple_edit::install_message_handling(::message::dispatch * pinterface)
{
   ::user::edit_plain_text::install_message_handling(pinterface);
}



