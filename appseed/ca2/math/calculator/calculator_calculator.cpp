#include "framework.h"


namespace calculator
{


   calculator::calculator(::ca2::application * papp) :
      ca2(papp),
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





