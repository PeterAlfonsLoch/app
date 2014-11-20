#include "framework.h"


namespace filehandler
{


   menu_library::menu_library(::aura::application * papp) :
      element(papp),
      ::aura::library(papp, 0, "app"),
      ::filehandler::library(papp)
   {

   }


   menu_library::~menu_library()
   {

   }

   
} // namespace filehandler





