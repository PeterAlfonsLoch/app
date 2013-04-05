#pragma once


namespace nature
{


   class database;


} // namespace nature


namespace bergedge
{


   class document;
   class view;


   class CLASS_DECL_ca2 bergedge :
      virtual public ::platform::application,
      virtual public ::filemanager::item_action,
      virtual public ::bergedge_interface
   {
   public:


      index                                                          m_iEdge;

      bool                                                           m_bShowPlatform;

      ::ca::applicationsp                                            m_pappCurrent;
      string_map < ::ca::applicationsp >               m_mapApplication;


      ::userbase::single_document_template *                         m_ptemplate_bergedge;
      ::userbase::single_document_template *                         m_ptemplate_platform;
      ::userbase::single_document_template *                         m_ptemplate_nature;
      ::userbase::single_document_template *                         m_ptemplate_html;
      sp(document)                                                     m_pbergedgedocument;
      sp(::platform::document)                                           m_pplatformdocument;
      sp(::nature::document)                                             m_pnaturedocument;
      nature::database *                                             m_pdatabase;


      var                                                            m_varTopicFile;
      var                                                            m_varCurrentViewFile;

      bool                                                           m_bDrawCursor;

      string_map < sp(::uinteraction::interaction) >     m_mapUinteraction;


      bergedge();
      virtual ~bergedge();
      virtual void construct();

      bool initialize_instance();
      virtual int32_t exit_instance();

      bool InitializeLocalDataCentral();

      virtual bool bergedge_start();

      void _001OnFileNew();

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);

      virtual ::ca::applicationsp get_app() const;

      void OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema);

      void load_string_table();

      virtual bool file_manager_open_file(::filemanager::data * pdata, ::fs::item_array & itema);

      void initialize_bergedge_application_interface();

      virtual bool create_bergedge(::ca::create_context * pcreatecontext);

      virtual void on_app_request_bergedge_callback(::ca::applicationsp papp);

      


      // semantics defined by application
      using platform::application::request;
      virtual void request(::ca::create_context * pcreatecontext);
      // main loosely coupled semantics
      // varFile   : empty, one file path, many file paths, one file object, one or more file objects to be opened
      // varQuery  : more ellaborated requests for the application - syntax and semantic defined by requested application

      virtual sp(::user::interaction) get_request_parent_ui(sp(::user::interaction) pinteraction, ::ca::create_context * pcontext);

      virtual sp(::user::interaction) get_request_parent_ui(::userbase::main_frame * pmainframe, ::ca::create_context * pcontext);

      virtual ::user::place_holder_ptra get_place_holder(::userbase::main_frame * pmainframe, ::ca::create_context * pcontext);

      virtual bool place(::userbase::main_frame * pmainframe, ::ca::create_context * pcontext);

      virtual void request_topic_file(var & varQuery);

      virtual void request_topic_file();

      virtual void check_topic_file_change();

      void on_exclusive_instance_conflict(::ca::EExclusiveInstance eexclusive);

      void launch_app(const char * psz);
      void install_app(const char * psz);

      ::bergedge::document *            get_document();
      ::bergedge::view *                get_view();
      sp(::platform::document)          get_platform();
      sp(::nature::document)            get_nature();

      virtual bool initialize1();

      virtual bool initialize();

      virtual bool os_native_bergedge_start();

      virtual int32_t main();

      virtual bool on_uninstall();

      virtual bool is_serviceable();

      virtual service_base * allocate_new_service();

      void on_request(::ca::create_context * pcreatecontext);

      ::ca::applicationsp application_get(const char * pszType, const char * pszId, bool bCreate = true, bool bSynch = true, ::ca::application_bias * pbiasCreate = NULL);

      virtual bool is_bergedge();

      ::ca::applicationsp get_current_application();

      virtual void get_screen_rect(LPRECT lprect);

      virtual bool on_install();

      virtual void set_app_title(const char * pszType, const char * pszAppId, const char * pszTitle);

      virtual ::bergedge::bergedge * get_bergedge();

   };


} // namespace bergedge



