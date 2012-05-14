#include "framework.h"


not_supported_exception::not_supported_exception(const not_supported_exception & e) :
   interface_only_exception(e)
{

}

not_supported_exception::not_supported_exception(const char * pszTip)
   : interface_only_exception(pszTip)
{

}

not_supported_exception::~not_supported_exception()
{

}


