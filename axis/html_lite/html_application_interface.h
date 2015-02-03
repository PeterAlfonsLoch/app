#pragma once


namespace html
{


   class CLASS_DECL_HTML application_interface :
      virtual public ::aura::application_interface
   {
   public:


      /*index                                        m_iNewEdge;

      mutex                                        m_mutex;
      mutex                                        m_mutexDelete;
      class ::core::stra                           m_stra;
      class ::core::service                        m_service;

      class ::core::patch                          m_patch;*/

      application_interface();
      virtual ~application_interface();


      virtual void construct(const char * pszAppId);

      virtual bool is_system();

      //virtual bool process_initialize();

      //virtual bool initialize2();

      //virtual bool initialize_instance();

      //virtual bool finalize();

      //virtual int32_t exit_instance();



      //virtual int32_t main();
      //virtual bool InitApplication();

      //virtual bool initialize();
      //virtual bool initialize1();
      //virtual bool initialize3();

      //virtual bool bergedge_start();


      inline ::html::html *                 html()         { return m_pauraapp->m_pcoresystem->m_phtml; }
      virtual ::html::html * create_html();



      DECL_GEN_SIGNAL(on_application_signal);
      //void assert_valid() const;
      //void dump(dump_context & context) const;


   };


} // namespace html





