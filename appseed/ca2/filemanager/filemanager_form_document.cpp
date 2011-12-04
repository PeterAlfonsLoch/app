#include "StdAfx.h"


file_manager_form_document::file_manager_form_document(::ca::application * papp) :
   ca(papp),
   data_container(papp),
   document_interface(papp),
   form_document(papp),
   html_document(papp),
   ::document(papp),
   ::userbase::document(papp)
{
}