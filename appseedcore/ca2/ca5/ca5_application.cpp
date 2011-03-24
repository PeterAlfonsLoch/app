#include "StdAfx.h"


namespace ca5
{

   application::application()
   {
      //m_strMainStringTable = "main_string_table.xml";
   }

   application::~application()
   {
   }

   bool application::initialize()
   {
      
      if(!::userbase::application::initialize())
         return false;


      if(!is_system())
      {
         defer_initialize_user_presence();
      }

      return true;

   }

   void application::defer_initialize_user_presence()
   {

      if(user::presence_central_container::is_initialized())
         return;

      // it may not be initialized, due
      // licensing for example
      if(user::presence_central_container::initialize_central_container(this))
      {
         TRACE("user presence enabled");
      }
      else
      {
         TRACE("user presence not enabled");
      }

   }


} //namespace ca5