#pragma once
   


namespace plane
{


   class CLASS_DECL_ca application : 
      virtual public ::planebase::application
   {
   public:



      application();
      application(const char * pszId);
      virtual ~application();

      virtual void construct();
      virtual void construct(const char * pszId);
      
      virtual bool initialize_instance();
      virtual int32_t  exit_instance();

      virtual void _001OnFileNew();
      virtual bool bergedge_start();


      virtual bool is_serviceable();
      virtual service_base * allocate_new_service();


      virtual bool on_install();
      virtual bool on_uninstall();

      virtual int32_t run();

      virtual void on_request(::ca::create_context * pcreatecontext);

      sp(::user::document_interface) _001OpenDocumentFile(var varFile);

      ::ca::applicationsp get_system();

      virtual ::planebase::application * assert_running(const char * pszAppdId);

   };



} // namespace plane


