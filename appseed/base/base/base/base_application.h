#pragma once

CLASS_DECL_BASE void set_splash(oswindow oswindow);
CLASS_DECL_BASE oswindow get_splash();

enum EExclusiveInstance
{

   ExclusiveInstanceNone,
   ExclusiveInstanceLocal,
   ExclusiveInstanceLocalId,
   ExclusiveInstanceGlobal,
   ExclusiveInstanceGlobalId,
   ExclusiveInstanceLicense

};


enum e_application_signal
{

   application_signal_initialize1, // cgcl // first initialization
   application_signal_initialize2, // cst  // second initialization
   application_signal_initialize3, // third initialization and so on...
   application_signal_initialize, // last initialization
   application_signal_start,
   application_signal_process_initialize,
   application_signal_finalize,
   application_signal_exit_instance,
   application_signal_init_application,
   application_signal_none

};


class machine_event_data;
namespace html
{
   class html;
} // namespace html




class CLASS_DECL_BASE application_signal_details :
   public signal_details
{
public:


   e_application_signal             m_esignal;
   int32_t                          m_iRet;
   bool                             m_bOk;


   application_signal_details(sp(base_application) papp, class ::signal * psignal, e_application_signal esignal);


};



class CLASS_DECL_BASE base_application :
   virtual public thread,
   virtual public ::core::live_object,
   virtual public command_target_interface,
   virtual public request_interface,
   virtual public message_queue,
   virtual public int_scalar_source
{
public:




   smart_pointer < base_application >              m_pimpl;
   sp(service_base)                                m_pservice;



   base_system *                                   m_pbasesystem;
   base_session *                                  m_pbasesession;
   ::application *                                 m_pplaneapp; // can be used only from core and upper
   string_to_ptr                                   m_appmap;
   string                                          m_strAppName;
   allocatorsp                                     m_allocer;
   sp(::command_thread)                            m_pcommandthread;
   sp(class signal)                                m_psignal;

   ::html::html *                                  m_phtml; // only defined  in core;


   EExclusiveInstance                              m_eexclusiveinstance;

   sp(::mutex)                                     m_pmutexLocal;
   sp(::mutex)                                     m_pmutexLocalId;
   sp(::mutex)                                     m_pmutexGlobal;
   sp(::mutex)                                     m_pmutexGlobalId;


   sp(::fs::fs)                                    m_spfs;
   class ::http::application                       m_http;
   sp(::fontopus::fontopus)                        m_pfontopus;
   class ::file::dir::application                  m_dir;
   class ::file::application                       m_file;
   sp(math::math)                                  m_pmath;
   sp(geometry::geometry)                          m_pgeometry;
   sp(::sockets::sockets)                          m_psockets;
   sp(class ::fs::data)                            m_spfsdata;
   bool                                            m_bZipIsDir;
   stringa                                         m_straMatterLocator;
   sp(::user::str_context)                         m_puserstrcontext;
   string                                          m_strLibraryName;
   string                                          m_strAppId;
   sp(::user::interaction_ptr_array)               m_pframea;
   sp(::user::user)                                m_spuser;
   sp(::database::server)                          m_spdataserver;
#ifdef WINDOWS
   HINSTANCE                                       m_hinstance;
#endif
   map < ::user::e_key, ::user::e_key, bool, bool > *                            m_pmapKeyPressed;


   bool                                            m_bUpdateMatterOnInstall;


   bool                                            m_bLicense;
   string                                          m_strBaseSupportId;
   sp(class ::fontopus::license)                   m_splicense;
   int32_t                                         m_iWaitCursorCount;         // for wait cursor (>0 => waiting)
   HCURSOR                                         m_hcurWaitCursorRestore; // old cursor to restore after wait cursor


   string                                          m_strRoot;
   string                                          m_strDomain;
   string                                          m_strLocale;
   string                                          m_strSchema;

   bool                                            m_bSessionSynchronizedCursor;
   point                                           m_ptCursor;
   rect                                            m_rectScreen;
   bool                                            m_bSessionSynchronizedScreen;
   sp(core::savings)                               m_psavings;

   string                                          m_strCa2ModulePath;
   string                                          m_strCa2ModuleFolder;
   string                                          m_strModulePath;
   string                                          m_strModuleFolder;

   string                                          m_strCmdLine;
   // Initial state of the application's window; normally,
   // this is an argument to ShowWindow().
   int32_t                                         m_nCmdShow;
   size_t                                          m_nSafetyPoolSize;      // ideal size
   manual_reset_event *                            m_peventReady;
   string                                          m_strInstallToken;
   string                                          m_strInstallType;
   bool                                            m_bIfs;
   mutex                                           m_mutexMatterLocator;



   mutex                                           m_mutexStr;
   string_table                                    m_stringtable;
   string_table                                    m_stringtableStd;


   static UINT                                     APPM_LANGUAGE;
   static WPARAM                                   WPARAM_LANGUAGE_UPDATE;

   bool                                            m_bBaseProcessInitialize;
   bool                                            m_bBaseInitializeInstance;


   //int64_t                                         m_iProgressInstallStart;
   //int64_t                                         m_iProgressInstallStep;
   //int64_t                                         m_iProgressInstallEnd;


   base_application();
   virtual ~base_application();


   virtual sp(element) alloc(sp(type) info);
   virtual sp(element) alloc(const id & idType);


   virtual int32_t simple_message_box(sp(::user::interaction) puiOwner, const char * pszMessage, UINT fuStyle = MB_OK);
   virtual int32_t simple_message_box_timeout(sp(::user::interaction) pwndOwner, const char * pszMessage, ::duration durationTimeOut, UINT fuStyle);
   int32_t simple_message_box(const char * pszMessage, UINT fuStyle);
   virtual string message_box(const string & pszMatter, property_set & propertyset);


   virtual string load_string(id id);
   virtual bool load_string(string & str, id id);
   virtual void load_string_table();
//   virtual string load_string(id id);
  // virtual bool load_string(string & str, id id);
   bool load_cached_string(string & str, id id, bool bLoadStringTable);
   bool load_cached_string_by_id(string & str, id id, const string & pszFallbackValue, bool bLoadStringTable);
   void load_string_table(const string & pszApp, const string & pszId);



   virtual bool is_system();
   virtual bool is_session();
   virtual bool is_serviceable();


   virtual bool init_main_data(::core::main_init_data * pdata);




   ::core::savings &                         savings();
   inline class ::http::application &        http()         { return m_http; }
   inline class ::file::dir::application &   dir()          { return m_dir; }
   inline class ::file::application &        file()         { return m_file; }
   inline sp(::fontopus::fontopus)           fontopus()     { return m_pfontopus; }
   inline ::sockets::sockets &               sockets()      { return *m_psockets; }
   inline sp(class ::user::user)             user()         { return m_spuser; }
   math::math &                              math();
   geometry::geometry &                      geometry();
   inline class ::fontopus::license &        license()      { return *m_splicense; }
   inline sp(class ::fs::data)               fs()           { return m_spfsdata; }
   inline ::database::server &               dataserver()   { return *m_spdataserver;  }


   ::user::str_context *                     str_context();


   virtual ::fontopus::user * safe_get_user();
   virtual ::fontopus::user * get_user();
   virtual ::fontopus::user * create_current_user();


   virtual bool is_licensed(const char * pszId, bool bInteractive = true);
   virtual string get_license_id();


   virtual bool do_prompt_file_name(var & varFile, UINT nIDSTitle, uint32_t lFlags, bool bOpenFileDialog, sp(::user::impact_system) ptemplate, sp(::user::object) pdocument);


   virtual void get_cursor_pos(LPPOINT lppoint);

   virtual sp(::user::interaction) release_capture_uie();
   virtual sp(::user::interaction) get_capture_uie();


   void process(machine_event_data * pdata);



   virtual bool open_link(const string & strLink, const string & pszTarget = "");




   ::user::interaction_ptr_array & frames();
   virtual void add_frame(sp(::user::interaction) pwnd);
   virtual void remove_frame(sp(::user::interaction) pwnd);

   virtual void DoWaitCursor(int32_t nCode); // 0 => restore, 1=> begin, -1=> end
   virtual void ShowWaitCursor(bool bShow = true);


#ifndef METROWIN
   virtual void get_time(timeval *p);
#endif


   virtual string get_locale();
   virtual string get_schema();
   virtual string get_locale_schema_dir(const string & strLocale, const string & strSchema);
   virtual string get_locale_schema_dir(const string & strLocale);
   virtual string get_locale_schema_dir();



   virtual void set_locale(const string & lpcsz, ::action::context actioncontext);
   virtual void set_schema(const string & lpcsz, ::action::context actioncontext);
   virtual void on_set_locale(const string & lpcsz, ::action::context actioncontext);
   virtual void on_set_schema(const string & lpcsz, ::action::context actioncontext);




   //   virtual string matter_as_string(const char * pszMatter, const char * pszMatter2 = NULL);
   //   virtual string dir_matter(const char * pszMatter, const char * pszMatter2 = NULL);
   virtual bool is_inside_time_dir(const char * pszPath);
   virtual bool file_is_read_only(const char * pszPath);
   virtual string file_as_string(var varFile);
   virtual string dir_path(const char * psz1, const char * psz2, const char * psz3 = NULL);
   virtual string dir_name(const char * psz);
   virtual bool dir_mk(const char * psz);
   virtual string file_title(const char * psz);
   virtual string file_name(const char * psz);

   ::file::binary_buffer_sp file_get_file(var varFile, uint32_t uiFlags);


   // Wall-eeeeee aliases
   sp(::command_thread) command_central();
   sp(::command_thread) command_thread();
   sp(::command_thread) guideline();
   sp(::command_thread) command();
   sp(::command_thread) directrix();
   sp(::command_thread) axiom();
   sp(::command_thread) creation();





   //virtual void on_allocation_error(const sp(type) info);
   //virtual sp(element) on_alloc(const sp(type) info);

   virtual bool verb();



   virtual bool app_map_lookup(const char * psz, void * &);
   virtual void app_map_set(const char * psz, void *);

   virtual bool Ex2OnAppInstall();
   virtual bool Ex2OnAppUninstall();


   template < class APP >
   APP & cast_app()
   {
      if (this == NULL)
         return (*(APP *)NULL);
      void * papp;
#ifdef WINDOWS
      if (!app_map_lookup(typeid(APP).name(), papp))
#else
      if(!app_map_lookup(typeid(APP).name(), papp))
#endif
      {
         papp = dynamic_cast <APP *> (this);
#ifdef WINDOWS
         app_map_set(typeid(APP).name(), papp);
#else
         app_map_set(typeid(APP).name(), papp);
#endif
      }
      return (*(APP *)papp);
   }

   virtual void _001CloseApplication();


   virtual thread * GetThread();

   virtual bool get_auth(const string & pszForm, string & strUsername, string & strPassword);


   sp(::user::interaction) get_active_guie();
   sp(::user::interaction) get_focus_guie();

   virtual ::count get_monitor_count();
   virtual bool  get_monitor_rect(index i, LPRECT lprect);
   virtual ::count get_desk_monitor_count();
   virtual bool  get_desk_monitor_rect(index i, LPRECT lprect);


   virtual bool is_key_pressed(::user::e_key ekey);
   virtual void set_key_pressed(::user::e_key ekey, bool bPressed);

#ifdef METROWIN
   virtual sp(::user::interaction) window_from_os_data(void * pdata);
   virtual sp(::user::interaction) window_from_os_data_permanent(void * pdata);
#else
   virtual sp(window) window_from_os_data(void * pdata);
   virtual sp(window) window_from_os_data_permanent(void * pdata);
#endif


   using ::thread::construct;
   virtual void construct();


   virtual bool process_initialize();

   virtual bool initialize1();
   virtual bool initialize2();
   virtual bool initialize3();

   virtual bool initialize_instance();
   virtual int32_t exit_instance();

   virtual bool initialize();

   bool ca_process_initialize();
   bool ca_initialize1();
   bool ca_initialize2();
   bool ca_initialize3();

   bool ca_finalize();

   virtual bool is_installing();
   virtual bool is_uninstalling();


   virtual int32_t run();

   virtual int32_t main();
   virtual bool main_start();
   virtual int32_t on_run();
   virtual int32_t pre_run();
   virtual bool initial_check_directrix();
   virtual bool os_native_bergedge_start();

   virtual bool InitApplication();

   virtual bool on_install();
   virtual bool on_uninstall();


   virtual bool system_add_app_install(const char * pszId);


   virtual void fill_locale_schema(::str::international::locale_schema & localeschema);
   virtual void fill_locale_schema(::str::international::locale_schema & localeschema, const char * pszLocale, const char * pszSchema);


   virtual bool update_appmatter(::sockets::socket_handler & h, ::sockets::http_session * & psession, const char * pszRoot, const char * pszRelative);
   virtual bool update_appmatter(::sockets::socket_handler & h, ::sockets::http_session * & psession, const char * pszRoot, const char * pszRelative, const char * pszLocale, const char * pszStyle);


   virtual void LockTempMaps();
   virtual bool UnlockTempMaps(bool bDeleteTemps = TRUE);
   virtual void TermThread(HINSTANCE hInstTerm);



   virtual sp(window) FindWindow(const char * lpszClassName, const char * lpszWindowName);
   virtual sp(window) FindWindowEx(oswindow oswindowParent, oswindow oswindowChildAfter, const char * lpszClass, const char * lpszWindow);

   virtual string get_version();

   virtual void set_thread(thread * pthread);

   virtual void SetCurrentHandles();

   virtual void set_env_var(const string & var, const string & value);
   virtual uint32_t get_thread_id();


   virtual bool set_main_init_data(::core::main_init_data * pdata);


   virtual bool _001OnDDECommand(const char * lpcsz);
   virtual void _001EnableShellOpen();
   virtual sp(::user::object) _001OpenDocumentFile(var varFile);
   virtual void _001OnFileNew(signal_details * pobj);

   virtual sp(::user::printer) get_printer(const char * pszDeviceName);


   virtual bool update_module_paths();

   virtual string draw2d_get_default_library_name();
   virtual string multimedia_audio_get_default_library_name();
   virtual string multimedia_audio_mixer_get_default_library_name();
   virtual string veriwell_multimedia_music_midi_get_default_library_name();

   virtual string show_auth_window(LPRECT lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strFontopusServer);
   virtual bool get_temp_file_name_template(string & str, const char * pszName, const char * pszExtension, const char * pszTemplate);

   virtual bool get_temp_file_name(string & str, const char * pszName, const char * pszExtension);


   virtual void get_screen_rect(LPRECT lprect);

   virtual void Ex1OnFactoryExchange();

   virtual string get_ca2_module_folder();
   virtual string get_ca2_module_file_path();
   virtual string get_module_folder();
   virtual string get_module_file_path();
   virtual string get_module_title();
   virtual string get_module_name();



   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;

   virtual ::visual::icon * set_icon(object * pobject, ::visual::icon * picon, bool bBigIcon);
   virtual ::visual::icon * get_icon(object * pobject, bool bBigIcon) const;

   virtual bool final_handle_exception(::exception::exception & e);

   virtual ::fontopus::fontopus * create_fontopus();
   virtual ::user::user * create_user();


   service_base * get_service();
   virtual service_base * allocate_new_service();
   virtual bool create_new_service();

   virtual bool create_service();
   virtual bool remove_service();

   virtual bool start_service();
   virtual bool stop_service();


   virtual void on_service_request(sp(::create_context) pcreatecontext);

   virtual sp(::base_application) assert_running(const char * pszAppId);

   virtual bool is_running();

   virtual string get_mutex_name_gen();

   virtual void on_exclusive_instance_conflict(EExclusiveInstance eexclusive);
   virtual void on_exclusive_instance_local_conflict();

   virtual string get_local_mutex_id();
   virtual string get_global_mutex_id();

   virtual ::mutex * get_local_mutex();
   virtual ::mutex * get_global_mutex();

   virtual string get_local_mutex_name(const char * pszAppName);
   virtual string get_local_id_mutex_name(const char * pszAppName, const char * pszId);
   virtual string get_global_mutex_name(const char * pszAppName);
   virtual string get_global_id_mutex_name(const char * pszAppName, const char * pszId);

   virtual string get_local_mutex_name();
   virtual string get_local_id_mutex_name();
   virtual string get_global_mutex_name();
   virtual string get_global_id_mutex_name();

   virtual bool check_exclusive();
   virtual bool release_exclusive();

   virtual void draw2d_factory_exchange();


   virtual void on_set_scalar(e_scalar escalar, int64_t iValue);
   virtual void get_scalar_minimum(e_scalar escalar, int64_t & i);
   virtual void get_scalar(e_scalar escalar, int64_t & i);
   virtual void get_scalar_maximum(e_scalar escalar, int64_t & i);

   virtual void message_queue_message_handler(signal_details * pobj);


   bool safe_is_running();


   virtual void on_request(sp(::create_context) pcreatecontext);


};




inline allocatorsp element::allocer()
{
   return m_pbaseapp->m_allocer;
}



inline sp(::command_thread) object::command_thread()
{

   return m_pbaseapp->command_thread();

}



class CLASS_DECL_BASE application_ptra :
   virtual public spa(base_application)
{
public:


   application_ptra() { }


   application_ptra(const application_ptra & a) :
      spa(base_application)(a)
   {

   }

   inline application_ptra & operator = (const application_ptra & a)
   {

      spa(base_application)::operator = (a);

      return *this;

   }


#if defined(MOVE_SEMANTICS)

   application_ptra(application_ptra && a) :
      spa(base_application)(a)
   {

   }

   inline application_ptra & operator = (application_ptra && a)
   {

      spa(base_application)::operator = (a);

      return *this;

   }

#endif

   base_application * find_by_app_name(const string & strAppName);

   base_application * find_running_defer_try_quit_damaged(const string & strAppName);

};




