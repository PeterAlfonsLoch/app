#include "framework.h"

#if defined(LINUX) || defined(APPLEOS)
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

      if(!::core::application::initialize1())
         return false;

      return true;

   }

   bool application::initialize()
   {

      if(!::core::application::initialize())
         return false;


      return true;

   }



} //namespace sphere





