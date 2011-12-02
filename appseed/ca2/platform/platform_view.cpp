﻿#include "StdAfx.h"
#include "view.h"
#include "document.h"

/*
   ON_WM_PLATFORM()
   ON_COMMAND(ID_FILE_PRINT, form_view::OnFilePrint)
   ON_COMMAND(ID_FILE_PRINT_DIRECT, form_view::OnFilePrint)
   ON_COMMAND(ID_FILE_PRINT_PREVIEW, form_view::OnFilePrintPreview)
*/

namespace platform
{

   view::run::run()
   {
      m_papp = NULL;
      m_pview = NULL;
      m_plink = NULL;
   }

   view::link::link(::ax::application * papp) :
      m_button(papp)
   {
      m_prun = NULL;
   }

   view::view(::ax::application * papp) :
      ax(papp),
      ::user::interaction(papp),
      ::user::scroll_view(papp),
      ::userbase::view(papp),
      ::userbase::scroll_view(papp),
      ::user::form(papp),
      ::userbase::form_view(papp),
      html_form(papp),
      html_form_view(papp),
      form_view(papp),
      m_dibBkImage(papp),
      m_dibBk(papp),
      m_dibV(papp),
      m_dib_veriwell(papp),
      m_dib_winactionarea(papp),
      m_buttonschema(papp),
      m_font1(papp),
      m_font2(papp),
      m_font3(papp),
      m_brushBk(papp),
      m_brushProgress3(papp),
      m_brushProgress2(papp),
      m_brushProgress1(papp)
   {
      m_buttonschema.m_crBkDisabled = RGB(126, 127, 128);
      m_buttonschema.m_crBkPress = RGB(200, 127, 200);
      m_buttonschema.m_crBkHover = RGB(220, 255, 220);
      m_buttonschema.m_crBkNormal = RGB(120, 220, 255);
      m_buttonschema.m_bBorder = false;
      m_buttonschema.m_crTextDisabled = RGB(0, 0, 0);
      m_buttonschema.m_crTextPress = RGB(255, 255, 0);
      m_buttonschema.m_crTextHover = RGB(100, 180, 110);
      m_buttonschema.m_crTextNormal = RGB(100, 100, 20);
      m_brushBk->CreateSolidBrush(RGB(255, 250, 245));
      m_brushProgress1->CreateSolidBrush(RGB(120, 180, 255));
      m_brushProgress2->CreateSolidBrush(RGB(255, 240, 200));
      m_brushProgress3->CreateSolidBrush(RGB(128, 128, 128));

      LOGFONT lf;

      memset(&lf, 0, sizeof(lf));
      strcpy(lf.lfFaceName, "Geneva");
      lf.lfPitchAndFamily = FF_SWISS;
      lf.lfHeight = 16;

      m_buttonschema.m_font->CreateFontIndirectA(&lf);

      m_font1->CreateFontIndirect(&lf);

      memset(&lf, 0, sizeof(lf));
      strcpy(lf.lfFaceName, "Geneva");
      lf.lfPitchAndFamily = FF_SWISS;
      lf.lfWeight = 900;
      lf.lfHeight = 32;
      m_font2->CreateFontIndirect(&lf);

      memset(&lf, 0, sizeof(lf));
      strcpy(lf.lfFaceName, "Geneva");
      lf.lfPitchAndFamily = FF_SWISS;
      lf.lfWeight = 100;
      lf.lfItalic = 1;
      lf.lfHeight = 20;
      m_font3->CreateFontIndirect(&lf);

      m_dProgress = -1.0;
      m_dProgress1 = -1.0;
      m_dProgress2 = -1.0;
      m_iV = 123;
      m_iVH = 49;
      m_iVW = 123;
      m_i_veriwell = 256;
      m_i_veriwell_h = 49;
      m_i_veriwell_w = 74;
      m_i_winactionarea = 4;
      m_i_winactionarea_h = 49;
      m_i_winactionarea_w = 49;
   }

   view::~view()
   {
   }

