#include "StdAfx.h"
#include "mixeruserbase_frame_window.h"
#include "mixeruserbase_thread.h"


namespace mixeruserbase
{


   central::central(::ca::application * papp) :
      ca(papp)
   {
      m_pdoctemplate = NULL;
   }

   central::~central()
   {
      if(m_pdoctemplate != NULL)
      {
         delete m_pdoctemplate;
         m_pdoctemplate = NULL;
      }
   }




   void central::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      ::user::interaction::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CLOSE, pinterface, this, &central::_001OnClose);
   }

   void central::_001OnClose(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
      DestroyWindow();
   }





   ::userbase::multiple_document_template * central::CreateDocTemplate(::ca::application * papp)
   {

      if(m_pdoctemplate == NULL)
      {
         m_pdoctemplate = new ::userbase::multiple_document_template(
            papp,
            "mixeruserbase/mixer",
            ::ca::get_type_info < document > (),
            ::ca::get_type_info < frame_window > (),
            ::ca::get_type_info < main_view > ());
      }
      return m_pdoctemplate;
   }

   bool central::Initialize(::ca::application * papp)
   {
      set_app(papp);
      m_pthread = AfxBeginThread < thread >(get_app());

      if(m_pthread == NULL)
         return false;


   
   

      m_idPlaybackPane        = "mixeruibase::playback_pane";
      m_strPlaybackIcon       = "matter://mixer/icon_playback_16.png";
      m_strPlaybackTitle      = "<string id='mplite:mixer_playback_tab'>Playback</string>";

      m_idRecordingPane       = "mixeruibase::recording_pane";
      m_strRecordingIcon      = "matter://mixer/icon_recording_16.png";
      m_strRecordingTitle     = "<string id='mplite:mixer_recording_tab'>Recording</string>";

      m_pthread->m_event.wait();

      thread::initialize * pinitialize = new thread::initialize;

      pinitialize->m_pcentral = this;

      m_pthread->PostThreadMessage(
         thread::MessageMain,
         thread::MessageMainWparamInitialize,
         (LPARAM) pinitialize);

      CreateDocTemplate(get_app());

      if(get_document_template() == NULL)
         return false;

      return true;
   }

   void central::DisplayAMixer()
   {
      m_pthread->PostThreadMessage(
         thread::MessageMain,
         thread::MessageMainWparamDisplayAMixer,
         0);
   }

   void central::on_thread_exit_instance()
   {
      m_pdoctemplate->close_all_documents(false);
   }

   ::userbase::multiple_document_template * central::get_document_template()
   {
      return m_pdoctemplate;
   }



} // namespace mixeruserbase


