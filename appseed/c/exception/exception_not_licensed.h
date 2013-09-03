#pragma once


class CLASS_DECL_c not_licensed : 
   virtual public ::exception::base
{
public:


   vsstring      m_strRealm;    // license realm
   vsstring      m_strUrl;      // licensing url


   not_licensed(sp(base_application) papp, const char * pszRealm, const char * pszUrl);
   not_licensed(const not_licensed & e);
   virtual ~not_licensed();


};
