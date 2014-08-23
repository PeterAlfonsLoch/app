#include "framework.h"


namespace colorertake5
{


   colorertake5::colorertake5(::axis::application * papp) :
      element(papp),
      ::axis::departament(papp)
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




