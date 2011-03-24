#pragma once

namespace cube
{

   class CLASS_DECL_CA2_CUBE application : 
      public ::veriview::application
   {
   public:
      
      


      application();
      application(const char * pszId);
      virtual ~application();

      virtual void construct();
      virtual void construct(const char * pszId);
      virtual bool initialize_instance();

      virtual void _001OnFileNew();
      virtual bool bergedge_start();

      virtual bool on_install();

      virtual BOOL run();

      virtual void on_request(var & varFile, var & varQuery);

      ::document * _001OpenDocumentFile(var varFile);

      ::ca::application * get_system();

   };

   CLASS_DECL_CA2_CUBE application & app_cast(::ca::application * papp);

} // namespace cube