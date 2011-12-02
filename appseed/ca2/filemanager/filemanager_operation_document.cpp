#include "StdAfx.h"


file_manager_operation_document::file_manager_operation_document(::ax::application * papp) :
   ax(papp),
   data_container(papp),
   document_interface(papp),
   m_thread(papp),
   ::document(papp),
   ::userbase::document(papp)
{
   
}

BOOL file_manager_operation_document::on_new_document()
{
   return TRUE;
}

