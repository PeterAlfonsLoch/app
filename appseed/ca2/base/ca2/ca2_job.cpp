#include "framework.h"


namespace ca2
{


   job::job(sp(base_application) papp) :
      element(papp)
   {
      m_bCancel = false;
   }

   job::~job()
   {
   }


} // namespace ca2
