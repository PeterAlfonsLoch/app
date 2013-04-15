#include "framework.h"


file_manager_form_document::file_manager_form_document(sp(::ca::application) papp) :
   ca(papp),
   ::ca::data_container_base(papp),
   
   form_document(papp)
{
}



