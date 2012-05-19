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

      virtual void construct();
      virtual void construct(const char * pszId);
      
      virtual bool initialize_instance();
      virtual int  exit_instance();

      virtual void _001OnFileNew();
      virtual bool bergedge_start();


      virtual bool is_serviceable();
      virtual service_base * allocate_new_service();


      virtual bool on_install();
      virtual bool on_uninstall();

      virtual int run();

      virtual void on_request(::ca::create_context * pcreatecontext);

      ::user::document_interface * _001OpenDocumentFile(var varFile);

      ::ca::application * get_system();

   };

   
} // namespace cube



