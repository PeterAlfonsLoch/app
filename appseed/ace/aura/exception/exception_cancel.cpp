//#include "framework.h"


cancel_exception::cancel_exception(::aura::application * papp):
object(papp),
::call_stack(papp),
::exception::base(papp)
{
   
   debug_print(":cancel");

}


cancel_exception::cancel_exception(::aura::application * papp,const char * pszMessage):
object(papp),
::call_stack(papp),
::exception::base(papp)
{
   
   if(pszMessage == NULL)
   {
      
      debug_print(":cancel(NULL)");

   }
   else
   {
      
      debug_print(":cancel(\"%s\")",pszMessage);

   }

   m_strMessage = pszMessage;

}

cancel_exception::~cancel_exception()
{

}

bool cancel_exception::get_error_message(string & str,PUINT pnHelpContext)
{

   str = what();

   return true;

}



