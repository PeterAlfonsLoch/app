#pragma once


typedef struct rsa_st RSA;

namespace webserver
{


   class simage_accepta;
   typedef base_array < simage_accepta * > simage_accepta_ptr_array;
   class match_host;
   typedef ::ca::smart_pointer_array < match_host > match_host_array;
   class ui_redir;
   class fontopus_database;
   class way_database;


} // namespace webserver



namespace dynamic_source
{


   class CLASS_DECL_ca script_manager :
      virtual public ::ca::thread,
      virtual public ::ca::message_window_simple_callback
   {
   public:

      
      class CLASS_DECL_ca clear_include_matches_folder_watch :
         public ::file_watcher::listener_thread
      
      {
      public:

         
         script_manager *              m_pmanager;
         
         
         virtual void handle_file_action(::file_watcher::id watchid, const char * dir, const char * filename, ::file_watcher::e_action eaction);
        
         
      };

      
      class CLASS_DECL_ca session :
         virtual public ::ca::object
      {
      public:


         session();


         mutex                   m_mutex;
         ::ca::property_set       m_set;


      };

      class CLASS_DECL_ca plugin_map_item :
         virtual public ::ca::ca
      {
      public:


         string         m_strHost;
         string         m_strScript;
         string         m_strPlugin;

         plugin_map_item();
         plugin_map_item(const plugin_map_item & item);


         plugin_map_item & operator = (const plugin_map_item & item);

      };

      class CLASS_DECL_ca tunnel_map_item
      {
      public:


         string         m_strServer;
         uint32_t          m_dwLast;


      };


      spa(plugin_map_item)                      m_pluginmapitema;

      mutex                                     m_mutexIncludeMatches;
      ::collection::string_map < bool >         m_mapIncludeMatchesFileExists;
      ::collection::string_map < bool >         m_mapIncludeMatchesIsDir;
      mutex                                     m_mutexIncludeHasScript;
      ::collection::string_map < bool >         m_mapIncludeHasScript;
      mutex                                     m_mutexIncludeExpandMd5;
      string_to_string_map                      m_mapIncludeExpandMd5;


      int32_t                                       m_iTunnelPluginCount;
      mutex                                     m_mutexOutLink;
      ::collection::string_map < ::sockets::link_out_socket * > 
                                                m_mapOutLink;
      mutex                                     m_mutexInLink;
      ::collection::map < ::sockets::link_out_socket *, ::sockets::link_out_socket *, ::sockets::link_in_socket *, ::sockets::link_in_socket * > 
                                                m_mapInLink;
      mutex                                     m_mutexTunnel;
      ::collection::string_map < tunnel_map_item > 
                                                m_mapTunnel;

      mutex                                     m_mutexImageSize;
      ::collection::string_map < size >         m_mapImageSize;




      string                                    m_strNamespace;
      string                                    m_strNetnodePath;
      string                                    m_strNetseedPath;
      string                                    m_strNetseedDsCa2Path;
                                               
      mutex                                     m_mutexSimage;
      mutex                                     m_mutexSpider;
                                               
      mutex                                     m_mutexRsa;
      
#ifdef MACOS
      
      raw_array < SecKeyRef >                   m_rsaptra;

#elif defined(BSD_STYLE_SOCKETS)

      raw_array < RSA * >                       m_rsaptra;

#else

      raw_array < ::Windows::Security::Cryptography::Core::CryptographicKey ^ > m_rsaptra;

#endif

      uint32_t                                     m_dwLastRsa;



      int64_t                                   m_iDatabaseWaitTimeOut;

      mutex                                     m_mutexSession;
      ::collection::string_map < session >      m_mapSession;
      mutex                                     m_mutexMusicDbPool;
      mutex                                     m_mutexWayDbPool;
      script_cache *                            m_pcache;
      script_compiler *                         m_pcompiler;
      uint32_t                                     m_dwBuildTimeWindow;
      uint32_t                                     m_dwBuildTimeRandomWindow;

      string_to_string_map                      m_strmapFunUserKey;

      string                                    m_strPersistentError;

      mutex                                     m_mutexPersistentStr;
      mutex                                     m_mutexUiRedir;
      mutex                                     m_mutexTagId;
      string_to_string_map                      m_tagid;
      string_to_string_map                      m_usersecuretagid;
      mutex                                     m_mutexTagName;
      string_to_string_map                      m_tagname;


      string                                    m_strSeed;


      script_manager(::ca::application * papp);
      ~script_manager();

      bool initialize_instance();

      bool include_matches_file_exists(const string & strPath);
      void set_include_matches_file_exists(const string & strPath, bool bFileExists);
      bool include_matches_is_dir(const string & strPath);
      bool include_has_script(const string & strPath);
      string include_expand_md5(const string & strPath);
      void set_include_expand_md5(const string & strPath, const string & strMd5);

      session * get_session(mutex * & pmutex, const char * pszId);


      script_instance * get(const string & strName);
      using ::ca::thread::handle;
      virtual void handle(::dynamic_source::httpd_socket * psocket);
      script_instance * get_output_internal(::dynamic_source::script_instance * pinstanceParent, const string & strName);
      using thread::run;
      void run(const char * lpcszName);

      void LoadEnv();

      string get_library_build_log();



      virtual void message_window_message_handler(::ca::signal_object * pobj);

      void clear_include_matches();
      static UINT c_cdecl clear_include_matches_FolderWatchThread(LPVOID lpParam); // thread procedure

      virtual string real_path(const string & str);
      virtual string real_path(const string & strBase, const string & str);


#ifdef MACOS
      
      SecKeyRef get_rsa_key();
      
#elif defined(BSD_STYLE_SOCKETS)

      RSA * get_rsa_key();

#else

      ::Windows::Security::Cryptography::Core::CryptographicKey ^ get_rsa_key();

#endif
      
      void calc_rsa_key();


      virtual void on_load_env();

      virtual void register_plugin(const char * pszHost, const char * pszScript, const char * pszName, script * pscript);


      virtual string get_root_plugin();


      void wait_link_out(const char * pszServer, ::sockets::link_in_socket * pinsocket);
      bool has_link_out_link(const char * pszServer, ::sockets::link_in_socket * pinsocket, ::sockets::httpd_socket * phttpdsocket);
      ::sockets::link_in_socket * get_link_in(const char * pszServer, ::sockets::link_out_socket * poutsocket);
      bool is_online(const char * pszServer);
      ::sockets::link_out_socket * create_link_out(const char * pszServer, ::sockets::httpd_socket * phttpdsocket);
      size get_image_size(const string & strFile);
      bool extract_image_size(const string & strFile, size * psize);


   };


} // namespace dynamic_source


