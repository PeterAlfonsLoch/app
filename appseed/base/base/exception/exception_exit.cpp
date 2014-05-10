#include "framework.h"


exit_exception::exit_exception(sp(::base::application) papp, const char * pszMessage) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   ::simple_exception(papp, pszMessage)
{

}


exit_exception::exit_exception(const exit_exception & e) :
   element(e),
   ::call_stack(e),
   ::exception::base(e),
   ::simple_exception(e)
{

}


exit_exception::~exit_exception()
{

}



