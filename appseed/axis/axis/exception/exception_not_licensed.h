#pragma once


class CLASS_DECL_AXIS not_licensed : 
   virtual public ::exception::base
{
public:


   string      m_strRealm;    // license realm
   string      m_strUrl;      // licensing url


   not_licensed(sp(::base::application) papp, const char * pszRealm, const char * pszUrl);
   not_licensed(const not_licensed & e);
   virtual ~not_licensed();


};
