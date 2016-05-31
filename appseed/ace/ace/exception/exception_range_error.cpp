//#include "framework.h"


range_error::range_error(::ace::application * papp,const char * pszError):
object(papp),
::call_stack(papp),
::exception::base(papp),
error_exception(papp,pszError)
{

   if(pszError == NULL)
   {

      debug_print(":range_error(NULL)");

   }
   else
   {

      debug_print(":range_error(\"%s\")",pszError);

   }

}


range_error::~range_error()
{

}
