#include "framework.h"


operation_canceled_exception::operation_canceled_exception(sp(::application) papp) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   ::simple_exception(papp)
{

}


operation_canceled_exception::operation_canceled_exception(sp(::application) papp, const char * pszMessage) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   ::simple_exception(papp, pszMessage)
{

}

operation_canceled_exception::~operation_canceled_exception()
{

}
