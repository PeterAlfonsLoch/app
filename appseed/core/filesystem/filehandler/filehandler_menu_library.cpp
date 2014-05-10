#include "framework.h"


namespace filehandler
{


   menu_library::menu_library(sp(::base::application) papp) :
      element(papp),
      ::base_library(papp),
      ::core::library(papp, "app"),
      ::filehandler::library(papp)
   {
   }

   menu_library::~menu_library()
   {
   }

   
} // namespace filehandler




