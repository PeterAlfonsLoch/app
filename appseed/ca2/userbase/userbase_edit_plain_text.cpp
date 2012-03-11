#include "StdAfx.h"


namespace userbase
{


   edit_plain_text::edit_plain_text(::ca::application * papp) :
      ca(papp),
      ::user::interaction(papp),
      ::user::edit_plain_text(papp),
      ::user::scroll_view(papp)
   {
   }

   void edit_plain_text::install_message_handling(::gen::message::dispatch * pinterface)
   {
      ::user::edit_plain_text::install_message_handling(pinterface);
   }


} // namespace userbase


