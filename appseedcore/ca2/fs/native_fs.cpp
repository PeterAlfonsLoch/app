#include "StdAfx.h"


namespace fs
{


   native::native(::ca::application * papp) :
      ::ca::ca(papp),
      ::ca::data(papp),
      ::fs::data(papp)
   {
   }


   // optional if ls_dir is implemented
   bool native::has_subdir(const char * pszPath)
   {
      return System.dir().has_subdir(pszPath);
   }

   bool native::ls(const char * pszDir, stringa * pstraPath, stringa * pstraTitle)
   {
      System.dir().ls(pszDir, pstraPath, pstraTitle);
      return true;
   }

   bool native::is_dir(const char * pszPath)
   {
      return System.dir().is(pszPath);
   }
   
   void native::root_ones(stringa & stra)
   {
      return System.dir().root_ones(stra);
   }

   void native::get_ascendants_path(const char * pszPath, stringa & stra)
   {
      return System.file().get_ascendants_path(pszPath, stra);
   }

   void native::get_ascendants_name(const char * lpcsz, stringa & straParam)
   {
      return System.file().get_ascendants_name(lpcsz, straParam);
   }

   string native::eat_end_level(const char * pszPath, int iCount)
   {
      string strPath(pszPath);
      while(iCount > 0)
      {
         strPath = filemanager::_shell::_017FilePathGetParent(strPath);
         iCount--;
      }
      return strPath;
/*      string strPath(pszPath);
      int iFind1 = -1;
      int iFind2 = -1;
      int iFind = -1;
      while(iCount > 0)
      {
         iFind1 = strPath.reverse_find('/', iFind);
         iFind2 = strPath.reverse_find('\\', iFind);
         iFind = max(iFind1, iFind2);
         iCount--;
         if(iCount <= 0)
            break;
         if(iFind < 0)
            return "";
      }
      return strPath.Left(iFind);*/
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

   ::ex1::filesp native::get_file(var varFile, UINT nOpenFlags, ::ex1::file_exception_sp * pexception)
   {
      ::ex1::filesp spfile(get_app());

      // ::ex1::file::mode_read | ::ex1::file::shareDenyNone | ::ex1::file::type_binary
      if(!spfile->open(varFile.get_string(), nOpenFlags, pexception))
      {
         throw new ex1::file_exception_sp(get_app());
      }

      return spfile;
   }

   bool native::file_exists(const char * pszPath)
   {
      return System.file().exists(pszPath);
   }


} // namespace fs