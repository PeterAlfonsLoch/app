//#include "framework.h"


invalid_index_exception::invalid_index_exception(::aura::application * papp):
object(papp),
::call_stack(papp),
::exception::base(papp),
::simple_exception(papp),
invalid_argument_exception(papp)
{

   debug_print(":invalid_index_exception");

}


invalid_index_exception::invalid_index_exception(::aura::application * papp,const char * pszMessage):
object(papp),
::call_stack(papp),
::exception::base(papp),
::simple_exception(papp,pszMessage),
invalid_argument_exception(papp,pszMessage)
{

   if(pszMessage == NULL)
   {

      debug_print(":invalid_index_exception(NULL)");

   }
   else
   {

      debug_print(":invalid_index_exception(\"%s\")",pszMessage);

   }

}


invalid_index_exception::~invalid_index_exception()
{

}
