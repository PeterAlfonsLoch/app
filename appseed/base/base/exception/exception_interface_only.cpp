#include "framework.h"


interface_only_exception::interface_only_exception(sp(::base::application) papp, const char * pszTip) : 
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   not_implemented(papp, pszTip)
{
      if(pszTip == NULL)
      {
         printf(":interface_only_exception(NULL)");
      }
      else
      {
         printf(":interface_only_exception(\"%s\")",pszTip);
      }
   }

interface_only_exception::interface_only_exception(const interface_only_exception & e) : 
   element(e),
   ::call_stack(e),
   ::exception::base(e),
   not_implemented(e)
{
}

interface_only_exception::~interface_only_exception()
{
}
