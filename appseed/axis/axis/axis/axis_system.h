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


      virtual string install_get_version() override;
      virtual void install_set_version(const char * pszVersion) override;
      virtual string install_get_latest_build_number(const char * pszVersion) override;
      virtual int32_t install_start(const char * pszCommandLine,const char * pszBuild) override;


      virtual bool process_initialize();

      virtual bool initialize1();

      virtual bool initialize2();


      virtual bool verb();



      virtual string dir_appmatter_locator(::aura::application * papp);



      virtual bool is_system();


      virtual string crypto_md5_text(const string & str);

      virtual void install_progress_add_up(int iAddUp = 1);


      virtual ::aura::session * on_create_session();

      virtual void on_request(sp(::create) pcreate);

   };


} // namespace axis







void CLASS_DECL_AXIS __start_system(::axis::system * psystem);




