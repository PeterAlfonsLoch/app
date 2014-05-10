#include "framework.h"


io_exception::io_exception(sp(::base::application) papp) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   simple_exception(papp)
{

}


io_exception::io_exception(sp(::base::application) papp, const char * pszMessage) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   simple_exception(papp, pszMessage)
{

}


io_exception::~io_exception()
{

}
