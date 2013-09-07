#include "framework.h"


job::job(sp(base_application) papp) :
   element(papp)
{
   m_bCancel = false;
}

job::~job()
{
}

