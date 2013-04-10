#pragma once


namespace plane
{


   class view;


   class CLASS_DECL_ca session :
      virtual public ::plane::application,
      virtual public ::ca::session
   {
   public:


      class run_application
      {
      public:
         run_application();
         index                   m_iEdge;
         string                  m_strApp;
         string                  m_strQuery;
         ::bergedge::bergedge *  m_pbergedgeParent;
         sp(::ca::application)     m_papp;
         bool                    m_bMakeVisible;
         sp(::user::interaction)   m_puiParent;
         ::ca::property_set       m_setParameters;
      };


      class run_start_installer :
         virtual public ::ca::object
      {
      public:
         virtual void run_start_install(const char * pszInstall) = 0;
      };

      class CLASS_DECL_ca map :
         virtual public ::map < index, index, sp(::plane::session), sp(::plane::session) >
      {
      };


      ::bergedge::bergedge *                                m_pbergedge;
      sp(::bergedge_interface)                                m_pbergedgeInterface;


      index                                                 m_iEdge;

      bool                                                  m_bShowPlatform;

      sp(::ca::application)                                   m_pappCurrent;
      string_map < sp(::ca::application) >                    m_mapApplication;


      var                                                   m_varTopicFile;
      var                                                   m_varCurrentViewFile;

      bool                                                  m_bDrawCursor;

      sp(::ifs)                                                 m_pifs;
      sp(::fs::remote_native)                                   m_prfs;
      sp(::userpresence::userpresence)                        m_puserpresence;




      ::visual::e_cursor m_ecursor;
      ::visual::e_cursor m_ecursorDefault;


      session();
      virtual ~session();


      virtual void construct();


      virtual bool initialize();
      virtual bool initialize_instance();

      virtual bool finalize();
      virtual int32_t exit_instance();

      bool InitializeLocalDataCentral();

      virtual bool bergedge_start();


      inline ::userpresence::userpresence & userpresence() { return *m_puserpresence; }

      void _001OnFileNew();

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);

      virtual sp(::ca::application) get_app() const;

      void load_string_table();

      void initialize_bergedge_application_interface();

      virtual bool create_bergedge(sp(::ca::create_context) pcreatecontext);

      virtual ::visual::cursor * get_cursor();
      virtual void set_cursor(::visual::e_cursor ecursor);
      virtual void set_default_cursor(::visual::e_cursor ecursor);
      virtual ::visual::cursor * get_default_cursor();



      // semantics defined by application
      virtual void request_create(sp(::ca::create_context) pcreatecontext);
      // main loosely coupled semantics
      // varFile   : empty, one file path, many file paths, one file object, one or more file objects to be opened
      // varQuery  : more ellaborated requests for the application - syntax and semantic defined by requested application

      virtual sp(::user::interaction) get_request_parent_ui(sp(::user::interaction) pinteraction, sp(::ca::create_context) pcontext);

      virtual void request_topic_file(var & varQuery);

      virtual void request_topic_file();

      virtual void check_topic_file_change();

      void on_exclusive_instance_conflict(::ca::EExclusiveInstance eexclusive);

      void launch_app(const char * psz);
      void install_app(const char * psz);

      void on_request(sp(::ca::create_context) pcreatecontext);

      sp(::ca::application) application_get(const char * pszType, const char * pszId, bool bCreate = true, bool bSynch = true, ::ca::application_bias * pbiasCreate = ::null());

      virtual bool open_by_file_extension(const char * pszPathName, ::ca::application_bias * pbiasCreate = ::null());

      virtual bool open_by_file_extension(sp(::ca::create_context) pcreatecontext);

      virtual bool is_session();

      sp(::ca::application) get_current_application();

      virtual void get_screen_rect(LPRECT lprect);

      virtual bool on_install();


      virtual void set_app_title(const char * pszType, const char * pszAppId, const char * pszTitle);

      //////////////////////////////////////////////////////////////////////////////////////////////////
      // Session/Bergedge
      //
      virtual ::bergedge::view * get_view();
      virtual ::bergedge::document * get_document();


      virtual bool is_mouse_button_pressed(::user::e_mouse emouse);


      virtual bool is_remote_session();

      using ::plane::application::start_application;
      sp(::planebase::application) start_application(const char * pszType, const char * pszAppId, sp(::ca::create_context) pcreatecontext);


      virtual COLORREF get_default_color(uint64_t ui);


   };


} // namespace plane



