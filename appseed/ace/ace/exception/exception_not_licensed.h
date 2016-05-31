#pragma once


class CLASS_DECL_ACE not_licensed : 
   virtual public ::exception::base
{
public:


   string      m_strRealm;    // license realm
   string      m_strUrl;      // licensing url


   not_licensed(::ace::application * papp, const char * pszRealm, const char * pszUrl);
   not_licensed(const not_licensed & e);
   virtual ~not_licensed();


};
