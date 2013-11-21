#include "framework.h"


simple_document::simple_document(sp(base_application) papp) : 
   element(papp),
   ::user::object(papp),
   m_set(papp)
{
}

simple_document::~simple_document()
{
}



