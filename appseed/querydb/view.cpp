#include "StdAfx.h"
#include "view.h"
#include <Psapi.h>

namespace querydb
{

   view::view(::ca::application * papp) :
      ca(papp),
      ::user::interaction(papp),
      ::userbase::view(papp),
      m_areaa(papp),
      m_taskthread(papp, this),
      m_dibBkImage(papp),
      m_dibBk(papp),
      m_dibcolor_blend_Area(papp),
      m_dibcolor_blend_Task(papp),
      m_dibV(papp),
      m_dib_veriwell(papp),
      m_dib_bergedge(papp),
      m_dibShutDown(papp),
      m_calendar(papp),
      m_font(papp),
      m_brushBkActive(papp),
      m_brushBkInactive(papp),
      m_clock(papp)
   {
      m_brushBkActive->CreateSolidBrush(RGB(150, 255, 130));
      m_brushBkInactive->CreateSolidBrush(RGB(128, 208, 120));
      LOGFONT lf;
      memset(&lf, 0, sizeof(lf));

      strcpy(lf.lfFaceName, "Verdana");
      lf.lfHeight = 13;
      m_font->CreateFontIndirect(&lf);

      m_calendar.m_font->CreateFontIndirect(&lf);
      lf.lfHeight = 15;
      lf.lfWeight = 900;
      m_calendar.m_fontYear->CreateFontIndirect(&lf);
      m_calendar.m_fontMonth->CreateFontIndirect(&lf);
      m_calendar.m_fontSpin->CreateFontIndirect(&lf);

      m_sizeNotifyIcon.cx = 16;
      m_sizeNotifyIcon.cy = 16;

      m_sizeNotifyIconMargin.cx = 2;
      m_sizeNotifyIconMargin.cy = 2;

      m_areaa.add(new area(papp));
      m_areaa.add(new area(papp));
      m_areaa.add(new area(papp));
      m_areaa.add(new area(papp));
      m_areaa[0].m_pview = this;
      m_areaa[1].m_pview = this;
      m_areaa[2].m_pview = this;
      m_areaa[3].m_pview = this;
      m_iArea = 0;
      m_iItemHeight = 26;
      m_iTaskOffset = 1000;
      m_iClockOffset = 10000;
   //   m_iNotificationAreaButtonOffset = 10100;
      m_iNotificationAreaOffset = 10200;
      m_iClockH = 30;
      m_iDragTask = -1;
      m_bDragTask = false;
      m_iNotificationAreaH = 30;
      m_bNotificationArea = true;
      m_bShowCalendar = false;
      m_calendar.set_time(time::get_current_time());
      m_iNotificationAreaColumnCount = 15;
      m_iV = 123;
      m_iVH = 49;
      m_iVW = 123;
      m_i_veriwell = 256;
      m_i_veriwell_h = 49;
      m_i_veriwell_w = 74;
      m_i_bergedge = 4;
      m_i_bergedge_h = 49;
      m_i_bergedge_w = 49;
      m_iShutDown = 60000;
      m_iShutDownW = 49;
      m_iShutDownH = 49;
      m_bShutDown = false;
      m_hwndWinservice1 = NULL;
      m_bEnsureApps = true;
      m_dwEnsureAppTimer = 0;
      m_dwEnsureWinService1Timer = 0;
   }

   view::~view()
   {
   }

   void view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::view::_001InstallMessageHandling(pinterface);

