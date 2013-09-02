#include "framework.h"


namespace ca2
{


   job::job(sp(::application) papp) :
      element(papp)
   {
      m_bCancel = false;
   }

   job::~job()
   {
   }


} // namespace ca2
