#include "framework.h"


file_manager_operation_document::file_manager_operation_document(sp(::ca2::application) papp) :
   ca2(papp),
   m_thread(papp),
   ::ca2::data_container_base(papp),
   
   ::user::document(papp)
{
   
}

bool file_manager_operation_document::on_new_document()
{
   return TRUE;
}



