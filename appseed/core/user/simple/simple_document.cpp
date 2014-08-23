#include "framework.h"


simple_document::simple_document(sp(::aura::application) papp) : 
   element(papp),
   ::data::data_container_base(papp),
   ::user::document(papp),
   m_set(papp)
{
}

simple_document::~simple_document()
{
}



