#include "StdAfx.h"


namespace mail
{

   account::account(::ca::application * papp) :
      ca(papp),
      m_pop3(papp)
   {
      m_dwCheckTime = 1000 * 60 * 2;
      m_dwLastCheck = ::GetTickCount();
   }
}