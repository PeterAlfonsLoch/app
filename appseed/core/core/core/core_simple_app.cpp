//#include "framework.h"


namespace core
{


   app::app() :
      ::aura::system(this, NULL),
      ::axis::system(this),
      ::base::system(this)
   {

   }

   app::~app()
   {

   }


} // namespace core






