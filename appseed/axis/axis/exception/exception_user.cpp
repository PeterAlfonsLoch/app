#include "framework.h"


user_exception::user_exception(sp(::axis::application) papp) :
   element(papp),
   ::call_stack(papp),
   ::exception::axis(papp),
   ::simple_exception(papp)
{
         printf(":user");

}


user_exception::~user_exception()
{

}


