//#include "framework.h"


user_exception::user_exception(::aura::application * papp) :
   object(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   ::simple_exception(papp)
{

   debug_print(":user");

}


user_exception::~user_exception()
{

}


