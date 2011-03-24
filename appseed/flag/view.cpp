#include "StdAfx.h"
#include <math.h>


namespace flag
{

   view::view(::ca::application * papp) :
      ca(papp),
      ::userbase::view(papp)
   {
   }

   view::~view()
   {
   }

   void view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::view::_001InstallMessageHandling(pinterface);

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

   //	IGUI_WIN_MSG_LINK(WM_USER + 177     , this, this, &view::_001OnTabClick);
   //	IGUI_WIN_MSG_LINK(WM_APP + 119      , this, this, &view::_001OnWavePlayerEvent);
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

   void view::on_update(::view * pSender, LPARAM lHint, ::radix::object* phint) 
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      view_update_hint * puh = dynamic_cast < view_update_hint * > (phint);
      if(puh != NULL && puh->m_etype == view_update_hint::TypeOpenDocument)
      {
       //  class rect rectClient(0, 0, 884, 884);
         ///::visual::dib_sp dib(get_app());
         /*if(Application.m_puiInitialPlaceHolderContainer != NULL)
         {
            simple_frame_window * pframe1 = dynamic_cast < simple_frame_window * > (Application.m_puiInitialPlaceHolderContainer->GetParentFrame());
            pframe1->WfiFullScreen(true, false);
            simple_frame_window * pframe2;
            if(Application.command_line().m_varQuery.has_property("client_only"))
            {
               pframe2 = dynamic_cast < simple_frame_window * > (GetParentFrame());
            }
            else
            {
               pframe2 = dynamic_cast < simple_frame_window * > (GetParentFrame()->GetParentFrame());
            }
            pframe2->WfiFullScreen(true, false);
         }*/
         /*if(dib->area() > 0)
         {
            double dx = (double) rectClient.width() / (double) max(1, dib->width());
            double dy = (double) rectClient.height() / (double) max(1, dib->height());
            double dr = min(dx, dy);
            if(dr == 0)
               return;

            m_spdib->create(dib->width() * dr, dib->height() * dr);
            m_spdib->get_graphics()->SetStretchBltMode(STRETCH_HALFTONE);
            m_spdib->get_graphics()->StretchBlt(0, 0, 
               (int) (dib->width() * dr),
               (int) (dib->height() * dr),
               dib->get_graphics(),
               0, 0, 
               dib->width(), 
               dib->height(),
               SRCCOPY);
         }*/
      }	
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
      rect rectClient;
      GetClientRect(rectClient);
      pdc->SetStretchBltMode(HALFTONE);

      ::ca::dib * pdib = get_document()->m_spdib;

      if(pdib->area() == 0)
         return;
      
      double r;
      if(Application.command_line().m_varQuery.has_property("rate"))
      {
         r = Application.command_line().m_varQuery["rate"].get_double();
         if(r < 0.01)
            r = 0.01;
      }
      else
      {
         r = 1.2;
      }

      double r1 = 0.4 * r;
      double r2 = 0.15 * r;
      double r3 = 0.0 * r;
      double r4 = 0.0 * r;
      double r5 = 0.28 * r;
      double r6 = 0.4 * r;
      double zamp = 33.0;

      ::ca::dib_sp dib(get_app());

      dib->create(pdib->width() * r1 + pdib->height() * r2 + zamp * r3 + 5,  pdib->width() * r4 + pdib->height() * r5 + zamp * r6 + 5);
      int aw = pdib->width();
      int bh = pdib->height();
      int w = dib->width();
      int h = dib->height();

      dib->Fill(0, 255, 255, 255);
      
