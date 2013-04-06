#include "framework.h"

temporary_exception::temporary_exception(const temporary_exception & e) : 
   ca(e),
   ::call_stack(e),
   ::base_exception(e),
   m_strTip(e.m_strTip)
{
}

temporary_exception::temporary_exception(sp(::ca::application) papp, const char * pszTip) : 
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   m_strTip(pszTip)
{
}

temporary_exception::~temporary_exception()
{
}

