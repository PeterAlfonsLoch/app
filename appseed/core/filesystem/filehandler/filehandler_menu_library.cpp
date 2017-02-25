#include "framework.h"


namespace filehandler
{


   menu_library::menu_library(::aura::application * papp) :
      object(papp),
      ::aura::library(papp, 0, "app"),
      ::filehandler::library(papp)
   {

   }


   menu_library::~menu_library()
   {

   }

   
} // namespace filehandler





