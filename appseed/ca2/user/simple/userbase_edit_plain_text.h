#pragma once


namespace userbase
{


   class CLASS_DECL_ca2 edit_plain_text :
      public ::user::edit_plain_text
   {
   public:
      
      
      edit_plain_text(sp(::ca::application) papp);


      virtual void install_message_handling(::ca::message::dispatch * pinterface);


   };


} // namespace userbase


