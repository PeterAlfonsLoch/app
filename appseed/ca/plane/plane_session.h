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
         ::ca::application *     m_papp;
         bool                    m_bMakeVisible;
         ::user::interaction *   m_puiParent;
         gen::property_set       m_setParameters;
      };


      class run_start_installer
      {
      public:
         virtual void run_start_install(const char * pszInstall) = 0;
      };

      class CLASS_DECL_ca map :
         virtual public ::collection::map < index, index, ::plane::session *, ::plane::session * >
      {
      };


      ::bergedge::bergedge *                                m_pbergedge;
      ::bergedge_interface *                                m_pbergedgeInterface;


      index                                                 m_iEdge;

      bool                                                  m_bShowPlatform;

      ::ca::application *                                   m_pappCurrent;
      ::collection::string_map < ::ca::application *  >     m_mapApplication;


      var                                                   m_varTopicFile;
      var                                                   m_varCurrentViewFile;

      bool                                                  m_bDrawCursor;

      ifs *                                                 m_pifs;
      fs::remote_native *                                   m_prfs;


      session();
      virtual ~session();
      virtual void construct();

      bool initialize_instance();
      virtual int exit_instance();

      bool InitializeLocalDataCentral();

      virtual bool bergedge_start();

      void _001OnFileNew();

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);

      virtual ::ca::application * get_app() const;

      void load_string_table();

      void initialize_bergedge_application_interface();

      virtual bool create_bergedge(::ca::create_context * pcreatecontext);


      // semantics defined by application
      using ::plane::application::request;
      virtual void request(::ca::create_context * pcreatecontext);
      // main loosely coupled semantics
      // varFile   : empty, one file path, many file paths, one file object, one or more file objects to be opened
      // varQuery  : more ellaborated requests for the application - syntax and semantic defined by requested application

      virtual ::user::interaction * get_request_parent_ui(::user::interaction * pinteraction, ::ca::create_context * pcontext);

      virtual ::user::interaction * get_request_parent_ui(::userbase::main_frame * pmainframe, ::ca::create_context * pcontext);

      virtual void request_topic_file(var & varQuery);

      virtual void request_topic_file();

      virtual void check_topic_file_change();

      void on_exclusive_instance_conflict(::radix::EExclusiveInstance eexclusive);

      void launch_app(const char * psz);
      void install_app(const char * psz);

      void on_request(::ca::create_context * pcreatecontext);

      ::ca::application * application_get(const char * pszType, const char * pszId, bool bCreate = true, bool bSynch = true, ::ca::application_bias * pbiasCreate = NULL);

      virtual bool open_by_file_extension(const char * pszPathName, ::ca::application_bias * pbiasCreate = NULL);

      virtual bool open_by_file_extension(::ca::create_context * pcreatecontext);

      virtual bool is_session();

      ::ca::application * get_current_application();

      virtual void get_screen_rect(LPRECT lprect);

      virtual bool on_install();


      virtual void set_app_title(const char * pszType, const char * pszAppId, const char * pszTitle);

      //////////////////////////////////////////////////////////////////////////////////////////////////
      // Session/Bergedge
      //
      virtual ::bergedge::view * get_view();
      virtual ::bergedge::document * get_document();
      virtual FileManagerTemplate * GetStdFileManagerTemplate();


      virtual bool is_mouse_button_pressed(::user::e_mouse emouse);


      virtual bool is_remote_session();

      using ::plane::application::start_application;
      ::planebase::application * start_application(const char * pszType, const char * pszAppId, ::ca::create_context * pcreatecontext);


   };


} // namespace plane



