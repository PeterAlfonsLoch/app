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
                                                                     
      sp(::base::application)                                            m_pappCurrent;
      string_map < sp(::base::application) >               m_mapApplication;
                                                                     
      
      sp(::user::single_document_template)                         m_ptemplate_main;
      sp(::user::single_document_template)                         m_ptemplate_pane;

      pane_view *                                                    m_ppaneview;
                                                                     
                                                                     
      var                                                            m_varTopicFile;
      var                                                            m_varCurrentViewFile;
                                                                     
      bool                                                           m_bDrawCursor;

      string_map < ::user::uinteraction::interaction * >     m_mapUinteraction;


      application();
      virtual ~application();
      virtual void construct();

      bool initialize_instance();
      virtual int32_t exit_instance();

      virtual bool bergedge_start();

      void OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema);

      void load_string_table();

      virtual bool file_manager_open_file(::filemanager::data * pdata, ::fs::item_array & itema);

      void initialize_bergedge_application_interface();

      virtual void request_topic_file(var & varQuery);

      virtual void request_topic_file();

      virtual void check_topic_file_change();

      void on_exclusive_instance_conflict(::EExclusiveInstance eexclusive);
      
      void launch_app(const char * psz);
      void install_app(const char * psz);

      virtual bool initialize1();

      virtual bool initialize();

      virtual bool os_native_bergedge_start();

      virtual int32_t main();

      virtual bool on_uninstall();

      virtual bool is_serviceable();

      virtual service_base * allocate_new_service();

      void on_request(sp(::create_context) pcreatecontext);

      sp(::base::application) application_get(const char * pszType, const char * pszId, bool bCreate = true, bool bSynch = true, application_bias * pbiasCreate = NULL);

      sp(::base::application) get_current_application();

      //virtual void get_screen_rect(LPRECT lprect);

      virtual bool on_install();

      virtual void set_app_title(const char * pszType, const char * pszAppId, const char * pszTitle);

   };


} // namespace userstack



