#include "framework.h"


namespace userfs
{


   userfs::userfs(::base::application * papp) :
      element(papp),
      ::base::departament(papp)
   {

   }

   userfs::~userfs()
   {

   }

   bool userfs::initialize()
   {

      if(Application.is_system())
      {
         System.factory().creatable_small < ::userfs::main_view > ();
         System.factory().creatable_small < ::userfs::tree > ();
         System.factory().creatable_small < ::userfs::list > ();
         System.factory().creatable_small < ::userfs::list_item > ();
      }


      if(!::base::departament::initialize())
         return false;


      return true;


   }


} // namespace core





