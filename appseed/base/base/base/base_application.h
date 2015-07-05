#pragma once


namespace base
{


   class CLASS_DECL_BASE application :
      virtual public ::axis::application
   {
   public:


      bool                                            m_bBaseProcessInitialize;
      bool                                            m_bBaseProcessInitializeResult;

      bool                                            m_bBaseInitializeInstance;
      bool                                            m_bBaseInitializeInstanceResult;

      bool                                            m_bBaseInitialize1;
      bool                                            m_bBaseInitialize1Result;

      bool                                            m_bBaseInitialize;
      bool                                            m_bBaseInitializeResult;



      application();
      virtual ~application();


      virtual ::user::interaction * get_active_guie();
      virtual ::user::interaction * get_focus_guie();


      virtual ::user::interaction * window_from_os_data(void * pdata);

      virtual sp(::user::interaction) release_capture_uie();
      virtual sp(::user::interaction) get_capture_uie();




      virtual sp(type) user_default_controltype_to_typeinfo(::user::e_control_type e_type);


//      inline ::database::server &               dataserver()   { return *(m_spdataserver.m_p); }
//
//      //virtual void tellme_destroyed(::user::interaction * pui, bool * pDestroyed, bool bTell = true);
//
//      //virtual int32_t simple_message_box_timeout(sp(::user::interaction) pwndOwner,const char * pszMessage,::duration durationTimeOut,UINT fuStyle);
//
//
//
//
//      virtual bool is_system();
//      virtual bool is_session();
//      virtual bool is_serviceable();
//
//
//      virtual ::user::user * create_user();
//
//
//      virtual ::user::interaction * main_window();
//
//
//      virtual void on_create_keyboard();
//
//
//      virtual int32_t simple_message_box(::user::primitive * puiOwner,const char * pszMessage,UINT fuStyle = MB_OK);
//      virtual int32_t simple_message_box_timeout(::user::primitive * pwndOwner,const char * pszMessage,::duration durationTimeOut,UINT fuStyle);
//      int32_t simple_message_box(const char * pszMessage,UINT fuStyle);
//      virtual string message_box(const string & pszMatter,property_set & propertyset);
//
//
//
//      virtual bool do_prompt_file_name(var & varFile,UINT nIDSTitle,uint32_t lFlags,bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument);
//
//
//      virtual sp(::user::interaction) release_capture_uie();
//      virtual sp(::user::interaction) get_capture_uie();
//
//
//      //void process_machine_event_data(machine_event_data * pdata);
//
//
//
//      virtual void process_message_filter(int32_t code,signal_details * pobj);
//
//      virtual bool get_frame(::user::interaction * & pui);
//      virtual void add_frame(sp(::user::interaction) pwnd);
//      virtual void remove_frame(sp(::user::interaction) pwnd);
//
//
//      virtual void DoWaitCursor(int32_t nCode); // 0 => restore, 1=> begin, -1=> end
//      virtual void ShowWaitCursor(bool bShow = true);
//
//
//#ifndef METROWIN
//      virtual void get_time(timeval *p);
//#endif
//
//      virtual bool on_thread_on_idle(::thread_impl * pimpl,LONG lCount);
//      virtual bool post_user_message(::thread_impl * pimpl,::user::primitive * pui,UINT message,WPARAM wparam = 0,lparam lparam = 0);
//
//
//      virtual bool is_window(::user::primitive * pui);
//      virtual LRESULT send_message(::user::primitive * pui,UINT message,WPARAM wparam = 0,lparam lparam = 0);
//      virtual oswindow get_safe_handle(::user::primitive * pui);
//      virtual void dispatch_user_message(::signal_details * pbase);
//      virtual ::user::interaction * get_parent(::user::interaction * pui);
//      virtual bool enable_window(::user::primitive * pui,bool bEnable = true);
//      virtual bool set_window_text(::user::interaction * pui,const string & strText);
//      virtual ptr_array < ::thread > get_thread(::user::primitive * pui);
//      virtual void add_thread(::user::primitive * pui,::thread * pthread);
//      virtual void remove_thread(::user::primitive * pui,::thread * pthread);
//      virtual void window_graphics_update_window(window_graphics * & pdata,oswindow interaction_impl,COLORREF * pOsBitmapData,const RECT & rect,int cxParam, int cyParam, int iStride = -1);
//
//
//
//
//
//
//
//
//
//      virtual bool verb();
//
//
//
//
//      virtual bool Ex2OnAppInstall();
//      virtual bool Ex2OnAppUninstall();
//
//
//
//
//      virtual void _001CloseApplication();
//
//
//      virtual string get_license_id();
//
//
//      virtual ::user::interaction * get_active_guie();
//      virtual ::user::interaction * get_focus_guie();
//
//
//      virtual ::user::interaction * window_from_os_data(void * pdata);
//
//
//      virtual void construct(const char * pszAppId);
//
//
//      virtual bool process_initialize();
//
//      virtual bool initialize1();
//      virtual bool initialize2();
//      virtual bool initialize3();
//
//      virtual bool initialize_instance();
//      virtual int32_t exit_instance();
//
//      virtual bool initialize();
//      virtual bool finalize();
//
//
//
//
//      virtual int32_t run();
//
//      virtual bool pre_run();
//      virtual int32_t main();
//      virtual int32_t on_run();
//      virtual int32_t application_pre_run();
//      virtual bool initial_check_directrix();
//      virtual bool os_native_bergedge_start();
//
//      virtual bool InitApplication();
//
//      virtual bool on_install();
//      virtual bool on_uninstall();
//
//
//      virtual bool system_add_app_install(const char * pszId);
//
//
//
//
//
//      virtual void TermThread(HINSTANCE hInstTerm);
//
//
//
//      virtual sp(::user::interaction) FindWindow(const char * lpszClassName,const char * lpszWindowName);
//      virtual sp(::user::interaction) FindWindowEx(oswindow oswindowParent,oswindow oswindowChildAfter,const char * lpszClass,const char * lpszWindow);
//
//      virtual string get_version();
//
//      virtual void SetCurrentHandles();
//
//      virtual void set_env_var(const string & var,const string & value);
//      virtual uint32_t get_thread_id();
//
//
//      //virtual bool _001OnDDECommand(const char * lpcsz);
//      //virtual void _001EnableShellOpen();
//      //virtual ::user::document * _001OpenDocumentFile(var varFile);
//      //virtual void _001OnFileNew(signal_details * pobj);
//
//      virtual sp(::aura::printer) get_printer(const char * pszDeviceName);
//
//
//      virtual bool update_module_paths();
//
//
//      virtual string get_cred(const string & strRequestUrl,const RECT & rect,string & strUsername,string & strPassword,string strToken,string strTitle,bool bInteractive);
//
//      virtual bool get_temp_file_name_template(string & str,const char * pszName,const char * pszExtension,const char * pszTemplate);
//
//      virtual bool get_temp_file_name(string & str,const char * pszName,const char * pszExtension);
//
//      virtual void assert_valid() const;
//
//      virtual void dump(dump_context & dumpcontext) const;
//
//      virtual ::visual::icon * set_icon(object * pobject,::visual::icon * picon,bool bBigIcon);
//
//      virtual ::visual::icon * get_icon(object * pobject,bool bBigIcon) const;
//
//      virtual bool final_handle_exception(::exception::exception & e);
//
//      virtual void on_service_request(sp(::create) pcreatecontext);
//
//      virtual string get_mutex_name_gen();
//
//      virtual void on_exclusive_instance_conflict(EExclusiveInstance eexclusive);
//
//      virtual void on_exclusive_instance_local_conflict();
//
//      virtual void draw2d_factory_exchange();
//
//      virtual void on_request(sp(::create) pcreatecontext);
//
//      virtual bool defer_initialize_twf();
//
//      virtual bool assert_user_logged_in();
//
//      virtual sp(::message::base) get_message_base(LPMESSAGE lpmsg);
//
//      virtual void process_message(signal_details * pobj);
//
//      //virtual ::user::interaction * get_active_guie();
//      //virtual ::user::interaction * get_focus_guie();
//
//      virtual bool set_keyboard_layout(const char * pszPath,::action::context actioncontext);
//      virtual sp(type) user_default_controltype_to_typeinfo(::user::e_control_type e_type);
//      virtual int32_t hotplugin_host_starter_start_sync(const char * pszCommandLine,::aura::application * papp,hotplugin::host * phost,hotplugin::plugin * pplugin = NULL) override;

virtual ::user::interaction * main_window();


      void process_message_filter(int32_t code,signal_details * pobj);

      virtual bool get_frame(::user::interaction * & pui);
      virtual void add_frame(sp(::user::interaction) pwnd);
      virtual void remove_frame(sp(::user::interaction) pwnd);

      virtual string get_cred(const string & strRequestUrl,const RECT & rect,string & strUsername,string & strPassword,string strToken,string strTitle,bool bInteractive);

      virtual ::user::user * create_user();

      virtual bool on_thread_on_idle(::thread_impl * pimpl,LONG lCount);

      virtual bool is_window(::user::primitive * pui);
      virtual LRESULT send_message(::user::primitive * pui,UINT message,WPARAM wparam = 0,lparam lparam = 0);
      virtual oswindow get_safe_handle(::user::primitive * pui);
      virtual void dispatch_user_message(::signal_details * pbase);
      virtual ::user::interaction * get_parent(::user::interaction * pui);
      virtual bool enable_window(::user::primitive * pui,bool bEnable = true);
      virtual bool set_window_text(::user::interaction * pui,const string & strText);
      virtual ptr_array < ::thread > get_thread(::user::primitive * pui);
      virtual void add_thread(::user::primitive * pui,::thread * pthread);
      virtual void remove_thread(::user::primitive * pui,::thread * pthread);
      virtual void window_graphics_update_window(window_graphics * & pdata,oswindow interaction_impl,COLORREF * pOsBitmapData,const RECT & rect,int cxParam,int cyParam,int iStride = -1,bool bTransferBuffer = true);

      virtual void process_message(signal_details * pobj);


      int32_t hotplugin_host_host_starter_start_sync(const char * pszCommandLine,::aura::application * papp,host * phost,plugin * pplugin);



   };


} // namespace base






