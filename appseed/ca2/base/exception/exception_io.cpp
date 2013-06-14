#include "framework.h"


io_exception::io_exception(sp(::ca2::application) papp) :
   ca2(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   simple_exception(papp)
{

}


io_exception::io_exception(sp(::ca2::application) papp, const char * pszMessage) :
   ca2(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   simple_exception(papp, pszMessage)
{

}


io_exception::~io_exception()
{

}
