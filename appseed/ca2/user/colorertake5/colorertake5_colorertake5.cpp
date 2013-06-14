#include "framework.h"


namespace colorertake5
{


   colorertake5::colorertake5(::ca2::application * papp) :
      ca2(papp),
      ::ca2::section(papp)
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




