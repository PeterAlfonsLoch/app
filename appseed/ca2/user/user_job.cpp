#include "framework.h"


namespace user
{


   job::job(sp(::ca2::application) papp) :
      ca2(papp),
      ::ca2::job(papp)
   {

   }


   job::~job()
   {

   }


} // namespace user





