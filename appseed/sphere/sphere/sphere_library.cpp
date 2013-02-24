#include "framework.h"


namespace sphere
{


   library::library() :
      ::ca::single_application_library < application > ("app"),
      ::filehandler::menu_library(),
      ::ca::library("app")
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


/*   ::ca::application * library::get_new_app(const char * pszAppId)
   {

      if(ca::str::equals_ci(pszAppId, "calculator"))
      {
         return new ::calculator::application();
      }
      else if(ca::str::equals_ci(pszAppId, "command"))
      {
         return new ::command::application();
      }
      else if(ca::str::equals_ci(pszAppId, "userstack"))
      {
         return new ::userstack::application();
      }
      else if(ca::str::equals_ci(pszAppId, "default_file_handler"))
      {
         return new ::filehandler::application();
      }

      return ::ca::single_application_library < application >::get_new_app(pszAppId);

   }*/


} // namespace sphere


#ifndef _WIN32
extern "C"
#endif
::ca::library * get_new_library()
{
   return new ::sphere::library();
}
