#include "framework.h"


namespace core
{



   system::system() :
      base_system(this)
   {

      idEmpty = "";

      ::draw2d::dib::static_initialize();

   }


   system::~system()
   {

   }


   void system::construct()
   {

      ::application::construct();

      ::base_system::construct();

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

   bool system::process_initialize()
   {

      if(!::base_system::process_initialize())
         return false;

      return true;

   }

   bool system::initialize_instance()
   {

      if(!::base_system::initialize_instance())
         return false;

      //if(!::application::initialize_instance())
        // return false;

      return true;

   }


   int32_t system::exit_instance()
   {

      ::base_system::exit_instance();

      return 0;

   }


} // namespace core



