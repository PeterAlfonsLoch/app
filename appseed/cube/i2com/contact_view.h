#pragma once

namespace i2com
{
   class CLASS_DECL_CA2_CUBE contact_view :
      public form_view
   {
   public:


      contact_view(::ca::application * papp);

      
      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pdispatch);

      virtual void refresh();

      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnTimer)

   };

} // namespace i2com