   void view::install_message_handling(::gen::message::dispatch * pinterface)
   {
      form_view::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &view::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &view::_001OnPaint);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &view::_001OnContextMenu);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &view::_001OnMouseMove);

      //connect_command(ID_FILE_PRINT, form_view::OnFilePrint)
      //connect_command(ID_FILE_PRINT_DIRECT, form_view::OnFilePrint)
      //connect_command(ID_FILE_PRINT_PREVIEW, form_view::OnFilePrintPreview)

      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &view::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &view::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(gen::application::APPM_LANGUAGE, pinterface, this, &view::_001OnAppLanguage);

   }

   #ifdef _DEBUG
   void view::assert_valid() const
   {
      form_view::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      form_view::dump(dumpcontext);
   }
   #endif //_DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // ::view message handlers

   // vmpLightView.cpp : implementation of the ::view class
   //



   BOOL view::PreCreateWindow(CREATESTRUCT& cs)
   {
      cs.lpszClass = System.RegisterWndClass(
         CS_DBLCLKS |
         CS_OWNDC,
         0, 0, 0);
      cs.style &= ~WS_EX_CLIENTEDGE;
      return form_view::PreCreateWindow(cs);
   }
   /////////////////////////////////////////////////////////////////////////////
   // ::view printing

   void view::_001OnInitialUpdate(gen::signal_object * pobj)
   {
      form_view::_001OnInitialUpdate(pobj);
      load_links();

      //str += "</body></html>";

//      string strFile = System.file().time_square();

  //    Application.file().put_contents(strFile, str);

    //  get_document()->open_document(strFile);


   }

   ::user::interaction* view::get_guie()
   {
      return this;
   }

   void view::on_update(::view * pSender, LPARAM lHint, ::radix::object* phint)
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(phint);
      if(lHint == 123)
      {

      }
   }

   database::user::interaction* view::BackViewGetWnd()
   {
      return this;
   }
   void view::_001OnDestroy(gen::signal_object * pobj)
   {
      form_view::_001OnDestroy(pobj);

   }




   void view::_001OnPaint(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   //CPaintDC spgraphics(this); // device context for platforming


     // spgraphics->TextOut(20, 20, "Carlos Gustavo Cecyn Lundgren é minha Vida Eterna, meu Coração Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
   }


   /*void view:: _001OnDraw(::ax::graphics * pdc)
   {
      m_hwnd = GetSafeHwnd();
      pdc->SetBkMode(TRANSPARENT);

      //FIBITMAP * pdib = imaging::LoadImageFile("C:\\screenshot.jpeg");

      //::ax::bitmap bmp2;

      //bmp2.Attach(imaging::FItoHBITMAP(pdib, true));
      //::ax::graphics_sp dc2;
      //dc2.CreateCompatibleDC(pdc);
      //dc2.SelectObject(bmp2);

      //::SendMessage(::GetDesktopWindow(), WM_PRINT, (WPARAM)(HDC)spgraphics, PRF_CHILDREN | PRF_NONCLIENT | PRF_CLIENT);

      //pdc->BitBlt(0, 0, 1280, 1024, &dc2, 0, 0, SRCCOPY);
   //   pdc->TextOut(20, 20, "Curitiba, 24 de fevereiro de 2008.");
     // pdc->TextOut(20, 80, "Carlos Gustavo Cecyn Lundgren é minha Vida Eterna, meu Coração Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
      //pdc->TextOut(20, 110, "Assinado Camilo Sasuke Tsumanuma.");
   }*/

   void view::_001OnCreate(gen::signal_object * pobj)
   {

      if(pobj->previous())
         return;

      SetTimer(198477, 230, NULL);


      //FIBITMAP * pfi;

      //::ax::graphics * pdc = GetDC();

      m_dibBkImage.load_from_matter("casweden1.png");

      m_dibBk->create(1280, 1024);
      //gen::savings & savings = System.savings();
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

      SetTimer(21977, 1984 * 11, NULL);  // max. 12 fps

      check_apps();




      //pfi = System.imaging().LoadImageFile(
        // System.dir().standard_square_matter());
      m_dibV.load_from_matter("votagus_mountains_and_valleys-123.png");

      //pfi = System.imaging().LoadImageFile(
         //System.dir().standard_square_matter());
      m_dib_veriwell.load_from_matter("veriwell_2008_green_h49.png");

      //pfi = System.imaging().LoadImageFile(
        // System.dir().standard_square_matter());
      m_dib_winactionarea.load_from_matter("winactionarea.png");


      System.imaging().color_blend(m_dibBk->get_graphics(), 0, 0, 1280, 1024, RGB(235, 245, 255), 31);

   }
   void view::_001OnContextMenu(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::context_menu, pcontextmenu, pobj)
      point point = pcontextmenu->GetPoint();

   }

   document * view::get_document()
   {
      return dynamic_cast < document * > (form_view::get_document());
   }



   void view::SetScreen(int iScreen)
   {
      m_iScreen = iScreen;

   /*   if(iScreen == 0)
      {
         m_buttonKaraoke._001SetVisible(true);
      }
      else
      {
         m_buttonKaraoke._001SetVisible(false);
      }*/
      _001RedrawWindow();
   }

   bool view::BaseOnControlEvent(::user::control_event * pevent)
   {
      if(pevent->m_eevent == ::user::event_button_clicked)
      {
         for(int i = 0; i < m_linka.get_size(); i++)
         {
            if(pevent->m_puie->m_id == m_linka[i].m_strBrief)
            {
               SetScreen(1);
               string strApp = m_linka[i].m_strSrc;
               gen::str::ends_eat_ci(strApp, ".dll");

               ::ax::create_context_sp cc(&Application.command_central());

               cc->m_spCommandLine->m_strApp   = strApp;
               cc->m_spCommandLine->m_varFile  = Bergedge.m_varTopicFile;

               Bergedge.command().request(cc);
            }
         }
      }
      else if(pevent->m_eevent == ::user::event_mouse_enter)
      {
   //     if(pevent->m_pcontrol->m_pwndi == &m_buttonKaraoke)
         {
         }
     //    else
         {
         }
      }
      else if(pevent->m_eevent == ::user::event_mouse_leave)
      {
      }
      return true;
   }




   void view:: _001OnDraw(::ax::graphics * pdc)
   {
      form_view::_001OnDraw(pdc);
//      document * pdoc = get_document();
      class imaging & imaging = System.imaging();


      rect rectClient;
      GetClientRect(rectClient);



      if(rectClient.width() <= 0
         || rectClient.height() <= 0)
         return;
      /*rect rectDesktop = System.m_monitorinfoa[0].rcMonitor;
      if(rectDesktop.width() < 800)
      {
         rectDesktop.left = 0;
         rectDesktop.right = ::GetSystemMetrics(SM_CXSCREEN);
      }
      if(rectDesktop.height() < 600)
      {
         rectDesktop.top = 0;
         rectDesktop.bottom = ::GetSystemMetrics(SM_CYSCREEN);
      }*/
      if(System.savings().is_trying_to_save(gen::resource_processing))
      {
         pdc->FillRect(&rectClient, m_brushBk);
      }
      else
      {
         ::ax::dib_sp spdib(get_app());
         ::ax::dib_sp spdib2(get_app());
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


      class rect rectThumb;
      if(m_pbergedge != NULL && &Bergedge != NULL)
      {
         Bergedge.get_document()->get_bergedge_view()->GetWindowRect(rectThumb);
         if(rectThumb.area() > 0)
         {
            ::ax::dib_sp dib(get_app());
            dib->create(1920, 1080);
            keeper < bool > keepOnDraw(&dynamic_cast <::platform::frame * >(GetParentFrame())->m_bOnDraw, true, false, true);
            Bergedge.get_document()->get_bergedge_view()->_000OnDraw(dib->get_graphics());
            dib->get_graphics()->SetViewportOrg(0, 0);
            keepOnDraw.KeepAway();

            ::ax::dib_sp dibThumb(get_app());
            double dRate = 184.0 / rectThumb.width();
            dibThumb->create((int) (dRate * rectThumb.width()), (int) (dRate * rectThumb.height()));
            dibThumb->get_graphics()->SetStretchBltMode(HALFTONE);
            dibThumb->get_graphics()->StretchBlt(0, 0, dibThumb->width(), dibThumb->height(), dib->get_graphics(), rectThumb.left, rectThumb.top, rectThumb.width(), rectThumb.height(), SRCCOPY);

            imaging.bitmap_blend(pdc, point(10, 10), dibThumb->size(), dibThumb->get_graphics(), null_point(), (byte) (255.0 * 0.67));
         }
      }

/*      pdc->SetBkMode(TRANSPARENT);
      pdc->SelectObject(m_font1);
      pdc->SetTextColor(RGB(108, 0, 108));
      LPTSTR lpsz8 = "ccvotagus ca2";
      pdc->TextOut(10, 10, lpsz8, strlen(lpsz8));
      pdc->SetTextColor(RGB(0, 0, 0));
      LPTSTR lpsz = "dedicated to Carlos Gustavo Cecyn Lundgren";
      pdc->TextOut(10, 30, lpsz, strlen(lpsz));
      LPTSTR lpsz2 = "program created on 2008-03-27";
      pdc->TextOut(10, 50, lpsz2, strlen(lpsz2));
      LPTSTR lpsz3 = "by Camilo Sasuke Tsumanuma";
      pdc->TextOut(10, 80, lpsz3, strlen(lpsz3));*/


      if(m_dProgress >= 0 && m_iScreen == 1)
      {
         RECT rectProgress;
         rectProgress = rectClient;
         rectProgress.left += 10;
         rectProgress.right -= 10;
         rectProgress.top += 200;
         rectProgress.bottom = rectProgress.top + 20;
         pdc->FillRect(&rectProgress, m_brushProgress3);
         rectProgress.left++;
         rectProgress.right--;
         rectProgress.top++;
         rectProgress.bottom--;
         pdc->FillRect(&rectProgress, m_brushProgress2);
         rectProgress.right = ((int) ((rectProgress.right - rectProgress.left) * m_dProgress)) + rectProgress.left;
         pdc->FillRect(&rectProgress, m_brushProgress1);
      }

      if(m_iScreen == 1)
      {
         pdc->SetTextColor(RGB(0, 108, 0));
         pdc->SelectObject(m_font2);
         pdc->TextOut(10, 110, m_strStatus1);
         pdc->SetTextColor(RGB(0, 0, 108));
         pdc->SelectObject(m_font3);
         pdc->TextOut(10, 170, m_strStatus2);
      }


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

      GetAreaThumbRect(rectArea, m_i_winactionarea);
      m_dib_winactionarea->bitmap_blend(pdc, rectArea);
      if(m_iHitArea == m_i_winactionarea)
      {
         imaging.color_blend(pdc, rectArea, RGB(140, 255, 110), 80);
      }


   }

   void view::open_document_file(::ax::create_context * pcreatecontext)
   {
      try
      {
         Bergedge.open_document_file(pcreatecontext);
      }
      catch(...)
      {
      }
   }


   void view::check_apps()
   {
   //   if(::IsDebuggerPresent())
     //    return;
      //if(!m_bEnsureApps)
        // return;

      if(::IsWindow(m_hwndWinactionarea) &&
         ::IsWindow(m_hwndCommand) &&
         ::IsWindow(m_hwndWinutil) &&
         ::IsWindow(m_hwndBergedge))
      {
         return;
      }
      m_hwndWinservice1       =  ::FindWindow(NULL, "ca2::fontopus::message_wnd::winservice_1");
      m_hwndWinactionarea     =  ::FindWindow(NULL, "ca2::fontopus::message_wnd::winactionarea");
      m_hwndCommand           =  ::FindWindow(NULL, "ca2::fontopus::message_wnd::command");
      m_hwndWinutil           =  ::FindWindow(NULL, "ca2::fontopus::message_wnd::winutil");
      m_hwndBergedge          =  ::FindWindow(NULL, "ca2::fontopus::message_wnd::bergedge");
   }


   int view::hit_test(point pt, e_element & eelement)
   {
      rect rectArea;
      GetAreaThumbRect(rectArea, m_iV);
      if(rectArea.contains(pt))
      {
         eelement = element_area;
         return m_iV;
      }
      GetAreaThumbRect(rectArea, m_i_veriwell);
      if(rectArea.contains(pt))
      {
         eelement = element_area;
         return m_i_veriwell;
      }
      GetAreaThumbRect(rectArea, m_i_winactionarea);
      if(rectArea.contains(pt))
      {
         eelement = element_area;
         return m_i_winactionarea;
      }
      eelement = element_none;
      return -1;
   }


   UINT AFX_CDECL view::ThreadProcShowWindow(LPVOID lpparam)
   {
      show_window * pshow = (show_window *) lpparam;
      if(pshow != NULL)
         pshow->show();
      delete pshow;
      return 0;
   }

   void view::_001OnAppLanguage(::gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::gen::message::base, pbase, pobj);
      load_links();
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
   }

   void view::mt_show_window(HWND hwnd, int iShow)
   {
      AfxBeginThread(
         get_app(),
         &view::ThreadProcShowWindow,
         new show_window(hwnd, iShow),
         THREAD_PRIORITY_HIGHEST);
   }

   view::show_window::show_window(HWND hwnd, int iShow)
   {
      m_hwnd   = hwnd;
      m_iShow  = iShow;
   }

   void view::_001OnTimer(gen::signal_object * pobj)
   {

      SCAST_PTR(::gen::message::timer, ptimer, pobj)

      if(ptimer->m_nIDEvent == 21977)
      {
         check_apps();
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
      else if(iArea == m_i_winactionarea)
      {
         lprect->bottom = rectClient.bottom;
         lprect->top = lprect->bottom - m_i_winactionarea_h;
         lprect->left = 1 + m_iVW + 5 + m_i_veriwell_w + 5;
         lprect->right = lprect->left + m_i_winactionarea_w;
      }
   }

   void view::_001OnLButtonUp(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::mouse, pmouse, pobj)
      pmouse->set_lresult(1);
      KillTimer(5432180);
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
      e_element eelement;
      int iHitArea = hit_test(pt, eelement);
/*      if(m_bDragTask && !m_bShowCalendar && !m_bShutDown)
      {
         m_bDragTask = false;
         if(m_iDragTask >= m_iTaskOffset
         && m_iDragTask < m_iTaskOffset + m_areaa[m_iArea].m_taska.get_size()
         && iHitArea >= 0
         && iHitArea < m_areaa.get_size())
         {
            HWND hwnd = m_areaa[m_iArea].m_taska[m_iDragTask - m_iTaskOffset].m_hwnd;
            rect rectArea;
            rect rectDesk0 = System.m_monitorinfoaDesk[0].rcMonitor;
            rect rectDesk1 = System.m_monitorinfoaDesk[1].rcMonitor;
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
               application & app = ::winactionarea::app_cast(get_app());
               app.m_hwndaHidden.add(hwnd);
               mt_show_window(hwnd, SW_HIDE);
            }
            return;
         }
      }*/
      if(iHitArea == m_iV)
      {
         check_apps();
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
      else if(iHitArea == m_i_winactionarea)
      {
         check_apps();
         if(::IsWindow(m_hwndWinactionarea))
         {
            mt_show_window(GetTopLevelFrame()->get_safe_handle(), SW_HIDE);
            ::PostMessage(m_hwndWinactionarea, WM_APP + 2000, 0, 2);
         }
      }
/*      else if(iHitArea == m_iShutDown)
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
  /*          if(iHitArea >= m_iNotificationAreaOffset && iHitArea < (m_iNotificationAreaOffset + m_notificationareainfo.m_infoa.get_size()))
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
*/
   }

   void view::_001OnMouseMove(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::mouse, pmouse, pobj)
      pmouse->set_lresult(1);
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
      e_element eelement;
      int iHitArea = hit_test(pt, eelement);
      if(m_iHitArea < 0 && iHitArea >=0)
         track_mouse_hover();
      m_iHitArea =  iHitArea;

   }

   void view::load_links()
   {
      for(int i = 0; i < m_linka.get_size(); i++)
      {
         m_linka[i].m_button.DestroyWindow();
      }
      m_linka.remove_all();

      string str = Application.file().as_string(Application.dir().matter("platform\\main_link.xml"));
      xml::node node(get_app());
      node.load(str);
      //str = "<html><head></head><body>";

      for(int i = 0; i < node.children().get_size(); i++)
      {
         if(node.child_at(i)->m_strName == "link")
         {
            link * plink = new link(get_app());
            m_linka.add(plink);

            plink->m_iId               = i;

            plink->m_strBrief          = node.child_at(i)->attr("brief");
            plink->m_strName           = node.child_at(i)->attr("name");
            plink->m_strDescription    = node.child_at(i)->attr("description");
            plink->m_strSrc            = node.child_at(i)->attr("src");

            plink->m_button.create(this, plink->m_strBrief);

            plink->m_button.m_etranslucency  = TranslucencyPresent;
            plink->m_button.m_pschema        = &m_buttonschema;

            plink->m_button._001SetButtonText(plink->m_strName);

            string strAttr             = node.child_at(i)->attr("icon");

            if(gen::str::begins_eat(strAttr, "matter://"))
            {
               plink->m_button.m_dib.load_from_matter(strAttr);
            }
            //str += "<input type=\"button\" value=\"" + plink->m_strName + "\" ";
            //str += "id=\"" + plink->m_strBrief + "\" /><br />";
         }
      }
      layout();
   }

   void view::layout()
   {
      int h = 20;
      int y = 400;
      for(int i = 0; i < m_linka.get_count(); i++)
      {
         m_linka[i].m_button.SetWindowPos(ZORDER_TOP, 11, y, 300, h, SWP_SHOWWINDOW);
         y+=h;
      }
   }

} // namespace platform
