#include "framework.h"


not_implemented::not_implemented(const not_implemented & e) : 
   ca(e),
   ::call_stack(e),
   ::base_exception(e),
   m_strTip(e.m_strTip)
{
}

not_implemented::not_implemented(::ca::applicationsp papp, const char * pszTip) : 
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   m_strTip(pszTip)
{
}

not_implemented::~not_implemented()
{
}

