#include "framework.h"


memory_exception::memory_exception(sp(::axis::application) papp) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   simple_exception(papp)
{
      printf(":memory");
}


memory_exception::memory_exception(sp(::axis::application) papp, const char * pszMessage) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   simple_exception(papp, pszMessage) 
{
      if(pszMessage == NULL)
      {
         printf(":memory(NULL)");
      }
      else
      {
         printf(":memory(\"%s\")",pszMessage);
      }

}


memory_exception::~memory_exception()
{

}


