#include "StdAfx.h"
#include "view.h"
#include <Psapi.h>

namespace windesk
{

   view::view(::ca::application * papp) :
      ca(papp),
      ::user::interaction(papp),
      ::userbase::view(papp),
      m_dibBkImage(papp),
      m_dibBk(papp),
      m_dibcolor_blend_Area(papp),
      m_dibcolor_blend_Task(papp),
      m_dib_veriwell(papp),
      m_dibShutDown(papp),
      m_dibV(papp),
      m_font(papp)
   {

      m_brushBkActive.CreateSolidBrush(RGB(150, 255, 130));
      m_brushBkInactive.CreateSolidBrush(RGB(128, 208, 120));
      LOGFONT lf;
      memset(&lf, 0, sizeof(lf));

      strcpy(lf.lfFaceName, "Verdana");
      lf.lfHeight = 13;
      m_font->CreateFontIndirect(&lf);

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
      m_iNotificationAreaColumnCount = 15;
      m_iV = 123;
      m_iVH = 49;
      m_iVW = 123;
      m_i_veriwell = 256;
      m_i_veriwell_h = 49;
      m_i_veriwell_w = 74;
      m_iShutDown = 60000;
      m_iShutDownW = 49;
      m_iShutDownH = 49;
      m_bShutDown = false;
      m_bEnsureApps = true;
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

      //IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &::user::interaction::_001OnLButtonDown);
      //IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &::user::interaction::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &::user::interaction::_001OnKeyDown);
      IGUI_WIN_MSG_LINK(WM_KEYUP, pinterface, this, &::user::interaction::_001OnKeyUp);

      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &view::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &view::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &view::_001OnTimer);

