#include "framework.h"


not_implemented::not_implemented(const not_implemented & e) : 
   ca2(e),
   ::call_stack(e),
   ::base_exception(e),
   m_strTip(e.m_strTip)
{
}

not_implemented::not_implemented(sp(::ca2::application) papp, const char * pszTip) : 
   ca2(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   m_strTip(pszTip)
{
}

not_implemented::~not_implemented()
{
}

