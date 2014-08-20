#include "framework.h"


namespace user
{


   edit_plain_text_view::edit_plain_text_view(sp(::axis::application) papp) :
      element(papp),
      ::user::interaction(papp),
      ::user::scroll_view(papp),
      ::data::data_listener(papp),
      ::colorertake5::base_editor(papp),
      ::user::edit_plain_text(papp)
   {

   }


   void edit_plain_text_view::install_message_handling(::message::dispatch * pinterface)
   {
      
      
      ::user::edit_plain_text::install_message_handling(pinterface);
      impact::install_message_handling(pinterface);
      //IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &edit_plain_text_view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &::user::edit_plain_text::_002OnMouseMove);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &::user::edit_plain_text::_002OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &::user::edit_plain_text::_002OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &::user::edit_plain_text::_002OnKeyDown);
      IGUI_WIN_MSG_LINK(WM_KEYUP, pinterface, this, &::user::edit_plain_text::_002OnKeyUp);


   }

   void edit_plain_text_view::_001OnSetText(::action::context actioncontext)
   {


      ::user::edit_plain_text::_001OnSetText(actioncontext);


   }

   void edit_plain_text_view::_001OnUpdate(::action::context actioncontext)
   {


      ::user::edit_plain_text::_001OnUpdate(actioncontext);


   }

   void edit_plain_text_view::layout()
   {


      // rect rectClient;
      // GetClientRect(rectClient);
      // SetWindowPos(0, rectClient.left, rectClient.top, rectClient.width(), rectClient.height(), SWP_SHOWWINDOW);
      // _001OnUpdate();
      ThreadProcScrollSize((LPVOID) dynamic_cast < ::user::edit_plain_text * > (this));


   }


} // namespace user