      IGUI_WIN_MSG_LINK(MessageOp, pinterface, this, &view::_001OnOp);
      IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &view::_001OnShowWindow);
      IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &view::_001OnDestroy);
      //IGUI_WIN_MSG_LINK(1257821, pinterface, this, &view::_001On1257821);

   }
   /////////////////////////////////////////////////////////////////////////////
   // ::view drawing

   void view::OnDraw(::ca::graphics * pdcScreen)
   {
      UNREFERENCED_PARAMETER(pdcScreen);
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

   /////////////////////////////////////////////////////////////////////////////
   // ::view message handlers

   // vmpLightView.cpp : implementation of the ::view class
   //


   /////////////////////////////////////////////////////////////////////////////
   // ::view


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
      UNREFERENCED_PARAMETER(phint);
   }

   void view::_001OnSize(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::user::win::message::size, psize, pobj)

      rect rectDesktop;
      Application.get_screen_rect(rectDesktop);

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
   }

   void view::_001OnPaint(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
   //	CPaintDC spgraphics(this); // device context for winactionareaing
     // spgraphics->TextOut(20, 20, "Carlos Gustavo Cecyn Lundgren é minha Vida Eterna, meu Coração Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
   }


   void view:: _001OnDraw(::ca::graphics * pdc)
   {
//      class imaging & imaging = Application.imaging();
      rect rectClient;
      GetClientRect(rectClient);
      //pdc->FillSolidRect(rectClient, RGB(205, 200, 191));
      //m_dibBk.to(pdc, 0, 0, rectClient.right, rectClient.bottom);
      ::ca::window * pwndDesktop = Application.get_desktop_window();
      HDC hdcScreen = ::GetDC(NULL);
      rect rectDesktop;
      pwndDesktop->GetWindowRect(rectDesktop);
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
      ::ca::dib_sp spdib(get_app());
      ::ca::dib_sp spdib2(get_app());
      spdib->create(rectClient.width(), rectClient.height());
      spdib2->create(rectClient.width(), rectClient.height());
      rect rectWindow = rectClient;
      ClientToScreen(rectWindow);
      spdib->create(rectClient.width(), rectClient.height());
      //::BitBlt(dc2, 0, 0, rectClient.width(), rectClient.height(), hdcScreen, rectWindow.left, rectWindow.top, SRCCOPY);
      //imaging.blur_(&spgraphics, 0, 0, rectClient.width(), rectClient.height(), &dc2, 0, 0, 2);
      /*imaging.bitmap_blend(pdc, 0, 0, 
         rectWindow.width(),
         rectWindow.height(),
         &spgraphics,
         0, 0, 49);*/
      ::ReleaseDC(NULL, hdcScreen);
      //pwndDesktop->ReleaseDC(pdcScreen);

      
      pdc->SetTextColor(RGB(0, 0, 0));
      HGDIOBJ hgdiOldFont = pdc->SelectObject(m_font);
      pdc->SetBkMode(TRANSPARENT);
      rect rectArea;

   /*   GetAreaThumbRect(rectArea, m_iV);
      m_dibV.to(pdc, rectArea.left, rectArea.top, rectArea.width(), rectArea.height());

      GetAreaThumbRect(rectArea, m_i_veriwell);
      m_dib_veriwell.to(pdc, rectArea.left, rectArea.top, rectArea.width(), rectArea.height());

      GetAreaThumbRect(rectArea, m_iShutDown);
      imaging.bitmap_blend(
         pdc,
         rectArea.left, rectArea.top, rectArea.width(), rectArea.height(),
         &m_dcShutDown, 0, 0);
      //m_dibShutDown.to(pdc, );
   /*
   /*   
      GetAreaThumbRect(rectArea, m_iNotificationAreaButtonOffset);

      string strNotificationAreaButton("Notification Area button");
      wstring wstrNotificationAreaButton = gen::international::utf8_to_unicode(strNotificationAreaButton);
      ::DrawTextW((HDC)pdc->get_os_data(), wstrNotificationAreaButton, wstrNotificationAreaButton.get_length(), rectArea, DT_VCENTER | DT_LEFT | DT_SINGLELINE);
   */

      //GetAreaThumbRect(rectArea, m_iClockOffset);
      string strDateTime;
      calendar(get_app()).GetDateTime(pdc->str_context(), strDateTime);
      wstring wstrDateTime = gen::international::utf8_to_unicode(strDateTime);
      ::DrawTextW((HDC)pdc->get_os_data(), wstrDateTime, wstrDateTime.get_length(), rectArea, DT_VCENTER | DT_LEFT | DT_SINGLELINE);
      {
//         COLORREF crBk;
         if(!m_bShutDown)
         {
         }
         rect rectText;
         rect rectIcon;
         rect rectPad;
//         WCHAR szWindowText[1024];
//         ::ca::brush * pbrBk;
         ::ca::brush * pbrOld = pdc->GetCurrentBrush();
//         bool bCurrentAreaTime = (::GetTickCount() - m_dwCurrentAreaTime) < 1000;
         if(m_bShutDown)
         {
            wstring wstr;
            //GetAreaThumbRect(rectArea, m_iTaskOffset);
            wstr = L"Reiniciar";
            ::DrawTextW((HDC)pdc->get_os_data(), wstr, wstr.get_length(), rectArea, DT_VCENTER | DT_LEFT | DT_SINGLELINE);
            //GetAreaThumbRect(rectArea, m_iTaskOffset + 1);
            wstr = L"Desligar";
            ::DrawTextW((HDC)pdc->get_os_data(), wstr, wstr.get_length(), rectArea, DT_VCENTER | DT_LEFT | DT_SINGLELINE);
         }
         else
         {
         }
         pdc->SelectObject(hgdiOldFont);
         pdc->SelectObject(pbrOld);
      }
      COLORREF crBk;
      if(m_bNotificationArea)
      {
         //rect rect1;
         //rect rect2;
   /*      GetAreaThumbRect(rect1, m_iNotificationAreaOffset);
         GetAreaThumbRect(rect2, m_iNotificationAreaOffset + m_iNotificationAreaColumnCount * 2 - 1);
         rectArea.union(rect1, rect2);
         imaging.color_blend(pdc, rectArea, RGB(184, 220, 177), 128);*/
         rect rectText;
         rect rectIcon;
         rect rectPad;
//         WCHAR szWindowText[1024];
         ::ca::brush * pbrBk;
         ::ca::brush * pbrOld = pdc->GetCurrentBrush();
//         bool bCurrentAreaTime = (::GetTickCount() - m_dwCurrentAreaTime) < 1000;
         for(int i = 0; i < m_notificationareainfo.m_infoa.get_size(); i++)
         {
            
            //GetAreaThumbRect(rectArea, m_iNotificationAreaOffset + i);
            rectArea.deflate(1, 1);
   /*         if((bCurrentAreaTime && i == m_iCurrentArea - m_iTaskOffset)
            || (!bCurrentAreaTime && m_areaa[m_iArea].m_hwndaPreserve[i] ==  m_areaa[m_iArea].m_hwnda[0]))
            {
               crBk = RGB(150, 255, 130);
               pbrBk = &m_brushBkActive;
               imaging.color_blend(pdc, rectArea, crBk, 123, &m_dibcolor_blend_Task);
               pdc->Draw3dRect(rectArea, RGB(150, 200, 135), RGB(190, 230, 184));
               rectArea.deflate(1, 1);
               pdc->Draw3dRect(rectArea, RGB(190, 230, 184), RGB(150, 200, 135));
            }
            else*/
            {
               crBk = RGB(128, 208, 120);
               pbrBk = &m_brushBkInactive;
               //imaging.color_blend(pdc, rectArea, crBk, 52, &m_dibcolor_blend_Task);
               //pdc->Draw3dRect(rectArea, RGB(110, 150, 90), RGB(250, 255, 240));
               rectArea.deflate(1, 1);
               //pdc->Draw3dRect(rectArea, RGB(250, 255, 240), RGB(110, 150, 90));
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
            //::GetWindowTextW(m_areaa[m_iArea].m_hwndaPreserve[i], szWindowText, sizeof(szWindowText) / sizeof(WCHAR));
            m_notificationareainfo.m_pil16->draw(pdc, i, rectIcon.top_left(),
               rectIcon.size(), point(0, 0), 0);
            wstring wstr;
            wstr = gen::international::utf8_to_unicode(m_notificationareainfo.m_infoa[i].sTip);
   //         ::DrawTextW((HDC)pdc->get_os_data(), wstr, wstr.get_length(), rectText, DT_VCENTER | DT_LEFT | DT_END_ELLIPSIS | DT_SINGLELINE);
      /*      if(m_areaa[m_iArea].m_hwndaPreserve[i] ==  m_areaa[m_iArea].m_hwnda[0])
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
         pdc->SelectObject(hgdiOldFont);
         pdc->SelectObject(pbrOld);
      }
   }


   void view::_001OnCreate(gen::signal_object * pobj) 
   {
      if(pobj->previous())
         return;

      SetTimer(3003, 300, NULL);
      SetTimer(543218, 1000, NULL);

      m_dibBkImage.load_from_matter("casweden1.png");
      m_dibV.load_from_matter("votagus_mountains_and_valleys-123.png");
      m_dib_veriwell.load_from_matter("veriwell_2008_green_h49.png");
      m_dibShutDown.load_from_matter("shut_down.png");

      /*
      pfi = Application.imaging().LoadImageFile(
         System.dir().standard_square_matter("shut_down.png"));
      ::ca::bitmap * pbmp = Application.imaging().FItoHBITMAP(pfi, true);
      BITMAP bmp;
      pbmp->GetObject(sizeof(bmp), &bmp);
      m_dibShutDown->create(bmp.bmWidth, bmp.bmHeight);
      ::ca::graphics_sp dc1;
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
      ReleaseDC(pdc);*/
      
      m_dibBkImage->copy(m_dibBk);
      m_dibBk->create(1280, 1024);
      Application.imaging().color_blend(m_dibBk->get_graphics(), 0, 0, 1280, 1024, RGB(235, 245, 255), 31);
      m_notificationareainfo.Initialize(get_app());


      frame * pframe = dynamic_cast < frame * > (GetTopLevelFrame());
      pframe->m_pview = this;
   /*   winaction_frame * pframe = dynamic_cast < winaction_frame * > (GetParentFrame());
      if(pframe != NULL)
      {
         pframe->m_pwinactionareaview = this;
      }*/
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


   int view::hit_test(point pt)
   {
      rect rectArea;
      //GetAreaThumbRect(rectArea, m_iV);
      if(rectArea.contains(pt))
      {
         return m_iV;
      }
      //GetAreaThumbRect(rectArea, m_i_veriwell);
      if(rectArea.contains(pt))
      {
         return m_i_veriwell;
      }
      //GetAreaThumbRect(rectArea, m_iShutDown);
      if(rectArea.contains(pt))
      {
         return m_iShutDown;
      }
      //GetAreaThumbRect(rectArea, m_iClockOffset);
      if(rectArea.contains(pt))
      {
         return m_iClockOffset;
      }
   /*   GetAreaThumbRect(rectArea, m_iNotificationAreaButtonOffset);
      if(rectArea.contains(pt))
      {
         return m_iNotificationAreaButtonOffset;
      }*/
      for(int i = 0; i < m_notificationareainfo.m_infoa.get_size(); i++)
      {
         //GetAreaThumbRect(rectArea, m_iNotificationAreaOffset + i);
         if(rectArea.contains(pt))
         {
            return m_iNotificationAreaOffset + i;
         }
      }
      for(int i = 0; i < 4; i++)
      {
         //GetAreaThumbRect(rectArea, i);
         if(rectArea.contains(pt))
         {
            return i;
         }
      }
      return -1;
   }

   void view::_001OnLButtonDown(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)

      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
      int iHitArea = hit_test(pt);
      if(iHitArea >= 0 && !m_bShutDown)
      {
      }

   }

   void view::_001OnLButtonUp(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
      KillTimer(5432180);
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
      int iHitArea = hit_test(pt);
      if(m_bDragTask && !m_bShutDown)
      {
      }
      if(iHitArea == m_iV)
      {
	      ensure_apps();
   /*	   if(::IsWindow(m_hwndWinutil))
	      {
		      GetTopLevelFrame()->ShowWindow(SW_HIDE);
            ::PostMessage(m_hwndWinutil, WM_APP + 2000, 0, 2);
	      }*/
      }
      else if(iHitArea == m_i_veriwell)
      {
         ::ShellExecute(NULL, NULL, System.dir().votagus("cast\\ccvotagus\\spa.exe"), NULL, NULL, SW_SHOW);
      }
      else if(iHitArea == m_iShutDown)
      {
         m_bShutDown = !m_bShutDown;
         _001RedrawWindow();
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
      }
      else if(iHitArea >= 0)
      {
         {
      /*      else if(iHitArea == m_iNotificationAreaButtonOffset)
            {
               m_notificationareainfo.Refresh();
               m_bNotificationArea = true;
            }*/
   /*         if(iHitArea >= m_iNotificationAreaOffset && iHitArea < (m_iNotificationAreaOffset + m_notificationareainfo.m_infoa.get_size()))
            {
               m_notificationareainfo.LeftClick(iHitArea - m_iNotificationAreaOffset);
               ::Sleep(100);
               GetParentFrame()->ShowWindow(SW_HIDE);
            }*/
            //else if(iHitArea >= m_iClockOffset)
            //{
              // ToggleShowCalendar();
            //}
         }
      }

   }


   void view::_001OnOp(gen::signal_object * pobj)
   {
//      SCAST_PTR(::user::win::message::base, pbase, pobj)
      UNREFERENCED_PARAMETER(pobj);
   }



   void view::_001OnTimer(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::timer, ptimer, pobj)
      if(ptimer->m_nIDEvent == 543218)
      {
         if(IsWindowVisible())
         {
            m_notificationareainfo.Refresh();
         }
      }
      else if(ptimer->m_nIDEvent == 5432180)
      {
         KillTimer(ptimer->m_nIDEvent);
         m_bDragTask = true;
      }
      else if(ptimer->m_nIDEvent == 3003)
      {
         point pt;
         Application.get_cursor_pos(&pt);
         HWND hwnd = ::WindowFromPoint(pt);
         if(GetTopLevelParent()->_get_handle() != hwnd
            && !user::WndUtil::IsAscendant(GetParentFrame()->_get_handle(), hwnd))
         {
            //GetParentFrame()->ShowWindow(SW_HIDE);
         }
      }
      else if(ptimer->m_nIDEvent == 21977)
      {
         ensure_apps();
      }
   }


   UINT AFX_CDECL view::ThreadProcShowWindow(LPVOID lpparam)
   {
      show_window * pshow = (show_window *) lpparam;
      if(pshow->m_iShow == -1)
      {
         ::SetForegroundWindow(pshow->m_hwnd);
         ::SetWindowPos(pshow->m_hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
      }
      else
      {
         if(pshow->m_iShow == SW_RESTORE)
         {
            ::SetForegroundWindow(pshow->m_hwnd);
         }
         ::ShowWindow(pshow->m_hwnd, pshow->m_iShow);
      }
      pshow->m_pview->PostMessageA(MessageOp, OpUpdateCurrentArea);
      delete pshow;
      return 0;
   }

   view::show_window::show_window(HWND hwnd, int iShow, ::view * pview)
   {
      m_hwnd   = hwnd;
      m_iShow  = iShow;
      m_pview  = pview;
   }



   void view::_001OnShowWindow(gen::signal_object * pobj) 
   {
//      SCAST_PTR(::user::win::message::show_window, pshowwindow, pobj)
      UNREFERENCED_PARAMETER(pobj);
   }


   void view::ensure_apps()
   {
      if(!m_bEnsureApps)
         return;
      if(::IsWindow(m_hwndWinactionarea) &&
         ::IsWindow(m_hwndCommand) &&
         ::IsWindow(m_hwndWinutil))
         return;
      EnumWindows(GetAppsEnumWindowsProc, (LPARAM) this);
      if(!::IsWindow(m_hwndWinactionarea))
      {
         /*::ShellExecuteW(
               NULL, 
               NULL, 
               gen::international::utf8_to_unicode(m_strWinactionarea),
               NULL,
               gen::international::utf8_to_unicode(System.dir().name(m_strWinactionarea)),
               SW_SHOW);*/
      }
      if(!::IsWindow(m_hwndCommand))
      {
         /*::ShellExecuteW(
               NULL, 
               NULL, 
               gen::international::utf8_to_unicode(m_id),
               NULL,
               gen::international::utf8_to_unicode(System.dir().name(m_id)),
               SW_SHOW);*/
      }
   }


   BOOL CALLBACK view::GetAppsEnumWindowsProc(      
       HWND hwnd,
       LPARAM lParam)
   {
      view * pview = (view *) lParam;
//      DWORD dwThreadId;
//      DWORD dwProcessId;
//      HICON hicon16;
//      HICON hicon48;
      DWORD dwptr;
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 1, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 2)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 2, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 4)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 4, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 5)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 5, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 8)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 8, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 11)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 11, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 23)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 23, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 33)
      {
         return TRUE;
      }
      if(::SendMessageTimeout(hwnd, WM_APP + 2000, 33, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr))
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

      }
      return TRUE;
   }

} // namespace windesk