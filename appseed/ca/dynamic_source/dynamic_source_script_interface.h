#pragma once


namespace dynamic_source
{


   class script;
   class script_manager;


   class httpd_socket;

   
   class CLASS_DECL_ca script_interface :
      virtual public ::html::file
   {
      
      script_interface *                  m_pinstanceMain;
      script_interface *                  m_pinstanceParent;
      httpd_socket *                      m_pnetnodesocket;
      script_manager *                    m_pmanager;


   public:


      sp(::http::memory_file)             m_spmemoryfileFallback;

      script *                            m_pscript;

      



      int32_t                                 m_iDebug;
      
      script_interface();
      virtual ~script_interface();

      virtual void run();


      virtual void dinit();
      virtual void dprint(const char *);



      virtual ::ca::property     & get(const char * pszKey);


      virtual bool main_initialize();
      virtual bool main_finalize();


      virtual ::http::file & output_file();


      virtual void on_initialize();
      virtual void initialize(script_interface * pinterfaceMain, script_interface * pinterfaceParent, httpd_socket * pnetnodesocket, script_manager * pmanager);
      
      script_interface * main_instance()
      {
         return m_pinstanceMain;
      }

      script_interface * parent()
      {
         return m_pinstanceParent;
      }

      httpd_socket * netnodesocket()
      {
         return m_pnetnodesocket;
      }

      script_manager * manager()
      {
         return m_pmanager;
      }

   };


} // namespace dynamic_source



