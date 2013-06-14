#include "framework.h"


invalid_argument_exception::invalid_argument_exception(sp(::ca2::application) papp) :
   ca2(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   simple_exception(papp)
{

}


invalid_argument_exception::invalid_argument_exception(sp(::ca2::application) papp, const char * pszMessage) :
   ca2(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   simple_exception(papp, pszMessage)
{

}


invalid_argument_exception::~invalid_argument_exception()
{

}
