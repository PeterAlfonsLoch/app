#include "framework.h"

#if defined(LINUX) || defined(MACOS)
#include <dlfcn.h>
#endif



namespace asphere
{


   application::application()
   {
   }

   application::~application()
   {
   }


   bool application::initialize1()
   {

      if(!::plane::application::initialize1())
         return false;

      return true;

   }

   bool application::initialize()
   {

      if(!::plane::application::initialize())
         return false;


      return true;

   }



} //namespace sphere





