#include "framework.h"


namespace calculator
{


   calculator::calculator(::aura::application * papp) :
      ::object(papp),
      ::aura::department(papp)
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





