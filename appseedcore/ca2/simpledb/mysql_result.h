#pragma once

namespace mysql
{

   class database;

   class CLASS_DECL_ca result :
      virtual public ::radix::object
   {
   public:
      virtual ~result();

      void * fetch_row(); // MYSQL_ROW
      unsigned long * fetch_lengths(); // MYSQL_ROW
      __int64 num_rows();
      int num_fields();

      friend class database;
   protected:
      //result(database * pdatabase, bool bAutoDelete, MYSQL_RES * pres);
      result(database * pdatabase, bool bAutoDelete, void * pres);
      bool free_result();
      database * m_pdatabase;
      void * m_pres; // MYSQL_RES
      int   m_iFieldCount;
      bool m_bAutoDelete;
   };


} //   namespace mysql