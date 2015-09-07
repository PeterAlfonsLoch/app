//#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"


namespace user
{


   schema_layered_frame::schema_layered_frame(::aura::application * papp) :
      object(papp)
   {


   }


   bool schema_layered_frame::get_translucency(ETranslucency & etranslucency)
   {

      etranslucency = TranslucencyPresent;

      return true;

   }


} // namespace user






