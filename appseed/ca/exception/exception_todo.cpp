#include "framework.h"


todo::todo(::ca::application * papp, const char * pszTip) :
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   not_implemented_exception(papp, pszTip)
{
}


todo::todo(const todo & e) :
   ca(e),
   ::call_stack(e),
   ::base_exception(e),
   not_implemented_exception(e)
{
}


todo::~todo()
{
}



