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

      m_spprompt = canew(prompt(this));

      return true;

   }

   


} // namespace userstack



