//#include "framework.h"


namespace simpledb
{


   database::database(::aura::application * papp):
      ::object(papp)
   {
      
      m_pmutex = new mutex(papp);

      m_protocol = 0;

   }


   database::~database()
   {

      close();

      ::aura::del(m_pmutex);

   }


   bool database::initialize()
   {

      return true;

   }

   bool database::connect(
      const char * pszHost,
      const char * pszUser,
      const char * pszPassword,
      const char * pszDatabase,
      int32_t iPort,
      const char * pszSocketName,
      uint32_t uiFlags)
   {
      return false;
   }

   bool database::close()
   {
         return false;

   }

   string database::error1(const char * pszPrefix)
   {
      return "";
   }

   void database::trace_error1(const char * pszPrefix)
   {
      m_strLastError += error1(pszPrefix);
      TRACE0(m_strLastError);
   }

   sp(result) database::query(const char * pszSql)
   {

            return NULL;
   }

   var database::query_item(const char * pszSql,var varDefault)
   {
      return ::var(::var::type_null);
   }
   bool database::query_blob(primitive::memory_base & memory,const char * pszSql)
   {
         return false;
   }
   var database::query_items(const char * pszSql)
   {
      return ::var(::var::type_null);
   }
   var database::query_row(const char * pszSql)
   {
      return ::var(::var::type_null);
   }
   var database::query_rows(const char * pszSql)
   {
      return ::var(::var::type_null);
   }

   var database::query_table_item(const char * table,const char * item,const char *where,var notfound)
   {
      return ::var(::var::type_null);
   }


   var database::get_agent(const char * pszTable,const char * psz,const char * pszUser)
   {
      return ::var(::var::type_null);
   }


   string database::real_escape_string(void * p,strsize iLen)
   {
      
      return "";
   }
   string database::real_escape_string(const char * psz)
   {
      return "";
   }

   var database::get_insert_id()
   {
      return -1;
   }

} //   namespace simpledb


