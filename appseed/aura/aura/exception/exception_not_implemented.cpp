#include "framework.h"


not_implemented::not_implemented(const not_implemented & e) : 
   element(e),
   ::call_stack(e),
   ::exception::base(e),
   m_strTip(e.m_strTip)
{
      printf(":not_implemented(copy)");
   }

not_implemented::not_implemented(sp(::axis::application) papp, const char * pszTip) : 
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   m_strTip(pszTip)
{
      if(pszTip == NULL)
      {
         printf(":not_implemented(NULL)");
      }
      else
      {
         printf(":not_implemented(\"%s\")",pszTip);
      }
}

not_implemented::~not_implemented()
{
}

