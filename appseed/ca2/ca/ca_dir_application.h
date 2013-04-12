#pragma once

namespace zip
{
   class Util;
}

namespace ca
{

   namespace dir
   {

      class CLASS_DECL_ca2 application :
         virtual public ::ca::object
      {
      public:


         application();
         virtual ~application();


         virtual string locale_schema(const char * pszLocale = ::null(), const char * pszStyle = ::null());
         virtual string locale_schema_matter(const char * pszLocale = ::null(), const char * pszStyle = ::null());
         virtual string matter(const string & str, bool bDir = false);
         virtual string matter(const string & str, const string & str2, bool bDir = false);
         virtual string matter(const string & str, const char * psz, bool bDir = false);
         virtual string matter(const char * psz, const string & str, bool bDir = false);
         virtual string matter(const char * lpcsz = ::null(), const char * lpcsz2 = ::null(), bool bDir = false);
         virtual string matter(const stringa & stra, bool bDir = false);

         virtual void   matter_ls(const string & str, stringa & stra);
         virtual string matter_file(const char * lpcsz = ::null(), const char * lpcsz2 = ::null(), bool bDir = false);
         virtual void   matter_ls_file(const string & str, stringa & stra);

         virtual string usersystemappdata(const char * lpcszPrefix, const char * lpcsz = ::null(), const char * lpcsz2 = ::null());
         virtual string userappdata(const char * lpcsz = ::null(), const char * lpcsz2 = ::null());
         virtual string userdata(const char * lpcsz = ::null(), const char * lpcsz2 = ::null());
         virtual string userfolder(const char * lpcsz = ::null(), const char * lpcsz2 = ::null());
         virtual string default_os_user_path_prefix();
         virtual string default_userappdata(const char * lpcszPrefix, const char * lpcszLogin , const char * pszRelativePath = ::null());
         virtual string default_userdata(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath = ::null());
         virtual string default_userfolder(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath = ::null());
         virtual string userquicklaunch(const char * pszRelativePath = ::null(), const char * lpcsz2 = ::null());
         virtual string userprograms(const char * pszRelativePath = ::null(), const char * lpcsz2 = ::null());


         virtual void  ls_pattern(const char * lpcsz, const char * lpcszPattern, stringa * pstraPath = ::null(), stringa * pstraTitle = ::null(), array < bool, bool > * pbaIsDir = ::null(), array < int64_t, int64_t > * piaSize = ::null());
         virtual void  ls(const char * lpcsz, stringa * pstraPath = ::null(), stringa * pstraTitle = ::null(), array < bool, bool > * pbaIsDir = ::null(), array < int64_t, int64_t > * piaSize = ::null());
         virtual void  rls_pattern(const char * lpcsz, const char * lpcszPattern, stringa * pstraPath = ::null(), stringa * pstraTitle = ::null(), stringa * pstraRelative = ::null(), array < bool, bool > * pbaIsDir = ::null(), array < int64_t, int64_t > * piaSize = ::null());
         virtual void  rls(const char * lpcsz, stringa * pstraPath = ::null(), stringa * pstraTitle = ::null(), stringa * pstraRelative = ::null());
         virtual void  rls_dir(const char * lpcsz, stringa * pstraPath = ::null(), stringa * pstraTitle = ::null(), stringa * pstraRelative = ::null());
         virtual void  ls_dir(const char * lpcsz, stringa * pstraPath = ::null(), stringa * pstraTitle = ::null());
         virtual bool  has_subdir(const char * lpcsz);
         virtual void  ls_file(const char * lpcsz, stringa * pstraPath = ::null(), stringa * pstraTitle = ::null());
         virtual bool  is(const char * lpcsz);
         virtual bool  is(const string & str);
         virtual bool  is(const var & var);
         virtual bool  is_inside(const char * lpcszDir, const char * lpcszPath);
         virtual bool  is_inside_time(const char * lpcsz);
         virtual void  root_ones(stringa & stra);
         virtual bool  mk(const char * lpcsz);
         virtual bool  rm(const char * psz, bool bRecursive = true);

         virtual string pathfind(const char * pszEnv, const char * pszTopic, const char * pszMode);

      };

   } // namespace dir

} // namespace ca
