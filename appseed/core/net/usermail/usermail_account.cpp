#include "framework.h"
#include "base/net/net_sockets.h"
#include "usermail_db_pop3.h"


namespace usermail
{


   account::account(sp(::aura::application) papp) :
      element(papp)
   {

      m_dwCheckTime = 1000 * 60 * 2;

      m_dwLastCheck = ::get_tick_count();

      m_ppop3 = new db_pop3(papp);

   }


} // namespace usermail






