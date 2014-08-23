#include "framework.h"


overflow_error::overflow_error(sp(::aura::application) papp, const char * pszError) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   error_exception(papp, pszError)
{
      if(pszError == NULL)
      {
         printf(":overflow_error(NULL)");
      }
      else
      {
         printf(":overflow_error(\"%s\")",pszError);
      }
}

overflow_error::~overflow_error()
{
}
