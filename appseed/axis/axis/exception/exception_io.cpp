#include "framework.h"


io_exception::io_exception(sp(::axis::application) papp) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   simple_exception(papp)
{
      printf(":io_exception");

}


io_exception::io_exception(sp(::axis::application) papp, const char * pszMessage) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   simple_exception(papp, pszMessage)
{
      if(pszMessage == NULL)
      {
         printf(":io_exception(NULL)");
      }
      else
      {
         printf(":io_exception(\"%s\")",pszMessage);
      }

}


io_exception::~io_exception()
{

}
