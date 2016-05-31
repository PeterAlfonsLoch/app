#pragma once


namespace file
{


   namespace dir
   {


      class CLASS_DECL_ACE system :
         virtual public ::object,
         virtual public ::file_watcher::listener_thread
      {
      public:



         class CLASS_DECL_ACE is_dir
         {
         public:

            bool           m_bIsDir;
            uint32_t       m_dwLastCheck;
            uint32_t       m_dwError;


         };


         class CLASS_DECL_ACE is_dir_map :
            virtual public file_path_map < is_dir >
         {
         public:


            mutex                m_mutex;
            uint32_t             m_dwTimeOut;


            is_dir_map(::ace::application * papp);


            bool lookup(const ::file::path & strPath,bool &bIsDir,uint32_t & dwLastError);
            bool lookup(const ::file::path & strPath,bool &bIsDir,uint32_t & dwLastError,int32_t iLast);
            void set(const ::file::path & strPath,bool bIsDir,uint32_t dwLastError);


         };


         is_dir_map           m_isdirmap;
         mutex                m_mutex;
         string               m_strApiCc;

         ::file::path         m_strCa2;
         ::file::path         m_pathCa2Module;
         ::file::path         m_pathModule;
         ::file::path         m_pathProfile;
         ::file::path         m_pathUser;



         system(::ace::application * papp);
         virtual ~system();


         virtual ::file::listing & ls(::ace::application * papp,listing & listing);


         virtual bool  is(const ::file::path & lpcsz,::ace::application * papp);

         virtual bool  is_or_definitively_not(bool & bIs, const ::file::path & lpcsz,::ace::application * papp);

         virtual bool  name_is(const ::file::path & lpcsz,::ace::application * papp);

         virtual bool  is_inside(const ::file::path & lpcszDir,const ::file::path & lpcszPath,::ace::application * papp);
         virtual bool  is_inside_time(const ::file::path & lpcsz,::ace::application * papp);
         virtual ::file::listing & root_ones(::file::listing & listing,::ace::application * papp);
         virtual bool  mk(const ::file::path & lpcsz,::ace::application * papp);
         virtual bool  rm(::ace::application * papp,const ::file::path & psz,bool bRecursive = true);

         //virtual ::file::path name(const ::file::path & psz);

         virtual bool has_subdir(::ace::application * papp,const ::file::path & psz);

         virtual ::file::path time();
         virtual ::file::path stage();
         virtual ::file::path stageapp();
         virtual ::file::path netseed();

         virtual ::file::path element();
         virtual ::file::path profile();

         virtual ::file::path module();
         virtual ::file::path ca2module();
         virtual ::file::path time_square(::ace::application * papp,const string & strPrefix = cnull,const string & = cnull);
         virtual ::file::path time_log(const string & strId);

         virtual ::file::path locale_schema(::ace::application * papp,const string & strLocale = cnull,const string & strStyle = cnull);
         virtual ::file::patha locale_schema_matter(::ace::application * papp,const string & strLocale = cnull,const string & strStyle = cnull,const ::file::path & pszRoot = cnull,const ::file::path & pszApp = cnull);
         virtual ::file::patha locale_schema_matter(const string & strLocator, const string & strLocale = cnull, const string & strStyle = cnull);
         virtual ::file::path matter(::ace::application * papp,const ::file::patha & stra,bool bDir = false,const ::file::path & pszRoot = cnull,const ::file::path & pszApp = cnull);
         virtual ::file::path matter(::ace::application * papp,const ::file::path & path,bool bDir = false,const ::file::path & pszRoot = cnull,const ::file::path & pszApp = cnull);

         virtual ::file::path appmatter(string strApp, ::file::path pathRel);

         virtual void   matter_ls(::ace::application * papp, const ::file::path & str, ::file::patha & stra);
         virtual void   matter_ls_file(::ace::application * papp,const ::file::path & str,::file::patha & stra);

         //virtual ::file::path matter(::ace::application * papp);

         virtual ::file::path matter_from_locator(::ace::str_context * pcontext,const string & strLocator,const ::file::path & str);
         virtual void appmatter_locators(::file::path & strRoot,::file::path & strDomain,::ace::application * papp);
         virtual void appmatter_locators(::file::path & strRoot,::file::path & strDomain,const string & strLibraryName,const string & strAppName);
         virtual void appmatter_locators(::file::path & strRoot,::file::path & strDomain,const string & strAppName);
         virtual ::file::path appmatter_locator(::ace::application * papp);
         virtual ::file::path appmatter_locator(const string & strLibraryName,const string & strAppName);
         virtual ::file::path appmatter_locator(const string & strAppName);
         virtual ::file::path base_appmatter_locator(const ::file::path & strBase,const string & strLibraryName,const string & strAppName);
         virtual ::file::path base_appmatter_locator(const ::file::path & strBase,const string & strAppName);



         virtual ::file::path trash_that_is_not_trash(const ::file::path & psz);

         virtual ::file::path appdata();
         virtual ::file::path commonappdata_root();
         virtual ::file::path commonappdata();
         virtual ::file::path element_commonappdata(const string & strElement);

         virtual ::file::path usersystemappdata(::ace::application * papp,const string & lpcszPrefix);
         virtual ::file::path userappdata(::ace::application * papp);
         virtual ::file::path userdata(::ace::application * papp);
         virtual ::file::path userfolder(::ace::application * papp);
         virtual ::file::path default_os_user_path_prefix(::ace::application * papp);
         virtual ::file::path default_userappdata(::ace::application * papp,const string & lpcszPrefix,const string & lpcszLogin);
         virtual ::file::path default_userdata(::ace::application * papp,const string & lpcszPrefix,const string & lpcszLogin);
         virtual ::file::path default_userfolder(::ace::application * papp,const string & lpcszPrefix,const string & lpcszLogin);
         virtual ::file::path userquicklaunch(::ace::application * papp);
         virtual ::file::path userprograms(::ace::application * papp);

         virtual ::file::path commonprograms();

         virtual ::file::path pathfind(const string & pszEnv,const string & pszTopic,const string & pszMode,::ace::application * papp);

         virtual bool initialize();

         virtual ::file::path get_api_cc();

         virtual bool update_module_path();



      };


      typedef smart_pointer < system > system_sp;


   } // namespace dir


} // namespace file
















