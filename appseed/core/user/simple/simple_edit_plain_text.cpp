#include "framework.h"


simple_edit_plain_text::simple_edit_plain_text(sp(::aura::application) papp) :
   element(papp),
   ::user::interaction(papp),
   ::user::scroll_view(papp),
   ::data::data_listener(papp),
   ::colorertake5::base_editor(papp),
   ::user::edit_plain_text(papp)
{

}


simple_edit_plain_text::~simple_edit_plain_text()
{
   
}


void simple_edit_plain_text::install_message_handling(::message::dispatch * pinterface)
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

void simple_edit_plain_text::_001OnShowWindow(signal_details * pobj)
{

   SCAST_PTR(::message::show_window, pshowwindow, pobj);

   if (pshowwindow->m_bShow)
   {
      TRACE("Show event true simple_edit_plain_text");
   }

}


bool simple_edit_plain_text::ShowWindow(int32_t nCmdShow)
{

   if (nCmdShow != SW_HIDE)
   {

      TRACE("Going to Show simple_edit_plain_text");

   }

   return ::user::edit_plain_text::ShowWindow(nCmdShow);

}


