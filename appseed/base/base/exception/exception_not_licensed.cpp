#include "framework.h"


not_licensed::not_licensed(sp(::base::application) papp, const char * pszRealm, const char * pszUrl) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp)
{

   m_strRealm     = pszRealm;
   m_strUrl       = pszUrl;

}


not_licensed::not_licensed(const not_licensed & e) :
   element(e.get_app()),
   ::call_stack(e.get_app()),
   ::exception::base(e)
{

   m_strRealm     = e.m_strRealm;
   m_strUrl       = e.m_strUrl;

}


not_licensed::~not_licensed()
{
}

