#pragma once


namespace netnode
{


   class service;


   class CLASS_DECL_ca application :
      virtual public ::planebase::application
   {
   public:

      string                                    m_strFontopusServer;
      //::userbase::multiple_document_template *  m_ptemplateEdge;
      dynamic_source::script_manager *          m_pscriptmanager;

	  string									            m_strDatabaseServerHost;
	  int										            m_iDatabaseServerPort;



      application(void);
      virtual ~application(void);
      virtual void construct();


      virtual bool on_install();
      virtual bool on_uninstall();

      virtual void netnode_run();

      bool initialize_instance();
      int exit_instance();

      virtual bool is_serviceable();
      virtual service_base * allocate_new_service();
      ::netnode::service * get_service();


      dynamic_source::script_manager * get_script_manager();

      void get_Votagus_folder(string &str);

//      using ::cube2::application::process;
      void process(machine_event_data * pdata);

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
         
      virtual void pre_translate_message(gen::signal_object * pobj);

      virtual bool does_launch_window_on_startup();

      virtual void on_request(::ca::create_context * pcreatecontext);

   };


} // namespace netnode