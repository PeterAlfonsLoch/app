#include "framework.h"


runtime_error::runtime_error(::ca::application * papp, const char * pszError) :
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   error_exception(papp, pszError)
{
}

runtime_error::~runtime_error()
{
}
