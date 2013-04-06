#include "framework.h"


os_exception::os_exception(sp(::ca::application) papp) :
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   ::simple_exception(papp)
{

}


os_exception::os_exception(sp(::ca::application) papp, const char * pszMessage) :
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   ::simple_exception(papp, pszMessage)
{

}


os_exception::~os_exception()
{

}
