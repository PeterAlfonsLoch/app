#include "StdAfx.h"


namespace ca
{


   namespace dir
   {


      system::system(::ca::application * papp) :
         ca(papp)
      {
         m_pziputil = new zip::Util;
         m_isdirmap.m_dwTimeOut = 15000;
      }

      system::~system()
      {
         if(m_pziputil != NULL)
         {
            delete m_pziputil;
         }
      }

      bool system::path::is_equal(const char * lpcsz1, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz1);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      string system::path(const char * lpcszFolder, const char * lpcszRelative, const char * psz2)
      {
         UNREFERENCED_PARAMETER(lpcszFolder);
         UNREFERENCED_PARAMETER(lpcszRelative);
         UNREFERENCED_PARAMETER(psz2);
         throw interface_only_exception("this is an interface");
      }

      string system::relpath(const char * lpcszSource, const char * lpcszRelative, const char * psz2)
      {
         UNREFERENCED_PARAMETER(lpcszSource);
         UNREFERENCED_PARAMETER(lpcszRelative);
         UNREFERENCED_PARAMETER(psz2);
         throw interface_only_exception("this is an interface");
      }

      void system::root_ones(stringa & stra, ::ca::application * papp)
      {
         UNREFERENCED_PARAMETER(stra);
         throw interface_only_exception("this is an interface");
      }

      void system::rls_pattern(::ca::application * papp, const char * lpcsz, const char * pszPattern, stringa * pstraPath, stringa * pstraTitle, stringa * pstraRelative, base_array < bool, bool > * pbaIsDir, base_array < __int64, __int64 > * piaSize)
      {
         UNREFERENCED_PARAMETER(pstraRelative);
         UNREFERENCED_PARAMETER(pszPattern);
         if(gen::str::ends_ci(lpcsz, ".zip") || gen::str::find_ci(".zip:", lpcsz) >= 0)
         {
            throw "should implement recursive zip";
            m_pziputil->ls(papp, lpcsz, false, pstraPath, pstraTitle, NULL, pbaIsDir, piaSize);
            return;
         }
         throw not_implemented_exception("is really a directory or compressed directory/file??");
      
      }


      void system::ls_pattern(::ca::application * papp, const char * lpcsz, const char * pszPattern, stringa * pstraPath, stringa * pstraTitle, base_array < bool, bool > * pbaIsDir, base_array < __int64, __int64 > * piaSize)
      {
         UNREFERENCED_PARAMETER(pszPattern);
         if(gen::str::ends_ci(lpcsz, ".zip") || gen::str::find_ci(".zip:", lpcsz) >= 0)
         {
            m_pziputil->ls(papp, lpcsz, false, pstraPath, pstraTitle, NULL, pbaIsDir, piaSize);
            return;
         }
         throw not_implemented_exception("is really a directory or compressed directory/file??");
      
      }

      void system::ls(::ca::application * papp, const char * lpcsz, stringa * pstraPath, stringa * pstraTitle, base_array < bool, bool > * pbaIsDir, base_array < __int64, __int64 > * piaSize)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(pstraPath);
         UNREFERENCED_PARAMETER(pstraTitle);
         UNREFERENCED_PARAMETER(pbaIsDir);
         UNREFERENCED_PARAMETER(piaSize);
         throw interface_only_exception("this is an interface");
      }

      void system::rls(::ca::application * papp, const char * lpcsz, stringa * pstraPath, stringa * pstraTitle, stringa * pstraRelative)
      {
         if(gen::str::ends_ci(lpcsz, ".zip") || gen::str::find_ci(".zip:", lpcsz) >= 0)
         {
            m_pziputil->ls(papp, lpcsz, false, pstraPath, pstraTitle, pstraRelative);
            return;
         }
         else
         {
            return;
         }
      }

