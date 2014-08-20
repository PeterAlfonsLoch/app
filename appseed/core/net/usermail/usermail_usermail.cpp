#include "framework.h"


namespace usermail
{


   usermail::usermail(sp(::axis::application) papp) : 
      element(papp),
      ::axis::departament(papp)
   {
   }

   usermail::~usermail()
   {
   }


   bool usermail::initialize_instance()
   {

      if(!::axis::departament::initialize_instance())
         return FALSE;


      return true;
   }

   int32_t usermail::exit_instance()
   {
      try
      {
         ::axis::departament::exit_instance();
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
