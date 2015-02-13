#include "framework.h"


namespace zip
{

   class Util;

}


namespace file
{


   namespace dir
   {


      application::application(::aura::application * papp) :
         object(papp)
      {
      }

      application::~application()
      {
      }

      string application::locale_schema(const char * pszLocale, const char * pszStyle)
      {
         return m_pauraapp->m_paurasystem->m_spdir->locale_schema(get_app(), pszLocale, pszStyle);
      }

      stringa application::locale_schema_matter(const char * pszLocale, const char * pszStyle, const char * pszRoot, const char * pszApp)
      {
         return m_pauraapp->m_paurasystem->m_spdir->locale_schema_matter(get_app(), pszLocale, pszStyle, pszRoot, pszApp);
      }

      void application::matter_ls(const string & str, stringa & stra)
      {
         m_pauraapp->m_paurasystem->m_spdir->matter_ls(get_app(), str, stra);
      }

      void application::matter_ls_file(const string & str, stringa & stra)
      {
         m_pauraapp->m_paurasystem->m_spdir->matter_ls_file(get_app(), str, stra);
      }

      string application::matter(const string & str, bool bDir, const char * pszRoot, const char * pszApp)
      {
         return m_pauraapp->m_paurasystem->m_spdir->matter(get_app(), str, bDir, pszRoot, pszApp);
      }

      string application::matter(const string & str, const string & str2, bool bDir, const char * pszRoot, const char * pszApp)
      {
         return m_pauraapp->m_paurasystem->m_spdir->matter(get_app(), str, str2, bDir, pszRoot, pszApp);
      }

      string application::matter(const string & str, const char * psz, bool bDir, const char * pszRoot, const char * pszApp)
      {
         return m_pauraapp->m_paurasystem->m_spdir->matter(get_app(), str, psz, bDir, pszRoot, pszApp);
      }

      string application::matter(const char * psz, const string & str, bool bDir, const char * pszRoot, const char * pszApp)
      {
         return m_pauraapp->m_paurasystem->m_spdir->matter(get_app(), psz, str, bDir, pszRoot, pszApp);
      }

      string application::matter(const char * lpcsz, const char * lpcsz2, bool bDir, const char * pszRoot, const char * pszApp)
      {
         return m_pauraapp->m_paurasystem->m_spdir->matter(get_app(), lpcsz, lpcsz2, bDir, pszRoot, pszApp);
      }

      string application::matter_file(const char * lpcsz, const char * lpcsz2, bool bDir)
      {

         string strPath = m_pauraapp->m_paurasystem->m_spdir->matter(get_app(), lpcsz, lpcsz2, bDir);

         return strPath;

      }

      string application::matter(const stringa & stra, bool bDir, const char * pszRoot, const char * pszApp)
      {
         return m_pauraapp->m_paurasystem->m_spdir->matter(get_app(), stra, bDir, pszRoot, pszApp);
      }

      string application::usersystemappdata(const char * lpcszPrefix, const char * lpcsz, const char * lpcsz2)
      {
         return m_pauraapp->m_paurasystem->m_spdir->usersystemappdata(get_app(), lpcszPrefix, lpcsz, lpcsz2);
      }

      string application::userappdata(const char * lpcsz, const char * lpcsz2)
      {
         return m_pauraapp->m_paurasystem->m_spdir->userappdata(get_app(), lpcsz, lpcsz2);
      }

      string application::userdata(const char * lpcsz, const char * lpcsz2)
      {
         return m_pauraapp->m_paurasystem->m_spdir->userdata(get_app(), lpcsz, lpcsz2);
      }

      string application::userfolder(const char * lpcsz, const char * lpcsz2)
      {
         return m_pauraapp->m_paurasystem->m_spdir->userfolder(get_app(), lpcsz, lpcsz2);
      }

      string application::default_os_user_path_prefix()
      {
         return m_pauraapp->m_paurasystem->m_spdir->default_os_user_path_prefix(get_app());
      }

      string application::default_userappdata(const char * lpcszPrefix, const char * lpcszLogin , const char * pszRelativePath)
      {
         return m_pauraapp->m_paurasystem->m_spdir->default_userappdata(get_app(), lpcszPrefix, lpcszLogin, pszRelativePath);
      }

