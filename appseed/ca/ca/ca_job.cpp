#include "framework.h"


namespace ca
{


   job::job(::ca::applicationsp papp) :
      ca(papp)
   {
      m_bCancel = false;
   }

   job::~job()
   {
   }


} // namespace ca