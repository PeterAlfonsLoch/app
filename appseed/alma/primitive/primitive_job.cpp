#include "framework.h"


job::job(sp(::base::application) papp) :
element(papp)
{
   m_bCancel = false;
}

job::~job()
{
}

