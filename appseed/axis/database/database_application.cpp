#include "framework.h"


namespace database
{


   database::database()
   {
   }

   database::~database()
   {
   }

   bool database::initialize()
   {
      
      
      if(m_pauraapp->is_system())
      {
         System.factory().creatable_large < ::database::result_set > ();
      }


      return true;


   }

   ::database::server * database::get_data_server()
   {
      return NULL;
   }

   // should not call axis class implementation because database::database is inside a n-furcation of user::database
   int32_t database::exit_instance()
   {

      return 0;

   }

}