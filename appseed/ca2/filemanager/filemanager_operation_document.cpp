#include "framework.h"


file_manager_operation_document::file_manager_operation_document(::ca::application * papp) :
   ca(papp),
   m_thread(papp),
   ::userbase::document(papp)
{
   
}

bool file_manager_operation_document::on_new_document()
{
   return TRUE;
}



