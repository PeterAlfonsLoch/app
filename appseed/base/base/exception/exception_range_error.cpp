#include "framework.h"


range_error::range_error(sp(::base::application) papp, const char * pszError) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   error_exception(papp, pszError)
{
}

range_error::~range_error()
{
}
