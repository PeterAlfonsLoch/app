#include "StdAfx.h"

namespace userbase
{

   edit_plain_text::edit_plain_text(::ax::application * papp) :
      ax(papp),
      data_container(papp),
      ::user::interaction(papp),
      ::user::edit_plain_text(papp),
      colorertake5::base_editor(papp),
      ::user::scroll_view(papp),
      ex1::tree(papp),
      ::ax::data_listener(papp)
   {
   }

   void edit_plain_text::install_message_handling(::gen::message::dispatch * pinterface)
   {
      ::user::edit_plain_text::install_message_handling(pinterface);
   }

} // namespace userbase