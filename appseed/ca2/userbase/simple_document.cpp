#include "framework.h"


simple_document::simple_document(::ca::application * papp) : 
   ca(papp),
   userbase::document(papp),
   m_set(papp)
{
}

simple_document::~simple_document()
{
}



