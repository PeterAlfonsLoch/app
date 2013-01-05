#pragma once

namespace mail
{

   class CLASS_DECL_ca2 account :
      virtual public ::radix::object
   {
   public:
      account(::ca::application * papp);
      string         m_id;
      string         m_strEmail;
      string         m_strServer;
      string         m_strLogin;
      string         m_strMailDb;
      uint32_t          m_dwLastCheck;
      uint32_t          m_dwCheckTime;
      db_pop3        m_pop3;
   };

}