#pragma once


namespace userstack
{


   class view;


   class CLASS_DECL_sphere application :
      virtual public ::command::application
   {
   public:


      index                                                          m_iEdge;
                                                                     
      bool                                                           m_bShowPlatform;
                                                                     
      ::ca::application *                                            m_pappCurrent;
      ::collection::string_map < ::ca::application * >               m_mapApplication;
                                                                     
      
      ::userbase::single_document_template *                         m_ptemplate_main;
      ::userbase::single_document_template *                         m_ptemplate_pane;
                                                                     
                                                                     
      var                                                            m_varTopicFile;
      var                                                            m_varCurrentViewFile;
                                                                     
      bool                                                           m_bDrawCursor;

      ::collection::string_map < ::uinteraction::interaction * >     m_mapUinteraction;


      application();
      virtual ~application();
      virtual void construct();

      bool initialize_instance();
      virtual int32_t exit_instance();

      virtual bool bergedge_start();

      void _001OnFileNew();

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);

      virtual ::ca::application * get_app() const;

      void OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema);

      void load_string_table();

      virtual bool file_manager_open_file(::filemanager::data * pdata, ::fs::item_array & itema);

      void initialize_bergedge_application_interface();

      //virtual void request(::ca::create_context * pcreatecontext);
      // main loosely coupled semantics
      // varFile   : empty, one file path, many file paths, one file object, one or more file objects to be opened
      // varQuery  : more ellaborated requests for the application - syntax and semantic defined by requested application

      //virtual ::user::interaction * get_request_parent_ui(::user::interaction * pinteraction, ::ca::create_context * pcontext);

      //virtual ::user::interaction * get_request_parent_ui(::userbase::main_frame * pmainframe, ::ca::create_context * pcontext);

      //virtual ::user::place_holder_ptra get_place_holder(::userbase::main_frame * pmainframe, ::ca::create_context * pcontext);

      //virtual bool place(::userbase::main_frame * pmainframe, ::ca::create_context * pcontext);

      virtual void request_topic_file(var & varQuery);

      virtual void request_topic_file();

      virtual void check_topic_file_change();

      void on_exclusive_instance_conflict(::gen::EExclusiveInstance eexclusive);
      
      void launch_app(const char * psz);
      void install_app(const char * psz);

      virtual bool initialize1();

      virtual bool initialize();

      virtual bool os_native_bergedge_start();

      virtual int32_t main();

      virtual bool on_uninstall();

      virtual bool is_serviceable();

      virtual service_base * allocate_new_service();

      void on_request(::ca::create_context * pcreatecontext);

      ::ca::application * application_get(const char * pszType, const char * pszId, bool bCreate = true, bool bSynch = true, ::ca::application_bias * pbiasCreate = NULL);

      ::ca::application * get_current_application();

      virtual void get_screen_rect(LPRECT lprect);

      virtual bool on_install();

      virtual void set_app_title(const char * pszType, const char * pszAppId, const char * pszTitle);

   };


} // namespace userstack



