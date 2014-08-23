#include "framework.h"

temporary_exception::temporary_exception(const temporary_exception & e) : 
   element(e),
   ::call_stack(e),
   ::exception::base(e),
   m_strTip(e.m_strTip)
{
      printf(":temporary");
}

temporary_exception::temporary_exception(sp(::aura::application) papp, const char * pszTip) : 
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   m_strTip(pszTip)
{
      if(pszTip == NULL)
      {
         printf(":temporary(NULL)");
      }
      else
      {
         printf(":temporary(\"%s\")",pszTip);
      }
}

temporary_exception::~temporary_exception()
{
}

