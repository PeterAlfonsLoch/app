#include "framework.h"

temporary_exception::temporary_exception(const temporary_exception & e) : 
   ca2(e),
   ::call_stack(e),
   ::base_exception(e),
   m_strTip(e.m_strTip)
{
}

temporary_exception::temporary_exception(sp(::ca2::application) papp, const char * pszTip) : 
   ca2(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   m_strTip(pszTip)
{
}

temporary_exception::~temporary_exception()
{
}

