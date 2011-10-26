#include "StdAfx.h"


namespace eluce
{

   view::view(::ca::application * papp) :
      ca(papp),
      ::userbase::view(papp)
   {
   }

   view::~view()
   {
   }

   void view::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::view::install_message_handling(pinterface);

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
      ::userbase::view::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::userbase::view::dump(dumpcontext);
   }
   #endif 

   BOOL view::PreCreateWindow(CREATESTRUCT& cs)
   {
      cs.lpszClass = System.RegisterWndClass(
         CS_DBLCLKS |
         CS_OWNDC,
         0, 0, 0);
      cs.style &= ~WS_EX_CLIENTEDGE;
      return ::userbase::view::PreCreateWindow(cs);
   }
   void view::_001OnInitialUpdate(gen::signal_object * pobj) 
   {
      ::userbase::view::_001OnInitialUpdate(pobj);

   }

   void view::on_update(::view * pSender, LPARAM lHint, ::radix::object* phint) 
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);
   }

   void view::_001OnDestroy(gen::signal_object * pobj) 
   {
      ::userbase::view::_001OnDestroy(pobj);
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
      ::ca::dib * pdib = dynamic_cast < ::eluce::document * > (get_document())->m_spdib;
      rect rectClient;
      GetClientRect(rectClient);
      pdc->SetStretchBltMode(HALFTONE);
      double dx = (double) rectClient.width() / (double) max(1, pdib->width());
      double dy = (double) rectClient.height() / (double) max(1, pdib->height());
      double dr = min(dx, dy);
      if(dr == 0)
         return;

      rect rectBall;
      rectBall.left     = (LONG) ((rectClient.width() - (pdib->width() * dr)) / 2);
      rectBall.top      = (LONG) ((rectClient.height() - (pdib->height() * dr)) / 2);
      rectBall.right    = (LONG) (rectBall.left + (pdib->width() * dr));
      rectBall.bottom   = (LONG) (rectBall.top + (pdib->height() * dr));
                  visual::dib_sp dib(get_app());
            visual::dib_sp dib2(get_app());
            visual::dib_sp dib12(get_app());
            dib->create(rectBall.size());
            dib2->create(pdib->size());
            dib12->create(rectBall.size());
            ::ca::draw_dib_sp drawdib(get_app());
            dib->get_graphics()->SetStretchBltMode(HALFTONE);
            dib2->from(pdib->get_graphics());
            dib2->channel_copy(visual::rgba::channel_red, visual::rgba::channel_alpha);
            dib12->get_graphics()->SetStretchBltMode(HALFTONE);
            drawdib->draw(
               dib->get_graphics(),
               0,
               0,
               rectBall.width(),
               rectBall.height(),
               pdib,
               0, 0,
               pdib->width(), 
               pdib->height(),
               SRCCOPY);
            drawdib->draw(
               dib12->get_graphics(),
               0,
               0,
               rectBall.width(),
               rectBall.height(),
               dib2,
               0, 0,
               dib2->width(), 
               dib2->height(),
               SRCCOPY);
            dib12->channel_copy(visual::rgba::channel_alpha, visual::rgba::channel_red);
            //System.imaging().blur(dib->get_graphics(), null_point(), rectBall.size(), dib->get_graphics(), null_point(), -1);
            //System.imaging().blur(dib2->get_graphics(), null_point(), rectBall.size(), dib2->get_graphics(), null_point(), -1);
            //dib->get_graphics()->SetStretchBltMode(HALFTONE);
            //dib->get_graphics()->StretchBlt(0, 0, rectBall.width(), rectBall.height(), m_dibBall->get_graphics(), 0, 0, m_dibBall->width(), m_dibBall->height(), SRCCOPY);
            System.imaging().bitmap_blend(pdc, rectBall.top_left(), rectBall.size(), dib->get_graphics(), null_point(), dib12->get_graphics(), null_point());


   }

   void view::_001OnCreate(gen::signal_object * pobj) 
   {
      if(pobj->previous())
         return;
      
      SetTimer(123, 240, NULL);


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

} // namespace eluce
