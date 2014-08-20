#pragma once


#ifndef METROWIN



typedef char **MYSQL_ROW;		/* return data as array of strings */
typedef struct st_mysql MYSQL;


namespace mysql
{


   class CLASS_DECL_CORE database :
      virtual public ::object
   {
      friend class result;
   public:


      //spa(result) m_esultptra;
      MYSQL * m_pmysql; // MYSQL *
	  string m_strLastError;
      int64_t m_iLastUsedTime;

      int       m_protocol;


      database(sp(::axis::application) papp);
      virtual ~database();


      bool connect(
         const char * pszHost,
         const char * pszUser,
         const char * pszPassword,
         const char * pszDatabase,
         int32_t iPort = 0,
         const char * pszSocketName = NULL,
         uint32_t uiFlags = 0);

      bool close();

      virtual bool initialize();

      virtual sp(result) query(const char * pszSql);
      virtual var query_item(const char * pszSql, var varDefault = false);
      virtual bool query_blob(primitive::memory_base & memory, const char * pszSql);
      virtual var query_items(const char * pszSql);
      virtual var query_row(const char * pszSql);
      virtual var query_rows(const char * pszSql);

      template < class ARRAY1, class ARRAY2, class ARRAY3, class TYPE1, class TYPE2, class TYPE3 >
      ::count query_rows(const char * pszSql, ARRAY1 & a1, ARRAY2 & a2, ARRAY3 & a3, TYPE1 t1null, TYPE2 t2null, TYPE3 t3null)
      {

         sp(result) presult = query(pszSql);

         if(presult == NULL)
            return 0;

         MYSQL_ROW row;

         ::count ca = 0;

         while((row = (MYSQL_ROW) presult->fetch_row()) != NULL)
         {

            if(row[0] == NULL)
            {
               a1.add(t1null);
            }
            else
            {
               a1.add(::str::from_string < TYPE1 > (row[0]));
            }

            if(row[1] == NULL)
            {
               a2.add(t2null);
            }
            else
            {
               a2.add(::str::from_string < TYPE2 > (row[1]));
            }

            if(row[2] == NULL)
            {
               a3.add(t3null);
            }
            else
            {
               a3.add(::str::from_string < TYPE3 > (row[2]));
            }

            ca++;

         }

         return ca;

      }

      virtual var query_table_item(const char * table, const char * item, const char *where, var notfound = false);

      virtual var get_agent(const char * pszTable, const char * pszEmail, const char * pszUser);

      string real_escape_string(void * p, strsize iLine);
      string real_escape_string(const char * psz);

      var get_insert_id();

      string error1(const char * pszPrefix = NULL);
      void trace_error1(const char * pszPrefix = NULL);

   };


} //   namespace mysql




#endif