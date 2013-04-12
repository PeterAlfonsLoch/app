#pragma once

namespace mail
{

   class pop3_socket;

   class CLASS_DECL_ca simple_pop3 :
      virtual public pop3
   {
   public:
      string                  m_strUser;
      string                  m_strPass;
      string                  m_strHost;
      string                  m_strTransaction;

      int32_t                     m_iStatCount;
      int32_t                     m_iStatSize;

      int32_t                     m_iListSize;


      virtual string get_user();
      virtual string get_pass();
      virtual string get_host();
      virtual string get_transaction();

      virtual void set_stat_count(int32_t iCount);
      virtual void set_stat_size(int32_t iSize);

      virtual void set_list_size(int32_t iSize);

      simple_pop3(sp(::ca::application) papp);

      void store();

   };

}