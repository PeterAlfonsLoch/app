#include "framework.h"


range_error::range_error(sp(::axis::application) papp, const char * pszError) :
   element(papp),
   ::call_stack(papp),
   ::exception::axis(papp),
   error_exception(papp, pszError)
{
      if(pszError == NULL)
      {
         printf(":range_error(NULL)");
      }
      else
      {
         printf(":range_error(\"%s\")",pszError);
      }
}

range_error::~range_error()
{
}
