#include "framework.h"


void_implementation_exception::void_implementation_exception(const char * pszTip) : 
   not_implemented_exception(pszTip)
{
}

void_implementation_exception::void_implementation_exception(const void_implementation_exception & e) : 
   not_implemented_exception(e)
{
}

void_implementation_exception::~void_implementation_exception()
{
}
