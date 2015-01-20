#pragma once


namespace turboc
{


   class CLASS_DECL_TURBOC application:
      virtual public ::sphere::application
   {
   public:
      enum e_type
      {

         type_normal,
         type_mili,

      };


      e_type                                 m_etype;


      string                                 m_strTurboC;
      string                                 m_strAlternateTurboC;

      bool                                   m_bMultiverseChat;


      ::user::single_document_template *     m_ptemplateHelloMultiverseMain;
      ::user::single_document_template *     m_ptemplateHelloMultiverseView;
      ::user::single_document_template *     m_ptemplateHelloMultiverseSwitcher;

      mutex                                  m_mutexAiFont;

      int32_t                                m_iErrorAiFont;
      bool                                   m_bLoadAiFont;
      void *                                 m_faceAi;

      context *                              m_pcontext;

      ::turboc::main *                       m_pmain;

      PFN_MAIN                               m_pfnmainMain;


      application();
      virtual ~application();


      virtual bool initialize_instance();


      virtual bool start_main();
      virtual bool start_main(PFN_MAIN pfnMain);







      virtual int32_t  exit_instance();

      virtual void on_request(sp(::create) pcreatecontext);

      static UINT thread_proc_load_ai_font(void * pparam);
      virtual void load_ai_font();

   };


} // namespace userstack




