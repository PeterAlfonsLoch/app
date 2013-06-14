#include "framework.h"


void_implementation_exception::void_implementation_exception(sp(::ca2::application) papp, const char * pszTip) : 
   ca2(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   not_implemented(papp, pszTip)
{
}

void_implementation_exception::void_implementation_exception(const void_implementation_exception & e) : 
   ca2(e),
   ::call_stack(e),
   ::base_exception(e),
   not_implemented(e)
{
}

void_implementation_exception::~void_implementation_exception()
{
}
