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

      ::file::path application::locale_schema(const string & pszLocale,const string & pszStyle)
      {
         return m_pauraapp->m_paurasystem->m_spdir->locale_schema(get_app(), pszLocale, pszStyle);
      }

      ::file::patha application::locale_schema_matter(const string & pszLocale, const string & pszStyle, const char * pszRoot, const char * pszApp)
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

      //::file::path application::matter(const string & str, const string & str2, bool bDir, const string & pszRoot, const string & pszApp)
      //{
      //   return m_pauraapp->m_paurasystem->m_spdir->matter(get_app(), str, str2, bDir, pszRoot, pszApp);
      //}

      //::file::path application::matter(const string & str, const string & psz, bool bDir, const string & pszRoot, const string & pszApp)
      //{
      //   return m_pauraapp->m_paurasystem->m_spdir->matter(get_app(), str, psz, bDir, pszRoot, pszApp);
      //}

      //::file::path application::matter(const string & psz, const string & str, bool bDir, const string & pszRoot, const string & pszApp)
      //{
      //   return m_pauraapp->m_paurasystem->m_spdir->matter(get_app(), psz, str, bDir, pszRoot, pszApp);
      //}

      //::file::path application::matter(const string & lpcsz, const string & lpcsz2, bool bDir, const string & pszRoot, const string & pszApp)
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

      ::file::path application::usersystemappdata(const string & lpcszPrefix)
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

      ::file::path application::default_userappdata(const string & lpcszPrefix, const string & lpcszLogin)
      {
         return m_pauraapp->m_paurasystem->m_spdir->default_userappdata(get_app(), lpcszPrefix, lpcszLogin);
      }

      ::file::path application::default_userdata(const string & lpcszPrefix,const string & lpcszLogin)
      {
         return m_pauraapp->m_paurasystem->m_spdir->default_userdata(get_app(), lpcszPrefix, lpcszLogin);
      }

      ::file::path application::default_userfolder(const string & lpcszPrefix,const string & lpcszLogin)
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


      ::file::listing & application::ls(listing & listing)
      {

         return m_pauraapp->m_paurasystem->m_spdir.m_p->ls(m_pauraapp, listing);

      }


      bool application::has_subdir(const ::file::path & lpcsz)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->has_subdir(m_pauraapp, lpcsz);
      }


      bool application::is(const ::file::path & lpcsz)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->is(lpcsz, m_pauraapp);
      }

      bool application::is_inside(const ::file::path & lpcszDir,const ::file::path & lpcszPath)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->is_inside(lpcszDir, lpcszPath, m_pauraapp);
      }

      bool application::is_inside_time(const ::file::path & lpcsz)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->is_inside_time(lpcsz, m_pauraapp);
      }


      ::file::listing & application::root_ones(::file::listing & listing)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->root_ones(listing, m_pauraapp);
      }


      bool application::mk(const ::file::path & lpcsz)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->mk(lpcsz, m_pauraapp);
      }


      bool application::rm(const ::file::path & psz,bool bRecursive)
      {
         return m_pauraapp->m_paurasystem->m_spdir.m_p->rm(m_pauraapp, psz, bRecursive);
      }


      ::file::path application::pathfind(const string & pszEnv, const string & pszTopic, const string & pszMode)
      {
         return m_pauraapp->m_paurasystem->m_spdir->pathfind(pszEnv, pszTopic, pszMode, m_pauraapp);
      }


   } // namespace dir


} // namespace file


