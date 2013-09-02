#include "framework.h"


namespace fs
{


   native::native(sp(::application) papp) :
      element(papp),
      ::data(papp),
      ::fs::data(papp)
   {
   }


   // optional if ls_dir is implemented
   bool native::has_subdir(const char * pszPath)
   {

      return System.dir().has_subdir(get_app(), pszPath);

   }


   bool native::ls(const char * pszDir, stringa * pstraPath, stringa * pstraTitle)
   {

      System.dir().ls(get_app(), pszDir, pstraPath, pstraTitle);

      return true;

   }


   bool native::is_dir(const char * pszPath)
   {

      return System.dir().is(pszPath, get_app());

   }


   void native::root_ones(stringa & stra)
   {

      return System.dir().root_ones(stra, get_app());

   }


   void native::get_ascendants_path(const char * pszPath, stringa & stra)
   {

      return System.file().get_ascendants_path(pszPath, stra);

   }


   void native::get_ascendants_name(const char * lpcsz, stringa & straParam)
   {

      return System.file().get_ascendants_name(lpcsz, straParam);

   }


   string native::eat_end_level(const char * pszPath, int32_t iCount)
   {

      string strPath(pszPath);

      while(iCount > 0)
      {

         strPath = System.dir().name(strPath);

         iCount--;

      }

      return strPath;

   }


   string native::file_name(const char * pszPath)
   {

      return System.file().name_(pszPath);

   }


   string native::dir_path(const char * psz1, const char * psz2)
   {

      return System.dir().path(psz1, psz2);

   }


   bool native::file_move(const char * pszDst, const char * pszSrc)
   {

      System.file().move(pszDst, pszSrc);

      return true;

   }


   ::ca2::filesp native::get_file(var varFile, UINT nOpenFlags)
   {

      ::ca2::filesp spfile(allocer());

      // ::file::file::mode_read | ::file::file::shareDenyNone | ::file::file::type_binary
      if(!spfile->open(varFile.get_string(), nOpenFlags))
      {

         throw new ::file::exception(get_app(), ::file::exception::none, 01, varFile.get_string());

      }

      return spfile;

   }


   bool native::file_exists(const char * pszPath)
   {

      return ::file_exists_dup(pszPath);

   }


} // namespace fs



