#include "framework.h"


namespace core
{


   session::session()
   {
   
   
   }

   
   session::~session()
   {
   
   
   }

   bool session::initialize1()
   {

      if(!::base::session::initialize1())
         return false;

      if(!::application::initialize1())
         return false;

      return true;

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



