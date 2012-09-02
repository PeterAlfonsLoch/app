#include "framework.h"


os_exception::os_exception()
   : simple_exception()
{

}


os_exception::os_exception(const char * pszMessage)
   : simple_exception(pszMessage)
{

}


os_exception::~os_exception()
{

}
