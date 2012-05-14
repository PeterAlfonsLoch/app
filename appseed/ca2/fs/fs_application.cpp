#include "framework.h"


namespace ca2
{


   namespace fs
   {


      application::application()
      {
      }

      application::~application(void)
      {
      }

      bool application::initialize()
      {

         if(is_system())
         {
            System.factory().creatable_small < ::fs::main_view > ();
            System.factory().creatable_small < ::fs::tree > ();
            System.factory().creatable_small < ::fs::list > ();
         }


         if(!::userex::application::initialize())
            return false;


         return true;
      }
 


   } // namespace fs


} // namespace ca2


