#include "framework.h"



runtime_error::runtime_error(const string & strError, sp(::aura::application) papp):
element(papp),
::call_stack(papp),
::exception::base(papp),
error_exception(papp,strError)
{
   if(strError.is_empty())
   {
      printf(":runtime_error(\"empty\")");
   }
   else
   {
      printf(":runtime_error(str=\"%s\")",strError.c_str());
   }


}

runtime_error::runtime_error(sp(::aura::application) papp, const char * pszError) :
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
