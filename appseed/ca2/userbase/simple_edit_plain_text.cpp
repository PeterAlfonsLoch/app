#include "StdAfx.h"


simple_edit_plain_text::simple_edit_plain_text(::ca::application * papp) :
   ca(papp),
   ::user::interaction(papp),
   ::user::scroll_view(papp),
   ::user::edit_plain_text(papp)
{
}


void simple_edit_plain_text::install_message_handling(::gen::message::dispatch * pinterface)
{
   ::user::interaction::install_message_handling(pinterface);
   ::user::edit_plain_text::install_message_handling(pinterface);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &simple_edit_plain_text::_001OnCreate);
   IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &simple_edit_plain_text::_001OnShowWindow);
//   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &::user::edit_plain_text::_001OnLButtonDown);
//   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &::user::edit_plain_text::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &::user::edit_plain_text::_001OnKeyDown);
   IGUI_WIN_MSG_LINK(WM_KEYUP, pinterface, this, &::user::edit_plain_text::_001OnKeyUp);
}

void simple_edit_plain_text::_001OnShowWindow(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
//   SCAST_PTR(::gen::message::show_window, pshowwindow, pobj);

}


