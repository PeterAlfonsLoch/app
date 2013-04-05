#pragma once


namespace userbase
{


   class CLASS_DECL_ca2 form_list :
      virtual public ::userbase::view,
      virtual public ::user::form_list
   {
   public:
      
      
      form_list(::ca::applicationsp papp);
      virtual ~form_list();


      virtual void install_message_handling(::ca::message::dispatch * pdispatch);


   };



} // namespace userbase


