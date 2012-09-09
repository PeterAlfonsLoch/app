#include "framework.h"


todo::todo(const char * pszTip) :
   not_implemented_exception(pszTip)
{
}


todo::todo(const todo & e) :
   not_implemented_exception(e)
{
}


todo::~todo()
{
}



