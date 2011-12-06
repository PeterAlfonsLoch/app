#include "StdAfx.h"

namespace database
{

   application::application()
   {
   }

   application::~application()
   {
   }

   bool application::initialize()
   {
      
      
      if(is_system())
      {
         System.factory().creatable_large < ::database::result_set > ();
      }

      if(!::ca4::application::initialize())
         return false;

      return true;


   }

   ::database::server * application::get_data_server()
   {
      return NULL;
   }

   // should not call base class implementation because database::application is inside a n-furcation of user::application
   int application::exit_instance()
   {
      
      return 0;
   }

}