#include "framework.h"


not_supported_exception::not_supported_exception(const not_supported_exception & e) :
   element(e.get_app()),
   ::call_stack(e.get_app()),
   ::exception::base(e.get_app()),
   not_implemented(e),
   interface_only_exception(e)
{
      printf(":not_supported");
}

not_supported_exception::not_supported_exception(sp(::base::application) papp, const char * pszTip) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   not_implemented(papp, pszTip),
   interface_only_exception(papp, pszTip)
{
      if(pszTip == NULL)
      {
         printf(":not_supported_exception(NULL)");
      }
      else
      {
         printf(":not_supported_exception(\"%s\")",pszTip);
      }

}

not_supported_exception::~not_supported_exception()
{

}


