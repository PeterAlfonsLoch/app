#pragma once



namespace axis
{


   class CLASS_DECL_AXIS system:
      virtual public ::aura::system,
      virtual public ::axis::application
   {
   public:


      //::url::departament                           m_urldepartament;


      ::http::system                               m_httpsystem;


      ::crypto::crypto_sp                          m_spcrypto;
      sp(::install::install)                       m_spinstall;



      ::visual::visual                             m_visual;

      class ::fontopus::user_set                   m_userset;


      ::net::email_departament                     m_emaildepartament;

#if defined METROWIN && defined(__cplusplus_winrt)

      class os_data
      {
      public:

         sp(::user::interaction)                      m_pui;
         ::axis::system_window ^                      m_pwindow;


      };

#elif defined(APPLE_IOS)
      class os_data
      {
      public:

         sp(::user::interaction)                      m_pui;


      };

#elif defined(VSNORD)

      class os_data
      {
      public:

         sp(::user::interaction)                      m_pui;
         oswindow                                     m_oswindow;


      };

#else

      class os_data;

#endif

      //      ::user::interaction *                        m_psimpleui;
      os_data *                                    m_posdata;



      string_map < int_to_string >                 m_mapEnumToName;
      string_map < string_to_int >                 m_mapNameToEnum;
      ::user::window_draw *                        m_ptwf;



      ::aura::library                              m_libraryDraw2d;


      bool                                         m_bSystemSynchronizedCursor;
      bool                                         m_bSystemSynchronizedScreen;


#ifdef WINDOWSEX


      ::axis::system_interaction_impl *            m_psystemwindow;

      raw_array < MONITORINFO >                    m_monitorinfoa;
      raw_array < HMONITOR >                       m_hmonitora;
      raw_array < MONITORINFO >                    m_monitorinfoaDesk;

#endif

      ::user::schema *                             m_pschemaLayeredFrame;



      system(::aura::application * papp);
      virtual ~system();






      virtual void construct(const char * pszAppId);

      virtual bool initialize_instance();

      virtual int32_t exit_instance();
      virtual bool finalize();

      //::url::departament                           & url()     { return m_urldepartament; }

      inline class ::http::system                  & http()    { return m_httpsystem; }

      class ::crypto::crypto                       & crypto();
      ::install::install                           & install() { return *m_spinstall; }

      inline class ::visual::visual                & visual()     { return m_visual       ; }

      ::fontopus::user_set                         & userset();

      ::net::email_departament               & email();


      virtual string install_get_platform() override;
      virtual void install_set_platform(const char * pszPlatform) override;
      virtual string install_get_version() override;
      virtual void install_set_version(const char * pszVersion) override;
      virtual string install_get_latest_build_number(const char * pszVersion) override;
      virtual int32_t install_start(const char * pszCommandLine,const char * pszBuild) override;
      virtual int32_t install_progress_app_add_up(int iAddUp = 1) override;

      virtual bool process_initialize();

      virtual bool initialize1();

      virtual bool initialize2();


      virtual bool verb();



      virtual ::file::path dir_appmatter_locator(::aura::application * papp);



      virtual bool is_system();


      virtual string crypto_md5_text(const string & str);




      virtual ::aura::session * on_create_session();

      virtual void on_request(sp(::create) pcreate);



      //virtual void construct(const char * pszAppId);

      //virtual bool initialize_instance();

      //virtual int32_t exit_instance();
      //virtual bool finalize();





      sp(::user::window_draw)                         get_twf();





      //virtual bool verb();





      //virtual bool process_initialize();

      //virtual bool initialize1();

      //virtual bool initialize2();

      //virtual mutex * wait_twf();

      virtual bool defer_create_system_frame_window();

      //virtual bool is_system();




      virtual ::user::document * place_hold(::user::interaction * pui);

      virtual sp(::aura::session) query_session(index iEdge);



      virtual bool initialize_twf();


      void enum_display_monitors();

#if defined(WINDOWS)
      static_function BOOL CALLBACK monitor_enum_proc(HMONITOR hmonitor,HDC hdcMonitor,LPRECT lprcMonitor,LPARAM dwData);
      void monitor_enum(HMONITOR hmonitor,HDC hdcMonitor,LPRECT lprcMonitor);
#endif

      virtual index get_main_monitor(LPRECT lprect = NULL);
      virtual ::count get_monitor_count();
      virtual bool  get_monitor_rect(index iMonitor,LPRECT lprect);
      virtual ::count get_desk_monitor_count();
      virtual bool  get_desk_monitor_rect(index iMonitor,LPRECT lprect);

      virtual index get_ui_wkspace(::user::interaction * pui);
      virtual index get_main_wkspace(LPRECT lprect = NULL);
      virtual ::count get_wkspace_count();
      virtual bool  get_wkspace_rect(index iWkspace,LPRECT lprect);
      virtual ::count get_desk_wkspace_count();
      virtual bool  get_desk_wkspace_rect(index iWkspace,LPRECT lprect);

      virtual ::user::interaction * get_active_guie();
      virtual ::user::interaction * get_focus_guie();

      /*
      virtual string get_ca2_module_folder();
      virtual string get_ca2_module_file_path();
      virtual string get_module_folder();
      virtual string get_module_file_path();
      virtual string get_module_title();
      virtual string get_module_name();
      */

      //virtual string dir_appmatter_locator(::aura::application * papp);



      virtual void hist_hist(const char * psz);


      //virtual void on_request(sp(::create) pcreate);

   };


} // namespace axis







void CLASS_DECL_AXIS __start_system(::axis::system * psystem);




