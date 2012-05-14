#include "framework.h"


last_error_exception::last_error_exception() :
   hresult_exception(HRESULT_FROM_WIN32(::GetLastError()))
{
}

last_error_exception::~last_error_exception()
{
}
