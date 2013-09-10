#include "framework.h"


job::job(sp(base_application) papp) :
   base_element(papp)
{
   m_bCancel = false;
}

job::~job()
{
}

