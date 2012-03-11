#pragma once   


namespace webserver
{


   class CLASS_DECL_ca match_host
   {
   public:
      string m_strHostname;
      string m_strUserAgent;
      cregexp * m_ppcreHostname;
      cregexp * m_ppcreUserAgent;

      match_host(const char * hostname, const char * useragent = NULL);
      virtual ~match_host();

      bool matches(const char * hostname, const char * useragent = NULL);
   };


   typedef array_del_ptr < match_host > match_host_array;



} // namespace webserver