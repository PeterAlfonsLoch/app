#include "framework.h"


namespace filemanager
{


   form_document::form_document(sp(::base::application) papp):
      element(papp),
      ::data::data_container_base(papp),
      ::user::document(papp),
      html_document(papp),
      ::form_document(papp)
   {
      }


} // namespace filemanager



