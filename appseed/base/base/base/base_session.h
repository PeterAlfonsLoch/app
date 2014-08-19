#pragma once


namespace base
{


   class CLASS_DECL_BASE session:
      virtual public ::axis::session,
      virtual public ::base::application
   {
   public:

      

      //::user::interaction *                                    m_puiMouseMoveCapture;
      //::user::interaction *                                    m_puiLastLButtonDown;

      //bool                                                     m_bMatterFromHttpCache;

      //bool                                                     m_bSystemSynchronizedCursor;
      //point                                                    m_ptCursor;
      //bool                                                     m_bSystemSynchronizedScreen;
      //rect_array                                               m_rectaMonitor;
      //rect_array                                               m_rectaWkspace;
      //index                                                    m_iMainMonitor;
      //index                                                    m_iMainWkspace;



      //::core::platform *                                       m_pcoreplatform;
      //string_map < sp(::axis::application) >                   m_mapApplication;
      sp(::userpresence::userpresence)                         m_puserpresence;
      sp(::ifs)                                                m_pifs;
      sp(::fs::remote_native)                                  m_prfs;
      sp(::fs::fs)                                             m_spfs;
      sp(class ::fs::data)                                     m_spfsdata;
           //bool                                                     m_bDrawCursor;


      //::visual::e_cursor                                       m_ecursor;
      //::visual::e_cursor                                       m_ecursorDefault;
      //::base::copydesk_sp                                      m_spcopydesk;


      sp(::fontopus::fontopus)                                 m_pfontopus;
      //application_ptra                                         m_appptra;
      //sp(::user::interaction)                                  m_spuiFocus;
      //sp(::user::str_context)                                  m_puserstrcontext;
      sp(::sockets::sockets)                                   m_psockets;
      //bool                                                     m_bZipIsDir;
      //map < ::user::e_key,::user::e_key,bool,bool > *          m_pmapKeyPressed;
      //sp(::base::savings)                                      m_psavings;
      bool                                                     m_bIfs;
      //sp(::user::user)                                         m_spuser;
      sp(class ::fontopus::license)                   m_splicense;




      //::user::schema_simple_impl                               m_schemasimple;




      session(sp(::axis::application) papp);
      virtual ~session();

      inline ::userpresence::userpresence & userpresence() { return *m_puserpresence; }
      inline sp(::fontopus::fontopus)           fontopus()     { return m_pfontopus; }

      application_ptra & appptra();

      virtual bool is_session();


      void construct(sp(::axis::application) papp, int iPhase);

      virtual bool process_initialize();

      virtual bool initialize1();

      virtual bool initialize2();

      virtual bool initialize_instance();

      virtual bool initialize();

      virtual bool finalize();

      virtual int32_t exit_instance();


      inline sp(class ::fs::data)               fs()           { return m_spfsdata; }
      inline ::sockets::sockets &               sockets()      { return *m_psockets; }
      inline class ::fontopus::license &        license()      { return *m_splicense; }

      //::user::str_context *                     str_context();







      virtual sp(::axis::application) start_application(const char * pszType,const char * pszAppId,sp(::create_context) pcreatecontext);

      
      virtual ::fontopus::fontopus * create_fontopus();


      virtual ::fontopus::user * safe_get_user();


      virtual ::fontopus::user * get_user();
      virtual ::fontopus::user * create_current_user();


      virtual bool is_licensed(const char * pszId,bool bInteractive = true);


      virtual bool get_auth(const string & pszForm,string & strUsername,string & strPassword);


      virtual bool  get_window_minimum_size(LPSIZE lpsize);


      //virtual void  get_cursor_pos(LPPOINT lppoint);


      virtual bool on_ui_mouse_message(::message::mouse * pmouse);


      virtual sp(::user::interaction) get_active_guie();
      virtual sp(::user::interaction) get_focus_guie();


      //virtual string matter_as_string(const char * pszMatter,const char * pszMatter2);
      //virtual string dir_matter(const char * pszMatter,const char * pszMatter2);

      //virtual bool is_inside_time_dir(const char * pszPath);
      //virtual bool file_is_read_only(const char * pszPath);

   };


} // namespace base








//inline ::base::session & Sess(::axis::application * papp);




























