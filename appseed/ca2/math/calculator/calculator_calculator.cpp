#include "framework.h"


namespace calculator
{


   calculator::calculator(::ca2::application * papp) :
      element(papp),
      ::ca2::section(papp)
   {
   
   }


   calculator::~calculator()
   {

   }


   bool calculator::initialize()
   {

      return true;

   }


} // namespace calculator





