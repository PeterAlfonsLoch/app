#include "framework.h"


namespace userbase
{


   edit_plain_text::edit_plain_text(::ca::applicationsp papp) :
      ca(papp),
      ::user::interaction(papp),
      ::user::edit_plain_text(papp),
      ::user::scroll_view(papp)
   {
   }

   void edit_plain_text::install_message_handling(::ca::message::dispatch * pinterface)
   {
      ::user::edit_plain_text::install_message_handling(pinterface);
   }


} // namespace userbase


