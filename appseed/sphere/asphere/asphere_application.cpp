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

      if(!::application::initialize1())
         return false;

      return true;

   }

   bool application::initialize()
   {

      if(!::application::initialize())
         return false;


      return true;

   }



} //namespace sphere





