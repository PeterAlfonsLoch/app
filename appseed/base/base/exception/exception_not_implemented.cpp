#include "framework.h"


not_implemented::not_implemented(const not_implemented & e) : 
   element(e),
   ::call_stack(e),
   ::exception::base(e),
   m_strTip(e.m_strTip)
{
}

not_implemented::not_implemented(sp(::base::application) papp, const char * pszTip) : 
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   m_strTip(pszTip)
{
}

not_implemented::~not_implemented()
{
}

