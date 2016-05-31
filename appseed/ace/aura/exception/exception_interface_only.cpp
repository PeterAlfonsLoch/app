//#include "framework.h"


interface_only_exception::interface_only_exception(::aura::application * papp, const char * pszTip) : 
   object(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   not_implemented(papp, pszTip)
{

   if(pszTip == NULL)
   {

      debug_print(":interface_only_exception(NULL)");

   }
   else
   {

      debug_print(":interface_only_exception(\"%s\")",pszTip);

   }

}


interface_only_exception::interface_only_exception(const interface_only_exception & e) : 
   object(e),
   ::call_stack(e),
   ::exception::base(e),
   not_implemented(e)
{

}


interface_only_exception::~interface_only_exception()
{

}
