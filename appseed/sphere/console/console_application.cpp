#include "framework.h"


namespace console
{


   application::application()
   {
   }

   application::~application()
   {
   }


   bool application::initialize_instance()
   {


      if(!::asphere::application::initialize_instance())
         return false;


      m_spprompt = canew(prompt(this));

      return true;

   }

   


} // namespace userstack



