//#include "framework.h"


overflow_error::overflow_error(::ace::application * papp,const char * pszError):
object(papp),
::call_stack(papp),
::exception::base(papp),
error_exception(papp,pszError)
{

   if(pszError == NULL)
   {

      debug_print(":overflow_error(NULL)");

   }
   else
   {

      debug_print(":overflow_error(\"%s\")",pszError);

   }

}


overflow_error::~overflow_error()
{

}
