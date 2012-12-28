#pragma once


namespace cube
{


   class CLASS_DECL_ca2 application : 
      public ::cube8::application
   {
   public:
      
      


      application();
      application(const char * pszId);
      virtual ~application();


      using ::cubebase::application::construct;
      virtual void construct();
      
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

      ::user::document_interface * _001OpenDocumentFile(var varFile);

      ::ca::application * get_system();

   };

   
} // namespace cube



