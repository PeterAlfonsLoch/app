#include "framework.h"

namespace mail
{

   application::application()
   {
   }

   application::~application()
   {
   }


   bool application::initialize_instance()
   {

      if(!cube2::application::initialize_instance())
         return FALSE;


      return true;
   }

   BOOL application::exit_instance()
   {
      try
      {
         ::cube2::application::exit_instance();
      }
      catch(...)
      {
      }
      return 0;
   }


   void application::update_pop3_mail_lists()
   {
   }


} // namespace mail
