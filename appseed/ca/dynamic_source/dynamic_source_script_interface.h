#pragma once


namespace dynamic_source
{


   class script;
   class script_manager;


   class httpd_socket;

   
   class CLASS_DECL_ca script_interface :
      virtual public ::ca2::html_file
   {
   public:


      script *                            m_pscript;
      script_manager *                    m_pmanager;

      httpd_socket *                      m_pnetnodesocket;

      script_interface *                  m_pinstanceParent;
      script_interface *                  m_pinstanceMain;


      int                                 m_iDebug;
      


      virtual void run();


      virtual void dinit();
      virtual void dprint(const char *);



      virtual gen::property     & get(const char * pszKey);


      virtual bool main_initialize();
      virtual bool main_finalize();


      virtual ::http::file & output_file();

   };


} // namespace dynamic_source



