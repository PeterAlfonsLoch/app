#include "framework.h"

temporary_exception::temporary_exception(const temporary_exception & e) : 
   element(e),
   ::call_stack(e),
   ::exception::axis(e),
   m_strTip(e.m_strTip)
{
      printf(":temporary");
}

temporary_exception::temporary_exception(sp(::axis::application) papp, const char * pszTip) : 
   element(papp),
   ::call_stack(papp),
   ::exception::axis(papp),
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

