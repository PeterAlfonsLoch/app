#include "framework.h"


runtime_error::runtime_error(sp(base_application) papp, const char * pszError) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   error_exception(papp, pszError)
{
}

runtime_error::~runtime_error()
{
}
