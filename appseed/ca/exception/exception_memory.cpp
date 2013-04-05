#include "framework.h"


memory_exception::memory_exception(::ca::applicationsp papp) :
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   simple_exception(papp)
{

}


memory_exception::memory_exception(::ca::applicationsp papp, const char * pszMessage) :
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   simple_exception(papp, pszMessage) 
{

}


memory_exception::~memory_exception()
{

}


