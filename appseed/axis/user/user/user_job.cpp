#include "framework.h"


namespace user
{


   job::job(sp(::axis::application) papp) :
      element(papp),
      ::job(papp)
   {

   }


   job::~job()
   {

   }


} // namespace user





