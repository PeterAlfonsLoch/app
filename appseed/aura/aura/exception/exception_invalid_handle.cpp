#include "framework.h"


invalid_handle_exception::invalid_handle_exception(sp(::aura::application) papp) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   ::simple_exception(papp),
   os_exception(papp)
{
         printf(":invalid_handle_exception");
}


invalid_handle_exception::invalid_handle_exception(sp(::aura::application) papp, const char * pszMessage) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   ::simple_exception(papp),
   os_exception(papp, pszMessage)
{
      if(pszMessage == NULL)
      {
         printf(":invalid_handle_exception(NULL)");
      }
      else
      {
         printf(":invalid_handle_exception(\"%s\")",pszMessage);
      }

}


invalid_handle_exception::~invalid_handle_exception()
{

}
