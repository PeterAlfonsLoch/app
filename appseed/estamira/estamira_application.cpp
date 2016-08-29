#include "framework.h"


namespace estamira
{


   application::application()
   {

   }


   application::~application()
   {
   }


   bool application::initialize_instance()
   {

      if (!::hellomultiverse::application::initialize_instance())
         return false;

      if (!::multimedia::application::initialize_instance())
         return false;

      return true;

   }


   int32_t application::exit_instance()
   {

      return ::core::application::exit_instance();

   }



} // namespace estamira




