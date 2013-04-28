#include "framework.h"


namespace calculator
{


   calculator::calculator(::ca::application * papp) :
      ca(papp),
      ::ca::section(papp)
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





