#include "framework.h"


namespace filemanager
{


   form_document::form_document(::aura::application * papp):
      element(papp),
      ::data::data_container_base(papp),
      ::aura::document(papp),
      ::form_document(papp)
   {

   }


} // namespace filemanager



