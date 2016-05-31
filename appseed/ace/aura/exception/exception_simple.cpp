//#include "framework.h"


simple_exception::simple_exception(::aura::application * papp):
object(papp),
::call_stack(papp),
::exception::base(papp)
{

   m_strException = ":simple";

}


simple_exception::simple_exception(::aura::application * papp,const char * pszMessage):
object(papp),
::call_stack(papp),
::exception::base(papp)
{

   if(pszMessage == NULL)
   {

      m_strException = ":simple(NULL)";

   }
   else
   {

      m_strException = ":simple(\"";
      m_strException += pszMessage;
      m_strException += "\")";

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



