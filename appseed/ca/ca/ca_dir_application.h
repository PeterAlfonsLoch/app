#pragma once

namespace zip
{
   class Util;
}

namespace ca
{

   namespace dir
   {

      class CLASS_DECL_ca application :
         virtual public ::radix::object
      {
      public:


         application();
         virtual ~application();


         virtual string locale_schema(const char * pszLocale = NULL, const char * pszStyle = NULL);
         virtual string locale_schema_matter(const char * pszLocale = NULL, const char * pszStyle = NULL);
         virtual string matter(const char * lpcsz = NULL, const char * lpcsz2 = NULL);


         virtual string usersystemappdata(const char * lpcszPrefix, const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         virtual string userappdata(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         virtual string userdata(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         virtual string userfolder(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         virtual string default_os_user_path_prefix();
         virtual string default_userappdata(const char * lpcszPrefix, const char * lpcszLogin , const char * pszRelativePath = NULL);
         virtual string default_userdata(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath = NULL);
         virtual string default_userfolder(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath = NULL);
         virtual string userquicklaunch(const char * pszRelativePath = NULL, const char * lpcsz2 = NULL);
         virtual string userprograms(const char * pszRelativePath = NULL, const char * lpcsz2 = NULL);


         virtual void  ls_pattern(const char * lpcsz, const char * lpcszPattern, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, base_array < bool, bool > * pbaIsDir = NULL, base_array < __int64, __int64 > * piaSize = NULL);
         virtual void  ls(const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, base_array < bool, bool > * pbaIsDir = NULL, base_array < __int64, __int64 > * piaSize = NULL);
         virtual void  rls_pattern(const char * lpcsz, const char * lpcszPattern, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, stringa * pstraRelative = NULL, base_array < bool, bool > * pbaIsDir = NULL, base_array < __int64, __int64 > * piaSize = NULL);
         virtual void  rls(const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, stringa * pstraRelative = NULL);
         virtual void  rls_dir(const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, stringa * pstraRelative = NULL);
         virtual void  ls_dir(const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL);
         virtual bool  has_subdir(const char * lpcsz);
         virtual void  ls_file(const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL);
         virtual bool  is(const char * lpcsz);
         virtual bool  is(const string & str);
         virtual bool  is(const var & var);
         virtual bool  is_inside(const char * lpcszDir, const char * lpcszPath);
         virtual bool  is_inside_time(const char * lpcsz);
         virtual void  root_ones(stringa & stra);
         virtual bool  mk(const char * lpcsz);
         virtual bool  rm(const char * psz, bool bRecursive = true);


      };

   } // namespace dir

} // namespace ca