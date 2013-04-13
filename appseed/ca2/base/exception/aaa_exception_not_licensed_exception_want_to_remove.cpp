#include "framework.h"


not_licensed::not_licensed(const char * pszRealm, const char * pszUrl)
{

   m_strRealm     = pszRealm;
   m_strUrl       = pszUrl;

}


not_licensed::not_licensed(const not_licensed & e)
{

   m_strRealm     = e.m_strRealm;
   m_strUrl       = e.m_strUrl;

}


not_licensed::~not_licensed()
{
}

