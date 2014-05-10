#include "framework.h"


todo::todo(sp(::base::application) papp, const char * pszTip) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   not_implemented(papp, pszTip)
{
}


todo::todo(const todo & e) :
   element(e),
   ::call_stack(e),
   ::exception::base(e),
   not_implemented(e)
{
}


todo::~todo()
{
}



