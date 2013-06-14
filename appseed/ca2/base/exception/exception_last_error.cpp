#include "framework.h"


last_error_exception::last_error_exception(sp(::ca2::application) papp) :
   ca2(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   hresult_exception(papp, HRESULT_FROM_WIN32(::GetLastError()))
{
}

last_error_exception::~last_error_exception()
{
}
