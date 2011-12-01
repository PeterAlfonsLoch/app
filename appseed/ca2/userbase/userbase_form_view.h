#pragma once

namespace userbase
{

   class CLASS_DECL_ca form_view :
      virtual public scroll_view,
      virtual public ::user::form
   {
   public:
      form_view(::ca::application * papp);
      virtual ~form_view();

      virtual void install_message_handling(::gen::message::dispatch * pinterface);

      DECL_GEN_SIGNAL(_001OnCreate);
   };


} // namespace userbase