#include "StdAfx.h"
#include "simple_tab_control.h"


simple_tab_control::simple_tab_control(::ax::application * papp):
   ax(papp),
   ::user::interaction(papp),
   ::user::tab(papp),
   place_holder_container(papp)
{
}

simple_tab_control::~simple_tab_control()
{
}




void simple_tab_control::_001OnDraw(::ax::graphics *pdc)
{
   ::user::tab::_001OnDraw(pdc);
}

void simple_tab_control::pre_subclass_window() 
{
   _001BaseWndInterfaceMap();

   ::user::interaction::pre_subclass_window();
}


void simple_tab_control::install_message_handling(::gen::message::dispatch * pinterface)
{
   ::user::interaction::install_message_handling(pinterface);
   ::user::window_interface::install_message_handling(pinterface);
}