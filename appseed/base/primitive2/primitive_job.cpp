#include "framework.h"


job::job(sp(::axis::application) papp) :
element(papp)
{
   m_bCancel = false;
}

job::~job()
{
}

