#pragma once

namespace icube
{



   class CLASS_DECL_ca application : 
      virtual public ::fontopus::application
   {
   public:



      class ::ca::dir::application        m_dir;

      class ::ca2::file::application      m_file;
      class ::ca4::http::application      m_http;


      application();
      virtual ~application();


      class ::ca::dir::application        & dir();

      class ::ca2::file::application      & file();
      class ::ca4::http::application      & http(); 

      virtual void defer_initialize_twf();

      virtual int pre_run();
      virtual int on_run();

      virtual int main();
      virtual bool bergedge_start();
      virtual bool os_native_bergedge_start();


      virtual ::ca::application * instantiate_application(const char * pszId);
      virtual ::ca::application * create_application(const char * pszId, bool bSynch, ::ca::application_bias * pbias);

   };

   CLASS_DECL_ca application & app_cast(::ca::ca * papp);

   CLASS_DECL_ca UINT AFX_CDECL application_thread_procedure(LPVOID pvoid);

   typedef ::ca::application * (* LPFN_instantiate_application)(::ca::application * pappParent, const char * pszId);

   extern CLASS_DECL_ca LPFN_instantiate_application g_lpfn_instantiate_application;



} // namespace icube

