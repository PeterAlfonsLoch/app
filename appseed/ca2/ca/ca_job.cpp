#include "StdAfx.h"


namespace ca
{


   job::job(::ca::application * papp) :
      ca(papp)
   {
      m_bCancel = false;
   }

   job::~job()
   {
   }


} // namespace ca