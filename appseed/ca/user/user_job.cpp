#include "framework.h"


namespace user
{


   job::job(::ca::application * papp) :
      ca(papp),
      ::ca::job(papp)
   {

   }


   job::~job()
   {

   }


} // namespace user





