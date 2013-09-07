#include "framework.h"


namespace user
{


   job::job(sp(base_application) papp) :
      element(papp),
      ::core::job(papp)
   {

   }


   job::~job()
   {

   }


} // namespace user





