#include "framework.h"


file_manager_operation_document::file_manager_operation_document(sp(base_application) papp) :
   element(papp),
   m_thread(papp),
   ::user::object(papp)
{
   
}

bool file_manager_operation_document::on_new_document()
{
   return TRUE;
}



