#pragma once


namespace cube
{


   class CLASS_DECL_ca2 cube :
      virtual public ::cube8::application
   {
   public:


      sp(::ca2::filehandler::handler)              m_spfilehandler;
      plane::session::run_start_installer *        m_prunstartinstaller;
      plane::session::map *                        m_pbergedgemap;
      index                                        m_iNewEdge;
      class machine_event_central *                m_pmachineeventcentral;


      cube();
      virtual ~cube();


      //virtual int main();
      virtual BOOL InitApplication();

      virtual bool process_initialize();

      virtual bool initialize();
      virtual bool initialize1();
      virtual bool initialize3();

      virtual bool initialize_instance();

      virtual bool bergedge_start();

      virtual bool finalize();
      virtual int exit_instance();

      virtual index get_new_bergedge(::ca::application_bias * pbiasCreation = NULL);

      virtual void register_bergedge_application(::ca::application * papp);
      virtual void unregister_bergedge_application(::ca::application * papp);

 
      ::ca2::filehandler::handler      & filehandler();

 
      virtual bool base_support();

  
      DECL_GEN_SIGNAL(on_application_signal);

  
      using ::cube8::application::process;
      bool set_history(::ca::history * phistory);


      virtual bergedge::bergedge *             get_bergedge(index iEdge, ::ca::application_bias * pbiasCreation = NULL);
      virtual platform::document *             get_platform(index iEdge, ::ca::application_bias * pbiasCreation = NULL);
      virtual nature::document *               get_nature(index iEdge, ::ca::application_bias * pbiasCreation = NULL);

      virtual bergedge::bergedge *             query_bergedge(index iEdge);
      virtual void on_request(::ca::create_context * pcreatecontext);
      virtual ::ca::application * application_get(index iEdge, const char * pszId, bool bCreate = true, bool bSynch = true, ::ca::application_bias * pbiasCreate = NULL);
      virtual void open_by_file_extension(index iEdge, const char * pszPathName);
      virtual bool is_system();
      virtual bool set_main_init_data(::ca::main_init_data * pdata);

      virtual bool is_cube();

   };


} // namespace cube8


