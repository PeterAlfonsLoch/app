//#include "framework.h"


todo::todo(::aura::application * papp, const char * pszTip) :
   object(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   not_implemented(papp, pszTip)
{

   debug_print(":todo");

}


todo::todo(const todo & e) :
   object(e),
   ::call_stack(e),
   ::exception::base(e),
   not_implemented(e)
{

   debug_print(":todo(copy)");

}


todo::~todo()
{

}



