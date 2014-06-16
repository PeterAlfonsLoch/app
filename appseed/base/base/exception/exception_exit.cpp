#include "framework.h"


exit_exception::exit_exception(sp(::base::application) papp, const char * pszMessage) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   ::simple_exception(papp, pszMessage)
{
      if(pszMessage == NULL)
         printf(":exit(NULL)");
      else
         printf(":exit(\"%s\")", pszMessage);
}


exit_exception::exit_exception(const exit_exception & e) :
   element(e),
   ::call_stack(e),
   ::exception::base(e),
   ::simple_exception(e)
{
      printf(":exit(copy)");
}


exit_exception::~exit_exception()
{

}



