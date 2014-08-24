#include "framework.h"


namespace core
{


   simple_app::simple_app() :
      ::aura::system(this),
      ::axis::system(this),
      ::base::system(this)
   {

   }

   simple_app::~simple_app()
   {

   }


} // namespace core






