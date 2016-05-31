//#include "framework.h"


installing_exception::installing_exception(const installing_exception & e):
object(e.get_app()),
::call_stack(e.get_app()),
::exception::base(e.get_app()),
temporary_exception(e.get_app(),e.m_strTip)
{

   debug_print(":installing(copy)");

}


installing_exception::installing_exception(::ace::application * papp,const char * pszTip):
object(papp),
::call_stack(papp),
::exception::base(papp),
temporary_exception(papp,pszTip)
{
   
   if(pszTip == NULL)
   {

      debug_print(":installing(NULL)");

   }
   else
   {

      debug_print(":installing(\"%s\")",pszTip);

   }

}

installing_exception::~installing_exception()
{
}

