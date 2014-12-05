#include "framework.h"


namespace calculator
{


   calculator::calculator(::aura::application * papp) :
      element(papp),
      ::aura::departament(papp)
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





