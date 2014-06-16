#include "framework.h"


last_error_exception::last_error_exception(sp(::base::application) papp) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   hresult_exception(papp, HRESULT_FROM_WIN32(::GetLastError()))
{
   printf(":last_error_exception(%d)", ::GetLastError());
}

last_error_exception::~last_error_exception()
{
}
