#include "framework.h"


simple_document::simple_document(sp(::ca::application) papp) : 
   ca(papp),
   ::ca::data_container_base(papp),
   userbase::document(papp),
   m_set(papp)
{
}

simple_document::~simple_document()
{
}



