#pragma once   

class CLASS_DECL_CA2_CUBE match_host
{
public:
   string m_strHostname;
   string m_strUserAgent;
   CRegExp * m_ppcreHostname;
   CRegExp * m_ppcreUserAgent;
   
   match_host(const char * hostname, const char * useragent = NULL);
   
   bool matches(const char * hostname, const char * useragent = NULL);
};
   
   
typedef base_array < match_host * > match_host_ptr_array;
   
