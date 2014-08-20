#include "framework.h"


namespace filehandler
{


   menu_library::menu_library(sp(::axis::application) papp) :
      element(papp),
      ::base::library(papp, 0, "app"),
      ::filehandler::library(papp)
   {

   }


   menu_library::~menu_library()
   {

   }

   
} // namespace filehandler





