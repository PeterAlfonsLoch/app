#pragma once


class CLASS_DECL_ca not_licensed : 
   virtual public base_exception
{
public:


   string      m_strRealm;    // license realm
   string      m_strUrl;      // licensing url


   not_licensed(const char * pszRealm, const char * pszUrl);
   not_licensed(const not_licensed & e);
   virtual ~not_licensed();
};
