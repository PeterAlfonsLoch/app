#include "framework.h"


namespace calculator
{


   calculator::calculator(base_application * papp) :
      element(papp),
      base_departament(papp)
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





