#include "framework.h"


namespace core
{


   session::session(sp(::base::application) papp) :
      element(papp),
      ::thread(papp)
   {
   
   
   }

   
   session::~session()
   {
   
   
   }

   bool session::initialize1()
   {

      if(!::application::initialize1())
         return false;

      return true;

   }

   bool session::initialize()
   {

      if(!::application::initialize())
         return false;

      return true;

   }

   int32_t session::exit_instance()
   {
      
      ::application::exit_instance();

      return 0;

   }

   
   bool session::is_remote_session()
   {
      
      return false;

   }

   bool session::is_session()
   {

      return true;

   }



   

} // namespace core



