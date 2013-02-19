#include "framework.h"


namespace ca2
{


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


         if(!::cube2::application::initialize())
            return false;


         return true;


      }



   } // namespace calculator


} // namespace ca2


