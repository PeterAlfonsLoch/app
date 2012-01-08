#pragma once


#include "mysql/mysql.h"


namespace mysql
{

   class CLASS_DECL_ca database :
      virtual public ::radix::object
   {
   public:


      __int64 m_iLastUsedTime;
      

      database(::ca::application * papp);
      virtual ~database();
      bool connect(
         const char * pszHost, 
         const char * pszUser,
         const char * pszPassword, 
         const char * pszDatabase,
         int iPort = 0,
         const char * pszSocketName = NULL,
         unsigned int uiFlags = 0);

      bool close();

      virtual result * query(const char * pszSql);
      virtual var query_item(const char * pszSql, var varDefault = false);
      virtual bool query_blob(primitive::memory_base & memory, const char * pszSql);
      virtual var query_items(const char * pszSql);
      virtual var query_row(const char * pszSql);
      virtual var query_rows(const char * pszSql);

      template < class ARRAY1, class ARRAY2, class ARRAY3, class TYPE1, class TYPE2, class TYPE3 >
      ::count query_rows(const char * pszSql, ARRAY1 & a1, ARRAY2 & a2, ARRAY3 & a3, TYPE1 t1null, TYPE2 t2null, TYPE3 t3null)
      {

         result * presult = query(pszSql);

         if(presult == NULL)
            return gen::g_newconst;

         MYSQL_ROW row;

         ::count c = 0;

         while((row = (MYSQL_ROW) presult->fetch_row()) != NULL)
         {

            if(row[0] == NULL)
            {
               a1.add(t1null);
            }
            else
            {
               a1.add(gen::str::from_string < TYPE1 > (row[0]));
            }

            if(row[1] == NULL)
            {
               a2.add(t2null);
            }
            else
            {
               a2.add(gen::str::from_string < TYPE2 > (row[1]));
            }

            if(row[2] == NULL)
            {
               a3.add(t3null);
            }
            else
            {
               a3.add(gen::str::from_string < TYPE3 > (row[2]));
            }

            c++;

         }

         return c;

      }

      virtual var query_table_item(const char * table, const char * item, const char *where, var notfound = false);

      virtual var get_agent(const char * pszTable, const char * pszEmail, const char * pszUser);

      string real_escape_string(void * p, int iLine);
      string real_escape_string(const char * psz);

      var get_insert_id();

      string error1(const char * pszPrefix = NULL);
      void trace_error1(const char * pszPrefix = NULL);

      friend class result;
   protected:
      comparable_array < result * > m_resultptra;
      void * m_pmysql; // MYSQL *
   };


} //   namespace mysql