//#include "framework.h"


operation_canceled_exception::operation_canceled_exception(::aura::application * papp):
object(papp),
::call_stack(papp),
::exception::base(papp),
::simple_exception(papp)
{

   debug_print(":operation_canceled");

}


operation_canceled_exception::operation_canceled_exception(::aura::application * papp,const char * pszMessage):
object(papp),
::call_stack(papp),
::exception::base(papp),
::simple_exception(papp,pszMessage)
{

   if(pszMessage == NULL)
   {

      debug_print(":operation_canceled(NULL)");

   }
   else
   {

      debug_print(":operation_canceled(\"%s\")",pszMessage);

   }

}


operation_canceled_exception::~operation_canceled_exception()
{

}
