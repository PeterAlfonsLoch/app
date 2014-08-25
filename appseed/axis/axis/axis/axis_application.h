#pragma once


namespace axis
{


   class CLASS_DECL_AXIS application :
      virtual public ::aura::application
   {
   public:


      bool                                            m_bAxisProcessInitialize;
      bool                                            m_bAxisProcessInitializeResult;

      bool                                            m_bAxisInitializeInstance;
      bool                                            m_bAxisInitializeInstanceResult;

      bool                                            m_bAxisInitialize1;
      bool                                            m_bAxisInitialize1Result;

      bool                                            m_bAxisInitialize;
      bool                                            m_bAxisInitializeResult;

      synch_ptr_array < ::user::interaction >         m_framea;
      sp(::database::server)                          m_spdataserver;

      bool                                            m_bUpdateMatterOnInstall;


      int32_t                                         m_iWaitCursorCount;         // for wait cursor (>0 => waiting)






      static UINT                                     APPM_LANGUAGE;
      static WPARAM                                   WPARAM_LANGUAGE_UPDATE;

      bool                                            m_bShouldInitializeGTwf;
      sp(::user::interaction)                         m_pwndMain;
      bool                                            m_bInitializeProDevianMode;




      application();
      virtual ~application();


      
      inline ::database::server &               dataserver()   { return *m_spdataserver; }



      virtual int32_t simple_message_box_timeout(sp(::user::interaction) pwndOwner,const char * pszMessage,::duration durationTimeOut,UINT fuStyle);




      virtual bool is_system();
      virtual bool is_session();
      virtual bool is_serviceable();


      virtual ::user::user * create_user();



      virtual bool do_prompt_file_name(var & varFile,UINT nIDSTitle,uint32_t lFlags,bool bOpenFileDialog,sp(::user::impact_system) ptemplate,sp(::user::document) pdocument);


      virtual sp(::user::interaction) release_capture_uie();
      virtual sp(::user::interaction) get_capture_uie();


      //void process_machine_event_data(machine_event_data * pdata);



      virtual void process_message_filter(int32_t code,signal_details * pobj);

      ptr_array < ::user::interaction > frames();
      virtual void add_frame(sp(::user::interaction) pwnd);
      virtual void remove_frame(sp(::user::interaction) pwnd);


      virtual void DoWaitCursor(int32_t nCode); // 0 => restore, 1=> begin, -1=> end
      virtual void ShowWaitCursor(bool bShow = true);


#ifndef METROWIN
      virtual void get_time(timeval *p);
#endif

      virtual bool on_thread_on_idle(::thread_impl * pimpl,LONG lCount);
      virtual bool post_user_message(::thread_impl * pimpl,::user::interaction * pui,UINT message,WPARAM wparam = 0,lparam lparam = 0);
      virtual void message_handler(::thread_impl * pimpl,signal_details * pobj);


      virtual bool is_window(::user::interaction * pui);
      virtual LRESULT send_message(::user::interaction * pui,UINT message,WPARAM wparam = 0,lparam lparam = 0);
      virtual oswindow get_safe_handle(::user::interaction * pui);
      virtual void dispatch_user_message(::message::base * pbase);
      virtual ::user::interaction * get_parent(::user::interaction * pui);
      virtual bool enable_window(::user::interaction * pui,bool bEnable = true);
      virtual bool set_window_text(::user::interaction * pui,const string & strText);
      virtual ::thread * get_thread(::user::interaction * pui);
      virtual void set_thread(::user::interaction * pui,::thread * pthread);









      //virtual void on_allocation_error(const sp(type) info);
      //virtual sp(element) on_alloc(const sp(type) info);

      virtual bool verb();




      virtual bool Ex2OnAppInstall();
      virtual bool Ex2OnAppUninstall();




      virtual void _001CloseApplication();


      virtual string get_license_id();


      virtual ::user::interaction * get_active_guie();
      virtual ::user::interaction * get_focus_guie();


      virtual ::user::interaction * window_from_os_data(void * pdata);


      virtual void construct(const char * pszAppId);


      virtual bool process_initialize();

      virtual bool initialize1();
      virtual bool initialize2();
      virtual bool initialize3();

      virtual bool initialize_instance();
      virtual int32_t exit_instance();

      virtual bool initialize();
      virtual bool finalize();


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



      virtual sp(::user::interaction) FindWindow(const char * lpszClassName,const char * lpszWindowName);
      virtual sp(::user::interaction) FindWindowEx(oswindow oswindowParent,oswindow oswindowChildAfter,const char * lpszClass,const char * lpszWindow);

      virtual string get_version();

      virtual void SetCurrentHandles();

      virtual void set_env_var(const string & var,const string & value);
      virtual uint32_t get_thread_id();


      virtual bool _001OnDDECommand(const char * lpcsz);
      virtual void _001EnableShellOpen();
      virtual ::user::document * _001OpenDocumentFile(var varFile);
      virtual void _001OnFileNew(signal_details * pobj);

      virtual sp(::user::printer) get_printer(const char * pszDeviceName);


      virtual bool update_module_paths();

      virtual string draw2d_get_default_library_name();
      virtual string multimedia_audio_get_default_library_name();
      virtual string multimedia_audio_mixer_get_default_library_name();
      virtual string veriwell_multimedia_music_midi_get_default_library_name();

      virtual string get_cred(const RECT & rect, string & strUsername,string & strPassword, string strToken, string strTitle, bool bInteractive);

      virtual bool get_temp_file_name_template(string & str,const char * pszName,const char * pszExtension,const char * pszTemplate);

      virtual bool get_temp_file_name(string & str,const char * pszName,const char * pszExtension);





      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      virtual ::visual::icon * set_icon(object * pobject,::visual::icon * picon,bool bBigIcon);
      virtual ::visual::icon * get_icon(object * pobject,bool bBigIcon) const;

      virtual bool final_handle_exception(::exception::exception & e);




      virtual void on_service_request(sp(::create_context) pcreatecontext);


      virtual string get_mutex_name_gen();

      virtual void on_exclusive_instance_conflict(EExclusiveInstance eexclusive);
      virtual void on_exclusive_instance_local_conflict();



      virtual void draw2d_factory_exchange();


      virtual void on_request(sp(::create_context) pcreatecontext);

      virtual bool defer_initialize_twf();



      virtual bool assert_user_logged_in();

      //virtual bool init_main_data(::aura::main_init_data * pdata);

      //virtual bool set_main_init_data(::aura::main_init_data * pdata);

      virtual sp(::message::base) get_message_base(LPMESSAGE lpmsg);


   };


} // namespace axis






