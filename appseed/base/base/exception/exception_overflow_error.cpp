#include "framework.h"


overflow_error::overflow_error(sp(::base::application) papp, const char * pszError) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   error_exception(papp, pszError)
{
}

overflow_error::~overflow_error()
{
}
