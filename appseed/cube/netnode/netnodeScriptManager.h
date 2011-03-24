#pragma once

class netnodeScriptCache;
class netnodeScriptCompiler;
class netnodeScript;
class netnodeScriptInstance;

class CLASS_DECL_CA2_CUBE netnodeScriptManager :
   virtual public ::radix::thread,
   virtual public ::ca::message_window_simple_callback
{
public:

   class clear_include_matches_folder_watch
   {
   public:
      string                  m_strPath;
      netnodeScriptManager *  m_pmanager;
   };

   mutex m_mutexIncludeMatches;
   ::collection::map < string, string, bool, bool > m_mapIncludeMatchesFileExists;
   ::collection::map < string, string, bool, bool > m_mapIncludeMatchesIsDir;
   bool include_matches_file_exists(const char * pszPath);
   bool include_matches_is_dir(const char * pszPath);


   mutex m_mutexSimage;
   mutex m_mutexSpider;
   netnode::simage_accepta_ptr_array m_simageptra;
   match_host_ptr_array m_matchhostaSpider;
   __int64  m_iDatabaseWaitTimeOut;

   mutex m_mutexSession;
   ::collection::string_map < ::gen::property_set > m_mapSession;


   netnodeScriptManager(::ca::application * papp);
   ~netnodeScriptManager(void);

   bool initialize_instance();


   bool get_session(const char * pszId, ::gen::property_set & set);
   bool set_session(const char * pszId, ::gen::property_set & set);

   netnodeScriptInstance * get(const char * lpcszName);
   using ::radix::thread::handle;
   void handle(netnodeSocket * psocket);
   netnodeScriptInstance * get_output_internal(netnodeScriptImpl * pinstanceParent, const char * lpcszName);
   using thread::run;
   void run(const char * lpcszName);

   void LoadEnv();

   string get_library_build_log();

   critical_section           m_csMusicDbPool;
   critical_section           m_csCynceDbPool;
   netnodeScriptCache *         m_pcache;
   netnodeScriptCompiler *      m_pcompiler;
   ui_redir                   m_uiredir;
   DWORD                      m_dwBuildTimeWindow;
   DWORD                      m_dwBuildTimeRandomWindow;

   string_to_string_map       m_strmapFunUserKey;

   string                     m_strPersistentError;

   critical_section           m_csPersistentStr;
   critical_section           m_csUiRedir;
   mutex                     m_mutexTagId;
   string_to_string_map       m_tagid;
   string_to_string_map       m_usersecuretagid;
   mutex                     m_mutexTagName;
   string_to_string_map       m_tagname;
   base_array < comparable_array < fontopus_database * >> m_musicdba;
   comparable_array < cynce_database * > m_cyncedbptra;
   
   fontopus_database * new_musicdb(int iServer);
   void free_musicdb(fontopus_database * pdb);
   __int64 update_musicdb_list(int iServer);

   cynce_database * new_cyncedb();
   void free_cyncedb(cynce_database * pdb);
   __int64 update_cyncedb_list();

   fontopus_database * on_new_musicdb(int iServer);
   void on_free_musicdb(fontopus_database * pdb);

   cynce_database * on_new_cyncedb();
   void on_free_cyncedb(cynce_database * pdb);

   virtual void message_window_message_handler(gen::signal_object * pobj);

   void clear_include_matches();
   static UINT AFX_CDECL clear_include_matches_FolderWatchThread(LPVOID lpParam); // thread procedure

   virtual string real_path(const char * psz);
   virtual string real_path(const char * pszBase, const char * psz);

};
