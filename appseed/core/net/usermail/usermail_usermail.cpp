#include "framework.h"


namespace usermail
{


   usermail::usermail(application * papp) : 
      element(papp),
      ::departament(papp)
   {
   }

   usermail::~usermail()
   {
   }


   bool usermail::initialize_instance()
   {

      if(!::departament::initialize_instance())
         return FALSE;


      return true;
   }

   int32_t usermail::exit_instance()
   {
      try
      {
         ::departament::exit_instance();
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
