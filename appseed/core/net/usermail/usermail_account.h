#pragma once


namespace usermail
{


   class db_pop3;


   class CLASS_DECL_CORE account :
      virtual public ::object
   {
   public:
      
      
      string               m_id;
      string               m_strEmail;
      string               m_strServer;
      string               m_strLogin;
      string               m_strMailDb;
      uint32_t             m_dwLastCheck;
      uint32_t             m_dwCheckTime;
      db_pop3 *            m_ppop3;


      account(sp(::aura::application) papp);


   };


} // namespace usermail






