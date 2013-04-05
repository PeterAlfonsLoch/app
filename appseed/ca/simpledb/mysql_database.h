#pragma once


#ifndef METROWIN



typedef char **MYSQL_ROW;		/* return data as array of strings */


namespace mysql
{


   class CLASS_DECL_ca database :
      virtual public ::ca::object
   {


      friend class result;

   protected:


      comparable_array < result * > m_resultptra;
      void * m_pmysql; // MYSQL *


   public:


      int64_t m_iLastUsedTime;


      database(::ca::applicationsp papp);
      virtual ~database();


      bool connect(
         const char * pszHost,
         const char * pszUser,
         const char * pszPassword,
         const char * pszDatabase,
         int32_t iPort = 0,
         const char * pszSocketName = ::null(),
         uint32_t uiFlags = 0);

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

         if(presult == ::null())
            return 0;

         MYSQL_ROW row;

         ::count c = 0;

         while((row = (MYSQL_ROW) presult->fetch_row()) != ::null())
         {

            if(row[0] == ::null())
            {
               a1.add(t1null);
            }
            else
            {
               a1.add(::ca::str::from_string < TYPE1 > (row[0]));
            }

            if(row[1] == ::null())
            {
               a2.add(t2null);
            }
            else
            {
               a2.add(::ca::str::from_string < TYPE2 > (row[1]));
            }

            if(row[2] == ::null())
            {
               a3.add(t3null);
            }
            else
            {
               a3.add(::ca::str::from_string < TYPE3 > (row[2]));
            }

            c++;

         }

         return c;

      }

      virtual var query_table_item(const char * table, const char * item, const char *where, var notfound = false);

      virtual var get_agent(const char * pszTable, const char * pszEmail, const char * pszUser);

      string real_escape_string(void * p, strsize iLine);
      string real_escape_string(const char * psz);

      var get_insert_id();

      string error1(const char * pszPrefix = ::null());
      void trace_error1(const char * pszPrefix = ::null());

   };


} //   namespace mysql




#endif