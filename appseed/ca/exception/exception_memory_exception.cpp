#include "framework.h"


memory_exception::memory_exception()
   : simple_exception()
{

}

memory_exception::memory_exception(const char * pszMessage) :
   simple_exception(pszMessage)
{

}

memory_exception::~memory_exception()
{

}
