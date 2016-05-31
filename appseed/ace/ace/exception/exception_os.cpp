//#include "framework.h"


os_exception::os_exception(::ace::application * papp):
object(papp),
::call_stack(papp),
::exception::base(papp),
::simple_exception(papp)
{

   debug_print(":os_exception");

}


os_exception::os_exception(::ace::application * papp,const char * pszMessage):
object(papp),
::call_stack(papp),
::exception::base(papp),
::simple_exception(papp,pszMessage)
{

   if(pszMessage == NULL)
   {

      debug_print(":os_exception(NULL)");

   }
   else
   {

      debug_print(":os_exception(\"%s\")",pszMessage);

   }

}


os_exception::~os_exception()
{

}
