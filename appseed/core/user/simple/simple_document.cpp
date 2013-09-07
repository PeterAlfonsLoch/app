#include "framework.h"


simple_document::simple_document(sp(base_application) papp) : 
   element(papp),
   ::core::data_container_base(papp),
   
   user::document(papp),
   m_set(papp)
{
}

simple_document::~simple_document()
{
}



