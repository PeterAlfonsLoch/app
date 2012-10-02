#include "framework.h"

not_implemented_exception::not_implemented_exception(const not_implemented_exception & e) : 
   base_exception(e), 
   m_strTip(e.m_strTip)
{
}

not_implemented_exception::not_implemented_exception(const char * pszTip) : 
   m_strTip(pszTip)
{
}

not_implemented_exception::~not_implemented_exception(get_app())
{
}

