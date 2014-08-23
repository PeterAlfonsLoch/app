#include "framework.h"


os_exception::os_exception(sp(::aura::application) papp) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   ::simple_exception(papp)
{
      printf(":os_exception");
}


os_exception::os_exception(sp(::aura::application) papp, const char * pszMessage) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
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
