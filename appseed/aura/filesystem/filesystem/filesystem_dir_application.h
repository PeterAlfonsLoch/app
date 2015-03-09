#pragma once

namespace zip
{
   class Util;
}

namespace file
{

   namespace dir
   {

      class CLASS_DECL_AURA application:
         virtual public ::object
      {
      public:


         application(::aura::application * papp);
         virtual ~application();


         virtual ::file::path locale_schema(const char * pszLocale = NULL,const char * pszStyle = NULL);
         virtual ::file::patha locale_schema_matter(const char * pszLocale = NULL, const char * pszStyle = NULL, const char * pszRoot = NULL, const char * pszApp = NULL);
         virtual ::file::path matter(const ::file::path & path,bool bDir = false,const char * pszRoot = NULL,const char * pszApp = NULL);
         virtual ::file::path matter(const ::file::patha & stra,bool bDir = false,const char * pszRoot = NULL,const char * pszApp = NULL);

         virtual void   matter_ls(const string & str, ::file::patha & stra);
         virtual ::file::path matter_file(const ::file::path & path,bool bDir = false);
         virtual void   matter_ls_file(const string & str, ::file::patha & stra);

         virtual ::file::path usersystemappdata(const char * lpcszPrefix);
         virtual ::file::path userappdata();
         virtual ::file::path userdata();
         virtual ::file::path userfolder();
         virtual ::file::path default_os_user_path_prefix();
         virtual ::file::path default_userappdata(const char * lpcszPrefix, const char * lpcszLogin );
         virtual ::file::path default_userdata(const char * lpcszPrefix, const char * lpcszLogin);
         virtual ::file::path default_userfolder(const char * lpcszPrefix, const char * lpcszLogin);
         virtual ::file::path userquicklaunch();
         virtual ::file::path userprograms();


         virtual bool  ls_pattern(const char * lpcsz,const char * lpcszPattern,::file::patha * ppatha = NULL,::file::patha * ppathaName = NULL,bool_array * pbaIsDir = NULL,int64_array * piaSize = NULL);
         virtual bool  ls(const char * lpcsz,::file::patha * ppatha = NULL,::file::patha * ppathaName = NULL,bool_array * pbaIsDir = NULL,int64_array * piaSize = NULL);
         virtual bool  rls_pattern(const char * lpcsz, const char * lpcszPattern, ::file::patha * ppatha = NULL, ::file::patha * ppathaName = NULL, ::file::patha * ppathaRelative = NULL, bool_array * pbaIsDir = NULL, int64_array * piaSize = NULL);
         virtual bool  rls(const char * lpcsz, ::file::patha * ppatha = NULL, ::file::patha * ppathaName = NULL, ::file::patha * ppathaRelative = NULL);
         virtual bool  rls_dir(const char * lpcsz,::file::patha * ppatha = NULL,::file::patha * ppathaName = NULL,::file::patha * ppathaRelative = NULL);
         virtual bool  ls_dir(const char * lpcsz,::file::patha * ppatha = NULL,::file::patha * ppathaName = NULL);
         virtual bool  ls_file(const char * lpcsz,::file::patha * ppatha = NULL,::file::patha * ppathaName = NULL);
         

         virtual bool  has_subdir(const char * lpcsz);
         virtual bool  is(const char * lpcsz);
         virtual bool  is(const string & str);
         virtual bool  is(const var & var);
         virtual bool  is_inside(const char * lpcszDir, const char * lpcszPath);
         virtual bool  is_inside_time(const char * lpcsz);
         virtual void  root_ones(::file::patha & patha, ::file::patha & straTitle);
         virtual bool  mk(const char * lpcsz);
         virtual bool  rm(const char * psz, bool bRecursive = true);

         virtual ::file::path pathfind(const char * pszEnv,const char * pszTopic,const char * pszMode);

      };


      typedef smart_pointer < application > application_sp;


   } // namespace dir


} // namespace file







