#include "framework.h"
#ifdef WINDOWSEX
#include <ShlObj.h>
bool  SHGetSpecialFolderPath(oswindow oswindow,string &str,int32_t csidl,bool fCreate);
#endif


namespace fs
{


   link::link(sp(base_application) papp):
      element(papp),
      ::data::data(papp),
#ifdef WINDOWSEX
      //::fs::native(papp),
#endif
      ::fs::data(papp)
   {
      
   }


   // optional if ls_dir is implemented
   bool link::has_subdir(const char * pszPath)
   {

      return false;

   }


   bool link::ls(const char * pszDir,stringa * pstraPath,stringa * pstraTitle,int64_array * piaSize)
   {

      string strDir(pszDir);

      if(strDir == m_strRoot)
      {

         for(int i = 0; i < m_straSource.get_size(); i++)
         {

            if(pstraPath != NULL)
            {

               pstraPath->add(m_straTarget[i]);

            }

            if(pstraTitle != NULL)
            {

               pstraTitle->add(System.file().title_(m_straSource[i]));

            }

            if(piaSize != NULL)
            {

               piaSize->add(0);

            }

         }

      }

      return true;

   }


   bool link::is_dir(const char * pszPath)
   {

      return true;

   }


   void link::root_ones(stringa & stra)
   {

      stra.add(m_strRoot);

   }


/*   

   void link::get_ascendants_path(const char * pszPath,stringa & stra)
   {

      return System.file().get_ascendants_path(pszPath,stra);

   }


   void link::get_ascendants_name(const char * lpcsz,stringa & straParam)
   {

      return System.file().get_ascendants_name(lpcsz,straParam);

   }


   string link::eat_end_level(const char * pszPath,int32_t iCount)
   {

      string strPath(pszPath);

      while(iCount > 0)
      {

         strPath = System.dir().name(strPath);

         iCount--;

      }

      return strPath;

   }


   string link::file_name(const char * pszPath)
   {

      return System.file().name_(pszPath);

   }


   string link::dir_path(const char * psz1,const char * psz2)
   {

      return System.dir().path(psz1,psz2);

   }


   bool link::file_move(const char * pszDst,const char * pszSrc)
   {

      System.file().move(pszDst,pszSrc);

      return true;

   }


   ::file::buffer_sp link::get_file(var varFile,UINT nOpenFlags)
   {

      ::file::binary_buffer_sp spfile(allocer());

      // ::file::mode_read | ::file::share_deny_none | ::file::type_binary
      if(!spfile->open(varFile.get_string(),nOpenFlags))
      {

         throw new ::file::exception(get_app(),::file::exception::none,01,varFile.get_string());

      }

      return spfile;

   }


   bool link::file_exists(const char * pszPath)
   {

      return ::file_exists_dup(pszPath) != FALSE;

   }

*/


   bool link::tree_show_subdir(const char * pszPath)
   {

      if(pszPath == m_strRoot)
      {

         return true;

      }
      else
      {

         return false;

      }

   }

   void link::fill_os_user()
   {

      stringa straLink;

      string strSourceFolder;

#ifdef WINDOWSEX

      m_strRoot = "Favoritos";
      
      SHGetSpecialFolderPath(
         NULL,
         strSourceFolder,
         CSIDL_PROFILE,
         FALSE);

      strSourceFolder = System.dir().path(strSourceFolder, "links");

#endif

      Application.dir().ls(strSourceFolder,&straLink);

      for(int i = 0; i < straLink.get_size(); i++)
      {

         string strTarget;

         string strSource = straLink[i];

         System.os().resolve_link(strTarget,strSource);

         m_straSource.add(strSource);

         m_straTarget.add(strTarget);

      }

   }



} // namespace fs



