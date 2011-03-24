#include "StdAfx.h"

namespace verisimplevideo
{

   view::view(::ca::application * papp) :
      ca(papp),
      ::user::interaction(papp),
      ::userbase::view(papp),
      m_file(papp)
   {
      m_pplayer = AfxBeginThread < video::player > (get_app());
      
   }

   view::~view()
   {
   }

   void view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::view::_001InstallMessageHandling(pinterface);

      IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &view::_001OnSize);
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
      if(lHint == 123)
      {
         video::player_command command;


         m_file->open(get_document()->m_strOpenPath, ex1::file::type_binary | ex1::file::mode_read | ex1::file::shareDenyNone);

         command.OpenFile(m_file);
         m_pplayer->ExecuteCommand(command);

         command.Play();
         m_pplayer->ExecuteCommand(command);

         GetParentFrame()->SetActiveView(this);
      }
   }

   void view::_001OnSize(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::user::win::message::size, psize, pobj)
   }



   void view:: _001OnDraw(::ca::graphics * pdc)
   {
      if(!m_pplayer->IsPlaying())
      {
         pdc->TextOut(49, 49, "Carregado ou a Caminho... sei lá...");
         return;
      }
      m_pplayer->_001OnDraw(pdc);
      pdc->TextOut(49, 49, "ca2 verisimplevideo");
   }

   void view::_001OnCreate(gen::signal_object * pobj) 
   {
      if(pobj->previous())
         return;
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
      m_pplayer->m_pdecoder->DecoderSeekBegin();


      video::player_command command;


      command.Play();
      m_pplayer->ExecuteCommand(command);
   }


} // namespace verisimplevideo
