#include "framework.h"


exit_exception::exit_exception(sp(::ca2::application) papp, const char * pszMessage) :
   ca2(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   ::simple_exception(papp, pszMessage)
{

}


exit_exception::exit_exception(const exit_exception & e) :
   ca2(e),
   ::call_stack(e),
   ::base_exception(e),
   ::simple_exception(e)
{

}


exit_exception::~exit_exception()
{

}



