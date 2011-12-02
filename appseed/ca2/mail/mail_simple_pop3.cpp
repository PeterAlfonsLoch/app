#include "StdAfx.h"

namespace mail
{

   simple_pop3::simple_pop3(::ax::application * papp) :
      ax(papp),
      pop3(papp)
   {

      m_bRun = false;

   }

   string simple_pop3::get_user()
   {
      return m_strUser;
   }

   string simple_pop3::get_pass()
   {
      return m_strPass;
   }

   string simple_pop3::get_host()
   {
      return m_strHost;
   }

   string simple_pop3::get_transaction()
   {
      return m_strTransaction;
   }

   void simple_pop3::set_stat_count(int iCount)
   {
      m_iStatCount = iCount;
   }

   void simple_pop3::set_stat_size(int iSize)
   {
      m_iStatSize = iSize;
   }

   void simple_pop3::set_list_size(int iSize)
   {
      m_iListSize = iSize;
   }

   void simple_pop3::store()
   {
   }

} // namespace mail
