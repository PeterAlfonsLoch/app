#pragma once


namespace file
{


   namespace dir
   {


      class CLASS_DECL_AURA system :
         virtual public ::object
      {
      public:



         class CLASS_DECL_AURA is_dir
         {
         public:


            bool        m_bIsDir;
            uint32_t       m_dwLastCheck;
            uint32_t       m_dwError;


         };


         class CLASS_DECL_AURA is_dir_map :
            virtual public string_map < is_dir >
         {
         public:


            mutex             m_mutex;
            uint32_t             m_dwTimeOut;


            is_dir_map(::aura::application * papp);


            bool lookup(const string & strPath, bool &bIsDir, uint32_t & dwLastError);
            bool lookup(const string & strPath, bool &bIsDir, uint32_t & dwLastError, int32_t iLast);
            bool lookup(const char * pszPath, bool &bIsDir, uint32_t &dwLastError);
            void set(const char * pszPath, bool bIsDir, uint32_t dwLastError);
            void set(const string & strPath, bool bIsDir, uint32_t dwLastError);


         };


         is_dir_map           m_isdirmap;
         mutex                m_mutex;
         string               m_strApiCc;


         system(::aura::application * papp);
         virtual ~system();



         virtual bool  ls_pattern(::aura::application * papp,const char * lpcsz,const char * lpcszPattern,::file::patha * ppatha = NULL,::file::patha * ppathaName = NULL,bool bSize = false);
         virtual bool  ls(::aura::application * papp,const char * lpcsz,::file::patha * ppatha = NULL,::file::patha * ppathaName = NULL,bool bSize = false);
         virtual bool  rls_pattern(::aura::application * papp, const char * lpcsz, const char * lpcszPattern, ::file::patha * ppatha = NULL, ::file::patha * ppathaName = NULL, ::file::patha * ppathaRelative = NULL, bool_array * pbaIsDir = NULL, bool bSize = false, e_extract eextract = extract_first);
         virtual bool  rls(::aura::application * papp, const char * lpcsz, ::file::patha * ppatha = NULL, ::file::patha * ppathaName = NULL, ::file::patha * ppathaRelative = NULL, e_extract eextract = extract_first);
         virtual bool  rls_dir(::aura::application * papp,const char * lpcsz,::file::patha * ppatha = NULL,::file::patha * ppathaName = NULL,::file::patha * ppathaRelative = NULL);
         virtual bool  ls_dir(::aura::application * papp, const char * lpcsz, ::file::patha * ppatha = NULL, ::file::patha * ppathaName = NULL);
         virtual bool  has_subdir(::aura::application * papp, const char * lpcsz);
         virtual bool  ls_file(::aura::application * papp,const char * lpcsz,::file::patha * ppatha = NULL,::file::patha * ppathaName = NULL);

         virtual bool  is(const char * lpcsz, ::aura::application * papp);
         virtual bool  is(const string & str, ::aura::application * papp);
         virtual bool  is(const var & var, ::aura::application * papp);

         virtual bool  is_or_definitively_not(bool & bIs, const char * lpcsz, ::aura::application * papp);

         virtual bool  name_is(const char * lpcsz, ::aura::application * papp);
         virtual bool  name_is(const string & str, ::aura::application * papp);
         virtual bool  name_is(const var & var, ::aura::application * papp);

         virtual bool  is_inside(const char * lpcszDir, const char * lpcszPath, ::aura::application * papp);
         virtual bool  is_inside_time(const char * lpcsz, ::aura::application * papp);
         virtual void  root_ones(::file::patha & patha, stringa & straTitle, ::aura::application * papp);
         virtual bool  mk(const char * lpcsz, ::aura::application * papp);
         virtual bool  rm(::aura::application * papp, const char * psz, bool bRecursive = true);

         virtual ::file::path name(const char * psz);

         virtual ::file::path time();
         virtual ::file::path stage();
         virtual ::file::path stageapp();
         virtual ::file::path netseed();

         virtual ::file::path element();

         virtual ::file::path module();
         virtual ::file::path ca2module();
         virtual ::file::path time_square(::aura::application * papp,const char * pszPrefix = NULL,const char * pszSuffix = NULL);
         virtual ::file::path time_log(const char * pszId);

         virtual ::file::path locale_schema(::aura::application * papp,const string & strLocale,const string & strStyle);
         virtual ::file::patha locale_schema_matter(::aura::application * papp, const string & strLocale, const string & strStyle, const char * pszRoot = NULL, const char * pszApp = NULL);
         virtual ::file::patha locale_schema_matter(const string & strLocator, const string & strLocale, const string & strStyle);
         virtual ::file::path matter(::aura::application * papp,const ::file::patha & stra,bool bDir = false,const char * pszRoot = NULL,const char * pszApp = NULL);
         virtual ::file::path matter(::aura::application * papp,const ::file::path & path,bool bDir = false,const char * pszRoot = NULL,const char * pszApp = NULL);

         virtual void   matter_ls(::aura::application * papp, const ::file::path & str, ::file::patha & stra);
         virtual void   matter_ls_file(::aura::application * papp,const ::file::path & str,::file::patha & stra);

         //virtual ::file::path matter(::aura::application * papp);

         virtual ::file::path matter_from_locator(::aura::str_context * pcontext,const string & strLocator,const ::file::path & str);
         virtual void appmatter_locators(string & strRoot, string & strDomain, ::aura::application * papp);
         virtual void appmatter_locators(string & strRoot, string & strDomain, const string & strLibraryName, const string & strAppName);
         virtual void appmatter_locators(string & strRoot, string & strDomain, const string & strAppName);
         virtual ::file::path appmatter_locator(::aura::application * papp);
         virtual ::file::path appmatter_locator(const string & strLibraryName,const string & strAppName);
         virtual ::file::path appmatter_locator(const string & strAppName);
         virtual ::file::path base_appmatter_locator(const ::file::path & strBase,const string & strLibraryName,const string & strAppName);
         virtual ::file::path base_appmatter_locator(const ::file::path & strBase,const string & strAppName);



         virtual ::file::path trash_that_is_not_trash(const char * psz);

         virtual ::file::path appdata();
         virtual ::file::path commonappdata_root();
         virtual ::file::path commonappdata();
         virtual ::file::path element_commonappdata(const string & strElement);

         virtual ::file::path usersystemappdata(::aura::application * papp,const char * lpcszPrefix);
         virtual ::file::path userappdata(::aura::application * papp);
         virtual ::file::path userdata(::aura::application * papp);
         virtual ::file::path userfolder(::aura::application * papp);
         virtual ::file::path default_os_user_path_prefix(::aura::application * papp);
         virtual ::file::path default_userappdata(::aura::application * papp,const char * lpcszPrefix,const char * lpcszLogin);
         virtual ::file::path default_userdata(::aura::application * papp,const char * lpcszPrefix,const char * lpcszLogin);
         virtual ::file::path default_userfolder(::aura::application * papp,const char * lpcszPrefix,const char * lpcszLogin);
         virtual ::file::path userquicklaunch(::aura::application * papp);
         virtual ::file::path userprograms(::aura::application * papp);

         virtual ::file::path commonprograms();

         virtual ::file::path pathfind(const char * pszEnv,const char * pszTopic,const char * pszMode,::aura::application * papp);

         virtual bool initialize();

         virtual ::file::path get_api_cc();

      };


      typedef smart_pointer < system > system_sp;


   } // namespace dir


} // namespace file
















