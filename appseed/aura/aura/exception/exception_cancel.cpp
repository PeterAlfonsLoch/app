#include "framework.h"


cancel_exception::cancel_exception(sp(::aura::application) papp):
element(papp),
::call_stack(papp),
::exception::base(papp)
{
   printf(":cancel");
}

cancel_exception::cancel_exception(sp(::aura::application) papp,const char * pszMessage):
element(papp),
::call_stack(papp),
::exception::base(papp)
{
   if(pszMessage == NULL)
   {
      printf(":cancel(NULL)");
   }
   else
   {
      printf(":cancel(\"%s\")",pszMessage);
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



