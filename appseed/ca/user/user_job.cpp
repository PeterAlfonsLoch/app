#include "framework.h"


namespace user
{


   job::job(::ca::applicationsp papp) :
      ca(papp),
      ::ca::job(papp)
   {

   }


   job::~job()
   {

   }


} // namespace user





