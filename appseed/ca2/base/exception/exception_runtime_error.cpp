#include "framework.h"


runtime_error::runtime_error(sp(::ca2::application) papp, const char * pszError) :
   ca2(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   error_exception(papp, pszError)
{
}

runtime_error::~runtime_error()
{
}
