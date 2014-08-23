#include "framework.h"


job::job(sp(::aura::application) papp) :
element(papp)
{
   m_bCancel = false;
}

job::~job()
{
}

