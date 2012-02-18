#include "StdAfx.h"


namespace cube
{

   library::library() :
      ::ca2::single_application_library < application > (),
      ::ca2::filehandler::menu_library()
   {
   }



   void library::get_app_list(stringa & stra)
   {

      
      stra.add("fontopus2");
      stra.add("default_file_handler");
      stra.add("bergedge");

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
      if(strExtension == "mid" || strExtension == "kar" || strExtension == "st3")
      {
         straApp.add_unique("mplite");
         straApp.add_unique("vmsp");
      }

   }

   ::ca::application * library::get_new_app(const char * pszAppId)
   {

      if(gen::str::equals_ci(pszAppId, "bergedge"))
      {
         return new bergedge::bergedge();
      }

      return ::ca2::single_application_library < application >::get_new_app(pszAppId);

   }


} // namespace cube



::ca2::library * get_new_library()
{
   return new ::cube::library();
}