	   IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &view::_001OnDestroy);
	   IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &view::_001OnSize);
	   IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &view::_001OnPaint);
	   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &view::_001OnCreate);
	   IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &view::_001OnContextMenu);
	   IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &view::_001OnSetCursor);

      //IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &::user::interaction::_001OnLButtonDown);
      //IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &::user::interaction::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &::user::interaction::_001OnKeyDown);
      IGUI_WIN_MSG_LINK(WM_KEYUP, pinterface, this, &::user::interaction::_001OnKeyUp);

      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &view::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &view::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_RBUTTONUP, pinterface, this, &view::_001OnRButtonUp);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &view::_001OnMouseMove);
      IGUI_WIN_MSG_LINK(WM_MOUSELEAVE, pinterface, this, &view::_001OnMouseLeave);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &view::_001OnTimer);

      IGUI_WIN_MSG_LINK(MessageOp, pinterface, this, &view::_001OnOp);
      IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &view::_001OnShowWindow);
      IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &view::_001OnDestroy);
      IGUI_WIN_MSG_LINK(1257821, pinterface, this, &view::_001On1257821);

   }
   /////////////////////////////////////////////////////////////////////////////
   // ::view drawing

   void view::OnDraw(::ca::graphics * pdcScreen)
   {
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
      if(lHint == 5432108)
      {
         SetTimer(5432108, 100, NULL);
      }
   	
   }

   void view::_001OnDestroy(gen::signal_object * pobj) 
   {
      for(int i = 0; i < m_areaa.get_size(); i++)
      {
         for(int j = 0; j < m_areaa[i].m_taska.get_size(); j++)
         {
            HWND hwnd = m_areaa[i].m_taska[j].m_hwnd;
            mt_show_window(hwnd, SW_MINIMIZE);
         }
         /*for(int j = 0; j < m_areaa[i].m_hwndaTool.get_size(); j++)
         {
            HWND hwnd = m_areaa[i].m_hwndaTool[j];
            mt_show_window(hwnd, SW_MINIMIZE);
         }*/
      }
	   ::userbase::view::_001OnDestroy(pobj);
   }



   void view::_001OnSize(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::size, psize, pobj)


      rect rectDesktop = Application.m_monitorinfoa[0].rcMonitor;

      m_iWScreen = rectDesktop.width();
      m_iHScreen = rectDesktop.height();
      rect rectClient;
      GetClientRect(rectClient);
      rectClient.deflate(2, 2);
      int iW = rectClient.width() / 2;
      int iH = rectClient.height() / 2;
      iH = min(iH, 120);
      double r = (double) iW / (double) iH;
      double rScreen = (double) rectDesktop.width() / (double) rectDesktop.height();
      if(r < rScreen)
      {
         iH = (int) (iW / rScreen);
      }
      else if(r > rScreen)
      {
         iW = (int) (iH * rScreen);
      }
      m_iW = iW;
      m_iH = iH;
      m_calendar.set_pos(point(1, 1 + m_iClockH), size(350, 250));
      m_clock.set_pos(point(1, 1 + m_iClockH + 277), size(284, 284));
      for(int iArea = 0; iArea < m_areaa.get_count(); iArea++)
      {
         if(m_areaa[iArea].m_spdib->create(iW - 4, iH - 4))
         {
            Snapshot(iArea);
         }
      }
   }

   void view::_001OnPaint(gen::signal_object * pobj) 
   {
   //	CPaintDC spgraphics(this); // device context for winactionareaing
     // spgraphics->TextOut(20, 20, "Carlos Gustavo Cecyn Lundgren é minha Vida Eterna, meu Coração Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
   }


   void view:: _001OnDraw(::ca::graphics * pdc)
   {
      class imaging & imaging = Application.imaging();
      rect rectClient;
      GetClientRect(rectClient);
      if(rectClient.width() <= 0
         || rectClient.height() <= 0)
         return;
      rect rectDesktop = Application.m_monitorinfoa[0].rcMonitor;
      if(rectDesktop.width() < 800)
      {
         rectDesktop.left = 0;
         rectDesktop.right = ::GetSystemMetrics(SM_CXSCREEN);
      }
      if(rectDesktop.height() < 600)
      {
         rectDesktop.top = 0;
         rectDesktop.bottom = ::GetSystemMetrics(SM_CYSCREEN);
      }
      if(!Application.savings().should_save(gen::resource_processing))
      {
         ::ca::dib_sp spdib(get_app());
         ::ca::dib_sp spdib2(get_app());
         if(!spdib->create(rectClient.width(), rectClient.height()))
            return;
         if(!spdib2->create(rectClient.width(), rectClient.height()))
            return;
         rect rectWindow = rectClient;
         ClientToScreen(rectWindow);
         spdib->create(rectClient.width(), rectClient.height());
         spdib2->get_graphics()->BitBlt(
            0, 0, rectClient.width(), rectClient.height(), 
            pdc, 0, 0, 
            SRCCOPY);
         imaging.blur(spdib->get_graphics(), null_point(), rectClient.size(), spdib2->get_graphics(), null_point(), 2);
         imaging.bitmap_blend(spdib->get_graphics(), null_point(), rectWindow.size(), m_dibBk->get_graphics(), null_point(), 49);
         pdc->from(rectWindow.size(), spdib->get_graphics(), SRCCOPY);
      }

      
      pdc->SetTextColor(RGB(0, 0, 0));
      HGDIOBJ hgdiOldFont = pdc->SelectObject(m_font);
      pdc->SetBkMode(TRANSPARENT);
      rect rectArea;

      GetAreaThumbRect(rectArea, m_iV);
      m_dibV->bitmap_blend(pdc, rectArea);
      if(m_iHitArea == m_iV)
      {
         imaging.color_blend(pdc, rectArea, RGB(140, 255, 110), 80);
      }

      GetAreaThumbRect(rectArea, m_i_veriwell);
      m_dib_veriwell->bitmap_blend(pdc, rectArea);
      if(m_iHitArea == m_i_veriwell)
      {
         imaging.color_blend(pdc, rectArea, RGB(140, 255, 110), 80);
      }

      GetAreaThumbRect(rectArea, m_i_bergedge);
      m_dib_bergedge->bitmap_blend(pdc, rectArea);
      if(m_iHitArea == m_i_bergedge)
      {
         imaging.color_blend(pdc, rectArea, RGB(140, 255, 110), 80);
      }


      GetAreaThumbRect(rectArea, m_iShutDown);
      imaging.bitmap_blend(
         pdc,
         rectArea.top_left(), rectArea.size(),
         m_dibShutDown->get_graphics(), null_point());
      //m_dibShutDown.to(pdc, );
   /*
   /*   
      GetAreaThumbRect(rectArea, m_iNotificationAreaButtonOffset);

      string strNotificationAreaButton("Notification Area button");
      wstring wstrNotificationAreaButton = gen::international::utf8_to_unicode(strNotificationAreaButton);
      ::DrawTextW((HDC)pdc->get_os_data(), wstrNotificationAreaButton, wstrNotificationAreaButton.get_length(), rectArea, DT_VCENTER | DT_LEFT | DT_SINGLELINE);
   */

      GetAreaThumbRect(rectArea, m_iClockOffset);
      string strDateTime;
      calendar(get_app()).GetDateTime(pdc->str_context(), strDateTime);
      wstring wstrDateTime = gen::international::utf8_to_unicode(strDateTime);
      ::DrawTextW((HDC)pdc->get_os_data(), wstrDateTime, wstrDateTime.get_length(), rectArea, DT_VCENTER | DT_LEFT | DT_SINGLELINE);
      if(m_bShowCalendar)
      {
         m_calendar._001OnDraw(pdc);
         m_clock._001OnDraw(pdc);
      }
      else
      {
         COLORREF crBk;
         if(!m_bShutDown)
         {
            for(int i = 0; i < m_areaa.get_size(); i++)
            {
               GetAreaThumbRect(rectArea, i);
               rectArea.deflate(1, 1);
               if(m_iArea == i)
               {
                  crBk = RGB(150, 255, 130);
                  //imaging.color_blend(pdc, rectArea, crBk, 198);
                  pdc->Draw3dRect(rectArea, RGB(150, 200, 135), RGB(190, 230, 184));
                  rectArea.deflate(1, 1);
                  pdc->Draw3dRect(rectArea, RGB(190, 230, 184), RGB(150, 200, 135));
               }
               else
               {
                  crBk = RGB(128, 208, 120);
                  //imaging.color_blend(pdc, rectArea, crBk, 128);
                  pdc->Draw3dRect(rectArea, RGB(110, 150, 90), RGB(250, 255, 240));
                  rectArea.deflate(1, 1);
                  pdc->Draw3dRect(rectArea, RGB(250, 255, 240), RGB(110, 150, 90));
               }
               if(m_iArea != i && !m_areaa[i].m_bBlend)
               {
                  m_areaa[i].m_bBlend = true;
                  imaging.color_blend(m_areaa[i].m_spdib->get_graphics(), 0, 0, m_iW - 4, m_iH - 4, RGB(255, 255, 255), 77);
               }

               if(m_iArea == i)
               {
                  m_areaa[i].m_spdib->to(pdc, rectArea);
               }
               else
               {
                  imaging.bitmap_blend(pdc, rectArea.top_left(), rectArea.size(),
                     m_areaa[i].m_spdib->get_graphics(), null_point(), 184);
               }
               if(m_bDragTask && m_iHitArea == i)
               {
                  int w = m_iW - 4;
                  int h = m_iH - 4;
                  int x = rectArea.left;
                  int y = rectArea.top;
                  if(m_iHitSubArea < 0)
                  {
                  }
                  else if(m_iHitSubArea < 3)
                  {
                     if(m_iHitSubArea == 0)
                     {
                        imaging.color_blend(pdc, x + 0, y + 0, w / 2, h /2, RGB(255, 255, 255), 77);
                     }
                     else if(m_iHitSubArea == 1)
                     {
                        imaging.color_blend(pdc, x + 0, y + 0, w / 2, h, RGB(255, 255, 255), 77);
                     }
                     else
                     {
                        imaging.color_blend(pdc, x + 0, y + h / 2, w / 2, h / 2, RGB(255, 255, 255), 77);
                     }
                  }
                  else if(m_iHitSubArea < 6)
                  {
                     if(m_iHitSubArea == 3)
                     {
                        imaging.color_blend(pdc, x + 0, y + 0, w, h /2, RGB(255, 255, 255), 77);
                     }
                     else if(m_iHitSubArea == 4)
                     {
                        imaging.color_blend(pdc, x + 0, y + 0, w, h, RGB(255, 255, 255), 77);
                     }
                     else
                     {
                        imaging.color_blend(pdc, x + 0, y + h / 2, w, h / 2, RGB(255, 255, 255), 77);
                     }
                  }
                  else if(m_iHitSubArea < 9)
                  {
                     if(m_iHitSubArea == 6)
                     {
                        imaging.color_blend(pdc, x + w / 2, y + 0, w / 2, h /2, RGB(255, 255, 255), 77);
                     }
                     else if(m_iHitSubArea == 7)
                     {
                        imaging.color_blend(pdc, x + w / 2, y + 0, w / 2, h, RGB(255, 255, 255), 77);
                     }
                     else
                     {
                        imaging.color_blend(pdc, x + w / 2, y + h / 2, w / 2, h / 2, RGB(255, 255, 255), 77);
                     }
                  }
               }
            }
         }
         rect rectText;
         rect rectIcon;
         rect rectPad;
         WCHAR szWindowText[1024];
         ::ca::brush * pbrBk;
         ::ca::brush * pbrOld = pdc->GetCurrentBrush();
         bool bSoonAfterTaskChange = (::GetTickCount() - m_dwCurrentTaskChangeTime) < 1000;
         if(m_bShutDown)
         {
            wstring wstr;
            GetAreaThumbRect(rectArea, m_iTaskOffset);
            wstr = L"Restart computer";
            ::DrawTextW((HDC)pdc->get_os_data(), wstr, wstr.get_length(), rectArea, DT_VCENTER | DT_LEFT | DT_SINGLELINE);
            GetAreaThumbRect(rectArea, m_iTaskOffset + 1);
            wstr = L"Shutdown computer";
            ::DrawTextW((HDC)pdc->get_os_data(), wstr, wstr.get_length(), rectArea, DT_VCENTER | DT_LEFT | DT_SINGLELINE);
            GetAreaThumbRect(rectArea, m_iTaskOffset + 3);
            wstr = L"close windesk (this program and helper programs)";
            ::DrawTextW((HDC)pdc->get_os_data(), wstr, wstr.get_length(), rectArea, DT_VCENTER | DT_LEFT | DT_SINGLELINE);
         }
         else
         {
            for(int i = 0; i < m_areaa[m_iArea].m_taska.get_size(); i++)
            {
               bool bPathCaption = m_areaa[m_iArea].m_taska[i].m_bPathCaption;
               GetAreaThumbRect(rectArea, m_iTaskOffset + i);
               rectArea.deflate(1, 1);
               
               if((m_iTaskOffset + i) == m_iCurrentTask)
               {
                  if((m_iTaskOffset + i) == m_iHitArea)
                  {
                     crBk = RGB(220, 255, 200);
                  }
                  else
                  {
                     crBk = RGB(150, 255, 130);
                  }
                  pbrBk = m_brushBkActive;
                  imaging.color_blend(pdc, rectArea, crBk, 123, m_dibcolor_blend_Task);
                  pdc->Draw3dRect(rectArea, RGB(150, 200, 135), RGB(190, 230, 184));
                  rectArea.deflate(1, 1);
                  pdc->Draw3dRect(rectArea, RGB(190, 230, 184), RGB(150, 200, 135));
               }
               else if((m_iTaskOffset + i) == m_iHitArea)
               {
                  crBk = RGB(128, 208, 120);
                  pbrBk = m_brushBkInactive;
                  imaging.color_blend(pdc, rectArea, crBk, 52, m_dibcolor_blend_Task);
                  pdc->Draw3dRect(rectArea, RGB(110, 150, 90), RGB(250, 255, 240));
                  rectArea.deflate(1, 1);
                  pdc->Draw3dRect(rectArea, RGB(250, 255, 240), RGB(110, 150, 90));
               }
               else 
               {
                  crBk = RGB(255, 255, 255);
                  rectArea.deflate(1, 1);
                  pbrBk = NULL;
               }
               rectPad = rectArea;
               rectArea.deflate(2, 2);
               pdc->SetTextColor(RGB( 0, 0, 0));
               rectIcon = rectArea;
               rectIcon.left += 2;
               rectIcon.top += 2;
               rectIcon.right = rectIcon.left + 16;
               rectIcon.bottom = rectIcon.top + 16;
               rectText = rectArea;
               rectText.left = rectText.left + 18;
               rectText.right -= 2;
               ::GetWindowTextW(m_areaa[m_iArea].m_taska[i].m_hwnd, szWindowText, sizeof(szWindowText) / sizeof(WCHAR));
               ::DrawIconEx((HDC)pdc->get_os_data(), 
                  rectIcon.left, rectIcon.top,
                  m_areaa[m_iArea].m_taska[i].m_icon,
                  rectIcon.width(),
                  rectIcon.height(),
                  0,
                  pbrBk == NULL ? NULL : (HBRUSH) pbrBk->get_os_data(),
                  DI_IMAGE | DI_MASK);
               int iEllipsis = bPathCaption ? DT_PATH_ELLIPSIS : DT_END_ELLIPSIS;
               ::DrawTextW((HDC)pdc->get_os_data(), szWindowText, wcslen(szWindowText), rectText, DT_VCENTER | DT_LEFT | iEllipsis | DT_SINGLELINE);
         /*      if(m_areaa[m_iArea].m_hwndaPreserve[i] ==  m_areaa[m_iArea].m_taska[0])
               {
                  pdc->FillSolidRect(rectArea, RGB(200, 240, 190));
                  pdc->Draw3dRect(rectPad, RGB(63, 70, 55), RGB(200, 255, 190));
                  rectArea.deflate(1, 1);
                  pdc->Draw3dRect(rectArea, RGB(100, 110, 90), RGB(250, 255, 240));
               }
               else
               {
                  pdc->FillSolidRect(rectArea, RGB(128, 188, 120));
                  pdc->Draw3dRect(rectArea, RGB(200, 255, 190), RGB(63, 70, 55));
                  rectArea.deflate(1, 1);
                  pdc->Draw3dRect(rectArea, RGB(250, 250, 240), RGB(110, 100, 90));
               }*/
               
            }
         }
         pdc->SelectObject(hgdiOldFont);
         pdc->SelectObject(pbrOld);
      }
      //COLORREF crBk;
      if(m_bNotificationArea)
      {
         rect rectIcon;
         for(int i = 0; i < m_notificationareainfo.m_infoa.get_size(); i++)
         {
            GetAreaThumbRect(rectArea, m_iNotificationAreaOffset + i);
            rectIcon          = rectArea;
            rectIcon.deflate(m_sizeNotifyIconMargin);
            m_notificationareainfo.m_pil16->draw(pdc, i, rectIcon.top_left(), rectIcon.size(), point(0, 0), 0);
         }
      }
   }

   int WM_TSKBRCRT;

   BOOL CALLBACK EnumWindowsProc(HWND hwnd,LPARAM)
   {
     PostMessage(hwnd,WM_TSKBRCRT,0,0);
     return 1;
   }

   void view::_001OnCreate(gen::signal_object * pobj) 
   {
      if(pobj->previous())
         return;

      WM_TSKBRCRT=RegisterWindowMessageW(L"TaskbarCreated");
      EnumWindows(EnumWindowsProc,0);

      SetTimer(3003, 1984, NULL);
      SetTimer(543218, 784, NULL);
      SetTimer(1257784, 784, NULL);
      m_taskthread.Begin();

      m_dibBkImage.load_from_matter("casweden1.png");
      m_dibV.load_from_matter("votagus_mountains_and_valleys-123-trans.png");
      m_dib_veriwell.load_from_matter("veriwell_2008_green_h49-trans.png");
      m_dib_bergedge.load_from_matter("bergedge.png");

      //pfi = Application.imaging().LoadImageFile(
        // System.dir().standard_square_matter("shut_down.png"));
      m_dibShutDown.load_from_matter("shut_down.png");
      /*::ca::bitmap * pbmp = Application.imaging().FItoHBITMAP(pfi, true);
      BITMAP bmp;
      pbmp->GetObject(sizeof(bmp), &bmp);
      m_dibShutDown->create(bmp.bmWidth, bmp.bmHeight);
      ::ca::graphics_sp dc1(get_app());
      dc1->CreateCompatibleDC(NULL);
      dc1->SelectObject(pbmp);
      LPDWORD lpdata = (LPDWORD) bmp.bmBits;
      pbmp->GetBitmapBits(bmp.bmHeight * bmp.bmWidth * 4, m_dibShutDown->get_data());
      unsigned char * puch;
      for(int i = 0; i < bmp.bmHeight; i++)
      {
         for(int j = 0; j < bmp.bmWidth; j++)
         {
            puch = (unsigned char *) &m_dibShutDown->get_data()[i * bmp.bmWidth + j];
            m_dibShutDown->get_data()[i * bmp.bmWidth + j] = (puch[0] * puch[3] / 255)
               + ((puch[1] * puch[3] / 255) << 8)
               + ((puch[2] * puch[3] / 255) << 16)
               + (puch[3] << 24);
         }
      }
      */
      //m_dibShutDown.from(dc1, hbmp);
      //ReleaseDC(pdc);
      
      m_dibBk->create(1280, 1024);
      //gen::savings & savings = Application.savings();
      //if(
      const char * pszSessionName = getenv("sessionname");
      bool bConsole = false;
      if(pszSessionName != NULL)
      {
         if(strcmp(pszSessionName, "Console") == 0)
         {
            bConsole = true;
         }
      }
      bConsole = false;
      if(bConsole)
      {
         m_dibBkImage->copy(m_dibBk);
      }
      else
      {
         m_dibBk->Fill(84, 84, 77);
      }

      Application.imaging().color_blend(m_dibBk->get_graphics(), 0, 0, 1280, 1024, RGB(235, 245, 255), 31);
      m_notificationareainfo.Initialize(get_app());
      frame * pframe = dynamic_cast < frame * > (GetTopLevelFrame());
      if(pframe != NULL)
      {
         pframe->m_pwinactionareaview = this;
         pframe->m_ppaneview->m_pwinactionareaview = this;
      }
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

   void view::_001OnSetCursor(gen::signal_object * pobj) 
   {
      ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
   	
	   pobj->previous();
   }

   document * view::get_document()
   {
      return dynamic_cast < document * > (::userbase::view::get_document());
   }

   void view::SwitchArea(int iNewArea)
   {
      int iOldArea = m_iArea;
      application & app = ::querydb::app_cast(get_app());
      if(iNewArea != iOldArea)
      {
         m_iArea = iNewArea;
         for(int i = 0; i < m_areaa[iNewArea].m_hwnda.get_size(); i++)
         {
            mt_show_window(m_areaa[iNewArea].m_hwnda[i], SW_SHOW);
            app.m_hwndaHidden.remove(m_areaa[iNewArea].m_hwnda[i]);
         }
         Sleep(84);
         for(int i = 0; i < m_areaa[iOldArea].m_hwnda.get_size(); i++)
         {
            app.m_hwndaHidden.add(m_areaa[iOldArea].m_hwnda[i]);
            mt_show_window(m_areaa[iOldArea].m_hwnda[i], SW_HIDE);
         }
         Sleep(77);
         if(m_hwndaDesk.get_count() > 0)
         {
            ::SendMessage(m_hwndaDesk[0], WM_APP + 2000, 102326, iNewArea);
         }
      }
   }
   /*
   void view::Snapshot()
   {
      int iArea = m_iArea;
      SwitchArea(0);
      SwitchArea(1);
      SwitchArea(2);
      SwitchArea(3);
      SwitchArea(iArea);
   }
   */

   BOOL CALLBACK GetAppsEnumWindowsProc(      
       HWND hwnd,
       LPARAM lParam)
   {
      user::HWNDArray * phwnda = (user::HWNDArray *) lParam;
      phwnda->add(hwnd);
      return TRUE;
   }

   void get_app_wnda(user::HWNDArray & wnda)
   {
      EnumWindows(GetAppsEnumWindowsProc, (LPARAM) &wnda);
   }


   void _001DeferPaintScreen(HWND hwndExclude, ::ca::graphics * pdc)
   {
      rect rectUpdate = pdc->m_papp->m_psystem->m_monitorinfoa[0].rcMonitor;
      rect rectPaint;
      rectPaint = rectUpdate;
      user::HWNDArray wndaApp;
      get_app_wnda(wndaApp);
     

      rect rect5;
      rect rect9;
      for(int i = 0; i < wndaApp.get_count(); i++)
      {
         if(wndaApp[i] == hwndExclude)
         {
            wndaApp.remove_at(i);
            break;
         }
      }
      ::ca::rgn_sp rgnUpdate(pdc->m_papp);
      rgnUpdate->CreateRectRgnIndirect(rectUpdate);
      int j = 0;
      for(; j < wndaApp.get_count();)
      {
         if(!IsWindowVisible(wndaApp[j]))
         {
            wndaApp.remove_at(j);
         }
   /*      else if(::GetWindowLong(wndaApp[j], GWL_EXSTYLE) & WS_EX_LAYERED)
         {
            j++;
         }*/
         else
         {
            rect rectWindow;
            GetWindowRect(wndaApp[j], rectWindow);
            ::ca::rgn_sp rgnWindow(pdc->m_papp);
            rgnWindow->CreateRectRgnIndirect(rectWindow);
            ::ca::rgn_sp rgnIntersect(pdc->m_papp);
            rgnIntersect->CreateRectRgn(0, 0, 0, 0);
            rgnIntersect->CombineRgn(rgnUpdate, rgnWindow, RGN_AND);
            rect rectIntersectBox;
            rgnIntersect->GetRgnBox(rectIntersectBox);
            if(rectIntersectBox.is_empty())
            {
               wndaApp.remove_at(j);
            }
            else
            {
               rgnUpdate->CombineRgn(rgnUpdate, rgnWindow, RGN_DIFF);
               rect rectDiffBox;
               rgnUpdate->GetRgnBox(rectDiffBox);
               j++;
               if(rectDiffBox.is_empty())
               {
                  break;
               }
            }
         }
      }
      j--;
      for(; j >= 0; j--)
      {
         if(!IsWindowVisible(wndaApp[j]) ||
            IsIconic(wndaApp[j]))
            continue;
         GetWindowRect(wndaApp[j], rect5);
         rect9.intersect(rect5, rectUpdate);
         if(rect9.width() >0 && rect9.height() > 0)
         {
            if(GetWindowLong(wndaApp[j], GWL_EXSTYLE) & WS_EX_LAYERED)
            {
               //pdc->SetViewportOrg(rect5.top_left());
               ::ca::dib_sp spdib(pdc->m_papp);
               spdib->create(rect5.width(), rect5.height());
               //spgraphics->BitBlt(0, 0, rect5.width(), rect5.height(), pdc, rect5.left, rect5.top, SRCCOPY);
               int iRetry;
               iRetry = 10;
               while(iRetry > 0)
               {
                  InvalidateRect(wndaApp[j], NULL, FALSE);
                  if(::PrintWindow(wndaApp[j], (HDC) spdib->get_graphics()->get_os_data(), 0))
                     break;
                  //::SendMessage(wndaApp[j], WM_PRINTCLIENT, (WPARAM)(HDC)spgraphics,
                    //PRF_ERASEBKGND | PRF_CHILDREN | PRF_OWNED | PRF_CLIENT | PRF_NONCLIENT);
                  //break;
                  iRetry--;
               }

               pdc->BitBlt(rect5.left, rect5.top, rect5.width(), rect5.height(),
                  spdib->get_graphics(), 0, 0, SRCCOPY);
   //            pdc->FillSolidRect(rect5.left, rect5.top, 80, 80, RGB(0, 255, 0));
            }
            else
            {
               pdc->SetViewportOrg(point(0, 0));
               HDC hdcWindow = GetDCEx(wndaApp[j], NULL, DCX_WINDOW);
               ::BitBlt(
                  (HDC) pdc->get_os_data(),
                  rect9.left,
                  rect9.top,
                  rect9.width(), rect9.height(),
                  hdcWindow,
                  rect9.left - rect5.left,
                  rect9.top - rect5.top,
                  SRCCOPY);
               ::ReleaseDC(wndaApp[j], hdcWindow);
            }
         }
      }
   }

   void view::Snapshot(int iArea)
   {
      if(iArea < 0)
         return;
      if(iArea >= m_areaa.get_count())
         return;
      m_areaa[iArea].m_bBlend = false;

      ::ca::dib_sp dibScreen(get_app());
      if(!dibScreen->create(m_iWScreen, m_iHScreen))
         return;
      _001DeferPaintScreen(GetTopLevelFrame()->get_safe_handle(), dibScreen->get_graphics());

      if(m_areaa[iArea].m_spdib->get_graphics()->get_os_data() != NULL)
      {
         m_areaa[iArea].m_spdib->get_graphics()->SetStretchBltMode(HALFTONE);
         m_areaa[iArea].m_spdib->get_graphics()->StretchBlt(0, 0, m_iW - 4, m_iH - 4, 
            dibScreen->get_graphics(), 0, 0, m_iWScreen, m_iHScreen,
            SRCCOPY);
      }

   }

   void view::GetAreaThumbRect(LPRECT lprect, int iArea)
   {
      rect rectClient;
      GetClientRect(rectClient);
      if(iArea == m_iV)
      {
         lprect->bottom = rectClient.bottom;
         lprect->top = lprect->bottom - m_iVH;
         lprect->left = 1;
         lprect->right = lprect->left + m_iVW;
      }
      else if(iArea == m_i_veriwell)
      {
         lprect->bottom = rectClient.bottom;
         lprect->top = lprect->bottom - m_i_veriwell_h;
         lprect->left = 1 + m_iVW + 5;
         lprect->right = lprect->left + m_i_veriwell_w;
      }
      else if(iArea == m_i_bergedge)
      {
         lprect->bottom = rectClient.bottom;
         lprect->top = lprect->bottom - m_i_bergedge_h;
         lprect->left = 1 + m_iVW + 5 + m_i_veriwell_w + 5;
         lprect->right = lprect->left + m_i_bergedge_w;
      }
      else if(iArea == m_iShutDown)
      {
         lprect->bottom = rectClient.bottom;
         lprect->top = lprect->bottom - m_iShutDownH;
         lprect->right = rectClient.right - 1;
         lprect->left = lprect->right - m_iShutDownW;
         
      }
      else if(iArea >= m_iNotificationAreaOffset)
      {
         int iColCount = m_iNotificationAreaColumnCount;
         int iCol = (iArea - m_iNotificationAreaOffset) % iColCount;
         int iLin = (iArea - m_iNotificationAreaOffset) / iColCount;
         int cx = m_sizeNotifyIcon.cx + m_sizeNotifyIconMargin.cx * 2;
         int cy = m_sizeNotifyIcon.cy + m_sizeNotifyIconMargin.cy * 2;
         lprect->left = 1 + iCol * cx;
         lprect->top = rectClient.bottom - m_iVH - m_iItemHeight * 3 + cy * iLin;
         lprect->right = lprect->left + cx;
         lprect->bottom = lprect->top + cy;
      }
   /*   else if(iArea >= m_iNotificationAreaButtonOffset)
      {
         lprect->left = 1;
         lprect->top = 1 + m_iClockH + m_iH * 2 + 5;
         lprect->right = 350;
         lprect->bottom = lprect->top + m_iNotificationAreaH;
      }*/
      else if(iArea >= m_iClockOffset)
      {
         lprect->left = 1;
         lprect->top = 1;
         lprect->right = 350;
         lprect->bottom = lprect->top + m_iClockH;
         return;
      }
      else if(iArea >= m_iTaskOffset)
      {
         lprect->left = 1;
         //lprect->top = m_iClockH + m_iNotificationAreaH + m_iH * 2 + 5 + m_iItemHeight * ((iArea - m_iTaskOffset));
         lprect->top = m_iClockH + m_iH * 2 + 5 + m_iItemHeight * ((iArea - m_iTaskOffset));
         lprect->right = 350;
         lprect->bottom = lprect->top + m_iItemHeight;
      }
      else
      {
         switch(iArea)
         {
         case 0:
            lprect->left = 1;
            lprect->top = m_iClockH + 1;
            lprect->right = lprect->left + m_iW;
            lprect->bottom = lprect->top + m_iH;
            break;
         case 1:
            lprect->left = m_iW + 3;
            lprect->top = m_iClockH + 1;
            lprect->right = lprect->left + m_iW;
            lprect->bottom = lprect->top + m_iH;
            break;
         case 2:
            lprect->left = 1;
            lprect->top = m_iClockH + m_iH + 3;
            lprect->right = lprect->left + m_iW;
            lprect->bottom = lprect->top + m_iH;
            break;
         case 3:
            lprect->left = m_iW + 3;
            lprect->top = m_iClockH + m_iH + 3;
            lprect->right = lprect->left + m_iW;
            lprect->bottom = lprect->top + m_iH;
            break;
         }
      }
   }

   int view::hit_test(point pt)
   {
      rect rectArea;
      GetAreaThumbRect(rectArea, m_iV);
      if(rectArea.contains(pt))
      {
         return m_iV;
      }
      GetAreaThumbRect(rectArea, m_i_veriwell);
      if(rectArea.contains(pt))
      {
         return m_i_veriwell;
      }
      GetAreaThumbRect(rectArea, m_i_bergedge);
      if(rectArea.contains(pt))
      {
         return m_i_bergedge;
      }
      GetAreaThumbRect(rectArea, m_iShutDown);
      if(rectArea.contains(pt))
      {
         return m_iShutDown;
      }
      GetAreaThumbRect(rectArea, m_iClockOffset);
      if(rectArea.contains(pt))
      {
         return m_iClockOffset;
      }
   /*   GetAreaThumbRect(rectArea, m_iNotificationAreaButtonOffset);
      if(rectArea.contains(pt))
      {
         return m_iNotificationAreaButtonOffset;
      }*/
      if(m_bShutDown)
      {
         for(int i = 0; i < 11; i++)
         {
            GetAreaThumbRect(rectArea, m_iTaskOffset + i);
            if(rectArea.contains(pt))
            {
               return m_iTaskOffset + i;
            }
         }
         return - 1;
      }
      for(int i = 0; i < m_notificationareainfo.m_infoa.get_size(); i++)
      {
         GetAreaThumbRect(rectArea, m_iNotificationAreaOffset + i);
         if(rectArea.contains(pt))
         {
            return m_iNotificationAreaOffset + i;
         }
      }
      for(int i = 0; i < 4; i++)
      {
         GetAreaThumbRect(rectArea, i);
         if(rectArea.contains(pt))
         {
            return i;
         }
      }
      for(int i = 0; i < m_areaa[m_iArea].m_taska.get_size(); i++)
      {
         GetAreaThumbRect(rectArea, m_iTaskOffset + i);
         if(rectArea.contains(pt))
         {
            return m_iTaskOffset + i;
         }
      }
      return -1;
   }

   void view::_001OnLButtonDown(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
      pmouse->set_lresult(1);
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
      int iHitArea = hit_test(pt);
      if(iHitArea >= 0 && !m_bShowCalendar && !m_bShutDown)
      {
         if(iHitArea < m_areaa.get_size())
         {
         }
         else if(iHitArea >= m_iTaskOffset && iHitArea < (m_iTaskOffset + m_areaa[m_iArea].m_taska.get_size()))
         {
            m_iDragTask = iHitArea;
            SetTimer(5432180, 400, NULL); // DragTask
         }
      }
      
   }

   void view::_001OnMouseLeave(gen::signal_object * pobj)
   {
      m_iHitArea = -1;
   }


   void view::_001OnMouseMove(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
      pmouse->set_lresult(1);
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
      int iHitArea = hit_test(pt); 
      if(m_iHitArea < 0 && iHitArea >=0)
         track_mouse_hover();
      m_iHitArea =  iHitArea;

      if(m_bDragTask && !m_bShowCalendar && !m_bShutDown)
      {
         if(m_iDragTask >= m_iTaskOffset
         && m_iDragTask < m_iTaskOffset + m_areaa[m_iArea].m_taska.get_size()
         && iHitArea >= 0
         && iHitArea < m_areaa.get_size())
         {
            rect rectArea;
            GetAreaThumbRect(rectArea, iHitArea);
            if(pt.x < (rectArea.left + rectArea.width() / 3))
            {
               if(pt.y < (rectArea.top + rectArea.height() / 3))
               {
                  m_iHitSubArea = 0;
               }
               else if(pt.y < (rectArea.top + rectArea.height() * 2 / 3))
               {
                  m_iHitSubArea = 1;
               }
               else
               {
                  m_iHitSubArea = 2;
               }
            }
            else if(pt.x < (rectArea.left + rectArea.width() * 2 / 3))
            {
               if(pt.y < (rectArea.top + rectArea.height() / 3))
               {
                  m_iHitSubArea = 3;
               }
               else if(pt.y < (rectArea.top + rectArea.height() * 2 / 3))
               {
                  m_iHitSubArea = 4;
               }
               else
               {
                  m_iHitSubArea = 5;
               }
            }
            else
            {
               if(pt.y < (rectArea.top + rectArea.height() / 3))
               {
                  m_iHitSubArea = 6;
               }
               else if(pt.y < (rectArea.top + rectArea.height() * 2 / 3))
               {
                  m_iHitSubArea = 7;
               }
               else
               {
                  m_iHitSubArea = 8;
               }
            }
            
         }
      }
   }

   void view::_001OnLButtonUp(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
      pmouse->set_lresult(1);
      KillTimer(5432180);
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
      int iHitArea = hit_test(pt);
      if(m_bDragTask && !m_bShowCalendar && !m_bShutDown)
      {
         m_bDragTask = false;
         if(m_iDragTask >= m_iTaskOffset
         && m_iDragTask < m_iTaskOffset + m_areaa[m_iArea].m_taska.get_size()
         && iHitArea >= 0
         && iHitArea < m_areaa.get_size())
         {
            HWND hwnd = m_areaa[m_iArea].m_taska[m_iDragTask - m_iTaskOffset].m_hwnd;
            rect rectArea;
            rect rectDesk0 = Application.m_monitorinfoaDesk[0].rcMonitor;
            rect rectDesk1 = Application.m_monitorinfoaDesk[1].rcMonitor;
            GetAreaThumbRect(rectArea, iHitArea);
            if(::IsWindowVisible(hwnd))
            {
               ::ShowWindow(hwnd, SW_NORMAL);
            }
            if(pt.x < (rectArea.left + rectArea.width() / 3))
            {
               if(pt.y < (rectArea.top + rectArea.height() / 3))
               {
                  ::SetWindowPos(hwnd, HWND_TOP, rectDesk0.left, rectDesk0.top, rectDesk0.width(), rectDesk0.height() / 2, 0);
               }
               else if(pt.y < (rectArea.top + rectArea.height() * 2 / 3))
               {
                  ::SetWindowPos(hwnd, HWND_TOP, rectDesk0.left, rectDesk0.top, rectDesk0.width(), rectDesk0.height(), 0);
               }
               else
               {
                  ::SetWindowPos(hwnd, HWND_TOP, rectDesk0.left, rectDesk0.top + rectDesk0.height() / 2, rectDesk0.width(), rectDesk0.height() / 2, 0);
               }
            }
            else if(pt.x < (rectArea.left + rectArea.width() * 2 / 3))
            {
               if(pt.y < (rectArea.top + rectArea.height() / 3))
               {
                  ::SetWindowPos(hwnd, HWND_TOP, rectDesk0.left, rectDesk0.top, rectDesk1.right - rectDesk0.left, rectDesk0.height() / 2, 0);
               }
               else if(pt.y < (rectArea.top + rectArea.height() * 2 / 3))
               {
                  ::SetWindowPos(hwnd, HWND_TOP, rectDesk0.left, rectDesk0.top, rectDesk1.right - rectDesk0.left, rectDesk0.height(), 0);
               }
               else
               {
                  ::SetWindowPos(hwnd, HWND_TOP, rectDesk0.left, rectDesk0.top + rectDesk0.height() / 2, rectDesk1.right - rectDesk0.left, rectDesk0.height() / 2, 0);
               }
            }
            else
            {
               if(pt.y < (rectArea.top + rectArea.height() / 3))
               {
                  ::SetWindowPos(hwnd, HWND_TOP, rectDesk1.left, rectDesk1.top, rectDesk1.width(), rectDesk1.height() / 2, 0);
               }
               else if(pt.y < (rectArea.top + rectArea.height() * 2 / 3))
               {
                  ::SetWindowPos(hwnd, HWND_TOP, rectDesk1.left, rectDesk1.top, rectDesk1.width(), rectDesk1.height(), 0);
               }
               else
               {
                  ::SetWindowPos(hwnd, HWND_TOP, rectDesk1.left, rectDesk1.top + rectDesk1.height() / 2, rectDesk1.width(), rectDesk1.height() / 2, 0);
               }
            }
            if(m_iArea != iHitArea)
            {
               m_areaa[m_iArea].m_taska.remove_at(m_iDragTask - m_iTaskOffset);
               count count1 = m_areaa[m_iArea].m_hwnda.remove(hwnd);
               count count2 = m_areaa[m_iArea].m_hwndaHidden.remove(hwnd);
               m_areaa[iHitArea].m_taska.add(area::task(hwnd));
               if(count1 > 0)
               {
                  m_areaa[iHitArea].m_hwnda.add(hwnd);
               }
               else
               {
                  m_areaa[iHitArea].m_hwndaHidden.add(hwnd);
               }
               application & app = ::querydb::app_cast(get_app());
               app.m_hwndaHidden.add(hwnd);
               mt_show_window(hwnd, SW_HIDE);
            }
            return;
         }
      }
      if(iHitArea == m_iV)
      {
	      if(::IsWindow(m_hwndWinutil))
	      {
            mt_show_window(GetTopLevelFrame()->get_safe_handle(), SW_HIDE);
            ::PostMessage(m_hwndWinutil, WM_APP + 2000, 0, 2);
	      }
      }
      else if(iHitArea == m_i_veriwell)
      {
         ::ShellExecute(NULL, NULL, System.dir().votagus("cast\\ccvotagus\\spaadmin.exe"), NULL, NULL, SW_SHOW);
      }
      else if(iHitArea == m_i_bergedge)
      {
	      if(::IsWindow(m_hwndBergedge))
	      {
            ::PostMessage(m_hwndBergedge, WM_APP + 2000, 0, 2);
	      }
      }
      else if(iHitArea == m_iShutDown)
      {
         m_bShutDown = !m_bShutDown;
         _001RedrawWindow();
      }
      else if(iHitArea == m_iClockOffset)
      {
         ToggleShowCalendar();
      }
      else if(m_bShutDown)
      {
         if(iHitArea == m_iTaskOffset)
         {
            System.osi().reboot();
         }
         else if(iHitArea == m_iTaskOffset + 1)
         {
            System.osi().shutdown(true);
         }
         else if(iHitArea == m_iTaskOffset + 3)
         {
            m_bEnsureApps = false;
            GetTopLevelFrame()->ShowWindow(SW_HIDE);
            if(m_hwndaDesk.get_size() > 0)
               ::PostMessage(m_hwndaDesk[0], WM_APP + 2000, 3, 6);
            ::PostMessage(m_hwndWinactionarea, WM_APP + 2000, 3, 6);
            ::PostMessage(m_hwndCommand, WM_APP + 2000, 3, 6);
            ::PostMessage(m_hwndWinutil, WM_APP + 2000, 3, 6);
            ::PostMessage(m_hwndWinservice1, WM_APP + 2000, 3, 6);

            ::ShellExecute(
               NULL,
               NULL,
               System.dir().ca2("ccvotagus/spaadmin.exe"),
               " uninstall _set_windesk",
               System.dir().ca2("ccvotagus"),
               SW_HIDE);
            
            return;
            // spa boot should cling (installer should catch 
            // exit could and restart main application)
         }
      }
      else if(m_bShowCalendar)
      {
         switch(m_calendar.hit_test(pt))
         {
         case calendar::ElementPreviousMonth:
            m_calendar.previous_month();
            _001RedrawWindow();
            break;
         case calendar::ElementNextMonth:
            m_calendar.next_month();
            _001RedrawWindow();
            break;
         case calendar::ElementNextYear:
            m_calendar.next_year();
            _001RedrawWindow();
            break;
         case calendar::ElementPreviousYear:
            m_calendar.previous_year();
            _001RedrawWindow();
            break;
         default:
            {
               class time time;
               if(m_calendar.time_hit_test(time, pt))
               {
                  m_calendar.set_time(time);
                  _001RedrawWindow();
               }
            }
            break;
         }
      }
      else if(iHitArea >= 0)
      {
         {
      /*      else if(iHitArea == m_iNotificationAreaButtonOffset)
            {
               m_notificationareainfo.Refresh();
               m_bNotificationArea = true;
            }*/
            if(iHitArea >= m_iNotificationAreaOffset && iHitArea < (m_iNotificationAreaOffset + m_notificationareainfo.m_infoa.get_size()))
            {
               m_notificationareainfo.LeftClick(iHitArea - m_iNotificationAreaOffset);
               ::Sleep(100);
               mt_show_window(GetParentFrame()->get_safe_handle(), SW_HIDE);
            }
            else if(iHitArea >= m_iClockOffset)
            {
               ToggleShowCalendar();
            }
            else if(iHitArea < m_areaa.get_size())
            {
               SwitchArea(iHitArea);
               m_dw3003Time = ::GetTickCount();
               SetTimer(3003, 300, NULL);
               
            }
            else if(iHitArea >= m_iTaskOffset && iHitArea < (m_iTaskOffset + m_areaa[m_iArea].m_taska.get_size()))
            {
               m_iCurrentTask = iHitArea;
               m_dwCurrentTaskChangeTime = ::GetTickCount();
               HWND hwnd = m_areaa[m_iArea].m_taska[iHitArea - m_iTaskOffset].m_hwnd;
               if(::IsIconic(hwnd))
               {
                  mt_show_window(hwnd, SW_RESTORE);
               }
               else
               {
                  if(hwnd != m_areaa[m_iArea].m_taska[0].m_hwnd)
                  {
                     mt_show_window(hwnd, -1);
                     
                  }
                  else
                  {
                     mt_show_window(hwnd, SW_MINIMIZE);
                  }
               }
               Sleep(184 + 177);
               UpdateCurrentArea();
            }
         }
      }

   }

   void view::_001OnRButtonUp(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)

      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
      int iHitArea = hit_test(pt);
      if(iHitArea >= m_iNotificationAreaOffset 
      && iHitArea < (m_iNotificationAreaOffset + m_notificationareainfo.m_infoa.get_count()))
      {
         m_notificationareainfo.RightClick(iHitArea - m_iNotificationAreaOffset);
      }
      else if(iHitArea >= m_iClockOffset)
      {
      }
      else if(iHitArea >= m_iTaskOffset 
           && iHitArea < m_iTaskOffset + m_areaa[m_iArea].m_taska.get_size())
      {
         ::userbase::menu menu(get_app());
   /* xxx      menu.LoadMenu(::GetSystemMenu(GetTopLevelParent()->_get_handle(), FALSE));
         menu.set_app(get_app());
         menu.TrackPopupMenu(0, pmouse->m_pt.x, pmouse->m_pt.y, GetParentFrame());
         */
      }
      else if(iHitArea < 0)
      {
         ::userbase::menu menu(get_app());
         menu.LoadXmlMenu("querydb\\popup_winactionarea.xml");
         ::userbase::menu menuPopup(get_app(), menu.GetSubMenu(0));
         menuPopup.TrackPopupMenu(0, pmouse->m_pt.x, pmouse->m_pt.y, GetParentFrame());
      }
      
   }

   void view::_001OnOp(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj)
      if(pbase->m_wparam == OpUpdateCurrentArea)
      {
         UpdateCurrentArea();
      }
   }


   void view::area::UpdatePreserve()
   {
      for(int i = 0; i < m_taska.get_size();)
      {
         HWND hwnd = m_taska[i].m_hwnd;
         if(!::IsWindow(hwnd) || m_pview->m_hwndaWindesk.contains(hwnd))
         {
            m_taska.remove_at(i);
            m_hwnda.remove(hwnd);
            m_hwndaHidden.remove(hwnd);
            Application.m_hwndaHidden.remove(hwnd);
         }
         else if(!::IsWindowVisible(hwnd))
         {
            m_taska.remove_at(i);
            m_hwnda.remove(hwnd);
            m_hwndaHidden.add_unique(hwnd);
            Application.m_hwndaHidden.add_unique(hwnd);
         }
         else
         {
            int iStyle = ::GetWindowLong(hwnd, GWL_STYLE);
            int iStyleEx = ::GetWindowLong(hwnd, GWL_EXSTYLE);
            if(iStyleEx & WS_EX_TOOLWINDOW)
            {
               m_taska.remove_at(i);
            }
            else if(iStyleEx & WS_EX_APPWINDOW)
            {
               i++;
            }
            else
            {
               i++;
            }
            m_hwnda.add_unique(hwnd);
            m_hwndaHidden.remove(hwnd);
            Application.m_hwndaHidden.remove(hwnd);
         }
      }
      for(int i = 0; i < m_taska.get_size(); i++)
      {
         if(m_taska[i].m_icon.m_hicon != NULL)
            continue;
         HWND hwnd = m_taska[i].m_hwnd;
         HICON hicon = NULL;
         if(!::SendMessageTimeout(hwnd, WM_GETICON, ICON_BIG, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &hicon))
         {
            hicon = NULL;
         }
         if(hicon == NULL && !::SendMessageTimeout(hwnd, WM_GETICON, ICON_SMALL, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &hicon))
         {
            hicon = NULL;
         }
         if(hicon == NULL)
         {
#ifdef X86
            hicon = (HICON)GetClassLong(hwnd, GCL_HICONSM);
#endif
         }
         if(hicon == NULL)
         {
#ifdef X86
            hicon = (HICON)GetClassLong(hwnd, GCL_HICON);
#endif
         }
         if(hicon == NULL)
         {

            DWORD dwProcessId;
            char szFilename[1024];
            DWORD dwThreadId = ::GetWindowThreadProcessId(hwnd, &dwProcessId);
            HANDLE hprocess = (HANDLE) OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ , FALSE, dwProcessId);
            memset(szFilename, 0, sizeof(szFilename));
            ::GetModuleFileNameEx((HMODULE) hprocess, NULL, szFilename, sizeof(szFilename));
            string strFilename = szFilename;
            bool bPathCaption = strFilename.Right(13) == "\\explorer.exe";
            HICON hicon16;
            HICON hicon48;
            Application.shellimageset().GetIcon(
               m_pview->GetTopLevelParent()->_get_handle(), szFilename, L"", filemanager::_shell::IconNormal, 
               &hicon16, &hicon48);
            hicon = hicon16;
            if(hicon48 != NULL)
            {
               ::DestroyIcon(hicon48);
            }
            ::CloseHandle(hprocess);
         }
         
         visual::icon & icon = m_taska[i].m_icon;
         if(icon.m_bAutoDelete)
         {
            ::DestroyIcon(icon.m_hicon);
         }
         icon.m_hicon = hicon;
         icon.m_bAutoDelete = true;
      }
   }



   void view::_001OnTimer(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::timer, ptimer, pobj)
      if(ptimer->m_nIDEvent == 543217)
      {
         if(IsWindowVisible())
         {
            m_notificationareainfo.Refresh();
         }
         else
         {
            KillTimer(543217);
         }
      }
      else if(ptimer->m_nIDEvent == 543218)
      {
         if(IsWindowVisible())
         {
            UpdateCurrentArea();
         }
         else
         {
            KillTimer(543218);
         }
      }
      else if(ptimer->m_nIDEvent == 1257784)
      {
         if(IsWindowVisible())
         {
            Snapshot(m_iArea);
            if(!(GetExStyle() & WS_EX_LAYERED))
            {
               GetTopLevelParent()->_001RedrawWindow();
            }
         }
         else
         {
            KillTimer(1257784);
         }
      }
      else if(ptimer->m_nIDEvent == 5432108)
      {
         KillTimer(ptimer->m_nIDEvent);
         UpdateCurrentArea();
      }
      else if(ptimer->m_nIDEvent == 5432180)
      {
         KillTimer(ptimer->m_nIDEvent);
         m_bDragTask = true;
      }
      else if(ptimer->m_nIDEvent == 3003)
      {
      }
      else if(ptimer->m_nIDEvent == 21977)
      {
      }
   }

   void view::UpdateCurrentArea()
   {
      m_iCurrentTask = -1;
      EnumWindows(UpdateCurrentAreaEnumWindowsProc, (LPARAM) this);
      m_areaa[m_iArea].UpdatePreserve();
   }


   BOOL CALLBACK view::UpdateCurrentAreaEnumWindowsProc(      
       HWND hwnd,
       LPARAM lParam)
   {
      view * pview = (view *) lParam;

      int iStyle = ::GetWindowLong(hwnd, GWL_STYLE);
      int iStyleEx = ::GetWindowLong(hwnd, GWL_EXSTYLE);
      string str = gen::str::get_window_text(hwnd);
      if(gen::str::begins(str, "all ")
      && gen::str::ends(str, " - visual C++ 2008 Express Edition"))
         return TRUE;

      if(hwnd != pview->GetTopLevelParent()->_get_handle()
      && ::IsWindowVisible(hwnd)
      &&   !(iStyleEx & WS_EX_TOOLWINDOW)
      &&   ((iStyleEx & WS_EX_APPWINDOW)
      ||  (!(iStyle & WS_CHILD) && ::GetParent(hwnd) == NULL)))
      {
         if(!pview->m_hwndaWindesk.contains(hwnd))
         {
            if(!pview->m_areaa.contains(hwnd))
            {
               // flag ignored by querydb
               // please implement hide task with clicks and always maximized with clicks
               // in the "task bar", ("task bar" is Microsoft (tm) Windows (r) terminology);
               //if(iStyleEx & WS_EX_TOOLWINDOW)
               /*{
                  pview->m_areaa[pview->m_iArea].m_hwndaTool.add(pwnd->get_handle());
               }
               else
               {*/
               pview->m_areaa[pview->m_iArea].m_taska.add(area::task(hwnd));
               pview->m_areaa[pview->m_iArea].m_hwnda.add(hwnd);
               pview->m_areaa[pview->m_iArea].m_hwndaHidden.remove(hwnd);
               App(pview->get_app()).m_hwndaHidden.remove(hwnd);
               //}
            }
            if(pview->m_iCurrentTask == -1
            && pview->m_areaa[pview->m_iArea].m_taska.contains(hwnd))
            {
               pview->m_iCurrentTask = 
                  pview->m_iTaskOffset +
                  pview->m_areaa[pview->m_iArea].m_taska.find_first(hwnd);
            }
         }
      }
      return TRUE;
   }

   UINT AFX_CDECL view::ThreadProcShowWindow(LPVOID lpparam)
   {
      show_window * pshow = (show_window *) lpparam;
      if(pshow != NULL)
         pshow->show();
      delete pshow;
      return 0;
   }

   void view::show_window::show()
   {
      if(m_iShow == -1)
      {
         ::SetForegroundWindow(m_hwnd);
         ::SetWindowPos(m_hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
      }
      else
      {
         if(m_iShow == SW_RESTORE)
         {
            ::SetForegroundWindow(m_hwnd);
         }
         ::ShowWindow(m_hwnd, m_iShow);
      }
      if(m_pview != NULL)
      {
         m_pview->PostMessageA(MessageOp, OpUpdateCurrentArea);
      }
   }


   void view::mt_show_window(HWND hwnd, int iShow, view * pview)
   {
      AfxBeginThread(
         pview->get_app(), 
         &view::ThreadProcShowWindow, 
         new show_window(hwnd, iShow, pview),
         THREAD_PRIORITY_HIGHEST);
   }

   void view::mt_show_window(HWND hwnd, int iShow)
   {
      mt_show_window(hwnd, iShow, this);
   }

   view::show_window::show_window(HWND hwnd, int iShow, view * pview)
   {
      m_hwnd   = hwnd;
      m_iShow  = iShow;
      m_pview  = pview;
   }



   void view::_001OnShowWindow(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::show_window, pshowwindow, pobj)
   }


   bool view::ShowCalendar(bool bShow)
   {
      m_bShowCalendar = bShow;
      if(m_bShowCalendar)
      {
         SetTimer(321654, 284, NULL);
      }
      else
      {
         KillTimer(321654);
      }
      _001RedrawWindow();
      return m_bShowCalendar;
   }

   bool view::ToggleShowCalendar()
   {
      return ShowCalendar(!m_bShowCalendar);
   }

   view::area_array::area_array(::ca::application * papp) :
      ca(papp),
      array_app_alloc < area, area & >(papp)
   {
   }


   bool view::area_array::contains(HWND hwnd)
   {
      for(int iArea = 0; iArea < get_size(); iArea++)
      {
         if(element_at(iArea).m_taska.contains(hwnd))
            return true;
      }
      return false;
   }





   BOOL CALLBACK view::GetAppsEnumWindowsProc(      
       HWND hwnd,
       LPARAM lParam)
   {
      view * pview = (view *) lParam;
      DWORD dwThreadId;
      DWORD dwProcessId;
      HICON hicon16;
      HICON hicon48;
      DWORD dwptr;
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 1, 0, SMTO_BLOCK, 100, (PDWORD_PTR) &dwptr) || dwptr != 2)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 2, 0, SMTO_BLOCK, 100, (PDWORD_PTR) &dwptr) || dwptr != 4)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 4, 0, SMTO_BLOCK, 100, (PDWORD_PTR) &dwptr) || dwptr != 5)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 5, 0, SMTO_BLOCK, 100, (PDWORD_PTR) &dwptr) || dwptr != 8)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 8, 0, SMTO_BLOCK, 100, (PDWORD_PTR) &dwptr) || dwptr != 11)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 11, 0, SMTO_BLOCK, 100, (PDWORD_PTR) &dwptr) || dwptr != 23)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 23, 0, SMTO_BLOCK, 100, (PDWORD_PTR) &dwptr) || dwptr != 33)
      {
         return TRUE;
      }
      if(::SendMessageTimeout(hwnd, WM_APP + 2000, 33, 0, SMTO_BLOCK, 100, (PDWORD_PTR) &dwptr))
      {
         if(dwptr == 1)
         {
            pview->m_hwndCommand = hwnd;
         }
         else if(dwptr == 67)
         {
            pview->m_hwndWinactionarea = hwnd;
         }
         else if(dwptr == 68)
         {
            pview->m_hwndWinutil = hwnd;
         }
         else if(dwptr == 69)
         {
            pview->m_hwndaDesk.add_unique(hwnd);
         }
      }
      return TRUE;
   }


   void view::_001On1257821(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj)

      for(int i = 0; i < m_areaa.get_count(); i++)
      {
         for(int j = 0; j < m_areaa[i].m_taska.get_count(); j++)
         {
            string str = gen::str::get_window_text(m_areaa[i].m_taska[j].m_hwnd);
            if(str.find("visual C++ 2008 Express Edition") >= 0)
            {
               mt_show_window(m_areaa[i].m_taska[j].m_hwnd, SW_RESTORE);
            }
         }
      }

   }

   view::task_thread::task_thread(::ca::application * papp, view * pview) :
      ca(papp),
      thread(papp),
      simple_thread(papp),
      m_pview(pview)
   {
      m_dwLastWinserviceCheck = ::GetTickCount();
      m_dwLastEnsure = ::GetTickCount();
   }



   int view::task_thread::run()
   {
      while(get_run())
      {
         Sleep(1984 * 11);
      }
      return 0;
   }

   view::area::area(::ca::application * papp) :
      ca(papp),
      m_spdib(papp)
   {
   }

   view::area::task::task()
   {
      m_hwnd = NULL;
      m_bPathCaption = false;
   }

   view::area::task::task(HWND hwnd)
   {
      m_hwnd = hwnd;
      m_bPathCaption = false;
   }

   view::area::task::~task()
   {
   }

   int view::area::task_array::find_first(HWND hwnd)
   {
      for(int i = 0; i < get_count(); i++)
      {
         if(element_at(i).m_hwnd == hwnd)
            return i;
      }
      return -1;
   }

   bool view::area::task_array::contains(HWND hwnd)
   {
      return find_first(hwnd) >= 0;
   }

   void view::show_calendar(const char * psz)
   {
      m_bShowCalendar = true;
      class time time = time::get_current_time();
      int iPathCount = 0;
      time = System.datetime().strtotime(Application.str_context(), psz, time.get_time(), 0, iPathCount);
      m_calendar.set_time(time);
      GetTopLevelFrame()->ShowWindow(SW_MAXIMIZE);
      _001RedrawWindow();
   }


} // namespace querydb