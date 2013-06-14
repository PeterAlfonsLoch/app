#include "framework.h"


interface_only_exception::interface_only_exception(sp(::ca2::application) papp, const char * pszTip) : 
   ca2(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   not_implemented(papp, pszTip)
{
}

interface_only_exception::interface_only_exception(const interface_only_exception & e) : 
   ca2(e),
   ::call_stack(e),
   ::base_exception(e),
   not_implemented(e)
{
}

interface_only_exception::~interface_only_exception()
{
}
