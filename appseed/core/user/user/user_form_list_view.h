#pragma once


namespace user
{


   class CLASS_DECL_CORE form_list_view:
      virtual public ::user::show < ::user::form_list >
   {
   public:


      form_list_view();
      virtual ~form_list_view();


      virtual void install_message_handling(::message::dispatch *pinterface);

   };


} // namespace user





