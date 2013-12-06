#pragma once

namespace user
{

   class printer;


} // namespace user


namespace plane
{


   class CLASS_DECL_CORE application :
      virtual public ::application,
      virtual public ::database::client

   {
   public:

      sp(service_base)                    m_pservice;

      sp(class ::fs::data)                m_spfsdata;

      bool                                m_bIfs;
      bool                                m_bUpdateMatterOnInstall;
      sp(::userfs::userfs)                m_spuserfs;
      sp(::html::html)                    m_phtml;
      ::simpledb::simpledb                m_simpledb;
      sp(::userex::userex)                m_spuserex;


      application();
      virtual ~application();



      virtual bool on_install();
      virtual bool on_uninstall();


      virtual bool is_serviceable();
      virtual bool is_installing();
      virtual bool is_uninstalling();


      virtual int32_t run();


      service_base * get_service();
      virtual service_base * allocate_new_service();
      virtual bool create_new_service();


      virtual bool create_service();
      virtual bool remove_service();

      virtual bool start_service();
      virtual bool stop_service();


      virtual void on_service_request(sp(::create_context) pcreatecontext);




      virtual int32_t exit_instance();


      inline sp(class ::fs::data)               fs()           { return m_spfsdata     ; }
      inline sp(::html::html)                   html()         { return m_phtml        ; }
      inline class ::simpledb::simpledb         & simpledb()   { return m_simpledb     ; }
      inline sp(::userex::userex)               userex()       { return m_spuserex; }


      virtual bool process_initialize();


      virtual bool initialize();
      virtual bool initialize1();
      virtual bool initialize2();
      virtual bool initialize_instance();

      virtual void defer_initialize_twf();

      virtual int32_t pre_run();
      virtual int32_t on_run();

      virtual bool main_start();
      virtual int32_t main();
      virtual bool bergedge_start();
      virtual bool os_native_bergedge_start();


      virtual sp(base_application) instantiate_application(const char * pszType, const char * pszId, application_bias * pbias);
      virtual sp(base_application) create_application(const char * pszType, const char * pszId, bool bSynch, application_bias * pbias);


      virtual bool initial_check_directrix();

      virtual void set_title(const char * pszTitle);


      //////////////////////////////////////////////////////////////////////////////////////////////////
      // System/System
      //
      sp(::user::object) hold(sp(::user::interaction) pui);

      virtual ::count get_monitor_count();
      virtual bool  get_monitor_rect(index i, LPRECT lprect);
      virtual ::count get_desk_monitor_count();
      virtual bool  get_desk_monitor_rect(index i, LPRECT lprect);



      //////////////////////////////////////////////////////////////////////////////////////////////////
      // Session/Session
      //
      virtual sp(::bergedge::view) get_view();
      virtual sp(::bergedge::document) get_document();


      virtual void fill_locale_schema(::str::international::locale_schema & localeschema);
      virtual void fill_locale_schema(::str::international::locale_schema & localeschema, const char * pszLocale, const char * pszSchema);

      virtual bool update_appmatter(::sockets::socket_handler & h, ::sockets::http_session * & psession, const char * pszRoot, const char * pszRelative);
      virtual bool update_appmatter(::sockets::socket_handler & h, ::sockets::http_session * & psession, const char * pszRoot, const char * pszRelative, const char * pszLocale, const char * pszStyle);


      virtual bool add_library(::core::library * plibrary);

      virtual bool system_add_app_install(const char * pszId);

      virtual ::user::user * create_user();
      virtual ::userex::userex * create_userex();
      virtual ::userfs::userfs * create_userfs();
      virtual ::html::html * create_html();


      virtual void assert_valid() const;
      virtual void dump(dump_context & context) const;


      virtual void construct();
      virtual void construct(const char * pszId);


      virtual void _001OnFileNew();


      virtual void on_request(sp(::create_context) pcreatecontext);

      sp(::user::object) _001OpenDocumentFile(var varFile);

      sp(base_application) get_system();

      virtual sp(::plane::application) assert_running(const char * pszAppdId);









      // smart_pointer < ::cubebase::application >::oattrib
      // or any function needing it
      application & operator = (const application & app)
      {

         UNREFERENCED_PARAMETER(app);

         // do nothing

         return *this;

      }

      // get a file and if there are exceptions, should show end user friendly messages
      virtual ::file::binary_buffer_sp friendly_get_file(var varFile, UINT nOpenFlags);


      virtual void data_on_after_change(signal_details * pobj);

      using ::application::simple_message_box;
      virtual int32_t simple_message_box(sp(::user::interaction) puiOwner, const char * pszMessage, UINT fuStyle = MB_OK);
      virtual int32_t simple_message_box_timeout(sp(::user::interaction) pwndOwner, const char * pszMessage, ::duration durationTimeOut, UINT fuStyle = MB_OK);


   };


   CLASS_DECL_CORE UINT c_cdecl application_thread_procedure(LPVOID pvoid);

   typedef sp(base_application) (* LPFN_instantiate_application)(sp(base_application) pappParent, const char * pszId);

   extern CLASS_DECL_CORE LPFN_instantiate_application g_lpfn_instantiate_application;


} // namespace plane





namespace core
{

   // impl
   template < class APP >
   sp(base_application) single_application_library < APP > :: get_new_app(const char * pszAppId)
   {

      if(!contains_app(pszAppId))
         return NULL;

      sp(application) papp = canew(APP());

      if(papp == NULL)
         return NULL;

      try
      {
         papp->m_pplaneapp->construct(pszAppId);
      }
      catch(...)
      {
         try
         {
            papp.release();
         }
         catch(...)
         {
         }
         return NULL;
      }

      return papp;

   }


} // namespace core



