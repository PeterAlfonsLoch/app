#pragma once


namespace linux
{


   class CLASS_DECL_AURA dir :
      virtual public ::file::dir::system
   {
   public:


      ::file::path            m_strTimeFolder;
      ::file::path            m_strNetSeedFolder;

      ::file::path            m_strCa2;
      ::file::path            m_strCommonAppData;
      ::file::path            m_strProfile;
      ::file::path            m_strAppData;
      ::file::path            m_strPrograms;
      ::file::path            m_strCommonPrograms;


      dir(::ace::application * papp);


//      virtual string path(const char * pszFolder, strsize iLenFolder, const char * pszRelative, strsize iLenRelative, const char * psz2, strsize iLen2, bool bUrl);

  //    virtual string relpath(const char * lpcszSource, const char * lpcszRelative, const char * lpcsz2 = NULL);


//      virtual bool  ls_pattern(::ace::application * papp,const char * lpcsz,const char * lpcszPattern,stringa * pstraPath = NULL,stringa * pstraTitle = NULL,bool_array * pbaIsDir = NULL,int64_array * piaSize = NULL);
//      virtual bool  ls(::ace::application * papp,const char * lpcsz,stringa * pstraPath = NULL,stringa * pstraTitle = NULL,bool_array * pbaIsDir = NULL,int64_array * piaSize = NULL);
//      virtual bool  rls_pattern(::ace::application * papp, const char * lpcsz, const char * lpcszPattern, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, stringa * pstraRelative = NULL, bool_array * pbaIsDir = NULL, int64_array * piaSize = NULL, e_extract eextract = extract_first);
//      virtual bool  rls(::ace::application * papp, const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, stringa * pstraRelative = NULL, e_extract eextract = extract_first);
//      virtual bool  rls_dir(::ace::application * papp,const char * lpcsz,stringa * pstraPath = NULL,stringa * pstraTitle = NULL,stringa * pstraRelative = NULL);
//      virtual bool  ls_dir(::ace::application * papp,const char * lpcsz,stringa * pstraPath = NULL,stringa * pstraTitle = NULL);
//      virtual bool  ls_file(::ace::application * papp,const char * lpcsz,stringa * pstraPath = NULL,stringa * pstraTitle = NULL);
      virtual ::file::listing & ls(::ace::application * papp, ::file::listing & ls);


      virtual bool  is(const ::file::path & path, ::ace::application * papp);
      virtual bool  is_inside(const ::file::path & lpcszDir, const ::file::path & lpcszPath, ::ace::application * papp);
      virtual bool  is_inside_time(const ::file::path & lpcsz, ::ace::application * papp);
      virtual bool  name_is(const ::file::path & path,::ace::application * papp);
      virtual bool  has_subdir(::ace::application * papp,const ::file::path & lpcsz);

      virtual ::file::listing & root_ones(::file::listing & listing, ::ace::application * papp);
      virtual bool mk(const ::file::path & lpcsz, ::ace::application * papp);
      virtual bool rm(::ace::application * papp, const ::file::path & psz, bool bRecursive = true);


      //virtual ::file::path name(const ::file::path & lpcsz);

      virtual ::file::path time();
      virtual ::file::path stage();
      virtual ::file::path stageapp();
      virtual ::file::path netseed();

      // stage in ca2os spalib
    //  virtual string element(const char * lpcsz, const char * lpcsz2 = NULL);
      virtual ::file::path element();
//      virtual string element(const string & str);
//      virtual string element(const string & str, const string & str2);
//      virtual string element(const char * lpcsz, const string & str2);
//      virtual string element(const string & str, const char * lpcsz2);

//      virtual ::file::path module();
//      virtual ::file::path ca2module();
      virtual ::file::path time_square();
      virtual ::file::path time_log(const string & pszId);


      virtual ::file::path trash_that_is_not_trash(const ::file::path & psz);

      virtual ::file::path appdata();
      virtual ::file::path commonappdata();
      virtual ::file::path element_commonappdata(const string & strElement);

      virtual ::file::path usersystemappdata(::ace::application * papp, const string & lpcszPrefix);
      virtual ::file::path userappdata(::ace::application * papp);
      virtual ::file::path userdata(::ace::application * papp);
      //virtual ::file::path userfolder(::ace::application * papp);
      virtual ::file::path default_os_user_path_prefix(::ace::application * papp);
      virtual ::file::path default_userappdata(::ace::application * papp, const string & lpcszPrefix, const string & lpcszLogin);
      virtual ::file::path default_userdata(::ace::application * papp, const string & lpcszPrefix, const string & lpcszLogin);
      virtual ::file::path default_userfolder(::ace::application * papp, const string & lpcszPrefix, const string & lpcszLogin);
      virtual ::file::path userquicklaunch(::ace::application * papp);
      virtual ::file::path userprograms(::ace::application * papp);

      virtual ::file::path commonprograms();

      virtual bool initialize();
   };

} // namespace linux