      void system::rls_dir(::ca::application * papp, const char * lpcsz, stringa * pstraPath, stringa * pstraTitle, stringa * pstraRelative)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(pstraPath);
         UNREFERENCED_PARAMETER(pstraTitle);
         UNREFERENCED_PARAMETER(pstraRelative);
         throw interface_only_exception("this is an interface");
      }

      void system::ls_dir(::ca::application * papp, const char * lpcsz, stringa * pstraPath, stringa * pstraTitle)
      {
         if(gen::str::ends_ci(lpcsz, ".zip") || gen::str::find_ci(".zip:", lpcsz) >= 0)
         {
            m_pziputil->ls_dir(papp, lpcsz, pstraPath, pstraTitle);
            return;
         }
         else
         {
            return;
         }
      }

      bool system::has_subdir(::ca::application * papp, const char * lpcsz)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         throw interface_only_exception("this is an interface");
      }

      void system::ls_file(::ca::application * papp, const char * lpcsz, stringa * pstraPath, stringa * pstraTitle)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(pstraPath);
         UNREFERENCED_PARAMETER(pstraTitle);
         throw interface_only_exception("this is an interface");
      }

      bool system::is(const char * lpcszPath, ::ca::application * papp)
      {
         if(gen::str::ends_ci(lpcszPath, ".zip"))
            return true;
         if(gen::str::find_ci(".zip:", lpcszPath) >= 0)
         {
            bool bHasSubFolder;
            if(m_isdirmap.lookup(lpcszPath, bHasSubFolder))
               return bHasSubFolder;
            bHasSubFolder = m_pziputil->HasSubFolder(papp, lpcszPath);
            m_isdirmap.set(lpcszPath, bHasSubFolder);
            return bHasSubFolder;
         }
         return false;
      }


      bool system::is_dir_map::lookup(const char * pszPath, bool &bIsDir)
      {
         single_lock sl(&m_mutex);
         is_dir isdir;
         if(Lookup(pszPath, isdir))
         {
            if(::GetTickCount() > isdir.m_dwLastCheck + m_dwTimeOut)
            {
               return false;
            }
            bIsDir = isdir.m_bIsDir;
            return true;
         }
         return false;
      }
      
      void system::is_dir_map::set(const char * pszPath, bool bIsDir)
      {
         is_dir isdir;
         isdir.m_bIsDir = bIsDir;
         isdir.m_dwLastCheck = ::GetTickCount();
         set_at(pszPath, isdir);
      }


      string system::votagus(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      string system::time(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      string system::stage(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      string system::stageapp(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      string system::netseed(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      string system::ca2(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      string system::module(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      string system::ca2module(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      void system::time_square(string &str)
      {
         UNREFERENCED_PARAMETER(str);
         throw interface_only_exception("this is an interface");
      }

      string system::time_log(const char * pszId)
      {
         UNREFERENCED_PARAMETER(pszId);
         throw interface_only_exception("this is an interface");
      }

      bool system::mk(const char * lpcsz, ::ca::application * papp)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         throw interface_only_exception("this is an interface");
      }

      bool system::rm(::ca::application * papp, const char * psz, bool bRecursive)
      {
         UNREFERENCED_PARAMETER(psz);
         UNREFERENCED_PARAMETER(bRecursive);
         throw interface_only_exception("this is an interface");
      }

      string system::name(const char * path1)
      {
         UNREFERENCED_PARAMETER(path1);
         throw interface_only_exception("this is an interface");
      }

      string system::locale_style(::ca::application * papp, const char * pszLocale, const char * pszStyle)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(pszLocale);
         UNREFERENCED_PARAMETER(pszStyle);
         throw interface_only_exception("this is an interface");
      }

      string system::locale_style_matter(::ca::application * papp, const char * pszLocale, const char * pszStyle)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(pszLocale);
         UNREFERENCED_PARAMETER(pszStyle);
         throw interface_only_exception("this is an interface");
      }

      string system::matter(::ca::application * papp, const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      class system::path & system::path()
      {
         throw interface_only_exception("this is an interface");
      }

      bool system::initialize()
      {
         throw interface_only_exception("this is an interface");
      }

      string system::trash_that_is_not_trash(const char * lpcsz)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         throw interface_only_exception("this is an interface");
      }

      string system::appdata(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      string system::usersystemappdata(::ca::application * papp, const char * lpcszPrefix, const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcszPrefix);
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      string system::userappdata(::ca::application * papp, const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      string system::userdata(::ca::application * papp, const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      string system::userfolder(::ca::application * papp, const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      string system::default_os_user_path_prefix(::ca::application * papp)
      {
         UNREFERENCED_PARAMETER(papp);
         throw interface_only_exception("this is an interface");
      }

      string system::default_userappdata(::ca::application * papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcszPrefix);
         UNREFERENCED_PARAMETER(lpcszLogin);
         UNREFERENCED_PARAMETER(pszRelativePath);
         throw interface_only_exception("this is an interface");
      }

      string system::default_userdata(::ca::application * papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcszPrefix);
         UNREFERENCED_PARAMETER(lpcszLogin);
         UNREFERENCED_PARAMETER(pszRelativePath);
         throw interface_only_exception("this is an interface");
      }

      string system::default_userfolder(::ca::application * papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcszPrefix);
         UNREFERENCED_PARAMETER(lpcszLogin);
         UNREFERENCED_PARAMETER(pszRelativePath);
         throw interface_only_exception("this is an interface");
      }

      string system::userquicklaunch(::ca::application * papp, const char * lpcszRelativePath, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcszRelativePath);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      string system::userprograms(::ca::application * papp, const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      string system::commonprograms(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      bool system::is_inside_time(const char * pszPath, ::ca::application * papp)
      {
         UNREFERENCED_PARAMETER(pszPath);
         throw interface_only_exception("this is an interface");
      }

      bool system::is_inside(const char * pszDir, const char * pszPath, ::ca::application * papp)
      {
         UNREFERENCED_PARAMETER(pszDir);
         UNREFERENCED_PARAMETER(pszPath);
         throw interface_only_exception("this is an interface");
      }

      string system::sensitive_ccvotagus(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         return path(ca2("ccvotagus"), lpcsz, lpcsz2);
      }
 
   }  // namespace dir

} // namespace ca
