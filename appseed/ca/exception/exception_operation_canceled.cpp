#include "framework.h"


operation_canceled_exception::operation_canceled_exception()
{

}


operation_canceled_exception::operation_canceled_exception(const char * pszMessage)
   : simple_exception(pszMessage)
{

}

operation_canceled_exception::~operation_canceled_exception()
{

}
