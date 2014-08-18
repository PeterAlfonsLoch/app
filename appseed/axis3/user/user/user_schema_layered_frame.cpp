#include "framework.h"
namespace user{
   bool schema_layered_frame::get_translucency(ETranslucency & etranslucency)
   {
      etranslucency = TranslucencyPresent;
      return true;
   }
} // namespace user