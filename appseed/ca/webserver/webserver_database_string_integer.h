#pragma once


namespace webserver
{


   class database;


   class CLASS_DECL_ca database_string_integer :
      virtual public dynamic_source::ptr
   {    
   public:
      database_string_integer(webserver::database * pdatabase = NULL, const char * pszTable = NULL);

      using ptr::get;
      bool get(const char * psz, __int64 & n);
      void set(const char * psz, __int64 n);

      string m_strTable;
      webserver::database * m_pdatabase;
   };


} // namespace webserver



