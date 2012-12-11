#include "StdAfx.h"

namespace ca2
{
   userset::userset()
   {
      m_puser = NULL;
   }
   userset::~userset()
   {
   }
   ::radix::user::profile * userset::get_user()
   {
      if(m_puser == NULL)
      {
         m_puser = System.create_current_user();
      }
      return m_puser;
   }

   void userset::set_user(const char * psz)
   {
      UNREFERENCED_PARAMETER(psz);
   }

   void userset::set_user(::radix::user::profile * puser)
   {
      m_puser = puser;
   }
   
} // namespace ca2