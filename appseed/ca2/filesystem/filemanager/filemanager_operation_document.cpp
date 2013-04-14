#include "framework.h"


file_manager_operation_document::file_manager_operation_document(sp(::ca::application) papp) :
   ca(papp),
   m_thread(papp),
   ::ca::data_container_base(papp),
   ::ca::data_container(papp),
   ::user::document(papp)
{
   
}

bool file_manager_operation_document::on_new_document()
{
   return TRUE;
}



