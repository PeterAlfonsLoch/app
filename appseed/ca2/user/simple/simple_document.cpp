#include "framework.h"


simple_document::simple_document(sp(::ca::application) papp) : 
   ca(papp),
   ::ca::data_container_base(papp),
   ::ca::data_container(papp),
   user::document(papp),
   m_set(papp)
{
}

simple_document::~simple_document()
{
}



