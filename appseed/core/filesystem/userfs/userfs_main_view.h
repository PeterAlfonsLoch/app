#pragma once


namespace userfs
{


   class document;


   class CLASS_DECL_CORE main_view :
      public ::user::split_view
   {
   public:
         
      main_view(sp(::aura::application) papp);
      void install_message_handling(::message::dispatch * pinterface);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnTimer);


      ::user::document * get_document();

   };


} // namespace userfs



