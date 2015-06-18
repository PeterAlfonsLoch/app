//#include "framework.h"


namespace calculator
{

   application::application()
   {
   }

   application::~application()
   {
   }

   bool application::initialize()
   {


      if(!::asphere::application::initialize())
         return false;


      return true;


   }



} // namespace calculator


