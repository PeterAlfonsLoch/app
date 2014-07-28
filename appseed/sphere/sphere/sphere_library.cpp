#include "framework.h"


namespace sphere
{


   library::library(sp(::base::application) papp) :
      element(papp),
      ::base::library(papp,0, "app"),
      ::base::single_application_library < application > (papp, "app"),
      ::filehandler::library(papp),
      ::filehandler::menu_library(papp)
   {
   }



   void library::get_app_list(stringa & stra)
   {

      stra.add("calculator");
      stra.add("command");
      stra.add("default_file_handler");
      stra.add("userstack");

   }

   void library::get_extension_list(stringa & stra)
   {

      stra.add("*");

   }

   void library::get_extension_app(stringa & straApp, const char * pszExtension)
   {

      string strExtension(pszExtension);

      strExtension.make_lower();

      if(strExtension == "*")
      {
         straApp.add_unique("default_file_handler");
      }
      if(strExtension == "mid" || strExtension == "karaoke" || strExtension == "st3")
      {
         straApp.add_unique("mplite");
         straApp.add_unique("vmsp");
      }

   }


/*   sp(::base::application) library::get_new_app(const char * pszAppId)
   {

      if(::str::equals_ci(pszAppId, "calculator"))
      {
         return new ::calculator::application();
      }
      else if(::str::equals_ci(pszAppId, "command"))
      {
         return new ::command::application();
      }
      else if(::str::equals_ci(pszAppId, "userstack"))
      {
         return new ::userstack::application();
      }
      else if(::str::equals_ci(pszAppId, "default_file_handler"))
      {
         return new ::filehandler::application();
      }

      return ::base::single_application_library < application >::get_new_app(pszAppId);

   }*/


} // namespace sphere


#ifndef _WIN32
extern "C"
#endif
::base::library * get_new_library(sp(::base::application) papp)
{

   return new ::sphere::library(papp);

}
