#include "framework.h"


file_manager_form_document::file_manager_form_document(sp(::base::application) papp) :
   element(papp),
   ::data::data_container_base(papp),
   ::user::object(papp),
   html_document(papp),
   form_document(papp)
{
}



