//#include "framework.h"


invalid_handle_exception::invalid_handle_exception(::aura::application * papp) :
   object(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   ::simple_exception(papp),
   os_exception(papp)
{

   debug_print(":invalid_handle_exception");

}


invalid_handle_exception::invalid_handle_exception(::aura::application * papp, const char * pszMessage) :
   object(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   ::simple_exception(papp),
   os_exception(papp, pszMessage)
{

   if(pszMessage == NULL)
   {

      debug_print(":invalid_handle_exception(NULL)");

   }
   else
   {

      debug_print(":invalid_handle_exception(\"%s\")",pszMessage);

   }

}


invalid_handle_exception::~invalid_handle_exception()
{

}
