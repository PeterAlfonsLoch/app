#include "StdAfx.h"

namespace userbase
{

   scroll_view::scroll_view(::ax::application * papp) :
      ax(papp),
      ::user::interaction(papp),
      ::userbase::view(papp),
      ::user::scroll_view(papp)
   {
   }

   scroll_view::~scroll_view()
   {
   }

   void scroll_view::install_message_handling(::gen::message::dispatch * pinterface)
   {
      view::install_message_handling(pinterface);
      ::user::scroll_view::install_message_handling(pinterface);
   }

} // namespace userbase