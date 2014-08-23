#include "framework.h"


resource_exception::resource_exception(sp(::aura::application) papp) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   simple_exception(papp)
{
   printf(":resource_exception");
}


resource_exception::~resource_exception()
{

}

