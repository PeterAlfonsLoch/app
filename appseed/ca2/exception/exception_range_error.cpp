#include "framework.h"


range_error::range_error(sp(::ca::application) papp, const char * pszError) :
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   error_exception(papp, pszError)
{
}

range_error::~range_error()
{
}
