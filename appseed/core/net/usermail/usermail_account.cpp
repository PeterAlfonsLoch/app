#include "framework.h"


namespace usermail
{


   account::account(sp(::aura::application) papp) :
      element(papp),
      m_pop3(papp)
   {
      m_dwCheckTime = 1000 * 60 * 2;
      m_dwLastCheck = ::get_tick_count();
   }


} // namespace usermail






