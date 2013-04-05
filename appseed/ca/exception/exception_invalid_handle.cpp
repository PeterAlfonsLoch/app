#include "framework.h"


invalid_handle_exception::invalid_handle_exception(::ca::applicationsp papp) :
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   ::simple_exception(papp),
   os_exception(papp)
{

}


invalid_handle_exception::invalid_handle_exception(::ca::applicationsp papp, const char * pszMessage) :
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   ::simple_exception(papp),
   os_exception(papp, pszMessage)
{

}


invalid_handle_exception::~invalid_handle_exception()
{

}
