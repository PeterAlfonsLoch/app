#include "framework.h"


namespace userfs
{


   userfs::userfs(::ca::application * papp) :
      ca(papp),
      ::ca::section(papp)
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


      if(!::ca::section::initialize())
         return false;


      return true;


   }


} // namespace ca





