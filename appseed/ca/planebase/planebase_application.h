#pragma once


namespace planebase
{


   class CLASS_DECL_ca application :
      virtual public ::fontopus::application
   {
   public:


      service_base *                      m_pservice;
      class ::ca::dir::application        m_dir;
      class ::ca::file::application       m_file;
      class ::ca4::http::application      m_http;

      sp(class ::fontopus::license)       m_splicense;
      sp(class ::fs::data)                m_spfsdata;

      bool                                m_bIfs;



      application();
      virtual ~application();



      virtual bool on_install();
      virtual bool on_uninstall();


      virtual bool is_serviceable();


      virtual int run();

      
      service_base * get_service();
      virtual service_base * allocate_new_service();
      virtual bool create_new_service();

      
      virtual bool create_service();
      virtual bool remove_service();

      virtual bool start_service();
      virtual bool stop_service();


      virtual void on_service_request(::ca::create_context * pcreatecontext);




      virtual int exit_instance();


      class ::ca::dir::application        & dir();
      class ::ca::file::application       & file();
      class ::ca4::http::application      & http(); 

      class ::fontopus::license           & license();

      class ::fs::data                    * fs();


      
      virtual bool initialize();
      virtual bool initialize1();

      virtual void defer_initialize_twf();

      virtual int pre_run();
      virtual int on_run();

      virtual int main();
      virtual bool bergedge_start();
      virtual bool os_native_bergedge_start();


      virtual ::ca::application * instantiate_application(const char * pszId, ::ca::application_bias * pbias);
      virtual ::ca::application * create_application(const char * pszId, bool bSynch, ::ca::application_bias * pbias);

      virtual ::ex1::filesp get_file(var varFile, UINT nOpenFlags, ::ex1::file_exception_sp * pe = NULL);
      virtual ::ex1::byte_stream get_byte_stream(var varFile, UINT nOpenFlags, ::ex1::file_exception_sp * pe = NULL);


      virtual bool is_licensed(const char * pszId, bool bInteractive = true);

      //virtual ::user::interaction * get_request_parent_ui(gen::command_line * pline);

      virtual bool initial_check_directrix();





      virtual void set_title(const char * pszTitle);


      virtual FileManagerTemplate * GetStdFileManagerTemplate();



      //////////////////////////////////////////////////////////////////////////////////////////////////
      // System/Cube
      //
      ::document * hold(::user::interaction * pui);

      virtual count get_monitor_count();
      virtual bool  get_monitor_rect(index i, LPRECT lprect);
      virtual count get_desk_monitor_count();
      virtual bool  get_desk_monitor_rect(index i, LPRECT lprect);



      //////////////////////////////////////////////////////////////////////////////////////////////////
      // Session/Bergedge
      //
      virtual ::bergedge::view * get_view();
      virtual ::bergedge::document * get_document();



   };

   CLASS_DECL_ca UINT AFX_CDECL application_thread_procedure(LPVOID pvoid);

   typedef ::ca::application * (* LPFN_instantiate_application)(::ca::application * pappParent, const char * pszId);

   extern CLASS_DECL_ca LPFN_instantiate_application g_lpfn_instantiate_application;

   inline application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }


} // namespace cube4


