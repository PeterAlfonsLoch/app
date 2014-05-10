#include "framework.h"


invalid_argument_exception::invalid_argument_exception(sp(::base::application) papp) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   simple_exception(papp)
{

}


invalid_argument_exception::invalid_argument_exception(sp(::base::application) papp, const char * pszMessage) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   simple_exception(papp, pszMessage)
{

}


invalid_argument_exception::~invalid_argument_exception()
{

}
