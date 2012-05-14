#include "framework.h"


namespace user
{

   job::job(::ca::application * papp) :
      ca(papp),
      ::ca::job(papp)
   {
      m_pview = NULL;
   }

   job::~job()
   {
   }

} // namespace user