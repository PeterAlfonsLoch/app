#include "framework.h"

namespace user
{

   scroll_view::scroll_view(sp(::ca::application) papp) :
      ca(papp),
      ::user::interaction(papp),
      ::user::view(papp),
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

} // namespace user