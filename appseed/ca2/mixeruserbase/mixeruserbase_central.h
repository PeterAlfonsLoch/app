#pragma once


namespace mixeruserbase
{


   class thread;


   class CLASS_DECL_ca central :
      virtual public ::user::interaction
   {
   public:

      id                                           m_idPlaybackPane;
      string                                       m_strPlaybackTitle;
      string                                       m_strPlaybackIcon;


      id                                           m_idRecordingPane;
      string                                       m_strRecordingTitle;
      string                                       m_strRecordingIcon;

      thread *                                     m_pthread;
      ::userbase::multiple_document_template *     m_pdoctemplate;


      central(::ca::application * papp);
      virtual ~central();
   
      virtual void install_message_handling(::user::win::message::dispatch * pinterface);
      ::userbase::multiple_document_template * get_document_template();

      ::userbase::multiple_document_template * CreateDocTemplate(::ca::application * papp);
      void on_thread_exit_instance();
      void DisplayAMixer();
      bool Initialize(::ca::application * papp);
      static void SetMIXERVISUALCENTRAL(central * pMIXERVISUALCENTRAL);

      DECL_GEN_SIGNAL(_001OnClose)

   };


} // namespace mixeruibase

