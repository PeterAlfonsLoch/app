#pragma once


namespace dynamic_source
{


   class script;
   class script_instance;

   class library  :
      virtual public ::object
   {
   public:
      mutex m_mutex;
      string m_strError;
      file::plain_text_stream_memory_buffer     m_memfileError;
            file::plain_text_stream_memory_buffer     m_memfileLibError;
          ::file::listing                             m_straLibSourcePath;
      ::file::patha                             m_straLibSourceRelPath;
        ::file::patha                             m_straLibCppPath;
      ::file::listing                             m_straLibIncludePath;
      ::file::patha                             m_straLibIncludeRelPath;
            ::file::patha                             m_straLibHppPath;
          ::file::path                              m_strLibraryPath;

        uint32_t                                  m_dwLastLibraryVersionCheck;
            bool                                      m_bLastLibraryVersionCheck;
            ::aura::library                           m_libraryLib;


            raw_array < __time_t >                    m_ftaLibCreation;
          raw_array < __time_t >                    m_ftaLibAccess;
        raw_array < __time_t >                    m_ftaLibModified;

        library(::aura::application * papp);
        virtual ~library();

          void load_library();
        void unload_library();
   };

   class CLASS_DECL_PROGRAMMING script_compiler :
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


      string_map < sp(library) > m_mapLib;



                                                
      string                                    m_strDynamicSourceConfiguration;
      ::file::path                              m_strDynamicSourceStage;
      ::file::path                              m_strDynamicSourceStageFolder;
                                                
                                                
      string      m_strLibPlatform;

                                                
      stringa                                   m_straSync;
//      map_string_to_ptr                         m_mapLib;
      string                                    m_strLibsLibs;
      string                                    m_strEnv;
      sp(script_manager)                        m_pmanager;
      string                                    m_strSdk1;
      string                                    m_strPlatform;
      string                                    m_strStagePlatform;
      ::file_watcher::id                        m_filewatchid;
      ::file_watcher::id                        m_filewatchidFribox;
                                               
      string                                    m_strPlat1;
      string                                    m_strPlat2;
      ::file::path                              m_strTime;


      mutex                                     m_mutex;

      mutex                                     m_mutexLibrary;


      script_compiler(::aura::application * papp);
      virtual ~script_compiler();

      void initialize();
      void prepare_compile_and_link_environment();

      void run_persistent();

      bool defer_run_persistent(const char *psz);

      bool is_id(const char * psz, strsize iLen, const char * pszId, strsize iLenId, strsize & iIdLen);
      const char * next_nonspace(const char * psz);

      void compile(ds_script * pscript);

      void cppize(ds_script * pscript);
      void cppize(const ::file::path & pszSource,const ::file::path & pszDest,ecpptype e_type);

      void cppize1(ds_script * pscript);
      void cppize1(const ::file::path & pszSource,const ::file::path & pszDest,ecpptype e_type);

      string cppize2(const string & pszSource,bool bScript,stringa & straId);

      string get_ds_print(const char *psz)   ;

      void folder_watch();

      library & lib(const char * pszLibrary);
      void process_include(const char * pszInclude);

  //    bool library_DoesMatchVersion();


      virtual void handle_file_action(::file_watcher::id watchid, const char * dir, const char * filename, ::file_watcher::e_action action);


      void prepare1(const char * pszSource, const char * pszDest);


      virtual void parse_pstr_set();

      virtual void pstr_set(id pszTopic,id idLocale,id idSchema,const char * psz);

   };



} // namespace dynamic_source


