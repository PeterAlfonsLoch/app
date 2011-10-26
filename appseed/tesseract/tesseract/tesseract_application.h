#pragma once


namespace tesseract
{


   class CLASS_DECL_CA2_TESSERACT application : 
      public ::veriview::application
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

      virtual bool on_install();

      virtual BOOL run();

      virtual void on_request(::ca::create_context * pcreatecontext);

      ::document * _001OpenDocumentFile(var varFile);

      ::ca::application * get_system();

   };

   
   CLASS_DECL_CA2_TESSERACT application & app_cast(::ca::application * papp);


} // namespace tesseract