#include "framework.h"


namespace colorertake5
{


   colorertake5::colorertake5(::ca::application * papp) :
      ca(papp),
      ::ca::section(papp)
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




