#pragma once


namespace dynamic_source
{


   class script;
   class script_manager;


   class httpd_socket;

   
   class CLASS_DECL_CORE script_interface :
      virtual public ::html::file
   {
   public:


      
      script_interface *                  m_pinstanceMain;
      script_interface *                  m_pinstanceParent;
      httpd_socket *                      m_pnetnodesocket;
      script_manager *                    m_pmanager;


      sp(::file::memory_buffer)           m_spmemoryfileFallback;
      ::file::output_stream               m_ostreamFallback;

      script *                            m_pscript;

      int32_t                             m_iDebug;

      var                                 m_varRet;

      string                              m_strDebugRequestUri;
      string                              m_strDebugThisScript;

      
      script_interface();
      virtual ~script_interface();


      virtual void destroy();


      virtual void run();


      virtual void dinit();
      virtual void dprint(const char *);



      virtual property     & get(const char * pszKey);


      virtual bool main_initialize();
      virtual bool main_finalize();


      virtual ::file::stream_buffer & output_file();
      virtual ::file::output_stream & ostream();


      virtual void on_initialize();
      virtual void initialize(script_interface * pinterfaceMain, script_interface * pinterfaceParent, httpd_socket * pdssocket, script_manager * pmanager);
      
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


      virtual void set_session_value(id id, var value);
      virtual var get_session_value(id id);
      virtual string session_id(const char * pszId = NULL);

   };


} // namespace dynamic_source



