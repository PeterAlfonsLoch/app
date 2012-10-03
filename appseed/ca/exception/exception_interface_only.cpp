#include "framework.h"


interface_only_exception::interface_only_exception(::ca::application * papp, const char * pszTip) : 
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   not_implemented(papp, pszTip)
{
}

interface_only_exception::interface_only_exception(const interface_only_exception & e) : 
   ca(e),
   ::call_stack(e),
   ::base_exception(e),
   not_implemented(e)
{
}

interface_only_exception::~interface_only_exception()
{
}
