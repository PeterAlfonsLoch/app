#include "framework.h"


invalid_handle_exception::invalid_handle_exception(sp(::ca2::application) papp) :
   ca2(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   ::simple_exception(papp),
   os_exception(papp)
{

}


invalid_handle_exception::invalid_handle_exception(sp(::ca2::application) papp, const char * pszMessage) :
   ca2(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   ::simple_exception(papp),
   os_exception(papp, pszMessage)
{

}


invalid_handle_exception::~invalid_handle_exception()
{

}
