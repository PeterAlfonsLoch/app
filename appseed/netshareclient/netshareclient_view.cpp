#include "StdAfx.h"


namespace netshareclient
{

   view::view(::ca::application * papp) :
      ca(papp),
      ::userbase::view(papp)
   {
      m_bHover = false;
   }

   view::~view()
   {
   }

   void view::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::view::install_message_handling(pinterface);

	   IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &view::_001OnDestroy);
	   IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &view::_001OnSize);
	   IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &view::_001OnPaint);
	   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &view::_001OnCreate);
	   IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &view::_001OnContextMenu);
	   IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &view::_001OnSetCursor);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &view::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &view::_001OnMouseMove);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &view::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &view::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_USER + 1024, pinterface, this, &view::_001OnUser1024);
      IGUI_WIN_MSG_LINK(WM_MOUSELEAVE, pinterface, this, &view::_001OnMouseLeave);


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
      cs.lpszClass = Application.RegisterWndClass(
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

   void view::on_update(::view* pSender, LPARAM lHint, ::radix::object* phint) 
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

      double d = psize->m_size.cy;
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

   void view::_001OnPaint(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
	   //CPaintDC spgraphics(this); // device context for painting
      

     // spgraphics->TextOut(20, 20, "Carlos Gustavo Cecyn Lundgren é minha Vida Eterna, meu Coração Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
   }


   void view:: _001OnDraw(::ca::graphics * pdc)
   {
      single_lock sl(&m_parea->m_cs, TRUE);

      //::SendMessage(::GetDesktopWindow(), WM_PRINT, (WPARAM)(HDC)spgraphics, PRF_CHILDREN | PRF_NONCLIENT | PRF_CLIENT);

      rect rectClient;
      GetClientRect(rectClient);

      pdc->from(rectClient.size(), m_parea->m_dib1->get_graphics(), SRCCOPY);

      //point pt = m_pthread->m_tunnel.m_ptCursor;
      //pdc->FillSolidRect(pt.x - 2, pt.y - 2, 4, 4, RGB(0, 0, 255));
      //pdc->TextOut(20, 20, "Curitiba, 24 de fevereiro de 2008.");
      //pdc->TextOut(20, 80, "Carlos Gustavo Cecyn Lundgren é minha Vida Eterna, meu Coração Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
      //pdc->TextOut(20, 110, "Assinado Camilo Sasuke Tsumanuma.");

   }

   void view::_001OnCreate(gen::signal_object * pobj) 
   {
      if(pobj->previous())
         return;
      
      m_parea = new netshareclient::area(get_app());

      m_parea->m_dib1->create(1280, 1024);
      m_parea->m_dib2->create(1280, 1024);

      m_ecursor = ::visual::cursor_none;

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
         Application.simple_message_box(NULL,"Playlist");
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

   void view::_001OnTimer(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::timer, ptimer, pobj)

      if(ptimer->m_nIDEvent == 123)
      {
         /*gen::property_set post;
         gen::property_set headers;
         string strQuery;
         point pt;
         Application.get_cursor_pos(&pt);
         ScreenToClient(&pt);
         m_pthread->m_tunnel.set_cursor(pt.x, pt.y);*/
   /*   System.http().ms_download("http://" + m_strServer + "/set_cursor_pos?" + strQuery, "C:\\file2.txt",
            (dynamic_cast < ::fontopus::user * >(System.user().get_user()))->m_phttpcookies,
            post, headers, System.user().get_user());
         System.http().ms_download("http://" + m_strServer + "/snapshot.png", "C:\\file1.png",
            (dynamic_cast < ::fontopus::user * >(System.user().get_user()))->m_phttpcookies,
            post, headers, System.user().get_user());
         FIBITMAP * pfi1 = FreeImage_Load(FIF_PNG, "C:\\file1.png", 0);

      FIBITMAP * pfi2 = FreeImage_ConvertTo32Bits(pfi1);
      single_lock sl(&m_parea->m_cs, TRUE);
      void * pdata = FreeImage_GetBits(pfi2);
   //   if(str == "I")
      {
         memcpy(m_parea->m_dib1.m_pcolorref, pdata, 
            m_parea->m_dib1.m_size.cx * m_parea->m_dib1.m_size.cy * 4);
      }
     /* else
      {
         memcpy(m_parea->m_dib2.m_pcolorref, pdata, 
            m_parea->m_dib2.m_size.cx * m_parea->m_dib2.m_size.cy * 4);
         m_parea->m_dib1.xor(&m_parea->m_dib2);
      }*/
      /*FreeImage_Unload(pfi2);
      FreeImage_Unload(pfi1);
         _001RedrawWindow();*/
      }
   }

   void view::_001OnMouseMove(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
      point ptCursor;
      ptCursor = pmouse->m_pt;
      ScreenToClient(&ptCursor);
      m_pthread->m_tunnel.m_ptCursor = ptCursor;
      Bergedge.m_bDrawCursor = false;
      rect rectClient;
      GetClientRect(rectClient);
      bool bHover = rectClient.contains(ptCursor);
      pmouse->m_ecursor = ::visual::cursor_none;
      m_ecursor = ::visual::cursor_none;
      track_mouse_hover();
      if(!m_bHover)
      {
         if(bHover)
         {
            m_bHover = true;
         }
      }
      else
      {
         if(!bHover)
         {
            m_bHover = false;
         }
      }
   }

   void view::_001OnMouseLeave(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)

      m_bHover = false;
      Bergedge.m_bDrawCursor = true;

      rect rectClient;
      GetClientRect(rectClient);

      point ptCursor;
      Bergedge.get_cursor_pos(&ptCursor);
      ScreenToClient(&ptCursor);

      if(ptCursor.x < (rectClient.width() / 2))
      {
         if(ptCursor.y < (rectClient.height() / 2))
         {
            if(ptCursor.x < ptCursor.y)
            {
               ptCursor.x = 0;
            }
            else
            {
               ptCursor.y = 0;
            }
         }
         else
         {
            if(ptCursor.x < (rectClient.height() - ptCursor.y))
            {
               ptCursor.x = 0;
            }
            else
            {
               ptCursor.y = rectClient.height();
            }
         }
      }
      else
      {
         if(ptCursor.y < (rectClient.height() / 2))
         {
            if((rectClient.width() - ptCursor.x) < ptCursor.y)
            {
               ptCursor.x = rectClient.width();
            }
            else
            {
               ptCursor.y = 0;
            }
         }
         else
         {
            if((rectClient.width() - ptCursor.x) < (rectClient.height() - ptCursor.y))
            {
               ptCursor.x = rectClient.width();
            }
            else
            {
               ptCursor.y = rectClient.height();
            }
         }
      }
      m_pthread->m_tunnel.m_ptCursor = ptCursor;
   }

   void view::_001OnLButtonDown(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
      m_pthread->m_tunnel.m_ptCursor = pt;
      string strEvent;
      strEvent.Format("/l_button_down?x=%d&y=%d", pt.x, pt.y);
      m_pthread->m_tunnel.m_straEvent.add(strEvent);
      pmouse->m_bRet = true;
      pmouse->set_lresult(1);
   }

   void view::_001OnLButtonUp(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
      m_pthread->m_tunnel.m_ptCursor = pt;
      string strEvent;
      strEvent.Format("/l_button_up?x=%d&y=%d", pt.x, pt.y);
      m_pthread->m_tunnel.m_straEvent.add(strEvent);
      pmouse->m_bRet = true;
      pmouse->set_lresult(1);
   }

   void view::_001OnUser1024(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj)

      if(pbase->m_wparam == 0
      && pbase->m_lparam == 0)
      {
         _001RedrawWindow();
      }
   }

   bool view::netshare(const char * pszServer) 
   {
      

      if(GetParent()->GetParent() != NULL)
      {
         GetParent()->GetParent()->layout();
      }

      if(GetParent() != NULL)
      {
         GetParent()->layout();
      }

      layout();

      m_strServer = pszServer;
      m_pthread = new netshareclient::thread(get_app());
      m_pthread->m_tunnel.m_pview = this;
      m_pthread->m_tunnel.m_parea = m_parea;
      m_pthread->m_tunnel.m_strUrl = "https://" + m_strServer + "/";
      m_pthread->m_tunnel.m_host = m_strServer;
      m_pthread->m_tunnel.m_port = 443;
      //GetTopLevelFrame()->ShowWindow(SW_SHOW);
      m_pthread->Begin();
      return true;
   }
         

} // namespace netshareclient
