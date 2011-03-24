#pragma once

namespace mail
{

   class account :
      virtual public ::radix::object
   {
   public:
      account(::ca::application * papp);
      string         m_id;
      string         m_strEmail;
      string         m_strServer;
      string         m_strLogin;
      string         m_strMailDb;
      DWORD          m_dwLastCheck;
      DWORD          m_dwCheckTime;
      db_pop3        m_pop3;
   };

}