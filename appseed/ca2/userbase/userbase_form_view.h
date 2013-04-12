#pragma once

namespace userbase
{

   class CLASS_DECL_ca2 form_view :
      virtual public ::userbase::scroll_view,
      virtual public ::user::form
   {
   public:
      form_view(sp(::ca::application) papp);
      virtual ~form_view();

      virtual void install_message_handling(::ca::message::dispatch * pinterface);

      DECL_GEN_SIGNAL(_001OnCreate);
   };


} // namespace userbase
