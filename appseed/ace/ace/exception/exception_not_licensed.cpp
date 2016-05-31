//#include "framework.h"


not_licensed::not_licensed(::ace::application * papp, const char * pszRealm, const char * pszUrl) :
   object(papp),
   ::call_stack(papp),
   ::exception::base(papp)
{
   
   string str;

   m_strRealm     = pszRealm;
   str += "realm=" + m_strRealm + ";";
   m_strUrl       = pszUrl;
   str += "url=" + m_strUrl + ";";

   debug_print(":not_licensed(\"%s\"",str.c_str());

}


not_licensed::not_licensed(const not_licensed & e) :
   object(e.get_app()),
   ::call_stack(e.get_app()),
   ::exception::base(e)
{

   debug_print(":not_licensed(copy)");

   m_strRealm     = e.m_strRealm;
   m_strUrl       = e.m_strUrl;

}


not_licensed::~not_licensed()
{

}




