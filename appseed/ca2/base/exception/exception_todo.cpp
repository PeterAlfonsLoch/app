#include "framework.h"


todo::todo(sp(::ca2::application) papp, const char * pszTip) :
   ca2(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   not_implemented(papp, pszTip)
{
}


todo::todo(const todo & e) :
   ca2(e),
   ::call_stack(e),
   ::base_exception(e),
   not_implemented(e)
{
}


todo::~todo()
{
}



