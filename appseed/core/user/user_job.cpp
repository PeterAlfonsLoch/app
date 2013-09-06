#include "framework.h"


namespace user
{


   job::job(sp(base_application) papp) :
      element(papp),
      ::ca2::job(papp)
   {

   }


   job::~job()
   {

   }


} // namespace user





