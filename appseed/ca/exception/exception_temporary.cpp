#include "framework.h"

temporary_exception::temporary_exception(const temporary_exception & e) : 
   base_exception(e), 
   m_strTip(e.m_strTip)
{
}

temporary_exception::temporary_exception(const char * pszTip) : 
   m_strTip(pszTip)
{
}

temporary_exception::~temporary_exception()
{
}

