//#include "framework.h"


io_exception::io_exception(::aura::application * papp):
object(papp),
::call_stack(papp),
::exception::base(papp),
simple_exception(papp)
{

   debug_print(":io_exception");

}


io_exception::io_exception(::aura::application * papp,const char * pszMessage):
object(papp),
::call_stack(papp),
::exception::base(papp),
simple_exception(papp,pszMessage)
{

   if(pszMessage == NULL)
   {

      debug_print(":io_exception(NULL)");

   }
   else
   {

      debug_print(":io_exception(\"%s\")",pszMessage);

   }

}


io_exception::~io_exception()
{

}