      string application::default_userdata(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
      {
         return m_pauraapp->m_paurasystem->m_spdir->default_userdata(get_app(), lpcszPrefix, lpcszLogin, pszRelativePath);
      }

      string application::default_userfolder(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
      {
         return m_pauraapp->m_paurasystem->m_spdir->default_userfolder(get_app(), lpcszPrefix, lpcszLogin, pszRelativePath);
      }

      string application::userquicklaunch(const char * pszRelativePath, const char * lpcsz2)
      {
         return m_pauraapp->m_paurasystem->m_spdir->userquicklaunch(get_app(), pszRelativePath, lpcsz2);
      }

      string application::userprograms(const char * pszRelativePath, const char * lpcsz2)
      {
         return m_pauraapp->m_paurasystem->m_spdir->userprograms(get_app(), pszRelativePath, lpcsz2);
      }


      bool application::ls_pattern(const char * lpcsz,const char * lpcszPattern,stringa * pstraPath,stringa * pstraTitle,bool_array * pbaIsDir,int64_array * piaSize)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->ls_pattern(m_pauraapp, lpcsz, lpcszPattern, pstraPath, pstraTitle, pbaIsDir, piaSize);
      }

      bool application::ls(const char * lpcsz,stringa * pstraPath,stringa * pstraTitle,bool_array * pbaIsDir,int64_array * piaSize)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->ls(m_pauraapp, lpcsz, pstraPath, pstraTitle, pbaIsDir, piaSize);
      }

      bool application::rls_pattern(const char * lpcsz, const char * lpcszPattern, stringa * pstraPath, stringa * pstraTitle, stringa * pstraRelative, bool_array * pbaIsDir, int64_array * piaSize)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->rls_pattern(m_pauraapp, lpcsz, lpcszPattern, pstraPath, pstraTitle, pstraRelative, pbaIsDir, piaSize);
      }

      bool application::rls(const char * lpcsz, stringa * pstraPath, stringa * pstraTitle, stringa * pstraRelative)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->rls(m_pauraapp, lpcsz, pstraPath, pstraTitle, pstraRelative);
      }

      bool application::rls_dir(const char * lpcsz,stringa * pstraPath,stringa * pstraTitle,stringa * pstraRelative)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->rls_dir(m_pauraapp, lpcsz, pstraPath, pstraTitle, pstraRelative);
      }

      bool application::ls_dir(const char * lpcsz,stringa * pstraPath,stringa * pstraTitle)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->ls_dir(m_pauraapp, lpcsz, pstraPath, pstraTitle);
      }

      bool application::has_subdir(const char * lpcsz)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->has_subdir(m_pauraapp, lpcsz);
      }

      bool application::ls_file(const char * lpcsz,stringa * pstraPath,stringa * pstraTitle)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->ls_file(m_pauraapp, lpcsz, pstraPath, pstraTitle);
      }

      bool application::is(const char * lpcsz)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->is(lpcsz, m_pauraapp);
      }

      bool application::is(const string & str)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->is(str, m_pauraapp);
      }

      bool application::is(const var & var)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->is(var, m_pauraapp);
      }

      bool application::is_inside(const char * lpcszDir, const char * lpcszPath)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->is_inside(lpcszDir, lpcszPath, m_pauraapp);
      }

      bool application::is_inside_time(const char * lpcsz)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->is_inside_time(lpcsz, m_pauraapp);
      }


      void application::root_ones(stringa & straPath, stringa & straTitle)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->root_ones(straPath, straTitle, m_pauraapp);
      }


      bool application::mk(const char * lpcsz)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->mk(lpcsz, m_pauraapp);
      }


      bool application::rm(const char * psz, bool bRecursive)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->rm(m_pauraapp, psz, bRecursive);
      }


      string application::pathfind(const char * pszEnv, const char * pszTopic, const char * pszMode)
      {
         return m_pauraapp->m_paurasystem->m_spdir->pathfind(pszEnv, pszTopic, pszMode, m_pauraapp);
      }


   } // namespace dir


} // namespace file


