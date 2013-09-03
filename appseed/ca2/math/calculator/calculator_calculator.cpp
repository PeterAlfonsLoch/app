#include "framework.h"


namespace calculator
{


   calculator::calculator(application * papp) :
      element(papp),
      ::departament(papp)
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





