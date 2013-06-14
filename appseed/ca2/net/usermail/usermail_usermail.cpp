#include "framework.h"


namespace usermail
{


   usermail::usermail(::ca2::application * papp) : 
      ca2(papp),
      ::ca2::section(papp)
   {
   }

   usermail::~usermail()
   {
   }


   bool usermail::initialize_instance()
   {

      if(!::ca2::section::initialize_instance())
         return FALSE;


      return true;
   }

   int32_t usermail::exit_instance()
   {
      try
      {
         ::ca2::section::exit_instance();
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
