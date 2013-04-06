#include "framework.h"


user_exception::user_exception(sp(::ca::application) papp) :
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   ::simple_exception(papp)
{
   
}


user_exception::~user_exception()
{

}


