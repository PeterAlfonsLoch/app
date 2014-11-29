#pragma once



namespace simpledb
{


   class CLASS_DECL_CORE database:
      virtual public ::object
   {
      friend class result;
   public:


      string m_strLastError;
      int64_t m_iLastUsedTime;

      int       m_protocol;


      database(::aura::application * papp);
      virtual ~database();


      virtual bool connect(
         const char * pszHost,
         const char * pszUser,
         const char * pszPassword,
         const char * pszDatabase,
         int32_t iPort = 0,
         const char * pszSocketName = NULL,
         uint32_t uiFlags = 0);

      virtual bool close();

      virtual bool initialize();

      //virtual sp(result) query(const char * pszSql);
      virtual var query_item(const char * pszSql,var varDefault = false);
      virtual bool query_blob(primitive::memory_base & memory,const char * pszSql);
      virtual var query_items(const char * pszSql);
      virtual var query_row(const char * pszSql);
      virtual var query_rows(const char * pszSql);


      virtual var query_table_item(const char * table,const char * item,const char *where,var notfound = false);

      virtual var get_agent(const char * pszTable,const char * pszEmail,const char * pszUser);

      virtual string real_escape_string(void * p,strsize iLine);
      virtual string real_escape_string(const char * psz);

      virtual var get_insert_id();

      virtual string error1(const char * pszPrefix = NULL);
      virtual void trace_error1(const char * pszPrefix = NULL);

   };


} //   namespace simpledb



