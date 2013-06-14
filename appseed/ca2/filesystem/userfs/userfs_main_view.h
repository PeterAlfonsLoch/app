#pragma once


namespace userfs
{


   class document;


   class CLASS_DECL_ca2 main_view :
      public ::user::split_view
   {
   public:
         
      main_view(sp(::ca2::application) papp);
      void install_message_handling(::ca2::message::dispatch * pinterface);
      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnTimer)


      sp(::user::document) get_document();

   };


} // namespace userfs



