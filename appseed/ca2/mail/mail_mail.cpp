#include "framework.h"


namespace mail
{


   mail::mail()
   {
   }

   mail::~mail()
   {
   }


   bool mail::initialize_instance()
   {

      if(!::ca::section::initialize_instance())
         return FALSE;


      return true;
   }

   int32_t mail::exit_instance()
   {
      try
      {
         ::ca::section::exit_instance();
      }
      catch(...)
      {
      }
      return 0;
   }


   void mail::update_pop3_mail_lists()
   {
   }


} // namespace mail
