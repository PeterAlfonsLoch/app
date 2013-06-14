#include "framework.h"


resource_exception::resource_exception(sp(::ca2::application) papp) :
   ca2(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   simple_exception(papp)
{

}


resource_exception::~resource_exception()
{

}

