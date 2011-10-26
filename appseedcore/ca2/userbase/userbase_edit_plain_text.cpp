#include "StdAfx.h"

namespace userbase
{

   edit_plain_text::edit_plain_text(::ca::application * papp) :
      ca(papp),
      data_container(papp),
      ::user::interaction(papp),
      ::user::edit_plain_text(papp),
      colorertake5::base_editor(papp),
      ::user::scroll_view(papp),
      ex1::tree(papp),
      ::ca::data_listener(papp)
   {
   }

   void edit_plain_text::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      ::user::edit_plain_text::install_message_handling(pinterface);
   }

} // namespace userbase