#include "framework.h"


namespace core
{



   system::system()
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







} // namespace core



