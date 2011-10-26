#pragma once

namespace i2com
{

   class CLASS_DECL_CA2_TESSERACT form_view :
      virtual public ::form_view
   {
   public:
      form_view(::ca::application * papp);
      virtual ~form_view();

      document * get_document();   

      virtual void install_message_handling(::user::win::message::dispatch * pdispatch);

      DECL_GEN_SIGNAL(_001OnCreate)
   };


} // namespace i2com