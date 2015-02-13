//#include "framework.h"


os_exception::os_exception(::aura::application * papp) :
   object(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   ::simple_exception(papp)
{
      printf(":os_exception");
}


os_exception::os_exception(::aura::application * papp, const char * pszMessage) :
   object(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   ::simple_exception(papp, pszMessage)
{
      if(pszMessage == NULL)
      {
         printf(":os_exception(NULL)");
      }
      else
      {
         printf(":os_exception(\"%s\")",pszMessage);
      }
}


os_exception::~os_exception()
{

}
