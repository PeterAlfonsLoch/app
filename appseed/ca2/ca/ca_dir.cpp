#include "StdAfx.h"

namespace ca
{
   dir::dir(::ca::application * papp) :
      ca(papp)
   {
      m_pziputil = new zip::Util(papp);
   }

   dir::~dir()
   {
      if(m_pziputil != NULL)
      {
         delete m_pziputil;
      }
   }

   bool dir::path::is_equal(const char * lpcsz1, const char * lpcsz2)
   {
      UNREFERENCED_PARAMETER(lpcsz1);
      UNREFERENCED_PARAMETER(lpcsz2);
      throw interface_only_exception("this is an interface");
   }

   string dir::path(const char * lpcszFolder, const char * lpcszRelative, const char * psz2)
   {
      UNREFERENCED_PARAMETER(lpcszFolder);
      UNREFERENCED_PARAMETER(lpcszRelative);
      UNREFERENCED_PARAMETER(psz2);
      throw interface_only_exception("this is an interface");
   }

   string dir::relpath(const char * lpcszSource, const char * lpcszRelative, const char * psz2)
   {
      UNREFERENCED_PARAMETER(lpcszSource);
      UNREFERENCED_PARAMETER(lpcszRelative);
      UNREFERENCED_PARAMETER(psz2);
      throw interface_only_exception("this is an interface");
   }

   void dir::root_ones(stringa & stra)
   {
      UNREFERENCED_PARAMETER(stra);
      throw interface_only_exception("this is an interface");
   }

   void dir::rls_pattern(const char * lpcsz, const char * pszPattern, stringa * pstraPath, stringa * pstraTitle, stringa * pstraRelative, base_array < bool, bool > * pbaIsDir, base_array < __int64, __int64 > * piaSize)
   {
      if(gen::str::ends_ci(lpcsz, ".zip") || gen::str::find_ci(".zip:", lpcsz) >= 0)
      {
         throw "should implement recursive zip";
         m_pziputil->ls(lpcsz, false, pstraPath, pstraTitle, NULL, pbaIsDir, piaSize);
         return;
      }
      throw not_implemented_exception("is really a directory or compressed directory/file??");
      
   }


   void dir::ls_pattern(const char * lpcsz, const char * pszPattern, stringa * pstraPath, stringa * pstraTitle, base_array < bool, bool > * pbaIsDir, base_array < __int64, __int64 > * piaSize)
   {
      if(gen::str::ends_ci(lpcsz, ".zip") || gen::str::find_ci(".zip:", lpcsz) >= 0)
      {
         m_pziputil->ls(lpcsz, false, pstraPath, pstraTitle, NULL, pbaIsDir, piaSize);
         return;
      }
      throw not_implemented_exception("is really a directory or compressed directory/file??");
      
   }

