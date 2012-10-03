#include "framework.h"


operation_canceled_exception::operation_canceled_exception(::ca::application * papp) :
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   ::simple_exception(papp)
{

}


operation_canceled_exception::operation_canceled_exception(::ca::application * papp, const char * pszMessage) :
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   ::simple_exception(papp, pszMessage)
{

}

operation_canceled_exception::~operation_canceled_exception()
{

}
