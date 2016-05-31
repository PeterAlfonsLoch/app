#pragma once


namespace zip
{


   class Util;


}


namespace file
{


   namespace dir
   {


      class CLASS_DECL_ACE application:
         virtual public ::object
      {
      public:


         application(::ace::application * papp);
         virtual ~application();


         virtual ::file::path locale_schema(const string & pszLocale = cnull,const string & pszStyle = cnull);
         virtual ::file::patha locale_schema_matter(const string & pszLocale = cnull,const string & pszStyle = cnull,const ::file::path & pszRoot = cnull,const ::file::path & pszApp = cnull);
         virtual ::file::path matter(const ::file::path & path,bool bDir = false,const ::file::path & pszRoot = cnull,const ::file::path & pszApp = cnull);
         virtual ::file::path matter(const ::file::patha & stra,bool bDir = false,const ::file::path & pszRoot = cnull,const ::file::path & pszApp = cnull);

         virtual void   matter_ls(const ::file::path & str, ::file::patha & stra);
         virtual ::file::path matter_file(const ::file::path & path,bool bDir = false);
         virtual void   matter_ls_file(const ::file::path & str,::file::patha & stra);

         virtual ::file::path usersystemappdata(const string & lpcszPrefix);
         virtual ::file::path userappdata();
         virtual ::file::path userdata();
         virtual ::file::path userfolder();
         virtual ::file::path default_os_user_path_prefix();
         virtual ::file::path default_userappdata(const string & lpcszPrefix, const string & lpcszLogin );
         virtual ::file::path default_userdata(const string & lpcszPrefix, const string & lpcszLogin);
         virtual ::file::path default_userfolder(const string & lpcszPrefix, const string & lpcszLogin);
         virtual ::file::path userquicklaunch();
         virtual ::file::path userprograms();

         
         virtual listing & ls(listing & listing);
         

         virtual bool  has_subdir(const ::file::path & lpcsz);
         virtual bool  is(const ::file::path & lpcsz);
         //virtual bool  is(const string & str);
         //virtual bool  is(const var & var);
         virtual bool  is_inside(const ::file::path & lpcszDir, const ::file::path & lpcszPath);
         virtual bool  is_inside_time(const ::file::path & lpcsz);
         virtual ::file::listing & root_ones(::file::listing & listing);
         virtual bool  mk(const ::file::path & lpcsz);
         virtual bool  rm(const ::file::path & psz, bool bRecursive = true);

         virtual ::file::path pathfind(const string & pszEnv,const string & pszTopic,const string & pszMode);


      };


      typedef smart_pointer < application > application_sp;


   } // namespace dir


} // namespace file







