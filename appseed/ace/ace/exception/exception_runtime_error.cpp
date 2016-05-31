//#include "framework.h"



runtime_error::runtime_error(const string & strError,::ace::application * papp):
object(papp),
::call_stack(papp),
::exception::base(papp),
error_exception(papp,strError)
{

   if(strError.is_empty())
   {

      debug_print(":runtime_error(\"empty\")");

   }
   else
   {

      debug_print(":runtime_error(str=\"%s\")",strError.c_str());

   }


}

runtime_error::runtime_error(::ace::application * papp,const char * pszError):
object(papp),
::call_stack(papp),
::exception::base(papp),
error_exception(papp,pszError)
{

   if(pszError == NULL)
   {

      debug_print(":runtime_error(NULL)");

   }
   else
   {

      debug_print(":runtime_error(\"%s\")",pszError);

   }


}

runtime_error::~runtime_error()
{
}


