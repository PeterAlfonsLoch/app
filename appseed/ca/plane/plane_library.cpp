#include "framework.h"

#ifndef _WIN32
extern "C"
#endif
::ca2::library * get_new_library();

namespace plane
{


   library::library() :
      ::ca2::single_application_library < application > ("app")//,
//      ::ca2::filehandler::menu_library()
      ,::ca2::library("app")
   {
   }



   void library::get_app_list(stringa & stra)
   {


      stra.add("fontopus");
      stra.add("netnode");

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


} // namespace plane




#ifndef _WIN32
extern "C"
#endif
::ca2::library * get_new_library()
{
   return new ::plane::library();
}
