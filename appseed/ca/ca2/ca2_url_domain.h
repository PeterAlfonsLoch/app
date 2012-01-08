#pragma once


class CLASS_DECL_ca url_domain
{
public:
   
   
   string      m_strRadix;
   string      m_strSuffix;
   string      m_strDomain;
   string      m_strPrefix;
   string      m_strTopLevel;
   string      m_strName;
   string      m_strOriginalName;
   stringa     m_stra;
   ::count     m_iCount;
   bool        m_bHasWww;

   void create(const char * psz);

};
   
   
bool CLASS_DECL_ca server_is_top_domain(string strTop1, string strTop2);



