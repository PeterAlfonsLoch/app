#include "framework.h"


namespace user
{


   job::job(sp(::ca::application) papp) :
      ca(papp),
      ::ca::job(papp)
   {

   }


   job::~job()
   {

   }


} // namespace user





