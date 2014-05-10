#include "framework.h"


file_manager_operation_document::file_manager_operation_document(sp(::base::application) papp) :
   element(papp),
   ::data::data_container_base(papp),
   ::user::object(papp),
   m_thread(papp)
{
   
}

bool file_manager_operation_document::on_new_document()
{
   return TRUE;
}



