#include "framework.h"


not_licensed::not_licensed(sp(::axis::application) papp, const char * pszRealm, const char * pszUrl) :
   element(papp),
   ::call_stack(papp),
   ::exception::axis(papp)
{
      string str;
   m_strRealm     = pszRealm;
   str += "realm=" + m_strRealm + ";";
   m_strUrl       = pszUrl;
   str += "url=" + m_strUrl + ";";
   printf(":not_licensed(\"%s\"", str.c_str());
}


not_licensed::not_licensed(const not_licensed & e) :
   element(e.get_app()),
   ::call_stack(e.get_app()),
   ::exception::axis(e)
{

      printf(":not_licensed(copy)");
   m_strRealm     = e.m_strRealm;
   m_strUrl       = e.m_strUrl;

}


not_licensed::~not_licensed()
{
}

