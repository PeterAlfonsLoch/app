#pragma once


class CLASS_DECL_ca2 not_licensed : 
   virtual public base_exception
{
public:


   vsstring      m_strRealm;    // license realm
   vsstring      m_strUrl;      // licensing url


   not_licensed(sp(::ca2::application) papp, const char * pszRealm, const char * pszUrl);
   not_licensed(const not_licensed & e);
   virtual ~not_licensed();


};
