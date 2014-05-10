#include "framework.h"


simple_document::simple_document(sp(::base::application) papp) : 
   element(papp),
   ::data::data_container_base(papp),
   ::user::object(papp),
   m_set(papp)
{
}

simple_document::~simple_document()
{
}



