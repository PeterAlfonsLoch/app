#include "framework.h"


overflow_error::overflow_error(::ca::application * papp, const char * pszError) :
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   error_exception(papp, pszError)
{
}

overflow_error::~overflow_error()
{
}
