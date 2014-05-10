#pragma once


namespace dynamic_source
{


   class script;
   class script_instance;

   class script_compiler :
      virtual public ::object,
      virtual public ::file_watcher::listener_thread
   {
   public:


      enum ecpptype
      {
         cpptype_ds,
         cpptype_source,
         cpptype_include,
      };



      file::plain_text_stream_memory_buffer     m_memfileLibError;
      stringa                                   m_straLibSourcePath;
      stringa                                   m_straLibSourceRelPath;
      stringa                                   m_straLibCppPath;
      stringa                                   m_straLibIncludePath;
      stringa                                   m_straLibIncludeRelPath;
      stringa                                   m_straLibHppPath;
      string                                    m_strLibraryPath;
                                                
      uint32_t                                  m_dwLastLibraryVersionCheck;
      bool                                      m_bLastLibraryVersionCheck;
                                                
                                                
      string                                    m_strDynamicSourceConfiguration;
                                                
                                                
      base_library                             m_libraryLib;


      raw_array < __time_t >                    m_ftaLibCreation;
      raw_array < __time_t >                    m_ftaLibAccess;
      raw_array < __time_t >                    m_ftaLibModified;
                                                
                                                
      stringa                                   m_straSync;
      map_string_to_ptr                         m_mapLib;
      string                                    m_strLibsLibs;
      string                                    m_strEnv;
      sp(script_manager)                        m_pmanager;
      mutex                                     m_mutexLibrary;
      string                                    m_strSdk1;
      string                                    m_strPlatform;
      string                                    m_strLibPlatform;
      //::file_watcher::thread                  m_folderwatch;
      ::file_watcher::id                        m_filewatchid;
      ::file_watcher::id                        m_filewatchidFribox;
                                               
      string                                    m_strPlat1;
      string                                    m_strTime;


      script_compiler(sp(::base::application) papp);
      virtual ~script_compiler();

      void initialize();
      void prepare_compile_and_link_environment();

      void run_persistent();

      bool defer_run_persistent(const char *psz);

      bool is_id(const char * psz, strsize iLen, const char * pszId, strsize iLenId, strsize & iIdLen);
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


      virtual void handle_file_action(::file_watcher::id watchid, const char * dir, const char * filename, ::file_watcher::e_action action);


      void prepare1(const char * pszSource, const char * pszDest);


   };



} // namespace dynamic_source


