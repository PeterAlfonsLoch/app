//#include "framework.h"


memory_exception::memory_exception():
object(::get_thread_app()),
::call_stack(get_app()),
::exception::base(get_app()),
simple_exception(get_app())
{

   debug_print(":memory(void)");

}


memory_exception::memory_exception(::aura::application * papp):
object(papp),
::call_stack(papp),
::exception::base(papp),
simple_exception(papp)
{

   debug_print(":memory");

}


memory_exception::memory_exception(::aura::application * papp,const char * pszMessage):
object(papp),
::call_stack(papp),
::exception::base(papp),
simple_exception(papp,pszMessage)
{

   if(pszMessage == NULL)
   {

      debug_print(":memory(NULL)");

   }
   else
   {

      debug_print(":memory(\"%s\")",pszMessage);

   }

}


memory_exception::~memory_exception()
{

}


