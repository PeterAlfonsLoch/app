//#include "framework.h" // previously aura/user/user.h
//#include "aura/user/colorertake5/colorertake5.h"

namespace colorertake5
{


   colorertake5::colorertake5(::aura::application * papp) :
      object(papp),
      ::aura::department(papp)
   {
      
   }


   colorertake5::~colorertake5()
   {

   }


   bool colorertake5::initialize()
   {

      return true;

   }


} //namespace colorertake5




