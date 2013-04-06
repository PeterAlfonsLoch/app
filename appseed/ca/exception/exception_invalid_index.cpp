#include "framework.h"


invalid_index_exception::invalid_index_exception(sp(::ca::application) papp) :
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   ::simple_exception(papp),
   invalid_argument_exception(papp)
{

}


invalid_index_exception::invalid_index_exception(sp(::ca::application) papp, const char * pszMessage) :
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   ::simple_exception(papp, pszMessage),
   invalid_argument_exception(papp, pszMessage)
{

}


invalid_index_exception::~invalid_index_exception()
{

}
