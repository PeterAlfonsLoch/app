#include "framework.h"


range_error::range_error(sp(::aura::application) papp, const char * pszError) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
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
