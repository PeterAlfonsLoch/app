#pragma once

namespace mail
{

   class CLASS_DECL_ca account :
      virtual public ::radix::object
   {
   public:
      account(::ax::application * papp);
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