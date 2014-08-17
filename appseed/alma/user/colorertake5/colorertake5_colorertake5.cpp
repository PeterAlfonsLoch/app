#include "framework.h"


namespace colorertake5
{


   colorertake5::colorertake5(::base::application * papp) :
      element(papp),
      ::base::departament(papp)
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




