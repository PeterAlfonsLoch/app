//#include "framework.h"


io_exception::io_exception(::ace::application * papp):
object(papp),
::call_stack(papp),
::exception::base(papp),
simple_exception(papp)
{

   m_strException += ":io_exception";

}


io_exception::io_exception(::ace::application * papp,const char * pszMessage):
object(papp),
::call_stack(papp),
::exception::base(papp),
simple_exception(papp,pszMessage)
{

   if(pszMessage == NULL)
   {

      m_strException += ":io_exception(NULL)";

   }
   else
   {

      m_strException += ":io_exception(\"";
      m_strException += pszMessage;
      m_strException += "\")";

   }

}


io_exception::~io_exception()
{

}
