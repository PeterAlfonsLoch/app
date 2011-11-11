#include "StdAfx.h"

simple_edit::simple_edit(::ca::application * papp) :
   ca(papp),
   data_container(papp),
   ::user::interaction(papp),
   ::user::scroll_view(papp),
   colorertake5::base_editor(papp),
   ::user::edit_plain_text(papp),
   ::userbase::edit_plain_text(papp),
   ex1::tree(papp),
   ::ca::data_listener(papp)
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

void simple_edit::install_message_handling(::user::win::message::dispatch * pinterface)
{
   ::userbase::edit_plain_text::install_message_handling(pinterface);
}