#include "framework.h" // previously aura/user/user.h


namespace colorertake5
{


   colorertake5::colorertake5(::aura::application * papp) :
      element(papp),
      ::aura::departament(papp)
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




