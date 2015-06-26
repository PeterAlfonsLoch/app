//#include "framework.h"


simple_exception::simple_exception(::aura::application * papp):
object(papp),
::call_stack(papp),
::exception::base(papp)
{

   debug_print(":simple");

}


simple_exception::simple_exception(::aura::application * papp,const char * pszMessage):
object(papp),
::call_stack(papp),
::exception::base(papp)
{

   if(pszMessage == NULL)
   {

      debug_print(":simple(NULL)");

   }
   else
   {

      debug_print(":simple(\"%s\")",pszMessage);

   }

   m_strMessage = pszMessage;

}


simple_exception::~simple_exception()
{

}


bool simple_exception::get_error_message(string & str,PUINT pnHelpContext)
{

   str = what();

   return true;

}



