#include "framework.h"


memory_exception::memory_exception(sp(::ca2::application) papp) :
   ca2(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   simple_exception(papp)
{

}


memory_exception::memory_exception(sp(::ca2::application) papp, const char * pszMessage) :
   ca2(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   simple_exception(papp, pszMessage) 
{

}


memory_exception::~memory_exception()
{

}


