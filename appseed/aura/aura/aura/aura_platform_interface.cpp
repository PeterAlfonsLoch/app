#include "framework.h"


namespace aura
{


   platform_interface::platform_interface()
   {



   }


   platform_interface::~platform_interface()
   {

   }

   ::visual::cursor * platform_interface::get_cursor()
   {

      return NULL;

   }


   ::visual::cursor * platform_interface::get_default_cursor()
   {

      return NULL;

   }


   sp(::aura::application) platform_interface::start_application(const char * pszType,const char * pszAppId,sp(::create_context) pcreatecontext)
   {

      return NULL;

   }


} // namespace aura
















