#include "framework.h"


todo::todo(sp(::axis::application) papp, const char * pszTip) :
   element(papp),
   ::call_stack(papp),
   ::exception::axis(papp),
   not_implemented(papp, pszTip)
{
      printf(":todo");
}


todo::todo(const todo & e) :
   element(e),
   ::call_stack(e),
   ::exception::axis(e),
   not_implemented(e)
{
      printf(":todo(copy)");
}


todo::~todo()
{
}



