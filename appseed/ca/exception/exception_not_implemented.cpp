#include "framework.h"


not_implemented_exception::not_implemented_exception(const not_implemented_exception & e) : 
   ca(e),
   ::call_stack(e),
   ::base_exception(e),
   m_strTip(e.m_strTip)
{
}

not_implemented_exception::not_implemented_exception(::ca::application * papp, const char * pszTip) : 
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   m_strTip(pszTip)
{
}

not_implemented_exception::~not_implemented_exception()
{
}

