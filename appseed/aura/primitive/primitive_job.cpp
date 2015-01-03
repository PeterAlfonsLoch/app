//#include "framework.h"


job::job(::aura::application * papp) :
element(papp)
{
   m_bCancel = false;
}

job::~job()
{
}

