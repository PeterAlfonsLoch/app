#include "framework.h"


io_exception::io_exception(::ca::applicationsp papp) :
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   simple_exception(papp)
{

}


io_exception::io_exception(::ca::applicationsp papp, const char * pszMessage) :
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   simple_exception(papp, pszMessage)
{

}


io_exception::~io_exception()
{

}
