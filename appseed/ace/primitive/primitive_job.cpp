//#include "framework.h"


job::job(::ace::application * papp) :
object(papp)
{
   m_bCancel = false;
}

job::~job()
{
}

