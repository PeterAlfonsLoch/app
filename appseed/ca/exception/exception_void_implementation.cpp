#include "framework.h"


void_implementation_exception::void_implementation_exception(::ca::application * papp, const char * pszTip) : 
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   not_implemented_exception(papp, pszTip)
{
}

void_implementation_exception::void_implementation_exception(const void_implementation_exception & e) : 
   ca(e),
   ::call_stack(e),
   ::base_exception(e),
   not_implemented_exception(e)
{
}

void_implementation_exception::~void_implementation_exception()
{
}
