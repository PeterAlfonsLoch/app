#include "StdAfx.h"


namespace user
{

   job::job(::ax::application * papp) :
      ax(papp),
      ::ax::job(papp)
   {
      m_pview = NULL;
   }

   job::~job()
   {
   }

} // namespace user