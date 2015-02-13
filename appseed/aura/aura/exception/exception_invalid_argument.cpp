//#include "framework.h"


invalid_argument_exception::invalid_argument_exception(::aura::application * papp) :
   object(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   simple_exception(papp)
{
   printf(":invalid_argument_exception");

}


invalid_argument_exception::invalid_argument_exception(::aura::application * papp, const char * pszMessage) :
   object(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   simple_exception(papp, pszMessage)
{
      if(pszMessage == NULL)
      {
         printf(":invalid_argument_exception(NULL)");
      }
      else
      {
         printf(":invalid_argument_exception(\"%s\")",pszMessage);
      }
   }


invalid_argument_exception::~invalid_argument_exception()
{

}
