#include "framework.h"


user_exception::user_exception(sp(::aura::application) papp) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   ::simple_exception(papp)
{
         printf(":user");

}


user_exception::~user_exception()
{

}


