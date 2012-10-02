#include "framework.h"


interface_only_exception::interface_only_exception(const char * pszTip) : 
   not_implemented_exception(pszTip)
{
}

interface_only_exception::interface_only_exception(const interface_only_exception & e) : 
   not_implemented_exception(e)
{
}

interface_only_exception::~interface_only_exception(get_app())
{
}
