#pragma once


namespace dynamic_source
{


   class script;
   class script_instance;

   class script_compiler :
      virtual public ::radix::object,
      virtual public ::ex2::folder_watch::callback
   {
   public:


      enum ecpptype
      {
         cpptype_ds,
         cpptype_source,
         cpptype_include,
      };



      http::memory_file    m_memfileLibError;
      stringa              m_straLibSourcePath;
      stringa              m_straLibSourceRelPath;
      stringa              m_straLibCppPath;
      stringa              m_straLibIncludePath;
      stringa              m_straLibIncludeRelPath;
      stringa              m_straLibHppPath;
      string               m_strLibraryPath;


      string               m_strDynamicSourceConfiguration;


      ::ca::library        m_libraryLib;


      base_array < __time_t, __time_t & > m_ftaLibCreation;
      base_array < __time_t, __time_t & > m_ftaLibAccess;
      base_array < __time_t, __time_t & > m_ftaLibModified;


      stringa                 m_straSync;
      map_string_to_ptr       m_mapLib;
      string                  m_strLibsLibs;
      string                  m_strEnv;
      script_manager *  m_pmanager;
      mutex                   m_mutexLibrary;
      string                  m_strSdk1;
      string                  m_strPlatform;
      string                  m_strLibPlatform;
      ::ex2::folder_watch_sp  m_folderwatch;
      ::ex2::folder_watch_sp  m_folderwatchFribox;
      string                  m_strPlat1;
      string                  m_strTime;


      script_compiler(::ca::application * papp);
      virtual ~script_compiler(void);

      void initialize();
      void prepare_compile_and_link_environment();

      void run_persistent();

      bool defer_run_persistent(const char *psz);

      bool is_id(const char * psz, const char * pszId, strsize & iIdLen);
      const char * next_nonspace(const char * psz);

      void compile(ds_script * pscript);

      void cppize(ds_script * pscript);
      void cppize(const char * pszSource, const char * pszDest, ecpptype e_type);

      void cppize1(ds_script * pscript);
      void cppize1(const char * pszSource, const char * pszDest, ecpptype e_type);

      string cppize2(const char * pszSource, bool bScript, stringa & straId);

      string get_ds_print(const char *psz)   ;

      void folder_watch();

      void compile_library();
      void process_include(const char * pszInclude);

      bool library_DoesMatchVersion();
      void load_library();
      void unload_library();


      void on_file_action(::ex2::folder_watch::e_action eaction, const char * pszFolder, const char * psz);


      void prepare1(const char * pszSource, const char * pszDest);


   };



} // namespace dynamic_source


