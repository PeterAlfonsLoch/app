#pragma once

namespace fs
{


   class document;

   class CLASS_DECL_ca2 main_view :
      public ::user::split_view
   {
   public:
         
      main_view(sp(::ca::application) papp);
      void install_message_handling(::ca::message::dispatch * pinterface);
      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnTimer)


      sp(document) get_document();

   };


} // namespace fs


