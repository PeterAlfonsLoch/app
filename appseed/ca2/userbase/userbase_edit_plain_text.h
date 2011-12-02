#pragma once

namespace userbase
{

   class CLASS_DECL_ca edit_plain_text :
      virtual public ::user::edit_plain_text
   {
   public:
      edit_plain_text(::ax::application * papp);
      virtual void install_message_handling(::gen::message::dispatch * pinterface);
   };


} // namespace userbase