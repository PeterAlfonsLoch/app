#pragma once

namespace mail
{

   class pop3_socket;

   class CLASS_DECL_ca2 simple_pop3 :
      virtual public pop3
   {
   public:
      string                  m_strUser;
      string                  m_strPass;
      string                  m_strHost;
      string                  m_strTransaction;

      int                     m_iStatCount;
      int                     m_iStatSize;

      int                     m_iListSize;


      virtual string get_user();
      virtual string get_pass();
      virtual string get_host();
      virtual string get_transaction();

      virtual void set_stat_count(int iCount);
      virtual void set_stat_size(int iSize);

      virtual void set_list_size(int iSize);

      simple_pop3(::ca::application * papp);

      void store();

   };

}