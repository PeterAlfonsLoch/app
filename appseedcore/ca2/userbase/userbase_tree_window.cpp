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

   void tree_window::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::user::interaction::_001InstallMessageHandling(pinterface);
      ::user::tree::_001InstallMessageHandling(pinterface);
   }

} // namespace userbase