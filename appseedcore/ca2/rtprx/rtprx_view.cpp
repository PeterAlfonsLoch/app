#include "StdAfx.h"


namespace rtprx
{

   view::view(::ca::application * papp) :
      ca(papp),
      ::userbase::view(papp),
      gcom::backview::Interface(papp),
      gcom::backview::user::interaction(papp),
      KaraokeView(papp),
      ::mediaplay::view_interface(papp),
      mediaplay::view(papp),
      midi_player_interface(papp),
      m_spdib(papp),
      audio::WavePlayerInterface(papp),
      audio::WaveRecorderInterface(papp),
      midi_player_callback(papp)
   {
   }

   view::~view()
   {
   }

   void view::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      mediaplay::view::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &view::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &view::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &view::_001OnContextMenu);
      IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &view::_001OnSetCursor);
      IGUI_WIN_MSG_LINK(WM_ERASEBKGND, pinterface, this, &view::_001OnEraseBkgnd);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &view::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &view::_001OnMouseMove);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &view::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &view::_001OnLButtonUp);

   //   IGUI_WIN_MSG_LINK(WM_USER + 177     , this, this, &view::_001OnTabClick);
   //   IGUI_WIN_MSG_LINK(WM_APP + 119      , this, this, &view::_001OnWavePlayerEvent);
      //connect_command(ID_FILE_PRINT, ::userbase::view::OnFilePrint)
      //connect_command(ID_FILE_PRINT_DIRECT, ::userbase::view::OnFilePrint)
      //connect_command(ID_FILE_PRINT_PREVIEW, ::userbase::view::OnFilePrintPreview)


   }

   #ifdef _DEBUG
   void view::assert_valid() const
   {
      ::mediaplay::view::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::mediaplay::view::dump(dumpcontext);
   }
   #endif 

   BOOL view::PreCreateWindow(CREATESTRUCT& cs)
   {
      cs.lpszClass = System.RegisterWndClass(
         CS_DBLCLKS |
         CS_OWNDC,
         0, 0, 0);
      cs.style &= ~WS_EX_CLIENTEDGE;
      return ::mediaplay::view::PreCreateWindow(cs);
   }
   void view::_001OnInitialUpdate(gen::signal_object * pobj) 
   {
      ::mediaplay::view::_001OnInitialUpdate(pobj);

   }

   void view::on_update(::view * pSender, LPARAM lHint, ::radix::object* phint) 
   {
      ::mediaplay::view::on_update(pSender, lHint, phint);

      view_update_hint * puh = dynamic_cast < view_update_hint * > (phint);
      if(puh != NULL && puh->m_etype == view_update_hint::TypeOpenDocument)
      {
         m_spdib.load_from_file(get_document()->get_path_name());
      }   
      {
         ::mediaplay::view_update_hint * puh = dynamic_cast < ::mediaplay::view_update_hint * > (phint);
         if(lHint == 19847 || (puh != NULL && puh->is_type_of(mediaplay::view_update_hint::TypeAfterOpenDocument)))
         {
            imedia::position position;
            position = 0;
            _ExecutePlay(true, position);
         }
      }
   }

   void view::_001OnDestroy(gen::signal_object * pobj) 
   {
      ::mediaplay::view::_001OnDestroy(pobj);
   }

   void view::_001OnSize(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::user::win::message::size, psize, pobj)

   /*   pobj->previous();

      double d = psize->height();
      d /= GetSystemMetrics(SM_CYSCREEN);
      SetScale(d);

      GetClientRect(m_rectKaraokeView);


      rect rectClient;
      GetClientRect(rectClient);
      rect rect = rectClient;

      rect.top = rect.bottom - 24;
      m_viewlineStatus.SetPlacement(rect);


      m_rectKaraokeView.bottom -= 16;

      LayoutTitleLines();
      LayoutLyricTemplateLines();
      LayoutLyricLines();
      LayoutKaraokeBouncingBall();*/
   }

   void view:: _001OnDraw(::ca::graphics * pdc)
   {
      //m_spdib->to(pdc, m_spdib->width(), m_spdib->height());
      rect rectClient;
      GetClientRect(rectClient);
      pdc->SetStretchBltMode(HALFTONE);
      double dx = (double) rectClient.width() / (double) max(1, m_spdib->width());
      double dy = (double) rectClient.height() / (double) max(1, m_spdib->height());
      double dr = min(dx, dy);
      if(dr == 0)
         return;
      pdc->StretchBlt(0, 0, 
         (int) (m_spdib->width() * dr),
         (int) (m_spdib->height() * dr),
         m_spdib->get_graphics(),
         0, 0, 
         m_spdib->width(), 
         m_spdib->height(),
         SRCCOPY);

   }

   void view::_001OnCreate(gen::signal_object * pobj) 
   {
      
      application * papp = dynamic_cast < application * > (get_app());

   //   ::database::client::initialize(papp);


      if(!view::Initialize(&papp->GetMidiCentral()))
      {
         return;
      }

      if(pobj->previous())
         return;



      SetTimer(gen::Timer::ID_HOVER, 100, NULL);



      
      
   /* dbbreak   if(DILoad("GradualFilling", i))
      {
         m_bGradualFilling = i != 0;
      }
      if(data_get("BouncingBall", i))
      {
         m_bBouncingBall = i != 0;
      }*/
      /*
      bool bListenMinusOne;
      string str;
      str = get_data()->get_path_name();
      if(DBListenMinusOne(false, get_data()->get_path_name(), bListenMinusOne))
      {
        _ExecuteListenMinusOne(bListenMinusOne);
      }

      document * pdoc = dynamic_cast < document * > (get_document());
      SetKaraokeData(&pdoc->get_data()->GetKaraokeData());
//      m_lpbouncingball->SetKaraokeData(&pdoc->get_data()->GetKaraokeData());

      if(GetMidiPlayer() == NULL)
         if(!OpenMidiPlayer())
         {
            ASSERT(FALSE);
            throw 0;
         }

      //SetTimer(0, 50, NULL);

      m_lyrictemplatelines.remove_all();
      m_lyrictemplatelines.set_size(4);

      PrepareLyricTemplateLines();*/

   /*   audWaveCentral & wavecentral =
      audWaveCentralContainer::AppGetAudioWaveCentral();
      audWaveIn * pwavein = wavecentral.GetWaveIn();

      pwavein->Start();*/



   }

   void view::_001OnContextMenu(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::context_menu, pcontextmenu, pobj)
      point point = pcontextmenu->GetPoint();
   }

   void view::_001OnTabClick(int iTab)
   {
      if(iTab == 1)
      {
         System.simple_message_box(NULL, "Playlist");
      }
   }

   //void view::_001OnWavePlayerEvent(gen::signal_object * pobj)
   //{
     // SCAST_PTR(::user::win::message::base, pbase, pobj)
   //}

   //void view::_001OnUpdateViewEncoding(gen::signal_object * pobj)
   //{
     // SCAST_PTR(::user::win::message::update_cmd_ui, pupdatecmdui, pobj)
   //}
   //void view::_001OnViewEncoding(gen::signal_object * pobj)
   //{
     // SCAST_PTR(::user::win::message::command, pcommand, pobj)
   //}


   /*xxxvoid view::data_on_after_change(int iConfigurationId, int iLine, int iColumn, CVmsDataUpdateHint * puh)
   {
      if(iConfigurationId == _vmsp::CConfiguration::CfgKaraokeEncoding)
      {
         PrepareLyricLines();
         RedrawWindow();
      }
   }*/


   void view::_001OnSetCursor(gen::signal_object * pobj) 
   {
      ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
      
      pobj->previous();
   }
   void view::_001OnEraseBkgnd(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::erase_bkgnd, perasebkgnd, pobj)
      perasebkgnd->m_bRet = true;
      perasebkgnd->set_result(TRUE);
   }

   void view::_001OnTimer(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::timer, ptimer, pobj)

      if(ptimer->m_nIDEvent == 123)
      {
         gen::property_set post;
         gen::property_set headers;
         string strQuery;
         point pt;
         System.get_cursor_pos(&pt);
         ScreenToClient(&pt);
      }
   }

   void view::_001OnMouseMove(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
      string strQuery;
         gen::property_set post;
         gen::property_set headers;


   }

   void view::_001OnLButtonDown(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
   }

   void view::_001OnLButtonUp(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
   }

} // namespace rtprx
