#include "framework.h"


not_licensed::not_licensed(::ca::applicationsp papp, const char * pszRealm, const char * pszUrl) :
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp)
{

   m_strRealm     = pszRealm;
   m_strUrl       = pszUrl;

}


not_licensed::not_licensed(const not_licensed & e) :
   ca(e.get_app()),
   ::call_stack(e.get_app()),
   ::base_exception(e)
{

   m_strRealm     = e.m_strRealm;
   m_strUrl       = e.m_strUrl;

}


not_licensed::~not_licensed()
{
}

