//#include "framework.h"


not_implemented::not_implemented(const not_implemented & e):
object(e),
::call_stack(e),
::exception::base(e),
m_strTip(e.m_strTip)
{

   debug_print(":not_implemented(copy)");

}


not_implemented::not_implemented(::ace::application * papp,const char * pszTip):
object(papp),
::call_stack(papp),
::exception::base(papp),
m_strTip(pszTip)
{
   
   if(pszTip == NULL)
   {

      debug_print(":not_implemented(NULL)");

   }
   else
   {

      debug_print(":not_implemented(\"%s\")",pszTip);

   }

}


not_implemented::~not_implemented()
{

}





