#pragma once


namespace metrowin
{


   class CLASS_DECL_AURA dir:
      virtual public ::file::dir::system
   {
   public:


      ::file::path         m_strCa2;
      ::file::path         m_strTimeFolder;
      ::file::path         m_strNetSeedFolder;


      dir(::ace::application *  papp);


      //using ::file::dir::system::path;
      //virtual class ::file::path & path();
      //virtual string path(const char * pszFolder,strsize iLenFolder,const char * pszRelative,strsize iLenRelative,const char * psz2,strsize iLen2,bool bUrl);

      //virtual string relpath(const char * lpcszSource,const char * lpcszRelative,const char * lpcsz2 = NULL);
      //virtual bool  ls_pattern(::ace::application *  papp,const char * lpcsz,const char * lpcszPattern,stringa * pstraPath = NULL,stringa * pstraTitle = NULL,bool_array * pbaIsDir = NULL,int64_array * piaSize = NULL);
      virtual ::file::listing & ls(::ace::application *  papp,::file::listing & listing);
      //virtual bool  rls_pattern(::ace::application *  papp,const char * lpcsz,const char * lpcszPattern,stringa * pstraPath = NULL,stringa * pstraTitle = NULL,stringa * pstraRelative = NULL,bool_array * pbaIsDir = NULL,int64_array * piaSize = NULL,e_extract eextract = extract_first);
      //virtual bool  rls(::ace::application *  papp,const char * lpcsz,stringa * pstraPath = NULL,stringa * pstraTitle = NULL,stringa * pstraRelative = NULL,e_extract eextract = extract_first);
      //virtual bool  rls_dir(::ace::application *  papp,const char * lpcsz,stringa * pstraPath = NULL,stringa * pstraTitle = NULL,stringa * pstraRelative = NULL);
      //virtual bool  ls_dir(::ace::application *  papp,const char * lpcsz,stringa * pstraPath = NULL,stringa * pstraTitle = NULL);
      //virtual bool  ls_file(::ace::application *  papp,const char * lpcsz,stringa * pstraPath = NULL,stringa * pstraTitle = NULL);
      virtual bool  is(const ::file::path & path,::ace::application *  papp);
      //virtual bool  is(const string & str,::ace::application *  papp);
      virtual bool  name_is(const ::file::path & str,::ace::application *  papp);
      virtual bool  has_subdir(::ace::application *  papp, const ::file::path & path);
      virtual bool  is_inside(const ::file::path & pathDir, const ::file::path & path,::ace::application *  papp);
      virtual bool  is_inside_time(const ::file::path & path,::ace::application *  papp);
      virtual ::file::listing & root_ones(::file::listing & listing,::ace::application *  papp);
      virtual bool mk(const ::file::path & path,::ace::application *  papp);
      virtual bool rm(::ace::application *  papp, const ::file::path & path, bool bRecursive = true);


      //virtual string name(const char * lpcsz);
      //virtual string name(const string & str);

      ::file::path dir::userfolder(::ace::application *  papp);

      virtual ::file::path votagus();
      virtual ::file::path time();
      virtual ::file::path stage();
      virtual ::file::path stageapp();
      virtual ::file::path netseed();

      // stage in ccvotagus spalib
      virtual ::file::path element();

      //virtual ::file::path module();
      //virtual ::file::path ca2module();
      virtual ::file::path time_square();
      virtual ::file::path time_log();


      virtual ::file::path trash_that_is_not_trash(const ::file::path & path);

      virtual ::file::path appdata();

      virtual ::file::path usersystemappdata(::ace::application *  papp,const string & strPrefix);
      virtual ::file::path userappdata(::ace::application *  papp);
      virtual ::file::path userdata(::ace::application *  papp);
      //virtual ::file::path userfolder(::ace::application *  papp);
      virtual ::file::path default_os_user_path_prefix(::ace::application *  papp);
      virtual ::file::path default_userappdata(::ace::application *  papp,const string & strPrefix,const string & strLogin);
      virtual ::file::path default_userdata(::ace::application *  papp,const string & strPrefix,const string & strLogin);
      virtual ::file::path default_userfolder(::ace::application *  papp,const string & strPrefix,const string & strLogin);
      virtual ::file::path userquicklaunch(::ace::application *  papp);
      virtual ::file::path userprograms(::ace::application *  papp);

      virtual ::file::path commonprograms();

      virtual ::file::path commonappdata();

      virtual bool initialize();


   };


} // namespace metrowin





