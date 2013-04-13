#include "framework.h"


namespace ca
{


   job::job(sp(::ca::application) papp) :
      ca(papp)
   {
      m_bCancel = false;
   }

   job::~job()
   {
   }


} // namespace ca