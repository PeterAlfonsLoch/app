#include "framework.h"


resource_exception::resource_exception(::ca::application * papp) :
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   simple_exception(papp)
{

}


resource_exception::~resource_exception()
{

}

