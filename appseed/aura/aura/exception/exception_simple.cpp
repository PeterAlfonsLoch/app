//#include "framework.h"


simple_exception::simple_exception(::aura::application * papp):
object(papp),
::call_stack(papp),
::exception::base(papp)
{

   cat_exception(":simple");

}


simple_exception::simple_exception(::aura::application * papp,const char * pszMessage):
object(papp),
::call_stack(papp),
::exception::base(papp)
{

   if(pszMessage == NULL)
   {

      cat_exception(":simple(NULL)");

   }
   else
   {

      cat_exception(":simple(\"");
      cat_exception(pszMessage);
      cat_exception("\")");

   }

   cat_message(pszMessage);

}


simple_exception::~simple_exception()
{

}


bool simple_exception::get_error_message(string & str,PUINT pnHelpContext)
{

   str = what();

   return true;

}



