#include "StdAfx.h"



document::document(::ca::application * papp) :
   ca(papp),
   ::ca::data_container(papp)
{
   m_documentptra.add(this);

}

document::~document()
{
}

