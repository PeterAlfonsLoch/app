#pragma once

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
      virtual var query_items(const char * pszSql);
      virtual var query_row(const char * pszSql);
      virtual var query_rows(const char * pszSql);
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