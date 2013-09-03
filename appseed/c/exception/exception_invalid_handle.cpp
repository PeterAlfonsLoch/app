#include "framework.h"


invalid_handle_exception::invalid_handle_exception(sp(base_application) papp) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   ::simple_exception(papp),
   os_exception(papp)
{

}


invalid_handle_exception::invalid_handle_exception(sp(base_application) papp, const char * pszMessage) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   ::simple_exception(papp),
   os_exception(papp, pszMessage)
{

}


invalid_handle_exception::~invalid_handle_exception()
{

}
