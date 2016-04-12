#include "framework.h"
#ifndef METROWIN
#include "mysql/mysql.h"


namespace mysql
{


   result::result(database * pdatabase, MYSQL_RES * pres) :
      ::simpledb::result(pdatabase)
   {

//      m_pdatabase->m_resultptra.add(this);
      m_pres = pres;
      m_iFieldCount = -1;

   }


   result::~result()
   {

      free_result();

   }


   bool result::free_result()
   {
      
      try
      {
         if(m_pres != NULL)
         {
            mysql_free_result((MYSQL_RES *) m_pres);
         }
      }
      catch(...)
      {

      }

      try
      {

         if(m_pdatabase != NULL)
         {
//            m_pdatabase->m_resultptra.remove(this);
         }

      }
      catch(...)
      {
      }

      return true;

   }


   MYSQL_ROW result::fetch_row()
   {

      MYSQL_ROW row;

      if(m_pres == NULL)
         return NULL;

      row = mysql_fetch_row((MYSQL_RES *) m_pres);

      if(mysql_errno ((MYSQL *)(dynamic_cast < ::mysql::database * > ( m_pdatabase))->m_pmysql) != 0)
      {

         m_pdatabase->trace_error1( "mysql_fetch_row() failed");

      }

      return row;

   }


   unsigned long * result::fetch_lengths()
   {
      unsigned long * lengths;
      if(m_pres == NULL)
         return NULL;
      lengths = mysql_fetch_lengths((MYSQL_RES *) m_pres);
      if(mysql_errno((MYSQL *)(dynamic_cast < ::mysql::database * > (m_pdatabase))->m_pmysql) != 0)
         m_pdatabase->trace_error1( "mysql_fetch_row() failed");
      return lengths;
   }

   int32_t result::num_fields()
   {
      return mysql_num_fields((MYSQL_RES *) m_pres);
   }

   int64_t result::num_rows()
   {
      return mysql_num_rows ((MYSQL_RES *) m_pres);
   }


   /* process rows and then free the result set */
   //process_result_set (conn, res_set);




} // namespace mysql


#endif