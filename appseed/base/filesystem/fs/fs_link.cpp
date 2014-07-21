#include "framework.h"
#ifdef WINDOWSEX
#include <ShlObj.h>
bool  SHGetSpecialFolderPath(oswindow oswindow,string &str,int32_t csidl,bool fCreate);
#endif


namespace fs
{


   link::link(sp(::base::application) papp):
      element(papp),
      ::data::data(papp),
      ::fs::native(papp),
      ::fs::data(papp)
   {
      
   }


   // optional if ls_dir is implemented
   bool link::has_subdir(const char * pszPath)
   {

      string strDir(pszPath);

      strDir.trim();

      strDir.trim("/\\");

      if(strDir == m_strPath)
      {

         return true;

      }
      else
      {

         return native::has_subdir(pszPath);

      }

   }


   bool link::ls(const char * pszDir,stringa * pstraPath,stringa * pstraTitle,int64_array * piaSize)
   {

      string strDir(pszDir);

      strDir.trim();

      strDir.trim("/\\");

      if(strDir == m_strPath)
      {

         for(int i = 0; i < m_straPath.get_size(); i++)
         {

            if(pstraPath != NULL)
            {

               pstraPath->add(m_straPath[i]);

            }

            if(pstraTitle != NULL)
            {

               pstraTitle->add(System.file().title_(m_straPath[i]));

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

      string strDir(pszPath);

      strDir.trim();

      strDir.trim("/\\");

      if(strDir == m_strPath)
      {

         return true;

      }
      else
      {

         return native::is_dir(pszPath);

      }

   }


   void link::root_ones(stringa & straPath, stringa & straTitle)
   {

      straPath.add(m_strPath);
      straTitle.add(m_strTitle);

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

      string strDir(pszPath);

      strDir.trim();

      strDir.trim("/\\");

      if(strDir == m_strPath)
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

      m_strTitle = "Favoritos";
      
      SHGetSpecialFolderPath(
         NULL,
         strSourceFolder,
         CSIDL_PROFILE,
         FALSE);

      m_strPath = System.dir().path(strSourceFolder,"links");

#endif

      session().dir().ls(m_strPath,&m_straPath);


   }

   void link::fill_os_user_desktop()
   {

      stringa straLink;

      string strSourceFolder;

#ifdef WINDOWSEX

      m_strTitle = "Área de Trabalho";

      SHGetSpecialFolderPath(
         NULL,
         m_strPath,
         CSIDL_DESKTOP,
         FALSE);

#endif

      session().dir().ls(strSourceFolder,&m_straPath);


   }


} // namespace fs



