#include "framework.h"


runtime_error::runtime_error(sp(::axis::application) papp, const char * pszError) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   error_exception(papp, pszError)
{
      if(pszError == NULL)
      {
         printf(":runtime_error(NULL)");
      }
      else
      {
         printf(":runtime_error(\"%s\")",pszError);
      }


}

runtime_error::~runtime_error()
{
}
