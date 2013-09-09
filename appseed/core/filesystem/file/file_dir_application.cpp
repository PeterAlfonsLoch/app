#include "framework.h"


namespace zip
{

   class Util;

}


namespace file
{


   namespace dir
   {


      application::application()
      {
      }

      application::~application()
      {
      }

      string application::locale_schema(const char * pszLocale, const char * pszStyle)
      {
         return System.dir().locale_schema(get_app(), pszLocale, pszStyle);
      }

      string application::locale_schema_matter(const char * pszLocale, const char * pszStyle)
      {
         return System.dir().locale_schema_matter(get_app(), pszLocale, pszStyle);
      }

      void application::matter_ls(const string & str, stringa & stra)
      {
         System.dir().matter_ls(get_app(), str, stra);
      }

      void application::matter_ls_file(const string & str, stringa & stra)
      {
         System.dir().matter_ls_file(get_app(), str, stra);
      }

      string application::matter(const string & str, bool bDir)
      {
         return System.dir().matter(get_app(), str, bDir);
      }

      string application::matter(const string & str, const string & str2, bool bDir)
      {
         return System.dir().matter(get_app(), str, str2, bDir);
      }

      string application::matter(const string & str, const char * psz, bool bDir)
      {
         return System.dir().matter(get_app(), str, psz, bDir);
      }

      string application::matter(const char * psz, const string & str, bool bDir)
      {
         return System.dir().matter(get_app(), psz, str, bDir);
      }

      string application::matter(const char * lpcsz, const char * lpcsz2, bool bDir)
      {
         return System.dir().matter(get_app(), lpcsz, lpcsz2, bDir);
      }

      string application::matter_file(const char * lpcsz, const char * lpcsz2, bool bDir)
      {

         string strPath = System.dir().matter(get_app(), lpcsz, lpcsz2, bDir);

         if(strPath.begins_ci("http://") || strPath.begins_ci("https://"))
         {
            string strFileExists = strPath;
            strFileExists.replace(":", "_");
            strFileExists = System.dir().appdata("cache/" + strFileExists + ".exists_question");
            strFileExists.replace("\\\\", "\\", 2);
            string strFile = strPath;
            strFile.replace(":", "_");
            strFile = System.dir().appdata("cache/" + strFile + ".local_copy");
            strFile.replace("\\\\", "\\", 2);
            if(Application.file().exists(strFileExists))
            {
               if(Application.file().as_string(strFileExists) == "yes")
                  return strFile;
               else
                  return "";
            }
            if(System.file().output(get_app(), strFile, &System.compress(), &::core::compress::null, strPath))
            {
               Application.file().put_contents(strFileExists, "yes");
               return strFile;
            }
            else
            {
               Application.file().put_contents(strFileExists, "no");
               return "";
            }
         }
         else
         {
            return strPath;
         }

      }

      string application::matter(const stringa & stra, bool bDir)
      {
         return System.dir().matter(get_app(), stra, bDir);
      }

      string application::usersystemappdata(const char * lpcszPrefix, const char * lpcsz, const char * lpcsz2)
      {
         return System.dir().usersystemappdata(get_app(), lpcszPrefix, lpcsz, lpcsz2);
      }

      string application::userappdata(const char * lpcsz, const char * lpcsz2)
      {
         return System.dir().userappdata(get_app(), lpcsz, lpcsz2);
      }

      string application::userdata(const char * lpcsz, const char * lpcsz2)
      {
         return System.dir().userdata(get_app(), lpcsz, lpcsz2);
      }

      string application::userfolder(const char * lpcsz, const char * lpcsz2)
      {
         return System.dir().userfolder(get_app(), lpcsz, lpcsz2);
      }

      string application::default_os_user_path_prefix()
      {
         return System.dir().default_os_user_path_prefix(get_app());
      }

      string application::default_userappdata(const char * lpcszPrefix, const char * lpcszLogin , const char * pszRelativePath)
      {
         return System.dir().default_userappdata(get_app(), lpcszPrefix, lpcszLogin, pszRelativePath);
      }

