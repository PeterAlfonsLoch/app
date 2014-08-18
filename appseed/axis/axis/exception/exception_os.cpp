#include "framework.h"


os_exception::os_exception(sp(::axis::application) papp) :
   element(papp),
   ::call_stack(papp),
   ::exception::axis(papp),
   ::simple_exception(papp)
{
      printf(":os_exception");
}


os_exception::os_exception(sp(::axis::application) papp, const char * pszMessage) :
   element(papp),
   ::call_stack(papp),
   ::exception::axis(papp),
   ::simple_exception(papp, pszMessage)
{
      if(pszMessage == NULL)
      {
         printf(":os_exception(NULL)");
      }
      else
      {
         printf(":os_exception(\"%s\")",pszMessage);
      }
}


os_exception::~os_exception()
{

}
