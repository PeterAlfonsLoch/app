#include "framework.h"


void_implementation_exception::void_implementation_exception(sp(::base::application) papp, const char * pszTip) : 
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   not_implemented(papp, pszTip)
{
}

void_implementation_exception::void_implementation_exception(const void_implementation_exception & e) : 
   element(e),
   ::call_stack(e),
   ::exception::base(e),
   not_implemented(e)
{
}

void_implementation_exception::~void_implementation_exception()
{
}
