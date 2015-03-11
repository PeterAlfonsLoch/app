#pragma once


namespace windows
{



   class CLASS_DECL_AURA dir:
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


      dir(::aura::application * papp);


      virtual bool  ls_pattern(::aura::application * papp, const ::file::path & path,const string & lpcszPattern,::file::patha * ppatha = NULL,::file::patha * ppathaName = NULL,bool bSize = false);
      virtual bool  ls(::aura::application * papp, const ::file::path & path,::file::patha * ppatha = NULL,::file::patha * ppathaName = NULL,bool bSize = false);
      virtual bool  rls_pattern(::aura::application * papp, const ::file::path & path, const string & lpcszPattern, ::file::patha * ppatha = NULL, ::file::patha * ppathaName = NULL, ::file::patha * ppathaRelative = NULL, bool_array * pbaIsDir = NULL, bool bSize = false, e_extract eextract = extract_first);
      virtual bool  rls(::aura::application * papp, const ::file::path & path, ::file::patha * ppatha = NULL, ::file::patha * ppathaName = NULL, ::file::patha * ppathaRelative = NULL, e_extract eextract = extract_first);
      virtual bool  rls_dir(::aura::application * papp, const ::file::path & path,::file::patha * ppatha = NULL,::file::patha * ppathaName = NULL,::file::patha * ppathaRelative = NULL);
      virtual bool  ls_dir(::aura::application * papp, const ::file::path & path,::file::patha * ppatha = NULL,::file::patha * ppathaName = NULL);
      virtual bool  ls_file(::aura::application * papp, const ::file::path & path,::file::patha * ppatha = NULL,::file::patha * ppathaName = NULL);


      virtual bool  is(const ::file::path & path, ::aura::application * papp);
      virtual bool  is_inside(const ::file::path & pathFolder,const ::file::path & path,::aura::application * papp);
      virtual bool  is_inside_time(const ::file::path & path,::aura::application * papp);
      virtual bool  name_is(const ::file::path & path,::aura::application * papp);
      virtual bool  has_subdir(::aura::application * papp, const ::file::path & path);

      virtual void root_ones(::file::patha & patha, stringa & straTitle, ::aura::application * papp);
      virtual bool mk(const ::file::path & path,::aura::application * papp);
      virtual bool rm(::aura::application * papp, const ::file::path & path, bool bRecursive = true);
      

      virtual ::file::path name(const ::file::path & path);
              
      virtual ::file::path time();
      virtual ::file::path stage();
      virtual ::file::path stageapp();
      virtual ::file::path netseed();
      virtual ::file::path element();
              
      virtual ::file::path module();
      virtual ::file::path ca2module();
      virtual ::file::path time_square();
      virtual ::file::path time_log();


      virtual ::file::path trash_that_is_not_trash(const ::file::path & path);



      virtual ::file::path appdata();
      virtual ::file::path commonappdata_root();

      virtual ::file::path usersystemappdata(::aura::application * papp, const char * lpcszPrefix);
      virtual ::file::path userappdata(::aura::application * papp);
      virtual ::file::path userdata(::aura::application * papp);
      virtual ::file::path userfolder(::aura::application * papp);
      virtual ::file::path default_os_user_path_prefix(::aura::application * papp);
      virtual ::file::path default_userappdata(::aura::application * papp, const char * lpcszPrefix, const char * lpcszLogin );
      virtual ::file::path default_userdata(::aura::application * papp, const char * lpcszPrefix, const char * lpcszLogin);
      virtual ::file::path default_userfolder(::aura::application * papp, const char * lpcszPrefix, const char * lpcszLogin);
      virtual ::file::path userquicklaunch(::aura::application * papp);
      virtual ::file::path userprograms(::aura::application * papp);
              
      virtual ::file::path commonprograms();

      virtual bool initialize();


   };


} // namespace windows




