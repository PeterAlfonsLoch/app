//#include "framework.h"


job::job(::aura::application * papp) :
object(papp)
{
   m_bCancel = false;
}

job::~job()
{
}

