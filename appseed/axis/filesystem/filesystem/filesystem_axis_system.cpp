#include "framework.h"


namespace file
{


   namespace axis
   {


      system::system(::aura::application * papp) :
         ::object(papp),
         ::file::system(papp)
      {

      }


      system::~system()
      {

      }


      bool system::exists(const ::file::path & path, var * pvarQuery, ::aura::application * papp)
      {

         if (::str::begins(path, astr.strUifsProtocol))
         {
            
            return AppUser(papp).m_pifs->file_exists(path);
            
         }
         
         return ::file::system::exists(path, pvarQuery, papp);

      }


      var system::length(const ::file::path & strPath, ::aura::application * papp)
      {

         return length(strPath, NULL, papp);

      }


      var system::length(const ::file::path & path, var * pvarQuery, ::aura::application * papp)
      {

         if (::str::begins_ci(path, "http://") || ::str::begins_ci(path, "https://"))
         {

            property_set set(papp);

            return App(papp).http().length(path, set);

         }

         if (::str::begins_ci(path, "uifs://"))
         {

            return AppUser(papp).m_pifs->file_length(path);

         }

         return ::file::system::length(path, pvarQuery, papp);

      }



      ::file::file_sp system::get_file(var varFile,UINT nOpenFlags,cres * pfesp, ::aura::application * papp)
      {

         ::file::file_sp spfile;

         string strPath = varFile.get_file_path();

         if (::str::begins(strPath, astr.strIfsProtocol) || ::str::begins(strPath, astr.strUifsProtocol))
         {

            if (&AppUser(papp) == NULL)
            {

               spfile = NULL;

            }
            else
            {

               spfile = AppUser(papp).m_pifs->get_file(strPath, nOpenFlags, pfesp);

            }

         }


         return spfile;
   
      }


   } // namespace axis


} // namespace file






