#pragma once

namespace i2com
{

   class CLASS_DECL_CA2_CUBE form_view :
      virtual public ::form_view
   {
   public:
      form_view(::ca::application * papp);
      virtual ~form_view();

      document * get_document();   

      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pdispatch);

      DECL_GEN_SIGNAL(_001OnCreate)
   };


} // namespace i2com