#include "StdAfx.h"

simple_edit::simple_edit(::ax::application * papp) :
   ax(papp),
   data_container(papp),
   ::user::interaction(papp),
   ::user::scroll_view(papp),
   colorertake5::base_editor(papp),
   ::user::edit_plain_text(papp),
   ::userbase::edit_plain_text(papp),
   ex1::tree(papp),
   ::ax::data_listener(papp)
{

}

simple_edit::~simple_edit()
{
}


void simple_edit::_001OnDraw(::ax::graphics *pdc)
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