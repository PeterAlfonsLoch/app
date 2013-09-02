#include "framework.h"


last_error_exception::last_error_exception(sp(::application) papp) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   hresult_exception(papp, HRESULT_FROM_WIN32(::GetLastError()))
{
}

last_error_exception::~last_error_exception()
{
}