   void dir::ls(const char * lpcsz, stringa * pstraPath, stringa * pstraTitle, base_array < bool, bool > * pbaIsDir, base_array < __int64, __int64 > * piaSize)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      UNREFERENCED_PARAMETER(pstraPath);
      UNREFERENCED_PARAMETER(pstraTitle);
      UNREFERENCED_PARAMETER(pbaIsDir);
      UNREFERENCED_PARAMETER(piaSize);
      throw interface_only_exception("this is an interface");
   }

   void dir::rls(const char * lpcsz, stringa * pstraPath, stringa * pstraTitle, stringa * pstraRelative)
   {
      if(gen::str::ends_ci(lpcsz, ".zip") || gen::str::find_ci(".zip:", lpcsz) >= 0)
      {
         m_pziputil->ls(lpcsz, false, pstraPath, pstraTitle, pstraRelative);
         return;
      }
      else
      {
         return;
      }
   }

   void dir::rls_dir(const char * lpcsz, stringa * pstraPath, stringa * pstraTitle, stringa * pstraRelative)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      UNREFERENCED_PARAMETER(pstraPath);
      UNREFERENCED_PARAMETER(pstraTitle);
      UNREFERENCED_PARAMETER(pstraRelative);
      throw interface_only_exception("this is an interface");
   }

   void dir::ls_dir(const char * lpcsz, stringa * pstraPath, stringa * pstraTitle)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      UNREFERENCED_PARAMETER(pstraPath);
      UNREFERENCED_PARAMETER(pstraTitle);
      throw interface_only_exception("this is an interface");
   }

   bool dir::has_subdir(const char * lpcsz)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      throw interface_only_exception("this is an interface");
   }

   void dir::ls_file(const char * lpcsz, stringa * pstraPath, stringa * pstraTitle)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      UNREFERENCED_PARAMETER(pstraPath);
      UNREFERENCED_PARAMETER(pstraTitle);
      throw interface_only_exception("this is an interface");
   }

   bool dir::is(const char * lpcszPath)
   {
      if(gen::str::ends_ci(lpcszPath, ".zip"))
         return true;
      if(gen::str::find_ci(".zip:", lpcszPath))
      {
         return m_pziputil->HasSubFolder(lpcszPath);
      }
      return false;
   }

   string dir::votagus(const char * lpcsz, const char * lpcsz2)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      UNREFERENCED_PARAMETER(lpcsz2);
      throw interface_only_exception("this is an interface");
   }

   string dir::time(const char * lpcsz, const char * lpcsz2)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      UNREFERENCED_PARAMETER(lpcsz2);
      throw interface_only_exception("this is an interface");
   }

   string dir::stage(const char * lpcsz, const char * lpcsz2)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      UNREFERENCED_PARAMETER(lpcsz2);
      throw interface_only_exception("this is an interface");
   }

   string dir::stageapp(const char * lpcsz, const char * lpcsz2)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      UNREFERENCED_PARAMETER(lpcsz2);
      throw interface_only_exception("this is an interface");
   }

   string dir::netseed(const char * lpcsz, const char * lpcsz2)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      UNREFERENCED_PARAMETER(lpcsz2);
      throw interface_only_exception("this is an interface");
   }

   string dir::ca2(const char * lpcsz, const char * lpcsz2)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      UNREFERENCED_PARAMETER(lpcsz2);
      throw interface_only_exception("this is an interface");
   }

   string dir::module(const char * lpcsz, const char * lpcsz2)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      UNREFERENCED_PARAMETER(lpcsz2);
      throw interface_only_exception("this is an interface");
   }

   string dir::ca2module(const char * lpcsz, const char * lpcsz2)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      UNREFERENCED_PARAMETER(lpcsz2);
      throw interface_only_exception("this is an interface");
   }

   void dir::time_square(string &str)
   {
      UNREFERENCED_PARAMETER(str);
      throw interface_only_exception("this is an interface");
   }

   string dir::time_log(const char * pszId)
   {
      UNREFERENCED_PARAMETER(pszId);
      throw interface_only_exception("this is an interface");
   }

   bool dir::mk(const char * lpcsz)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      throw interface_only_exception("this is an interface");
   }

   string dir::name(const char * path1)
   {
      UNREFERENCED_PARAMETER(path1);
      throw interface_only_exception("this is an interface");
   }

   string dir::locale_style()
   {
      throw interface_only_exception("this is an interface");
   }

   string dir::matter(const char * lpcsz, const char * lpcsz2)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      UNREFERENCED_PARAMETER(lpcsz2);
      throw interface_only_exception("this is an interface");
   }

   class dir::path & dir::path()
   {
      throw interface_only_exception("this is an interface");
   }

   bool dir::initialize()
   {
      throw interface_only_exception("this is an interface");
   }

   string dir::trash_that_is_not_trash(const char * lpcsz)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      throw interface_only_exception("this is an interface");
   }

   string dir::appdata(const char * lpcsz, const char * lpcsz2)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      UNREFERENCED_PARAMETER(lpcsz2);
      throw interface_only_exception("this is an interface");
   }

   string dir::usersystemappdata(const char * lpcszPrefix, const char * lpcsz, const char * lpcsz2)
   {
      UNREFERENCED_PARAMETER(lpcszPrefix);
      UNREFERENCED_PARAMETER(lpcsz);
      UNREFERENCED_PARAMETER(lpcsz2);
      throw interface_only_exception("this is an interface");
   }

   string dir::userappdata(const char * lpcsz, const char * lpcsz2)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      UNREFERENCED_PARAMETER(lpcsz2);
      throw interface_only_exception("this is an interface");
   }

   string dir::userdata(const char * lpcsz, const char * lpcsz2)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      UNREFERENCED_PARAMETER(lpcsz2);
      throw interface_only_exception("this is an interface");
   }

   string dir::userfolder(const char * lpcsz, const char * lpcsz2)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      UNREFERENCED_PARAMETER(lpcsz2);
      throw interface_only_exception("this is an interface");
   }

   string dir::default_os_user_path_prefix()
   {
      throw interface_only_exception("this is an interface");
   }

   string dir::default_userappdata(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
   {
      UNREFERENCED_PARAMETER(lpcszPrefix);
      UNREFERENCED_PARAMETER(lpcszLogin);
      UNREFERENCED_PARAMETER(pszRelativePath);
      throw interface_only_exception("this is an interface");
   }

   string dir::default_userdata(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
   {
      UNREFERENCED_PARAMETER(lpcszPrefix);
      UNREFERENCED_PARAMETER(lpcszLogin);
      UNREFERENCED_PARAMETER(pszRelativePath);
      throw interface_only_exception("this is an interface");
   }

   string dir::default_userfolder(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
   {
      UNREFERENCED_PARAMETER(lpcszPrefix);
      UNREFERENCED_PARAMETER(lpcszLogin);
      UNREFERENCED_PARAMETER(pszRelativePath);
      throw interface_only_exception("this is an interface");
   }

   string dir::userquicklaunch(const char * lpcszRelativePath, const char * lpcsz2)
   {
      UNREFERENCED_PARAMETER(lpcszRelativePath);
      UNREFERENCED_PARAMETER(lpcsz2);
      throw interface_only_exception("this is an interface");
   }

   string dir::userprograms(const char * lpcsz, const char * lpcsz2)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      UNREFERENCED_PARAMETER(lpcsz2);
      throw interface_only_exception("this is an interface");
   }

   string dir::commonprograms(const char * lpcsz, const char * lpcsz2)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      UNREFERENCED_PARAMETER(lpcsz2);
      throw interface_only_exception("this is an interface");
   }

   bool dir::is_inside_time(const char * pszPath)
   {
      UNREFERENCED_PARAMETER(pszPath);
      throw interface_only_exception("this is an interface");
   }

   bool dir::is_inside(const char * pszDir, const char * pszPath)
   {
      UNREFERENCED_PARAMETER(pszDir);
      UNREFERENCED_PARAMETER(pszPath);
      throw interface_only_exception("this is an interface");
   }

   string dir::sensitive_ccvotagus(const char * lpcsz, const char * lpcsz2)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      UNREFERENCED_PARAMETER(lpcsz2);
      return path(ca2("ccvotagus"), lpcsz, lpcsz2);
   }

} // namespace ca
