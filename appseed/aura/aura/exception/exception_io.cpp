//#include "framework.h"


io_exception::io_exception(::aura::application * papp):
object(papp),
::call_stack(papp),
::exception::base(papp),
simple_exception(papp)
{

   cat_exception(":io_exception");

}


io_exception::io_exception(::aura::application * papp,const char * pszMessage):
object(papp),
::call_stack(papp),
::exception::base(papp),
simple_exception(papp,pszMessage)
{

   if(pszMessage == NULL)
   {

      cat_exception(":io_exception(NULL)");

   }
   else
   {

      cat_exception(":io_exception(\"");
      cat_exception(pszMessage);
      cat_exception("\")");

   }

}


io_exception::~io_exception()
{

}
