#include "framework.h"


namespace core
{



   system::system() :
      base_system(this)
   {

      idEmpty = "";

   }


   system::~system()
   {

   }



   void system::discard_to_factory(sp(element) pca)
   {
      UNREFERENCED_PARAMETER(pca);
   }

   sp(element) system::clone(sp(element) pca)
   {
      UNREFERENCED_PARAMETER(pca);
      return NULL;
   }



   bool system::is_system()
   {
      
      return true;

   }


   bool system::initialize_instance()
   {

      if(!::base_system::initialize_instance())
         return false;

      if(!::application::initialize_instance())
         return false;

      return true;

   }


} // namespace core



