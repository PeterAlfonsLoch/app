#pragma once


namespace axis
{


   class CLASS_DECL_AXIS application :
      virtual public application_interface
   {
   public:




      smart_pointer < application >                   m_pimpl;
      sp(service_base)                                m_pservice;

      bool                                            m_bAxisProcessInitialize;
      bool                                            m_bAxisProcessInitializeResult;

      bool                                            m_bAxisInitializeInstance;
      bool                                            m_bAxisInitializeInstanceResult;

      bool                                            m_bAxisInitialize1;
      bool                                            m_bAxisInitialize1Result;

      bool                                            m_bAxisInitialize;
      bool                                            m_bAxisInitializeResult;

      string_to_ptr                                   m_appmap;
      string                                          m_strAppName;
      allocatorsp                                     m_allocer;

      ::axis::main_init_data *            m_pinitmaindata;


      EExclusiveInstance                              m_eexclusiveinstance;

      sp(::mutex)                                     m_pmutexLocal;
      sp(::mutex)                                     m_pmutexLocalId;
      sp(::mutex)                                     m_pmutexGlobal;
      sp(::mutex)                                     m_pmutexGlobalId;



      string                                          m_strLibraryName;
      string                                          m_strAppId;
#ifdef WINDOWS
      HINSTANCE                                       m_hinstance;
#endif



      bool                                            m_bLicense;
      string                                          m_strAxisSupportId;
      int32_t                                         m_iWaitCursorCount;         // for wait cursor (>0 => waiting)



      // Initial state of the application's interaction_impl; normally,
      // this is an argument to ShowWindow().
      manual_reset_event *                            m_peventReady;
      string                                          m_strInstallToken;
      string                                          m_strInstallType;
      mutex                                           m_mutexMatterLocator;



      mutex                                           m_mutexStr;


      static UINT                                     APPM_LANGUAGE;
      static WPARAM                                   WPARAM_LANGUAGE_UPDATE;





      application();
      virtual ~application();


      virtual sp(element) alloc(sp(type) info);
      virtual sp(element) alloc(const id & idType);


      int32_t simple_message_box(const char * pszMessage,UINT fuStyle);
      virtual string message_box(const string & pszMatter,property_set & propertyset);





      virtual bool is_system();
      virtual bool is_session();
      virtual bool is_serviceable();






      


      virtual bool open_link(const string & strLink,const string & pszTarget = "");





      virtual void DoWaitCursor(int32_t nCode); // 0 => restore, 1=> begin, -1=> end
      virtual void ShowWaitCursor(bool bShow = true);


#ifndef METROWIN
      virtual void get_time(timeval *p);
#endif



      virtual bool verb();



      virtual bool app_map_lookup(const char * psz,void * &);
      virtual void app_map_set(const char * psz,void *);

      virtual bool Ex2OnAppInstall();
      virtual bool Ex2OnAppUninstall();


      template < class APP >
      APP & cast_app()
      {
         if(this == NULL)
            return (*(APP *)NULL);
         void * papp;
#ifdef WINDOWS
         if(!app_map_lookup(typeid(APP).name(),papp))
#else
         if(!app_map_lookup(typeid(APP).name(), papp))
#endif
         {
            papp = dynamic_cast <APP *> (this);
#ifdef WINDOWS
            app_map_set(typeid(APP).name(),papp);
#else
            app_map_set(typeid(APP).name(), papp);
#endif
         }
         return (*(APP *)papp);
      }

      virtual void _001CloseApplication();


      virtual string get_license_id();


      
      virtual void construct(const char * pszAppId);


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



      virtual bool update_module_paths();

      virtual string draw2d_get_default_library_name();
      virtual string multimedia_audio_get_default_library_name();
      virtual string multimedia_audio_mixer_get_default_library_name();
      virtual string veriwell_multimedia_music_midi_get_default_library_name();

      virtual string get_cred(const RECT & rect, string & strUsername,string & strPassword, string strToken, string strTitle, bool bInteractive);

      virtual bool get_temp_file_name_template(string & str,const char * pszName,const char * pszExtension,const char * pszTemplate);

      virtual bool get_temp_file_name(string & str,const char * pszName,const char * pszExtension);







      virtual bool final_handle_exception(::exception::exception & e);



      service_base * get_service();
      virtual service_base * allocate_new_service();
      virtual bool create_new_service();

      virtual bool create_service();
      virtual bool remove_service();

      virtual bool start_service();
      virtual bool stop_service();


      virtual void on_service_request(sp(::create_context) pcreatecontext);

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

      virtual void draw2d_factory_exchange();


      virtual void on_set_scalar(e_scalar escalar,int64_t iValue);
      virtual void get_scalar_minimum(e_scalar escalar,int64_t & i);
      virtual void get_scalar(e_scalar escalar,int64_t & i);
      virtual void get_scalar_maximum(e_scalar escalar,int64_t & i);



      bool safe_is_running();


      virtual void on_request(sp(::create_context) pcreatecontext);

      virtual bool defer_initialize_twf();



      void assert_user_logged_in();

      virtual bool init_main_data(::axis::main_init_data * pdata);

      virtual bool set_main_init_data(::axis::main_init_data * pdata);


   };






   class CLASS_DECL_AXIS application_ptra:
      virtual public spa(application)
   {
   public:


      application_ptra() { }


      application_ptra(const application_ptra & a):
         spa(application)(a)
      {

         }

      inline application_ptra & operator = (const application_ptra & a)
      {

         spa(application)::operator = (a);

         return *this;

      }


#if defined(MOVE_SEMANTICS)

      application_ptra(application_ptra && a):
         spa(application)(a)
      {

         }

      inline application_ptra & operator = (application_ptra && a)
      {

         spa(application)::operator = (a);

         return *this;

      }

#endif

      application * find_by_app_name(const string & strAppName);

      application * find_running_defer_try_quit_damaged(const string & strAppName);


      };




} // namespace axis



inline allocatorsp element::allocer()
{
   return m_pbaseapp->m_allocer;
}



