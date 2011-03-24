#pragma once

namespace userbase
{

   class CLASS_DECL_ca edit_plain_text :
      virtual public ::user::edit_plain_text
   {
   public:
      edit_plain_text(::ca::application * papp);
      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
   };


} // namespace userbase