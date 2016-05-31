//#include "framework.h"


exit_exception::exit_exception(::ace::application * papp, const char * pszMessage) :
   object(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   ::simple_exception(papp, pszMessage)
{

   m_iCheck = 0;

   if(pszMessage == NULL)
   {

      debug_print(":exit(NULL)");

   }
   else
   {

      debug_print(":exit(\"%s\")",pszMessage);

   }

   

}


exit_exception::exit_exception(const exit_exception & e) :
   object(e),
   ::call_stack(e),
   ::exception::base(e),
   ::simple_exception(e)
{
   m_iCheck = e.m_iCheck;
   debug_print(":exit(copy)");

}


exit_exception::~exit_exception()
{

}