      string application::default_userdata(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
      {
         return System.dir().default_userdata(get_app(), lpcszPrefix, lpcszLogin, pszRelativePath);
      }

      string application::default_userfolder(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
      {
         return System.dir().default_userfolder(get_app(), lpcszPrefix, lpcszLogin, pszRelativePath);
      }

      string application::userquicklaunch(const char * pszRelativePath, const char * lpcsz2)
      {
         return System.dir().userquicklaunch(get_app(), pszRelativePath, lpcsz2);
      }

      string application::userprograms(const char * pszRelativePath, const char * lpcsz2)
      {
         return System.dir().userprograms(get_app(), pszRelativePath, lpcsz2);
      }


      void application::ls_pattern(const char * lpcsz, const char * lpcszPattern, stringa * pstraPath, stringa * pstraTitle, bool_array * pbaIsDir, array < int64_t, int64_t > * piaSize)
      {
         return m_pbaseapp->m_pplaneapp->m_psystem->m_spdir.m_p->ls_pattern(m_pbaseapp, lpcsz, lpcszPattern, pstraPath, pstraTitle, pbaIsDir, piaSize);
      }

      void application::ls(const char * lpcsz, stringa * pstraPath, stringa * pstraTitle, bool_array * pbaIsDir, array < int64_t, int64_t > * piaSize)
      {
         return m_pbaseapp->m_pplaneapp->m_psystem->m_spdir.m_p->ls(m_pbaseapp, lpcsz, pstraPath, pstraTitle, pbaIsDir, piaSize);
      }

      void application::rls_pattern(const char * lpcsz, const char * lpcszPattern, stringa * pstraPath, stringa * pstraTitle, stringa * pstraRelative, bool_array * pbaIsDir, array < int64_t, int64_t > * piaSize)
      {
         return m_pbaseapp->m_pplaneapp->m_psystem->m_spdir.m_p->rls_pattern(m_pbaseapp, lpcsz, lpcszPattern, pstraPath, pstraTitle, pstraRelative, pbaIsDir, piaSize);
      }

      void application::rls(const char * lpcsz, stringa * pstraPath, stringa * pstraTitle, stringa * pstraRelative)
      {
         return m_pbaseapp->m_pplaneapp->m_psystem->m_spdir.m_p->rls(m_pbaseapp, lpcsz, pstraPath, pstraTitle, pstraRelative);
      }

      void application::rls_dir(const char * lpcsz, stringa * pstraPath, stringa * pstraTitle, stringa * pstraRelative)
      {
         return m_pbaseapp->m_pplaneapp->m_psystem->m_spdir.m_p->rls_dir(m_pbaseapp, lpcsz, pstraPath, pstraTitle, pstraRelative);
      }

      void application::ls_dir(const char * lpcsz, stringa * pstraPath, stringa * pstraTitle)
      {
         return m_pbaseapp->m_pplaneapp->m_psystem->m_spdir.m_p->ls_dir(m_pbaseapp, lpcsz, pstraPath, pstraTitle);
      }

      bool application::has_subdir(const char * lpcsz)
      {
         return m_pbaseapp->m_pplaneapp->m_psystem->m_spdir.m_p->has_subdir(m_pbaseapp, lpcsz);
      }

      void application::ls_file(const char * lpcsz, stringa * pstraPath, stringa * pstraTitle)
      {
         return m_pbaseapp->m_pplaneapp->m_psystem->m_spdir.m_p->ls_file(m_pbaseapp, lpcsz, pstraPath, pstraTitle);
      }

      bool application::is(const char * lpcsz)
      {
         return m_pbaseapp->m_pplaneapp->m_psystem->m_spdir.m_p->is(lpcsz, m_pbaseapp);
      }

      bool application::is(const string & str)
      {
         return m_pbaseapp->m_pplaneapp->m_psystem->m_spdir.m_p->is(str, m_pbaseapp);
      }

      bool application::is(const var & var)
      {
         return m_pbaseapp->m_pplaneapp->m_psystem->m_spdir.m_p->is(var, m_pbaseapp);
      }

      bool application::is_inside(const char * lpcszDir, const char * lpcszPath)
      {
         return m_pbaseapp->m_pplaneapp->m_psystem->m_spdir.m_p->is_inside(lpcszDir, lpcszPath, m_pbaseapp);
      }

      bool application::is_inside_time(const char * lpcsz)
      {
         return m_pbaseapp->m_pplaneapp->m_psystem->m_spdir.m_p->is_inside_time(lpcsz, m_pbaseapp);
      }


      void application::root_ones(stringa & stra)
      {
         return m_pbaseapp->m_pplaneapp->m_psystem->m_spdir.m_p->root_ones(stra, m_pbaseapp);
      }


      bool application::mk(const char * lpcsz)
      {
         return m_pbaseapp->m_pplaneapp->m_psystem->m_spdir.m_p->mk(lpcsz, m_pbaseapp);
      }


      bool application::rm(const char * psz, bool bRecursive)
      {
         return m_pbaseapp->m_pplaneapp->m_psystem->m_spdir.m_p->rm(m_pbaseapp, psz, bRecursive);
      }


      string application::pathfind(const char * pszEnv, const char * pszTopic, const char * pszMode)
      {
         return System.dir().pathfind(pszEnv, pszTopic, pszMode, m_pbaseapp);
      }


   } // namespace dir


} // namespace file


