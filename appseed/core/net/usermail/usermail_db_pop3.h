#pragma once


namespace usermail
{


   class account;
   class pop3_socket;
   class tree;
   class list;


   class CLASS_DECL_CORE db_pop3 :
      virtual public ::mail::pop3
   {
   public:
      
      
      ::sqlite::base        * m_pdatabase;
      ::sqlite::set         * m_pdataset;

      ::usermail::account       * m_paccount;
      critical_section        m_csDataset;
      string                  m_strTransaction;


      db_pop3(sp(::axis::application) papp);


      virtual string get_user();
      virtual string get_pass();
      virtual string get_host();
      virtual string get_transaction();

      virtual void start();

      void update_lists();

      void store();

      void filter_id();

      UINT run();

   };


} // namespace usermail




