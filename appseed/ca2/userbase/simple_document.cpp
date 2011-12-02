#include "StdAfx.h"


simple_document::simple_document(::ax::application * papp) : 
   ax(papp),
   data_container(papp),
   document_interface(papp),
   ::document(papp),
   userbase::document(papp),
   m_set(papp)
{
}

simple_document::~simple_document()
{
}
