//#include "framework.h"


invalid_character::invalid_character(::aura::application * papp,const char * pszMessage):
object(papp),
::call_stack(papp),
::exception::base(papp),
simple_exception(papp,pszMessage)
{

   if(pszMessage == NULL)
   {

      debug_print(":invalid_character(NULL)");

   }
   else
   {

      debug_print(":invalid_character(\"%s\")",pszMessage);

   }

}


invalid_character::~invalid_character()
{

}

