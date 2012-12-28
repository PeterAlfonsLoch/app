#pragma once


namespace planebase
{


   class CLASS_DECL_ca application :
      virtual public ::fontopus::application
   {
   public:


      service_base *                      m_pservice;
      class ::ca::dir::application        m_dir;
      class ::ca::file::application       m_file;
      class ::ca4::http::application      m_http;

      sp(class ::fontopus::license)       m_splicense;
      sp(class ::fs::data)                m_spfsdata;

      bool                                m_bIfs;
      bool                                m_bUpdateMatterOnInstall;



      application();
      virtual ~application();



      virtual bool on_install();
      virtual bool on_uninstall();


      virtual bool is_serviceable();
      virtual bool is_installing();
      virtual bool is_uninstalling();


      virtual int32_t run();

      
      service_base * get_service();
      virtual service_base * allocate_new_service();
      virtual bool create_new_service();

      
      virtual bool create_service();
      virtual bool remove_service();

      virtual bool start_service();
      virtual bool stop_service();


      virtual void on_service_request(::ca::create_context * pcreatecontext);




      virtual int32_t exit_instance();


      inline class ::ca::dir::application       & dir()        { return m_dir       ; }
      inline class ::ca::file::application      & file()       { return m_file      ; }
      inline class ::ca4::http::application     & http()       { return m_http      ; }
      inline class ::fontopus::license          & license()    { return m_splicense ; }
      inline class ::fs::data                   * fs()         { return m_spfsdata  ; }


      
      virtual bool initialize();
      virtual bool initialize1();

      virtual void defer_initialize_twf();

      virtual int32_t pre_run();
      virtual int32_t on_run();

      virtual bool main_start();
      virtual int32_t main();
      virtual bool bergedge_start();
      virtual bool os_native_bergedge_start();


      virtual ::ca::application * instantiate_application(const char * pszType, const char * pszId, ::ca::application_bias * pbias);
      virtual ::ca::application * create_application(const char * pszType, const char * pszId, bool bSynch, ::ca::application_bias * pbias);

      virtual ::ex1::filesp get_file(var varFile, UINT nOpenFlags);
      virtual ::ex1::byte_stream get_byte_stream(var varFile, UINT nOpenFlags);

      // get a file and if there are exceptions, should show end user friendly messages
      virtual ::ex1::filesp friendly_get_file(var varFile, UINT nOpenFlags);

      virtual bool is_licensed(const char * pszId, bool bInteractive = true);

      //virtual ::user::interaction * get_request_parent_ui(gen::command_line * pline);

      virtual bool initial_check_directrix();





      virtual void set_title(const char * pszTitle);


      virtual FileManagerTemplate * GetStdFileManagerTemplate();



      //////////////////////////////////////////////////////////////////////////////////////////////////
      // System/Cube
      //
      ::document * hold(::user::interaction * pui);

      virtual count get_monitor_count();
      virtual bool  get_monitor_rect(index i, LPRECT lprect);
      virtual count get_desk_monitor_count();
      virtual bool  get_desk_monitor_rect(index i, LPRECT lprect);



      //////////////////////////////////////////////////////////////////////////////////////////////////
      // Session/Bergedge
      //
      virtual ::bergedge::view * get_view();
      virtual ::bergedge::document * get_document();


      virtual void fill_locale_schema(gen::international::locale_schema & localeschema);
      virtual void fill_locale_schema(gen::international::locale_schema & localeschema, const char * pszLocale, const char * pszSchema);

      virtual bool update_appmatter(::sockets::socket_handler & h, ::sockets::http_session * & psession, const char * pszRoot, const char * pszRelative);
      virtual bool update_appmatter(::sockets::socket_handler & h, ::sockets::http_session * & psession, const char * pszRoot, const char * pszRelative, const char * pszLocale, const char * pszStyle);


      virtual bool add_library(::ca2::library * plibrary);

      virtual bool system_add_app_install(const char * pszId);

   };

   CLASS_DECL_ca UINT c_cdecl application_thread_procedure(LPVOID pvoid);

   typedef ::ca::application * (* LPFN_instantiate_application)(::ca::application * pappParent, const char * pszId);

   extern CLASS_DECL_ca LPFN_instantiate_application g_lpfn_instantiate_application;


} // namespace cube4


