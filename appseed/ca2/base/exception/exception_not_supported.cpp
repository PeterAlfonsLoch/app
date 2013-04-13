#include "framework.h"


not_supported_exception::not_supported_exception(const not_supported_exception & e) :
   ca(e.get_app()),
   ::call_stack(e.get_app()),
   ::base_exception(e.get_app()),
   not_implemented(e),
   interface_only_exception(e)
{

}

not_supported_exception::not_supported_exception(sp(::ca::application) papp, const char * pszTip) :
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   not_implemented(papp, pszTip),
   interface_only_exception(papp, pszTip)
{

}

not_supported_exception::~not_supported_exception()
{

}


