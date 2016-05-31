//#include "framework.h"


user_exception::user_exception(::ace::application * papp) :
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


