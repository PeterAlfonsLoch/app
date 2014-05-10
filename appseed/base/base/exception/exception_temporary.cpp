#include "framework.h"

temporary_exception::temporary_exception(const temporary_exception & e) : 
   element(e),
   ::call_stack(e),
   ::exception::base(e),
   m_strTip(e.m_strTip)
{
}

temporary_exception::temporary_exception(sp(::base::application) papp, const char * pszTip) : 
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   m_strTip(pszTip)
{
}

temporary_exception::~temporary_exception()
{
}

