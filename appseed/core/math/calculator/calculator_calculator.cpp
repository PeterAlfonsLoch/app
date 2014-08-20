#include "framework.h"


namespace calculator
{


   calculator::calculator(sp(::axis::application) papp) :
      element(papp),
      ::base::departament(papp)
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





