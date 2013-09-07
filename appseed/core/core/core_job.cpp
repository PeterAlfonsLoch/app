#include "framework.h"


namespace core
{


   job::job(sp(base_application) papp) :
      element(papp)
   {
      m_bCancel = false;
   }

   job::~job()
   {
   }


} // namespace core
