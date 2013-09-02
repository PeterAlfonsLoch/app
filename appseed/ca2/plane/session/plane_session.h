#pragma once


namespace plane
{


   class view;


   class CLASS_DECL_ca2 session :
      virtual public ::platform::application,
      virtual public ::filemanager::item_action,
      virtual public ::ca2::session
   {
   public:


      class run_application
      {
      public:
         run_application();
         index                   m_iEdge;
         string                  m_strApp;
         string                  m_strQuery;
         sp(::plane::session)      m_pbergedgeParent;
         sp(::application)   m_papp;
         bool                    m_bMakeVisible;
         sp(::user::interaction) m_puiParent;
         property_set      m_setParameters;
      };


      class run_start_installer :
         virtual public object
      {
      public:
         virtual void run_start_install(const char * pszInstall) = 0;
      };

      class CLASS_DECL_ca2 map :
         virtual public ::map < index, index, sp(::plane::session), sp(::plane::session) >
      {
      };


      index                                                 m_iEdge;

      bool                                                  m_bShowPlatform;

      sp(::application)                                   m_pappCurrent;
      string_map < sp(::application) >                    m_mapApplication;


      var                                                   m_varTopicFile;
      var                                                   m_varCurrentViewFile;

      bool                                                  m_bDrawCursor;

      sp(::ifs)                                                 m_pifs;
      sp(::fs::remote_native)                                   m_prfs;
      sp(::userpresence::userpresence)                        m_puserpresence;




      ::visual::e_cursor m_ecursor;
      ::visual::e_cursor m_ecursorDefault;


      sp(::user::single_document_template)                         m_ptemplate_bergedge;
      sp(::user::single_document_template)                         m_ptemplate_platform;
      sp(::user::single_document_template)                         m_ptemplate_nature;
      sp(::user::single_document_template)                         m_ptemplate_html;
      sp(::bergedge::document)                           m_pbergedgedocument;
      sp(::platform::document)                           m_pplatformdocument;
      sp(::nature::document)                             m_pnaturedocument;
      nature::database *                                 m_pdatabase;


      string_map < sp(::uinteraction::interaction) >     m_mapUinteraction;


      session();
      virtual ~session();
      virtual void construct();

      bool initialize_instance();
      virtual int32_t exit_instance();

      bool InitializeLocalDataCentral();

      virtual bool bergedge_start();

      void _001OnFileNew();

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);

      virtual ::ca2::application * get_app() const;

      void OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema);

      void load_string_table();

      virtual bool file_manager_open_file(::filemanager::data * pdata, ::fs::item_array & itema);

      void initialize_bergedge_application_interface();

      virtual bool create_bergedge(sp(create_context) pcreatecontext);

      virtual void on_app_request_bergedge_callback(sp(::application) papp);

      


      // semantics defined by application
      virtual void request_create(sp(create_context) pcreatecontext);
      // main loosely coupled semantics
      // varFile   : empty, one file path, many file paths, one file object, one or more file objects to be opened
      // varQuery  : more ellaborated requests for the application - syntax and semantic defined by requested application

      virtual sp(::user::interaction) get_request_parent_ui(sp(::user::interaction) pinteraction, sp(create_context) pcontext);

      virtual ::user::place_holder_ptra get_place_holder(sp(::user::frame_window) pmainframe, sp(create_context) pcontext);

      virtual bool place(sp(::user::main_frame) pmainframe, sp(create_context) pcontext);

      virtual void request_topic_file(var & varQuery);

      virtual void request_topic_file();

      virtual void check_topic_file_change();

      void on_exclusive_instance_conflict(::ca2::EExclusiveInstance eexclusive);

      void launch_app(const char * psz);
      void install_app(const char * psz);

      sp(::bergedge::document)            get_document();
      sp(::bergedge::view)                get_view();
      sp(::platform::document)          get_platform();
      sp(::nature::document)            get_nature();

      virtual bool initialize1();

      virtual bool initialize();

      virtual bool os_native_bergedge_start();

      virtual int32_t main();

      virtual bool on_uninstall();

      virtual bool is_serviceable();

      virtual service_base * allocate_new_service();

      void on_request(sp(create_context) pcreatecontext);

      sp(::application) application_get(const char * pszType, const char * pszId, bool bCreate = true, bool bSynch = true, application_bias * pbiasCreate = NULL);


      sp(::application) get_current_application();

      virtual void get_screen_rect(LPRECT lprect);

      virtual bool on_install();

      virtual void set_app_title(const char * pszType, const char * pszAppId, const char * pszTitle);

      virtual sp(::plane::session) get_session();

      virtual bool finalize();

      inline ::userpresence::userpresence & userpresence() { return *m_puserpresence; }


      virtual ::visual::cursor * get_cursor();
      virtual void set_cursor(::visual::e_cursor ecursor);
      virtual void set_default_cursor(::visual::e_cursor ecursor);
      virtual ::visual::cursor * get_default_cursor();

      virtual bool open_by_file_extension(const char * pszPathName, application_bias * pbiasCreate = NULL);
      virtual bool open_by_file_extension(create_context * pcc);

      virtual bool is_session();

      virtual bool is_mouse_button_pressed(::user::e_mouse emouse);

      virtual bool is_remote_session();

      using ::plane::application::start_application;
      sp(::plane::application) start_application(const char * pszType, const char * pszAppId, sp(create_context) pcreatecontext);


      virtual COLORREF get_default_color(uint64_t ui);


   };


} // namespace plane



