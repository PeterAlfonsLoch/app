#pragma once

class CLASS_DECL_ca url_domain_base
{
public:
   
   string         m_strOriginalName;
   
   const char *   m_pszRadix;
   int            m_iLenRadix;
   const char *   m_pszSuffix;
   int            m_iLenSuffix;
   const char *   m_pszDomain;
   int            m_iLenDomain;
   const char *   m_pszPrefix;
   int            m_iLenPrefix;
   const char *   m_pszTopLevel;
   int            m_iLenTopLevel;
   const char *   m_pszName;
   int            m_iLenName;

   int            m_iCount;
   bool           m_bHasWww;


   url_domain_base();

   void create(const char * pszServerName);


   static string get_name(const char * pszServerName);

};


class CLASS_DECL_ca url_domain :
   public url_domain_base
{
public:
   
   
   string      m_strRadix;
   string      m_strSuffix;
   string      m_strDomain;
   string      m_strPrefix;
   string      m_strTopLevel;
   string      m_strName;

   void create(const char * pszServerName);


};
   
   

bool CLASS_DECL_ca server_is_top_domain(const char * pszTop1, int iLen1, const char * pszTop2, int iLen2);
inline bool CLASS_DECL_ca server_is_top_domain(string strTop1, string strTop2)
{
   return server_is_top_domain(strTop1, strTop1.get_length(), strTop2, strTop2.get_length());
}


