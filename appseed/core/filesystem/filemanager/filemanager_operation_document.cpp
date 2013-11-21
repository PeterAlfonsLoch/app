#include "framework.h"


file_manager_operation_document::file_manager_operation_document(sp(base_application) papp) :
   element(papp),
   m_thread(papp),
<<<<<<< .mine
   ::user::object(papp)
=======
   ::data::data_container_base(papp),
   
   ::user::object(papp)
>>>>>>> .r7014
{
   
}

bool file_manager_operation_document::on_new_document()
{
   return TRUE;
}



