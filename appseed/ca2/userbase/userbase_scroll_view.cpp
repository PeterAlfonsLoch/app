#include "StdAfx.h"

namespace userbase
{

   scroll_view::scroll_view(::ca::application * papp) :
      ca(papp),
      ::user::interaction(papp),
      ::userbase::view(papp),
      ::user::scroll_view(papp)
   {
   }

   scroll_view::~scroll_view()
   {
   }

   void scroll_view::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      view::install_message_handling(pinterface);
      ::user::scroll_view::install_message_handling(pinterface);
   }

} // namespace userbase