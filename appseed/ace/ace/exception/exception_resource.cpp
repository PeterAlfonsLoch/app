//#include "framework.h"


resource_exception::resource_exception(::ace::application * papp) :
   object(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   simple_exception(papp)
{

   debug_print(":resource_exception");

}


resource_exception::~resource_exception()
{

}

