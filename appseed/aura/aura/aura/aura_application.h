#pragma once

namespace hotplugin
{
   class host;
   class plugin;
}

namespace aura
{


   class CLASS_DECL_AURA application :
      virtual public ::thread,
      virtual public int_scalar_source,
      virtual public ::file::listing_provider
   {
   public:

      // former ::aura::application_interface // moved on 2015-05-23 Sammstag while listening to RocketBeansTV (a German channel?) at TwitchTV
      ::aura::system *                                m_paurasystem;
      ::aura::session *                               m_paurasession;
      :: axis :: application *                        m_paxisapp; // can be used only from axis and upper
      :: axis ::system *                              m_paxissystem; // can be used only from axis and upper
      :: axis ::session *                             m_paxissession; // can be used only from axis and upper
      :: base :: application *                        m_pbaseapp; // can be used only from base and upper
      ::base::system *                                m_pbasesystem; // can be used only from base and upper
      ::base::session *                               m_pbasesession; // can be used only from base and upper
      ::core::application *                           m_pcoreapp; // can be used only from core and upper
      ::core::system *                                m_pcoresystem; // can be used only from core and upper
      ::core::session *                               m_pcoresession; // can be used only from core and upper



      smart_pointer < application >                   m_pimpl;
      sp(ipi)                                         m_pipi;
      sp(service_base)                                m_pservice;

      bool                                            m_bAuraProcessInitialize;
      bool                                            m_bAuraProcessInitializeResult;

      bool                                            m_bAuraInitializeInstance;
      bool                                            m_bAuraInitializeInstanceResult;

      bool                                            m_bAuraInitialize1;
      bool                                            m_bAuraInitialize1Result;

      bool                                            m_bAuraInitialize;
      bool                                            m_bAuraInitializeResult;

      string_to_ptr                                   m_appmap;
      string                                          m_strAppName;
      ::aura::allocatorsp                                       m_allocer;
      sp(::command_thread)                            m_pcommandthread;
      sp(class signal)                                m_psignal;

      ::aura::main_init_data *                        m_pinitmaindata;


      EExclusiveInstance                              m_eexclusiveinstance;

      sp(::mutex)                                     m_pmutexLocal;
      sp(::mutex)                                     m_pmutexLocalId;
      sp(::mutex)                                     m_pmutexGlobal;
      sp(::mutex)                                     m_pmutexGlobalId;

      bool                                   m_bService;



      ::file::patha                                   m_straMatterLocator;
      string                                          m_strLibraryName;
      string                                          m_strAppId;

      HINSTANCE                                       m_hinstance;


      bool                                            m_bUpdateMatterOnInstall;


      bool                                            m_bLicense;
      string                                          m_strBaseSupportId;


      string                                          m_strRoot;
      string                                          m_strDomain;
      string                                          m_strLocale;
      string                                          m_strSchema;

      // Initial state of the application's interaction_impl; normally,
      // this is an argument to ShowWindow().
      manual_reset_event *                            m_peventReady;
      string                                          m_strInstallToken;
      string                                          m_strInstallType;
      mutex                                           m_mutexMatterLocator;



      mutex                                           m_mutexStr;
      string_table                                    m_stringtable;
      string_table                                    m_stringtableStd;


      ::file::dir::application_sp                     m_spdir;
      ::file::application_sp                          m_spfile;
      application_bias                       m_biasCalling;


      application();
      virtual ~application();


      virtual void install_message_handling(::message::dispatch * pdispatch);


      virtual object * alloc(sp(type) info);
      virtual object * alloc(const id & idType);

      template < typename T >
      void alloc(T * & pt);
      template < typename T >
      T * alloc(sp(type) info)
      {
         object * p = alloc(info);
         if(p == NULL)
            return NULL;
         T * pt = dynamic_cast <T *>(p);
         if(pt == NULL)
         {
            ::release(p);
            return NULL;
         }
         return pt;
      }
      template < typename T >
      T * alloc(const id & idType)
      {
         object * p = alloc(idType);
         if(p == NULL)
            return NULL;
         T * pt = dynamic_cast <T *>(p);
         if(pt == NULL)
         {
            ::release(p);
            return NULL;
         }
         return pt;
      }


      //virtual void tellme_destroyed(::user::primitive * pui, bool * pDestroyed, bool bTell = true);


      virtual int32_t simple_message_box(::user::primitive * puiOwner,const char * pszMessage,UINT fuStyle = MB_OK);
      virtual int32_t simple_message_box_timeout(::user::primitive * pwndOwner,const char * pszMessage,::duration durationTimeOut,UINT fuStyle);
      int32_t simple_message_box(const char * pszMessage,UINT fuStyle);
      virtual string message_box(const string & pszMatter,property_set & propertyset);


      virtual string load_string(id id);
      virtual bool load_string(string & str,id id);
      virtual void load_string_table();
      //   virtual string load_string(id id);
      // virtual bool load_string(string & str, id id);
      bool load_cached_string(string & str,id id,bool bLoadStringTable);
      bool load_cached_string_by_id(string & str,id id,const string & pszFallbackValue,bool bLoadStringTable);
      void load_string_table(const string & pszApp,const string & pszId);

      virtual int32_t hotplugin_host_starter_start_sync(const char * pszCommandLine,::aura::application * papp,hotplugin::host * phost,hotplugin::plugin * pplugin = NULL);

      inline class ::file::dir::application &   dir()          { return *m_spdir; }
      inline class ::file::application &        file()         { return *m_spfile; }

      virtual bool on_run_exception(::exception::exception & e);
      virtual bool handle_not_installed(::not_installed & notinstalled);

      virtual bool is_system();
      virtual bool is_session();
      virtual bool is_serviceable();
      virtual bool is_user_service();

      void process_machine_event_data(machine_event_data * pdata);

      virtual bool open_link(const string & strLink,const string & pszTarget = "");


      virtual void DoWaitCursor(int32_t nCode); // 0 => restore, 1=> begin, -1=> end
      virtual void ShowWaitCursor(bool bShow = true);


#ifndef METROWIN

      virtual void get_time(timeval *p);

#endif

      virtual void process_message_filter(int32_t code,signal_details * pobj);

      virtual bool on_thread_on_idle(::thread_impl * pimpl,LONG lCount);
      virtual bool post_user_message(::thread_impl * pimpl,::user::primitive * pui,UINT message,WPARAM wparam = 0,lparam lparam = cnull);

      virtual bool is_window(::user::primitive * pui);
      virtual LRESULT send_message(::user::primitive * pui, UINT message, WPARAM wparam = 0, lparam lparam = NULL);
      virtual oswindow get_safe_handle(::user::primitive * pui);
      virtual void dispatch_user_message(::signal_details * pobj);
      virtual ::user::primitive * get_parent(::user::primitive * pui);
      virtual bool enable_window(::user::primitive * pui, bool bEnable = true);
      virtual bool set_window_text(::user::primitive * pui, const string & strText);
      virtual ptr_array < thread > get_thread(::user::primitive * pui);
      virtual void add_thread(::user::primitive * pui,::thread * pthread);
      virtual void remove_thread(::user::primitive * pui,::thread * pthread);
      virtual void window_graphics_update_window(window_graphics **  ppdata,oswindow interaction_impl,COLORREF * pOsBitmapData,const RECT & rect,int cxParam,int cyParam,int iStride = -1,bool bTransferBuffer = true);


      //virtual ::user::primitive * get_active_guie();
      //virtual ::user::primitive * get_focus_guie();


      // Wall-eeeeee aliases
      ::command_thread * command_central();
      ::command_thread * command_thread();
      ::command_thread * guideline();
      ::command_thread * command();
      ::command_thread * directrix();
      ::command_thread * axiom();
      ::command_thread * creation();





      virtual bool verb();



      virtual bool app_map_lookup(const char * psz,void * &);
      virtual void app_map_set(const char * psz,void *);

      virtual bool Ex2OnAppInstall();
      virtual bool Ex2OnAppUninstall();


      template < class APP >
      APP & cast_app()
      {
         return *dynamic_cast < APP * > (this);
      }

      virtual void _001CloseApplication();


      virtual string get_license_id();



      virtual void construct(const char * pszAppId);

#ifndef METROWIN
      virtual ::aura::ipi * create_ipi();
#endif

      virtual bool process_initialize();

      virtual bool initialize1();
      virtual bool initialize2();
      virtual bool initialize3();

      virtual bool initialize_instance();
      virtual int32_t exit_instance();

      virtual bool initialize();
      virtual bool finalize();

      bool ca_process_initialize();
      bool ca_initialize1();
      bool ca_initialize2();
      bool ca_initialize3();

      bool ca_finalize();

      virtual bool is_installing();
      virtual bool is_uninstalling();


      virtual int32_t run();

      virtual bool pre_run();
      virtual int32_t main();
      virtual int32_t on_run();
      virtual int32_t application_pre_run();
      virtual bool initial_check_directrix();
      virtual bool os_native_bergedge_start();

      virtual bool InitApplication();

      virtual bool on_install();
      virtual bool on_uninstall();


      virtual bool system_add_app_install(const char * pszId);





      virtual void TermThread(HINSTANCE hInstTerm);




      virtual string get_version();

      virtual void SetCurrentHandles();

      virtual void set_env_var(const string & var,const string & value);
      virtual uint32_t get_thread_id();


      virtual bool _001OnDDECommand(const char * lpcsz);
      virtual void _001EnableShellOpen();
      //virtual ::user::document *  _001OpenDocumentFile(var varFile);
      virtual void _001OnFileNew(signal_details * pobj);


      //virtual bool update_module_paths();

      virtual string draw2d_get_default_library_name();
      virtual string multimedia_audio_get_default_library_name();
      virtual string multimedia_audio_mixer_get_default_library_name();
      virtual string veriwell_multimedia_music_midi_get_default_library_name();

      virtual string get_cred(const string & strRequestUrl,const RECT & rect,string & strUsername,string & strPassword,string strToken,string strTitle,bool bInteractive);

      virtual bool get_temp_file_name_template(string & str,const char * pszName,const char * pszExtension,const char * pszTemplate);

      virtual bool get_temp_file_name(string & str,const char * pszName,const char * pszExtension);





      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      virtual bool final_handle_exception(::exception::exception & e);



      service_base * get_service();
      virtual service_base * allocate_new_service();
      virtual bool create_new_service();

      virtual bool create_service();
      virtual bool remove_service();

      virtual bool start_service();
      virtual bool stop_service();


      virtual void on_service_request(sp(::create) pcreatecontext);

      virtual sp(application) assert_running(const char * pszAppId);

      virtual bool is_running();

      virtual string get_mutex_name_gen();

      virtual void on_exclusive_instance_conflict(EExclusiveInstance eexclusive);
      virtual void on_exclusive_instance_local_conflict();

      virtual string get_local_mutex_id();
      virtual string get_global_mutex_id();

      virtual ::mutex * get_local_mutex();
      virtual ::mutex * get_global_mutex();

      virtual string get_local_mutex_name(const char * pszAppName);
      virtual string get_local_id_mutex_name(const char * pszAppName,const char * pszId);
      virtual string get_global_mutex_name(const char * pszAppName);
      virtual string get_global_id_mutex_name(const char * pszAppName,const char * pszId);

      virtual string get_local_mutex_name();
      virtual string get_local_id_mutex_name();
      virtual string get_global_mutex_name();
      virtual string get_global_id_mutex_name();

      virtual bool check_exclusive();
      virtual bool release_exclusive();

      virtual void on_set_scalar(e_scalar escalar,int64_t iValue,int iFlags);
      virtual void get_scalar_minimum(e_scalar escalar,int64_t & i);
      virtual void get_scalar(e_scalar escalar,int64_t & i);
      virtual void get_scalar_maximum(e_scalar escalar,int64_t & i);



      bool safe_is_running();


      virtual void on_request(sp(::create) pcreatecontext);

      // name by Mummi (Japanese -> Guddo : from English : Good, ca2 interpretation : Goods).
      // get/set serializables to user directory
      bool gudo_get(const string & strKey,::file::serializable & obj);
      bool gudo_set(const string & strKey,::file::serializable & obj);


      virtual bool assert_user_logged_in();

      virtual bool init_main_data(::aura::main_init_data * pdata);

      virtual bool set_main_init_data(::aura::main_init_data * pdata);


      //virtual void dir_matter_ls_file(const string & str,stringa & stra);
      //virtual string matter_as_string(const char * pszMatter,const char * pszMatter2 = NULL);
      //virtual string file().as_string(var varFile);
      //virtual string file().as_string(var varFile,var & varQuery);
      //virtual string dir().matter(const char * pszMatter,const char * pszMatter2 = NULL);
      //virtual bool is_inside_time_dir(const char * pszPath);
      //virtual bool file_is_read_only(const char * pszPath);
      //virtual bool file().exists(const char * pszPath);
      //virtual bool file_is_equal_path(const char * pszPath1,const char * pszPath2);
      //virtual bool dir().id(const char * psz);
      //virtual bool file_del(const char * psz);
      //virtual string file_extension(const char * pszPath);
      //virtual string dir_path(const char * psz1,const char * psz2,const char * psz3 = NULL);
      //virtual string dir_element(const char * psz = NULL);
      //virtual string dir_ca2module(const char * psz = NULL);
      //virtual string dir_name(const char * psz);
      //virtual void  dir_ls_dir(const char * lpcsz,::file::patha & patha);
      //virtual void  dir_rls(const char * lpcsz,::file::patha & patha);
      //virtual bool dir_mk(const char * psz);
      //virtual string file_title(const char * psz);
      //virtual string file().name_(const char * psz);
      //virtual string file_time_square();
      //virtual string dir_userappdata(const char * lpcsz = NULL,const char * lpcsz2 = NULL);
      //virtual string dir_appdata(const char * lpcsz = NULL,const char * lpcsz2 = NULL);
      //virtual string dir_simple_path(const string & str1,const string & str2);

//#ifdef APPLEOS
//      virtual CLASS_DECL_AURA string dir_pathfind(const char * pszEnv, const char * pszTopic, const char * pszMode);
//#endif

      //virtual ::file::buffer_sp file_get_file(var varFile,uint32_t uiFlags);

      virtual string http_get_locale_schema(const char * pszUrl,const char * pszLocale,const char * pszSchema);

      virtual sp(::message::base) get_message_base(LPMESSAGE lpmsg);

      virtual void process_message(signal_details * pobj);

      virtual void message_handler(signal_details * pobj);


      virtual string get_locale();
      virtual string get_schema();
      virtual ::file::path get_locale_schema_dir(const string & strLocale,const string & strSchema);
      virtual ::file::path get_locale_schema_dir(const string & strLocale);
      virtual ::file::path get_locale_schema_dir();

      virtual void set_locale(const string & lpcsz,::action::context actioncontext);
      virtual void set_schema(const string & lpcsz,::action::context actioncontext);
      virtual void on_set_locale(const string & lpcsz,::action::context actioncontext);
      virtual void on_set_schema(const string & lpcsz,::action::context actioncontext);


      virtual void fill_locale_schema(::str::international::locale_schema & localeschema);
      virtual void fill_locale_schema(::str::international::locale_schema & localeschema,const string & pszLocale,const string & pszSchema);


      virtual void defer_add_thread_run_wait(sync_object_ptra & soa);


      DECL_GEN_SIGNAL(_001OnApplicationRequest);







      virtual bool platform_open_by_file_extension(int iEdge, const char * pszPathName,application_bias * pbiasCreate = NULL);
      virtual bool platform_open_by_file_extension(int iEdge,::create * pcc);


      virtual sp(::aura::application) instantiate_application(const char * pszType,const char * pszId,application_bias * pbias);
      virtual sp(::aura::application) create_application(const char * pszType,const char * pszId,bool bSynch,application_bias * pbias);
      virtual ::aura::application * create_platform(::aura::session * psession);
      virtual bool start_application(bool bSynch,application_bias * pbias);

      virtual bool is_application();

      virtual ::file::listing & perform_file_listing(::file::listing & listing) override;

   };









} // namespace aura



