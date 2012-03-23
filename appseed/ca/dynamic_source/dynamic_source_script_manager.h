#pragma once


typedef struct rsa_st RSA;

namespace webserver
{


   class simage_accepta;
   typedef base_array < simage_accepta * > simage_accepta_ptr_array;
   class match_host;
   typedef array_del_ptr < match_host > match_host_array;
   class ui_redir;
   class fontopus_database;
   class cynce_database;


} // namespace webserver



namespace dynamic_source
{


   class CLASS_DECL_ca script_manager :
      virtual public ::radix::thread,
      virtual public ::ca::message_window_simple_callback
   {
   public:

      class clear_include_matches_folder_watch
      {
      public:
         string                  m_strPath;
         script_manager *  m_pmanager;
      };

      class session :
         virtual public ::radix::object
      {
      public:


         mutex                   m_mutex;
         gen::property_set       m_set;


      };

      mutex m_mutexIncludeMatches;
      ::collection::string_map < bool > m_mapIncludeMatchesFileExists;
      ::collection::string_map < bool > m_mapIncludeMatchesIsDir;
      mutex m_mutexIncludeHasScript;
      ::collection::string_map < bool > m_mapIncludeHasScript;
      mutex m_mutexIncludeExpandMd5;
      string_to_string_map             m_mapIncludeExpandMd5;






      string                  m_strNetnodePath;
      string                  m_strNetseedPath;

      mutex                   m_mutexSimage;
      mutex                   m_mutexSpider;

      mutex                   m_mutexRsa;
      raw_array < RSA * >     m_rsaptra;
      DWORD                   m_dwLastRsa;

      webserver::simage_accepta_ptr_array * m_psimageptra;
      webserver::match_host_array * m_pmatchhostaSpider;
      __int64  m_iDatabaseWaitTimeOut;

      mutex                                     m_mutexSession;
      ::collection::string_map < session >      m_mapSession;
      mutex                                     m_mutexMusicDbPool;
      mutex                                     m_mutexCynceDbPool;
      script_cache *                            m_pcache;
      script_compiler *                         m_pcompiler;
      webserver::ui_redir *                     m_puiredir;
      DWORD                                     m_dwBuildTimeWindow;
      DWORD                                     m_dwBuildTimeRandomWindow;

      string_to_string_map                      m_strmapFunUserKey;

      string                                    m_strPersistentError;

      mutex                                     m_mutexPersistentStr;
      mutex                                     m_mutexUiRedir;
      mutex                                     m_mutexTagId;
      string_to_string_map                      m_tagid;
      string_to_string_map                      m_usersecuretagid;
      mutex                                     m_mutexTagName;
      string_to_string_map                      m_tagname;

      base_array < comparable_array < ::webserver::fontopus_database * > > m_musicdba;
      comparable_array < ::webserver::cynce_database * > m_cyncedbptra;


      script_manager(::ca::application * papp);
      ~script_manager(void);

      bool initialize_instance();

      bool include_matches_file_exists(const string & strPath);
      void set_include_matches_file_exists(const string & strPath, bool bFileExists);
      bool include_matches_is_dir(const string & strPath);
      bool include_has_script(const string & strPath);
      string include_expand_md5(const string & strPath);
      void set_include_expand_md5(const string & strPath, const string & strMd5);

      session * get_session(mutex * & pmutex, const char * pszId);


      script_instance * get(const char * lpcszName);
      using ::radix::thread::handle;
      void handle(::netnode::socket * psocket);
      script_instance * get_output_internal(script_impl * pinstanceParent, const char * lpcszName);
      using thread::run;
      void run(const char * lpcszName);

      void LoadEnv();

      string get_library_build_log();


      webserver::fontopus_database * new_musicdb(int iServer);
      void free_musicdb(webserver::fontopus_database * pdb);
      __int64 update_musicdb_list(int iServer);

      webserver::cynce_database * new_cyncedb();
      void free_cyncedb(webserver::cynce_database * pdb);
      __int64 update_cyncedb_list();

      webserver::fontopus_database * on_new_musicdb(int iServer);
      void on_free_musicdb(webserver::fontopus_database * pdb);

      webserver::cynce_database * on_new_cyncedb();
      void on_free_cyncedb(webserver::cynce_database * pdb);

      virtual void message_window_message_handler(gen::signal_object * pobj);

      void clear_include_matches();
      static UINT AFX_CDECL clear_include_matches_FolderWatchThread(LPVOID lpParam); // thread procedure

      virtual string real_path(const char * psz);
      virtual string real_path(const char * pszBase, const char * psz);


      RSA * get_rsa_key();
      void calc_rsa_key();

   };


} // namespace dynamic_source


