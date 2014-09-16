#pragma once


namespace core
{


   class CLASS_DECL_CORE system :
      virtual public ::core::application,
      virtual public ::base::system
      #ifdef LINUX
      , virtual public ::exception::translator
      #endif
   {
   public:


      //core::platform::run_start_installer *        m_prunstartinstaller;
      //core::platform::map *                        m_pbergedgemap;
      index                                        m_iNewEdge;

      mutex                                        m_mutex;
      sp(::filehandler::handler)                   m_spfilehandler;


      mutex                                        m_mutexDelete;
      class ::core::stra                           m_stra;
      class ::core::service                        m_service;

      class ::core::patch                          m_patch;
      ::net::email_departament                     m_emaildepartament;

      sp(::core::platform::run_start_installer)    m_prunstartinstaller;
      sp(::core::platform::map)                    m_pbergedgemap;
      spa(::core::platform)                        m_planesessionptra;


      sp(class ::core::history)                    m_phistory;
      //      ::sockets::net                               m_net;
      //      sp(::core::filehandler::handler)  m_spfilehandler;


      // certain instantiators like npca2plugin and iexca2plugin rely
      // on the functionality of these variables cached information,
      // to avoid multiple initialization.
      bool                                         m_bInitApplication;
      bool                                         m_bInitApplicationResult;
      bool                                         m_bProcessInitialize;
      bool                                         m_bProcessInitializeResult;


      strid_map < ::aura::library * >              m_idmapCreateViewLibrary;

      comparable_array < ::aura::library * >       m_libraryptra;

#ifdef METROWIN
      Platform::Agile < Windows::UI::Core::CoreWindow > m_window;
#endif


      system(sp(::aura::application) papp = NULL);
      virtual ~system();


      virtual void construct(const char * pszAppId);

      virtual void discard_to_factory(sp(element) pca);

      virtual bool is_system();

      virtual bool process_initialize();

      virtual bool initialize2();

      virtual bool initialize_instance();

      virtual bool finalize();

      virtual int32_t exit_instance();



      //virtual int32_t main();
      virtual bool InitApplication();

      virtual bool initialize();
      virtual bool initialize1();
      virtual bool initialize3();

      virtual bool bergedge_start();


      virtual index get_new_bergedge(application_bias * pbiasCreation = NULL);

      spa(::core::platform) &    planesessionptra();
      inline sp(::html::html)                   html()         { return m_phtml; }


      virtual bool base_support();


      DECL_GEN_SIGNAL(on_application_signal);


      bool set_history(::core::history * phistory);


      virtual sp(::core::platform)             get_session(index iEdge,application_bias * pbiasCreation = NULL);


      virtual void on_request(sp(::create_context) pcreatecontext);

      //      virtual sp(::command_thread) command_thread();





      //virtual int32_t main();




      virtual void on_allocation_error(::aura::application * papp,sp(type) info);


      ::core::stra                           & stra();
      ::core::service                        & service();
      ::core::history                        & hist();

      class ::core::patch                    & patch();

      ::http::system                         & http();
      ::net::email_departament               & email();

      ::filehandler::handler                 & filehandler();

      






      bool sync_load_url(string & str,const char * lpszUrl,::fontopus::user * puser = NULL,::http::cookies * pcookies = NULL);




      uint32_t guess_code_page(const string & str);

#ifdef METROWIN

      virtual bool GetWindowRect(LPRECT lprect);

#endif

      virtual void post_fork_uri(const char * pszUri,application_bias * pbiasCreate);

      sp(::aura::session) query_session(index iEdge);

      virtual bool wait_twf(uint32_t dwTimeOut = INFINITE);





      virtual bool find_applications_from_cache();
      virtual bool find_applications_to_cache();
      virtual bool map_application_library(const char * pszLibrary);


      sp(::user::document) place_hold(sp(::user::interaction) pui);



      virtual bool on_install();

      virtual string get_host_location_url();

      virtual bool add_library(::aura::library * plibrary);

      //virtual void get_cursor_pos(LPPOINT lppoint);


      virtual bool set_main_init_data(::aura::main_init_data * pdata);



      void assert_valid() const;
      void dump(dump_context & context) const;

      virtual int32_t main();


   };


} // namespace core








void CLASS_DECL_CORE __start_core_system(::base::system * psystem);




