#include "framework.h"


namespace ca2
{


   namespace fs
   {


      fs::fs()
      {
      }

      fs::~fs()
      {
      }

      bool fs::initialize()
      {

         if(Application.is_system())
         {
            System.factory().creatable_small < ::fs::main_view > ();
            System.factory().creatable_small < ::fs::tree > ();
            System.factory().creatable_small < ::fs::list > ();
         }


         if(!::fs::fs::initialize())
            return false;


         return true;
      }
 


   } // namespace fs


} // namespace ca2


