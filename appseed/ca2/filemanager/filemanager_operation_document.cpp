#include "StdAfx.h"


file_manager_operation_document::file_manager_operation_document(::ca::application * papp) :
   ca(papp),
   data_container(papp),
   m_thread(papp),
   ::document(papp),
   ::userbase::document(papp)
{
   
}

BOOL file_manager_operation_document::on_new_document()
{
   return TRUE;
}

