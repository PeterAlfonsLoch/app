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

      ::file::path application::locale_schema(const char * pszLocale,const char * pszStyle)
      {
         return m_pauraapp->m_paurasystem->m_spdir->locale_schema(get_app(), pszLocale, pszStyle);
      }

      ::file::patha application::locale_schema_matter(const char * pszLocale, const char * pszStyle, const char * pszRoot, const char * pszApp)
      {
         return m_pauraapp->m_paurasystem->m_spdir->locale_schema_matter(get_app(), pszLocale, pszStyle, pszRoot, pszApp);
      }

      void application::matter_ls(const ::file::path & str,::file::patha & stra)
      {
         m_pauraapp->m_paurasystem->m_spdir->matter_ls(get_app(), str, stra);
      }

      void application::matter_ls_file(const ::file::path & str,::file::patha & stra)
      {
         m_pauraapp->m_paurasystem->m_spdir->matter_ls_file(get_app(), str, stra);
      }

      ::file::path application::matter(const ::file::path & path,bool bDir,const char * pszRoot,const char * pszApp)
      {
         return m_pauraapp->m_paurasystem->m_spdir->matter(get_app(), path, bDir, pszRoot, pszApp);
      }

      //::file::path application::matter(const string & str, const string & str2, bool bDir, const char * pszRoot, const char * pszApp)
      //{
      //   return m_pauraapp->m_paurasystem->m_spdir->matter(get_app(), str, str2, bDir, pszRoot, pszApp);
      //}

      //::file::path application::matter(const string & str, const char * psz, bool bDir, const char * pszRoot, const char * pszApp)
      //{
      //   return m_pauraapp->m_paurasystem->m_spdir->matter(get_app(), str, psz, bDir, pszRoot, pszApp);
      //}

      //::file::path application::matter(const char * psz, const string & str, bool bDir, const char * pszRoot, const char * pszApp)
      //{
      //   return m_pauraapp->m_paurasystem->m_spdir->matter(get_app(), psz, str, bDir, pszRoot, pszApp);
      //}

      //::file::path application::matter(const char * lpcsz, const char * lpcsz2, bool bDir, const char * pszRoot, const char * pszApp)
      //{
      //   return m_pauraapp->m_paurasystem->m_spdir->matter(get_app(), bDir, pszRoot, pszApp);
      //}

      ::file::path application::matter_file(const ::file::path & lpcsz,  bool bDir)
      {

         string strPath = m_pauraapp->m_paurasystem->m_spdir->matter(get_app(), lpcsz, bDir);

         return strPath;

      }

      ::file::path application::matter(const ::file::patha & stra,bool bDir,const char * pszRoot,const char * pszApp)
      {
         return m_pauraapp->m_paurasystem->m_spdir->matter(get_app(), stra, bDir, pszRoot, pszApp);
      }

      ::file::path application::usersystemappdata(const char * lpcszPrefix)
      {
         return m_pauraapp->m_paurasystem->m_spdir->usersystemappdata(get_app(), lpcszPrefix);
      }

      ::file::path application::userappdata()
      {
         return m_pauraapp->m_paurasystem->m_spdir->userappdata(get_app());
      }

      ::file::path application::userdata()
      {
         return m_pauraapp->m_paurasystem->m_spdir->userdata(get_app());
      }

      ::file::path application::userfolder()
      {
         return m_pauraapp->m_paurasystem->m_spdir->userfolder(get_app());
      }

      ::file::path application::default_os_user_path_prefix()
      {
         return m_pauraapp->m_paurasystem->m_spdir->default_os_user_path_prefix(get_app());
      }

      ::file::path application::default_userappdata(const char * lpcszPrefix, const char * lpcszLogin)
      {
         return m_pauraapp->m_paurasystem->m_spdir->default_userappdata(get_app(), lpcszPrefix, lpcszLogin);
      }

      ::file::path application::default_userdata(const char * lpcszPrefix,const char * lpcszLogin)
      {
         return m_pauraapp->m_paurasystem->m_spdir->default_userdata(get_app(), lpcszPrefix, lpcszLogin);
      }

      ::file::path application::default_userfolder(const char * lpcszPrefix,const char * lpcszLogin)
      {
         return m_pauraapp->m_paurasystem->m_spdir->default_userfolder(get_app(), lpcszPrefix, lpcszLogin);
      }

      ::file::path application::userquicklaunch()
      {
         return m_pauraapp->m_paurasystem->m_spdir->userquicklaunch(get_app());
      }

      ::file::path application::userprograms()
      {
         return m_pauraapp->m_paurasystem->m_spdir->userprograms(get_app());
      }


      bool application::ls_pattern(const char * lpcsz,const char * lpcszPattern,::file::patha * ppatha,::file::patha * ppathaName,bool_array * pbaIsDir,int64_array * piaSize)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->ls_pattern(m_pauraapp, lpcsz, lpcszPattern, ppatha, ppathaName, pbaIsDir, piaSize);
      }

      bool application::ls(const char * lpcsz,::file::patha * ppatha,::file::patha * ppathaName,bool_array * pbaIsDir,int64_array * piaSize)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->ls(m_pauraapp, lpcsz, ppatha, ppathaName, pbaIsDir, piaSize);
      }

      bool application::rls_pattern(const char * lpcsz, const char * lpcszPattern, ::file::patha * ppatha, ::file::patha * ppathaName, ::file::patha * ppathaRelative, bool_array * pbaIsDir, int64_array * piaSize)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->rls_pattern(m_pauraapp, lpcsz, lpcszPattern, ppatha, ppathaName, ppathaRelative, pbaIsDir, piaSize);
      }

      bool application::rls(const char * lpcsz, ::file::patha * ppatha, ::file::patha * ppathaName, ::file::patha * ppathaRelative)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->rls(m_pauraapp, lpcsz, ppatha, ppathaName, ppathaRelative);
      }

      bool application::rls_dir(const char * lpcsz,::file::patha * ppatha,::file::patha * ppathaName,::file::patha * ppathaRelative)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->rls_dir(m_pauraapp, lpcsz, ppatha, ppathaName, ppathaRelative);
      }

      bool application::ls_dir(const char * lpcsz,::file::patha * ppatha,::file::patha * ppathaName)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->ls_dir(m_pauraapp, lpcsz, ppatha, ppathaName);
      }

      bool application::has_subdir(const char * lpcsz)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->has_subdir(m_pauraapp, lpcsz);
      }

      bool application::ls_file(const char * lpcsz,::file::patha * ppatha,::file::patha * ppathaName)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->ls_file(m_pauraapp, lpcsz, ppatha, ppathaName);
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


      void application::root_ones(::file::patha & patha, stringa & straTitle)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->root_ones(patha, straTitle, m_pauraapp);
      }


      bool application::mk(const char * lpcsz)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->mk(lpcsz, m_pauraapp);
      }


      bool application::rm(const char * psz, bool bRecursive)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->rm(m_pauraapp, psz, bRecursive);
      }


      ::file::path application::pathfind(const char * pszEnv, const char * pszTopic, const char * pszMode)
      {
         return m_pauraapp->m_paurasystem->m_spdir->pathfind(pszEnv, pszTopic, pszMode, m_pauraapp);
      }


   } // namespace dir


} // namespace file


