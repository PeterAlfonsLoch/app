#include "framework.h"

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
/*         System.factory().creatable_small < main_view > ();
         System.factory().creatable_small < tree > ();
         System.factory().creatable_small < list > ();*/
      }

      if(!::user::application::initialize())
         return false;

      return true;
   }
 


} // namespace fs