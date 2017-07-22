#include "framework.h"


namespace estamira
{


   application::application()
   {

   }


   application::~application()
   {
   }


   bool application::initialize_application()
   {

//      if (!::hellomultiverse::application::initialize_application())
//         return false;

      if (!::multimedia::application::initialize_application())
         return false;

      return true;

   }


   int32_t application::exit_application()
   {

      return ::multimedia::application::exit_application();

   }



} // namespace estamira




