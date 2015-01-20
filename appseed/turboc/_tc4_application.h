#pragma once


namespace tc4
{


   class CLASS_DECL_APP_CORE_TC4 application :
      public ::turboc::application
   {
   public:
   
   
      enum e_type
      {
      
         type_normal,
         type_mili,
      
      };
      

      e_type                                 m_etype;
      string                                 m_strHelloMultiverse;
      string                                 m_strAlternateHelloMultiverse;

      bool                                   m_bMultiverseChat;
      
      
      ::user::single_document_template *     m_ptemplateHelloMultiverseMain;
      ::user::single_document_template *     m_ptemplateHelloMultiverseView;
      ::user::single_document_template *     m_ptemplateHelloMultiverseSwitcher;

      mutex                                  m_mutexAiFont;


      application();
      virtual ~application();


      virtual bool initialize_instance();
      virtual int32_t  exit_instance();

      virtual void on_request(sp(::create) pcreatecontext);

      static UINT thread_proc_load_ai_font(void * pparam);
      virtual void load_ai_font();
      int32_t                 m_iErrorAiFont;
      bool                    m_bLoadAiFont;
      void *                  m_faceAi; // FT_Face m_faceAi;



   };


} // namespace tc4



