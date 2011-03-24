#pragma once

namespace nature
{
   class database;
} // namespace nature

namespace bergedge
{

   class CLASS_DECL_ca bergedge :
      virtual public platform::application,
      virtual public filemanager::item_action
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
         virtual public ::collection::map < int, int, ::bergedge::bergedge *, ::bergedge::bergedge * >
      {
      };

      
      index                                                 m_iEdge;

      ::ca::application *                                   m_pappCurrent;
      ::collection::string_map < ::ca::application * >      m_mapApplication;


      ::userbase::single_document_template *                m_ptemplate_bergedge;
      ::userbase::single_document_template *                m_ptemplate_platform;
      ::userbase::single_document_template *                m_ptemplate_nature;
      ::userbase::single_document_template *                m_ptemplate_html;
      document *                                            m_pbergedgedocument;
      platform::document *                                  m_pplatformdocument;
      nature::document *                                    m_pnaturedocument;
      nature::database *                                    m_pdatabase;

      
      bergedge();
      virtual ~bergedge();
      virtual void construct();

      bool initialize_instance();
      BOOL exit_instance();

      bool InitializeLocalDataCentral();

      virtual bool bergedge_start();

      void _001OnFileNew();

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);

      virtual bool pre_process_command_line();
         

      virtual ::ca::application * get_app() const;
      void OnFileManagerOpenFile(
         ::filemanager::data * pdata, 
         ::fs::item_array & itema);

      void load_string_table();

      virtual bool file_manager_open_file(
            ::filemanager::data * pdata, 
            ::fs::item_array & itema);

      void initialize_bergedge_application_interface();

      virtual document * force_get_document();


      // semantics defined by application
      virtual void request(var & varFile, var & varQuery);
      // main loosely coupled semantics
      // varFile   : empty, one file path, many file paths, one file object, one or more file objects to be opened
      // varQuery  : more ellaborated requests for the application - syntax and semantic defined by requested application


      void on_exclusive_instance_conflict(::radix::EExclusiveInstance eexclusive);
      
      void launch_app(const char * psz);
      void install_app(const char * psz);

      bergedge::document *    get_document();
      platform::document *    get_platform();
      nature::document *      get_nature();

      void request_application(const char * pszId, var varFile, var varQuery, ::ca::application_bias * pbiasCreate);
      void request_application(ca2::application_request * prequest);

      ::ca::application * application_get(const char * pszId, bool bCreate = true, bool bSynch = true, ::ca::application_bias * pbiasCreate = NULL);

      void open_by_file_extension(const char * pszPathName);
      

   };

} // namespace bergedge