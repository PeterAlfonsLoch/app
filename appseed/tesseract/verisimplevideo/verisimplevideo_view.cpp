#include "StdAfx.h"


namespace verisimplevideo
{


   view::view(::ca::application * papp) :
      ca(papp),
      ::user::interaction(papp),
      ::userbase::view(papp),
      m_file(papp),
      KaraokeView(papp),
      midi_player_callback(papp),
      midi_player_interface(papp),
      WavePlayerInterface(papp),
      WaveRecorderInterface(papp),
      gcom::backview::Interface(papp),
      gcom::backview::user::interaction(papp),
      mediaplay::view_interface(papp),
      mediaplay::view(papp)

   {

      m_pplayer = AfxBeginThread < video::player > (get_app());
      m_bEnableShowGcomBackground = true;

   }

   view::~view()
   {
   }

   void view::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      ::mediaplay::view::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &view::_001OnTimer);
      connect_command("execute_play", &view::_001OnExecutePlay);
   }

   /////////////////////////////////////////////////////////////////////////////
   // ::view diagnostics

#ifdef _DEBUG
   void view::assert_valid() const
   {
      ::userbase::view::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::userbase::view::dump(dumpcontext);
   }
#endif //_DEBUG


   BOOL view::PreCreateWindow(CREATESTRUCT& cs)
   {
      cs.lpszClass = System.RegisterWndClass(
         CS_DBLCLKS |
         CS_OWNDC,
         0, 0, 0);
      cs.style &= ~WS_EX_CLIENTEDGE;
      return ::userbase::view::PreCreateWindow(cs);
   }

   void view::on_update(::view * pSender, LPARAM lHint, ::radix::object* phint) 
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(phint);
      if(lHint == 12)
      {
         video::player_command command;


         m_file = Application.get_file(get_document()->m_strOpenPath, ex1::file::type_binary | ex1::file::mode_read | ex1::file::shareDenyNone);

         command.OpenFile(m_file);
         m_pplayer->ExecuteCommand(command);

         command.Play();
         m_pplayer->ExecuteCommand(command);

         GetParentFrame()->SetActiveView(this);
      }
      else if(lHint == 123)
      {
         video::player_command command;


         command.Stop();
         m_pplayer->ExecuteCommand(command);

         m_pplayer->m_eventStopped.wait(seconds(60));

         GetParentFrame()->SetActiveView(this);
      }
      ::mediaplay::view_update_hint * puh = dynamic_cast < ::mediaplay::view_update_hint * > (phint);
      if(lHint == 19847 || (puh != NULL && puh->is_type_of(mediaplay::view_update_hint::TypeAfterOpenDocument)))
      {
         imedia::position position;
         position = 0;
         _ExecutePlay(true, position);
      }

      mediaplay::view::on_update(pSender, lHint, phint);
   }



   void view::layout() 
   {

      rect rectClient;

      GetClientRect(m_pplayer->m_rectClient);

      m_pplayer->layout();


   }



   void view:: _001OnDraw(::ca::graphics * pdc)
   {
      if(!m_pplayer->IsPlaying())
      {
         pdc->TextOut(49, 49, "Carregado ou a Caminho... sei lá...");
         return;
      }

      rect rectClient;

      GetClientRect(rectClient);

      m_pplayer->m_ptView.x = (rectClient.width() - m_pplayer->m_sizeView.cx) / 2;
      m_pplayer->m_ptView.y = (rectClient.height() - m_pplayer->m_sizeView.cy) / 2;

      m_pplayer->_001OnDraw(pdc);
      //pdc->TextOut(49, 49, "ca2 verisimplevideo");
   }

   void view::_001OnCreate(gen::signal_object * pobj) 
   {
      if(pobj->previous())
         return;
      m_pplayer->m_pmediaplaydocument = get_document();
   }

   void view::_001OnTimer(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
   }


   document * view::get_document()
   {
      return dynamic_cast < document * > (::userbase::view::get_document());
   }


   void view::_001OnExecutePlay(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      m_pplayer->m_pdecoder->DecoderSeekBegin();


      video::player_command command;


      command.Play();
      m_pplayer->ExecuteCommand(command);
   }


} // namespace verisimplevideo
