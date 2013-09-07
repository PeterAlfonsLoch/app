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



} // namespace core



