#pragma once



namespace base
{


   class CLASS_DECL_BASE system:
      virtual public ::axis::system,
      virtual public ::base::application
   {
   public:

#ifdef BSD_STYLE_SOCKETS

      ::sockets::SSLInitializer *                    m_psslinit;

#endif

      ::url::departament                           m_urldepartament;


      ::file::system_sp                            m_spfile;
      ::file::dir::system_sp                       m_spdir;
      sp(::sockets::net)                           m_spnet;
      ::net::port_forward_sp                       m_spportforward;
      ::http::system                               m_httpsystem;


      class ::fontopus::user_set                   m_userset;
      ::crypto::crypto_sp                          m_spcrypto;
      class ::base::compress                       m_compress;
      sp(::install::install)                       m_spinstall;


      void *                                       m_ftlibrary;


      ::visual::visual                             m_visual;



      system(sp(::axis::application) papp);
      virtual ~system();






      virtual void construct(const char * pszAppId);

      virtual bool initialize_instance();

      virtual int32_t exit_instance();
      virtual bool finalize();

      spa(::base::session)                         & basesessionptra();
      //application_ptra                                get_appptra();

      class base_factory                           & factory();
      inline ::url::departament                    & url()     { return m_urldepartament; }
      class ::str::base64                          & base64();

      inline class ::http::system                  & http()    { return m_httpsystem; }
      inline ::file::system                        & file()    { return *m_spfile; }
      inline ::file::dir::system                   & dir()     { return *m_spdir; }
      class ::sockets::net                         & net();
      class ::base::compress                       & compress();
      ::fontopus::user_set                         & userset();

      class ::crypto::crypto                       & crypto();
      ::install::install                           & install() { return *m_spinstall; }

      void *                                       & ftlibrary();

      inline class ::visual::visual                & visual()     { return m_visual       ; }




      virtual bool process_initialize();

      virtual bool initialize2();


      virtual void on_allocation_error(sp(::axis::application) papp,sp(type) info);



      virtual int32_t _001OnDebugReport(int32_t i1,const char * psz1,int32_t i2,const char * psz2,const char * psz3,va_list args);
      virtual int32_t _debug_logging_report(int32_t iReportType, const char * pszFilename, int32_t iLinenumber, const char * iModuleName, const char * pszFormat, va_list list);
      virtual bool assert_failed_line(const char * lpszFileName,int32_t iLine);
      virtual bool on_assert_failed_line(const char * pszFileName,int32_t iLine);





      virtual void appa_load_string_table();
      virtual void appa_set_locale(const char * pszLocale,::action::context actioncontext);
      virtual void appa_set_schema(const char * pszStyle,::action::context actioncontext);

      virtual bool assert_running_global(const char * pszAppName,const char * pszId = NULL);
      virtual bool assert_running_local(const char * pszAppName,const char * pszId = NULL);




      virtual string dir_appmatter_locator(sp(::axis::application) papp);

      virtual sp(::user::interaction) get_active_guie();
      virtual sp(::user::interaction) get_focus_guie();


      virtual bool is_system();

   };


} // namespace base







void CLASS_DECL_BASE __start_system(::base::system * psystem);




