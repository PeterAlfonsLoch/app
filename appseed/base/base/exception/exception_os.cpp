#include "framework.h"


os_exception::os_exception(sp(::base::application) papp) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   ::simple_exception(papp)
{

}


os_exception::os_exception(sp(::base::application) papp, const char * pszMessage) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   ::simple_exception(papp, pszMessage)
{

}


os_exception::~os_exception()
{

}
