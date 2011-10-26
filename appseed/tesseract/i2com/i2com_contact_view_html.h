#pragma once


namespace i2com
{


   class CLASS_DECL_CA2_TESSERACT contact_view_html :
      public form_view
   {
   public:


      contact_view_html(::ca::application * papp);

      
      virtual void install_message_handling(::user::win::message::dispatch * pdispatch);

      virtual void refresh();

      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnTimer)


   };


} // namespace i2com


