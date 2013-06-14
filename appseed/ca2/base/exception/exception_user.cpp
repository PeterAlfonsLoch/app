#include "framework.h"


user_exception::user_exception(sp(::ca2::application) papp) :
   ca2(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   ::simple_exception(papp)
{
   
}


user_exception::~user_exception()
{

}


