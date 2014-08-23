#include "framework.h"

installing_exception::installing_exception(const installing_exception & e) : 
   element(e.get_app()),
   ::call_stack(e.get_app()),
   ::exception::base(e.get_app()),
   temporary_exception(e.get_app(), e.m_strTip)
{
      printf(":installing(copy)");
}

installing_exception::installing_exception(sp(::aura::application) papp, const char * pszTip) : 
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   temporary_exception(papp, pszTip)
{
      if(pszTip == NULL)
      {
         printf(":installing(NULL)");
      }
      else
      {
         printf(":installing(\"%s\")",pszTip);
      }
}

installing_exception::~installing_exception()
{
}

