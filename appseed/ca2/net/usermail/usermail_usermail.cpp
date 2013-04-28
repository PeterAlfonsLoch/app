#include "framework.h"


namespace usermail
{


   usermail::usermail(::ca::application * papp) : 
      ca(papp),
      ::ca::section(papp)
   {
   }

   usermail::~usermail()
   {
   }


   bool usermail::initialize_instance()
   {

      if(!::ca::section::initialize_instance())
         return FALSE;


      return true;
   }

   int32_t usermail::exit_instance()
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


   void usermail::update_pop3_mail_lists()
   {
   }


} // namespace usermail
