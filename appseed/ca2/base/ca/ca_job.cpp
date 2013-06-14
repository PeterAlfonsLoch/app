#include "framework.h"


namespace ca2
{


   job::job(sp(::ca2::application) papp) :
      ca2(papp)
   {
      m_bCancel = false;
   }

   job::~job()
   {
   }


} // namespace ca2
