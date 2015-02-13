//#include "framework.h"


void_implementation_exception::void_implementation_exception(::aura::application * papp, const char * pszTip) : 
   object(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   not_implemented(papp, pszTip)
{
      if(pszTip == NULL)
      {
         printf(":void_implementation(NULL)");
      }
      else
      {
         printf(":void_implementation(\"%s\")",pszTip);
      }

}

void_implementation_exception::void_implementation_exception(const void_implementation_exception & e) : 
   object(e),
   ::call_stack(e),
   ::exception::base(e),
   not_implemented(e)
{
         printf(":void_implementation(copy)");

}

void_implementation_exception::~void_implementation_exception()
{
}
