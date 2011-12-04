#include "StdAfx.h"

namespace userbase
{

   tree_window::tree_window(::ca::application * papp) :
      ca(papp),
      data_container(papp),
      ::user::interaction(papp),
      ::user::scroll_view(papp),
      ::user::tree(papp),
      ex1::tree(papp)
   {
   }

   tree_window::~tree_window()
   {
   }

   void tree_window::install_message_handling(::gen::message::dispatch * pinterface)
   {
      ::user::interaction::install_message_handling(pinterface);
      ::user::tree::install_message_handling(pinterface);
   }

} // namespace userbase