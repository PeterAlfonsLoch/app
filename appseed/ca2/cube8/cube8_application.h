#pragma once


namespace cube8
{


   class CLASS_DECL_ca2 application : 
      virtual public ::cube5::application
   {
   public:


      application();
      virtual ~application();

      virtual int exit_instance();




      
      virtual bool initialize();
      virtual bool initialize1();

      //virtual int pre_run();
      //virtual int on_run();

      //virtual int main();
      //virtual bool bergedge_start();
      //virtual bool os_native_bergedge_start();


      //virtual bool initial_check_directrix();


      virtual void set_title(const char * pszTitle);


   };

   CLASS_DECL_ca2 application & app_cast(::ca::ca * papp);

   CLASS_DECL_ca2 UINT AFX_CDECL application_thread_procedure(LPVOID pvoid);

   typedef ::ca::application * (* LPFN_instantiate_application)(::ca::application * pappParent, const char * pszId);

   extern CLASS_DECL_ca2 LPFN_instantiate_application g_lpfn_instantiate_application;



} // namespace cube8

