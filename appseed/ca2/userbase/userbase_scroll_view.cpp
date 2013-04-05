#include "framework.h"

namespace userbase
{

   scroll_view::scroll_view(::ca::applicationsp papp) :
      ca(papp),
      ::user::interaction(papp),
      ::userbase::view(papp),
      ::user::scroll_view(papp)
   {
   }

   scroll_view::~scroll_view()
   {
   }

   void scroll_view::install_message_handling(::ca::message::dispatch * pinterface)
   {
      view::install_message_handling(pinterface);
      ::user::scroll_view::install_message_handling(pinterface);
   }

} // namespace userbase