      const double dBrightAngle = - 3.1415  * 60.0 / 180.0;
      int b5 = bh * r5;
      double darken = 0.40;
      DWORD dwTime = GetTickCount();
      double freq = 0.33f;
      double phiTime = dwTime * freq * 3.1415 * 2 / 1000.0;
      COLORREF * pdst = dib->get_data();
      double Arate = r * 0.25;
      for(int a = 0; a < aw; a++)
      {
         double phi = a / 84.0 +  phiTime;
         double cosa = cos(phi);
         double cosd = cos(phi + dBrightAngle);
         double m = (cosd + 1.0) * 0.5 * 153;
         double a1 = a * r1;
         double a4 = a * r4;
         double z = (cosa + 1.0) * zamp / 2.0;
         double z3 = z * r3;
         double z6 = z * r6;
         double ax = a1 + z3;
         double ay = a4 + z6;
         COLORREF * psrc = &pdib->get_data()[a];
         for(int b = 0; b < bh; b++)
         {
            double dx = ax + b * r2;
            double dy = ay + b * r5;
            int xref = (int) dx; 
            int yref = (int) dy;
            {
               int x = xref;
               int y = yref;

               COLORREF cr = *psrc;
               COLORREF crDst = pdst[x + w * y];

               int R = GetRValue(cr) * darken + m;
               int G = GetGValue(cr) * darken + m;
               int B = GetBValue(cr) * darken + m;
               if(R >= 255 || G >= 255 || B >= 255)
               {
                  R = 255;
                  G = 255;
                  B = 255;
               }
               if(crDst == 0x00ffffff)
               {
                  crDst = RGB(R, G, B);
               }
               else
               {
                  int R2 = GetRValue(crDst);
                  int G2 = GetGValue(crDst);
                  int B2 = GetBValue(crDst);
                  int A2 = (crDst & 0xff000000) >> 24;
                  A2 = min(A2 + ((256 - A2) * Arate), 255);
                  crDst = RGB((R2 + R) / 2, (G2 + G) / 2, (B2 + B) / 2) | (A2 << 24);
               }
               pdst[x + w * y] = crDst;
            }

            if((dx - (double) xref) >= 0.5)
            {
               int x = xref + 1;
               int y = yref;

               COLORREF cr = *psrc;
               COLORREF crDst = pdst[x + w * y];

               int R = GetRValue(cr) * darken + m;
               int G = GetGValue(cr) * darken + m;
               int B = GetBValue(cr) * darken + m;
               if(R >= 255 || G >= 255 || B >= 255)
               {
                  R = 255;
                  G = 255;
                  B = 255;
               }
               if(crDst == 0x00ffffff)
               {
                  crDst = RGB(R, G, B);
               }
               else
               {
                  int R2 = GetRValue(crDst);
                  int G2 = GetGValue(crDst);
                  int B2 = GetBValue(crDst);
                  int A2 = (crDst & 0xff000000) >> 24;
                  A2 = min(A2 + ((256 - A2) * Arate), 255);
                  crDst = RGB((R2 + R) / 2, (G2 + G) / 2, (B2 + B) / 2) | (A2 << 24);
               }
               pdst[x + w * y] = crDst;
            }
            if((dy - (double) yref) >= 0.5)
            {
               int x = xref;
               int y = yref + 1;

               COLORREF cr = *psrc;
               COLORREF crDst = pdst[x + w * y];

               int R = GetRValue(cr) * darken + m;
               int G = GetGValue(cr) * darken + m;
               int B = GetBValue(cr) * darken + m;
               if(R >= 255 || G >= 255 || B >= 255)
               {
                  R = 255;
                  G = 255;
                  B = 255;
               }
               if(crDst == 0x00ffffff)
               {
                  crDst = RGB(R, G, B);
               }
               else
               {
                  int R2 = GetRValue(crDst);
                  int G2 = GetGValue(crDst);
                  int B2 = GetBValue(crDst);
                  int A2 = (crDst & 0xff000000) >> 24;
                  A2 = min(A2 + ((256 - A2) * Arate), 255);
                  crDst = RGB((R2 + R) / 2, (G2 + G) / 2, (B2 + B) / 2) | (A2 << 24);
               }
               pdst[x + w * y] = crDst;
            }
            if((dx - (double) xref) >= 0.5 &&
            (dy - (double) yref) >= 0.5)
            {
               int x = xref + 1;
               int y = yref + 1;

               COLORREF cr = *psrc;
               COLORREF crDst = pdst[x + w * y];

               int R = GetRValue(cr) * darken + m;
               int G = GetGValue(cr) * darken + m;
               int B = GetBValue(cr) * darken + m;
               if(R >= 255 || G >= 255 || B >= 255)
               {
                  R = 255;
                  G = 255;
                  B = 255;
               }
               if(crDst == 0x00ffffff)
               {
                  crDst = RGB(R, G, B);
               }
               else
               {
                  int R2 = GetRValue(crDst);
                  int G2 = GetGValue(crDst);
                  int B2 = GetBValue(crDst);
                  int A2 = (crDst & 0xff000000) >> 24;
                  A2 = min(A2 + ((256 - A2) * Arate), 255);
                  crDst = RGB((R2 + R) / 2, (G2 + G) / 2, (B2 + B) / 2) | (A2 << 24);
               }
               pdst[x + w * y] = crDst;
            }
            psrc += aw;

         }
      }


      double dx = (double) rectClient.width() / (double) max(1, dib->width());
      double dy = (double) rectClient.height() / (double) max(1, dib->height());
      double dr = min(dx, dy);
      if(dr == 0)
         return;

      Application.imaging().bitmap_blend(pdc, point(0, 0), size((int) (dib->width() * dr), (int) (dib->height() * dr)),
         dib->get_graphics(),
         point(0, 0));

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
         Application.simple_message_box(NULL, "Playlist");
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
         Application.get_cursor_pos(&pt);
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

   document * view::get_document()
   {
      return dynamic_cast < document * > (::userbase::view::get_document());
   }

} // namespace flag
