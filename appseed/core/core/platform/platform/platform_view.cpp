#include "framework.h"


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
      m_pauraapp = NULL;
      m_pview = NULL;
      m_plink = NULL;
   }

   view::link::link(sp(::aura::application) papp) :
      m_button(papp)
   {
      m_prun = NULL;
   }

   view::view(sp(::aura::application) papp) :
      element(papp),
      ::user::interaction(papp),
      ::user::scroll_view(papp),
      ::user::form_interface(papp),
      ::user::form(papp),
      html_form(papp),
      html_form_view(papp),
      form_view(papp),
      m_dibBkImage(papp),
      m_dibBk(papp),
      m_dibV(papp),
      m_dib_veriwell(papp),
      m_dib_winactionarea(papp),
      m_buttonschema(papp),
      m_font1(allocer()),
      m_font2(allocer()),
      m_font3(allocer()),
      m_brushBk(allocer()),
      m_brushProgress3(allocer()),
      m_brushProgress2(allocer()),
      m_brushProgress1(allocer())
   {
      m_buttonschema.set_color(::user::color_background_disabled, ARGB(255, 126, 127, 128));
      m_buttonschema.set_color(::user::color_background_press,ARGB(255,200,127,200));
      m_buttonschema.set_color(::user::color_background_hover, ARGB(255,220,255,220));
      m_buttonschema.set_color(::user::color_background_normal,ARGB(255,120,220,255));
      m_buttonschema.m_bBorder = false;
      m_buttonschema.set_color(::user::color_text_disabled,ARGB(255,0,0,0));
      m_buttonschema.set_color(::user::color_text_press,ARGB(255,255,255,0));
      m_buttonschema.set_color(::user::color_text_hover,ARGB(255,100,180,110));
      m_buttonschema.set_color(::user::color_text_normal,ARGB(255,100,100,20));
      m_brushBk->create_solid(ARGB(255, 255, 250, 245));
      m_brushProgress1->create_solid(ARGB(255, 120, 180, 255));
      m_brushProgress2->create_solid(ARGB(255, 255, 240, 200));
      m_brushProgress3->create_solid(ARGB(255, 128, 128, 128));

      m_buttonschema.m_pfont.alloc(allocer());
      m_buttonschema.m_pfont->create_point_font("Geneva", 16);

      m_font1->create_point_font("Geneva", 16);

      m_font1->create_point_font("Geneva", 32, FW_BOLD);

      m_font1->create_point_font("Geneva", 20, FW_LIGHT, true);

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

   void view::install_message_handling(::message::dispatch * pinterface)
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
      IGUI_WIN_MSG_LINK(application::APPM_LANGUAGE, pinterface, this, &view::_001OnAppLanguage);

   }

#ifdef DEBUG
   void view::assert_valid() const
   {
      form_view::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      form_view::dump(dumpcontext);
   }
#endif //DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // ::user::impact message handlers

   // vmpLightView.cpp : implementation of the ::user::impact class
   //



   bool view::pre_create_window(::user::create_struct& cs)
   {
      cs.style &= ~WS_EX_CLIENTEDGE;
      return form_view::pre_create_window(cs);
   }
   /////////////////////////////////////////////////////////////////////////////
   // ::user::impact printing

   void view::_001OnInitialUpdate(signal_details * pobj)
   {
      form_view::_001OnInitialUpdate(pobj);
      load_links();

      //str += "</body></html>";

      //      string strFile = System.file().time_square();

      //    Application.file().put_contents(strFile, str);

      //  get_document()->open_document(strFile);


   }

   void view::on_update(sp(::user::impact) pSender, LPARAM lHint, object* phint)
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(phint);
      if(lHint == 123)
      {

      }
   }

   sp(::database::user::interaction) view::BackViewGetWnd()
   {
      return this;
   }
   void view::_001OnDestroy(signal_details * pobj)
   {
      form_view::_001OnDestroy(pobj);

   }




   void view::_001OnPaint(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }



   void view::_001OnCreate(signal_details * pobj)
   {

      if(pobj->previous())
         return;

      SetTimer(888888, 230, NULL);


      //FIBITMAP * pfi;

      //::draw2d::memory_graphics pdc(this);;

      m_dibBkImage.load_from_matter("casweden1.png");

      m_dibBk->create(1280, 1024);
      //::aura::savings & savings = Session.savings();
      //if(

      const char * pszSessionName = NULL;

#ifndef METROWIN

      pszSessionName = getenv("sessionname");

#endif

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
         *m_dibBkImage = *m_dibBk;
      }
      else
      {
         m_dibBk->Fill(0, 84, 84, 77);
      }

      SetTimer(21977, 1984 * 11, NULL);  // MAX. 12 fps

      check_apps();




      //pfi = System.visual().imaging().LoadImageFile(
      // System.dir().standard_square_matter());
      m_dibV.load_from_matter("wild_mountains_and_valleys-123.png");

      //pfi = System.visual().imaging().LoadImageFile(
      //System.dir().standard_square_matter());
      m_dib_veriwell.load_from_matter("veriwell_2008_green_h49.png");

      //pfi = System.visual().imaging().LoadImageFile(
      // System.dir().standard_square_matter());
      m_dib_winactionarea.load_from_matter("winactionarea.png");


      System.visual().imaging().color_blend(m_dibBk->get_graphics(), 0, 0, 1280, 1024, ARGB(255, 235, 245, 255), 31);

   }
   void view::_001OnContextMenu(signal_details * pobj)
   {
//      SCAST_PTR(::message::context_menu, pcontextmenu, pobj)
//         point point = pcontextmenu->GetPoint();

   }

   sp(::user::document) view::get_document()
   {
      return  (form_view::get_document());
   }



   void view::SetScreen(int32_t iScreen)
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
      RedrawWindow();
   }

   bool view::BaseOnControlEvent(::user::control_event * pevent)
   {
      if(pevent->m_eevent == ::user::event_button_clicked)
      {
         for(int32_t i = 0; i < m_linka.get_size(); i++)
         {
            if(pevent->m_puie->m_id == m_linka[i]->m_strBrief)
            {
               SetScreen(1);
               string strApp = m_linka[i]->m_strSrc;
               ::str::ends_eat_ci(strApp, ".dll");

               sp(::create_context) cc(Application.command_central());

               cc->m_spCommandLine->m_strApp   = strApp;
               cc->m_spCommandLine->m_varFile  = Platform.m_varTopicFile;

               Session.command()->request_create(cc);
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




   void view:: _001OnDraw(::draw2d::graphics * pdc)
   {
      form_view::_001OnDraw(pdc);
      //      sp(::user::document) pdoc = get_document();
      class imaging & imaging = System.visual().imaging();


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
      if(Session.savings().is_trying_to_save(::aura::resource_processing))
      {
         pdc->FillRect(rectClient, m_brushBk);
      }
      else
      {
         ::draw2d::dib_sp spdib(allocer());
         ::draw2d::dib_sp spdib2(allocer());
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
      if(&Session != NULL)
      {
         Platform.get_document()->get_bergedge_view()->GetWindowRect(rectThumb);
         if(rectThumb.area() > 0)
         {
            ::draw2d::dib_sp dib(allocer());
            dib->create(1920, 1080);
            keep < bool > keepOnDraw(&dynamic_cast < ::platform::frame * > (GetParentFrame())->m_bOnDraw, true, false, true);
            Platform.get_document()->get_bergedge_view()->_000OnDraw(dib->get_graphics());
            dib->get_graphics()->SetViewportOrg(0, 0);
            keepOnDraw.KeepAway();

            ::draw2d::dib_sp dibThumb(allocer());
            double dRate = 184.0 / rectThumb.width();
            dibThumb->create((int32_t) (dRate * rectThumb.width()), (int32_t) (dRate * rectThumb.height()));
            dibThumb->get_graphics()->SetStretchBltMode(HALFTONE);
            dibThumb->get_graphics()->StretchBlt(0, 0, dibThumb->m_size.cx, dibThumb->m_size.cy, dib->get_graphics(), rectThumb.left, rectThumb.top, rectThumb.width(), rectThumb.height(), SRCCOPY);

            imaging.bitmap_blend(pdc, point(10, 10), dibThumb->size(), dibThumb->get_graphics(), null_point(), (byte) (255.0 * 0.67));
         }
      }



      if(m_dProgress >= 0 && m_iScreen == 1)
      {
         RECT rectProgress;
         rectProgress = rectClient;
         rectProgress.left += 10;
         rectProgress.right -= 10;
         rectProgress.top += 200;
         rectProgress.bottom = rectProgress.top + 20;
         pdc->FillRect(rectProgress, m_brushProgress3);
         rectProgress.left++;
         rectProgress.right--;
         rectProgress.top++;
         rectProgress.bottom--;
         pdc->FillRect(rectProgress, m_brushProgress2);
         rectProgress.right = ((int32_t) ((rectProgress.right - rectProgress.left) * m_dProgress)) + rectProgress.left;
         pdc->FillRect(rectProgress, m_brushProgress1);
      }

      if(m_iScreen == 1)
      {
         ::draw2d::brush_sp brushText(allocer());
         brushText->create_solid(ARGB(255, 0, 108, 0));
         pdc->SelectObject(brushText);
         pdc->SelectObject(m_font2);
         pdc->TextOut(10, 110, m_strStatus1);
         brushText->create_solid(ARGB(255, 0, 0, 108));
         pdc->SelectObject(brushText);
         pdc->SelectObject(m_font3);
         pdc->TextOut(10, 170, m_strStatus2);
      }


      rect rectArea;

      GetAreaThumbRect(rectArea, m_iV);
      m_dibV->bitmap_blend(pdc, rectArea);
      if(m_iHitArea == m_iV)
      {
         imaging.color_blend(pdc, rectArea, ARGB(255, 140, 255, 110), 80);
      }

      GetAreaThumbRect(rectArea, m_i_veriwell);
      m_dib_veriwell->bitmap_blend(pdc, rectArea);
      if(m_iHitArea == m_i_veriwell)
      {
         imaging.color_blend(pdc, rectArea, ARGB(255, 140, 255, 110), 80);
      }

      GetAreaThumbRect(rectArea, m_i_winactionarea);
      m_dib_winactionarea->bitmap_blend(pdc, rectArea);
      if(m_iHitArea == m_i_winactionarea)
      {
         imaging.color_blend(pdc, rectArea, ARGB(255, 140, 255, 110), 80);
      }


   }

   void view::open_document_file(sp(::create_context) pcreatecontext)
   {
      try
      {
         Platform.userex()->open_document_file(pcreatecontext);
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
#if !defined(METROWIN) && !defined(LINUX) && !defined(APPLEOS)
      if(::IsWindow(m_oswindowWinactionarea) &&
         ::IsWindow(m_oswindowCommand) &&
         ::IsWindow(m_oswindowWinutil) &&
         ::IsWindow(m_oswindowBergedge))
      {
         return;
      }
      m_oswindowWinservice1       =  ::FindWindow(NULL, "::draw2d::fontopus::message_wnd::winservice_1");
      m_oswindowWinactionarea     =  ::FindWindow(NULL, "::draw2d::fontopus::message_wnd::winactionarea");
      m_oswindowCommand           =  ::FindWindow(NULL, "::draw2d::fontopus::message_wnd::command");
      m_oswindowWinutil           =  ::FindWindow(NULL, "::draw2d::fontopus::message_wnd::winutil");
      m_oswindowBergedge          =  ::FindWindow(NULL, "::draw2d::fontopus::message_wnd::bergedge");
#endif
   }


   index view::hit_test(point pt, e_element & eelement)
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


   UINT c_cdecl view::ThreadProcShowWindow(LPVOID lpparam)
   {
      show_window * pshow = (show_window *) lpparam;
      if(pshow != NULL)
         pshow->show();
      delete pshow;
      return 0;
   }

   void view::_001OnAppLanguage(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //      SCAST_PTR(::message::base, pbase, pobj);
      load_links();
   }

   void view::show_window::show()
   {
#ifdef WINDOWSEX
      if(m_iShow == -1)
      {
         ::SetForegroundWindow(m_oswindow);
         ::SetWindowPos(m_oswindow, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
      }
      else
      {
         if(m_iShow == SW_RESTORE)
         {
            ::SetForegroundWindow(m_oswindow);
         }
         ::ShowWindow(m_oswindow, m_iShow);
      }
#else
      throw todo(get_thread_app());
#endif
   }


   void view::mt_show_window(oswindow oswindow, int32_t iShow)
   {

      __begin_thread(get_app(), &view::ThreadProcShowWindow, new show_window(oswindow, iShow), ::multithreading::priority_highest);

   }


   view::show_window::show_window(oswindow oswindow, int32_t iShow)
   {
      m_oswindow   = oswindow;
      m_iShow  = iShow;
   }

   void view::_001OnTimer(signal_details * pobj)
   {

      SCAST_PTR(::message::timer, ptimer, pobj)

         if(ptimer->m_nIDEvent == 21977)
         {
            check_apps();
         }

   }

   void view::GetAreaThumbRect(LPRECT lprect, int32_t iArea)
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

   void view::_001OnLButtonUp(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj)
         pmouse->set_lresult(1);
      KillTimer(5432180);
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
      e_element eelement;
      index iHitArea = hit_test(pt, eelement);
      /*      if(m_bDragTask && !m_bShowCalendar && !m_bShutDown)
      {
      m_bDragTask = false;
      if(m_iDragTask >= m_iTaskOffset
      && m_iDragTask < m_iTaskOffset + m_areaa[m_iArea].m_taska.get_size()
      && iHitArea >= 0
      && iHitArea < m_areaa.get_size())
      {
      oswindow oswindow = m_areaa[m_iArea].m_taska[m_iDragTask - m_iTaskOffset].m_oswindow;
      rect rectArea;
      rect rectDesk0 = System.m_monitorinfoaDesk[0].rcMonitor;
      rect rectDesk1 = System.m_monitorinfoaDesk[1].rcMonitor;
      GetAreaThumbRect(rectArea, iHitArea);
      if(::IsWindowVisible)
      {
      ::ShowWindow(oswindow, SW_NORMAL);
      }
      if(pt.x < (rectArea.left + rectArea.width() / 3))
      {
      if(pt.y < (rectArea.top + rectArea.height() / 3))
      {
      ::SetWindowPos(oswindow, HWND_TOP, rectDesk0.left, rectDesk0.top, rectDesk0.width(), rectDesk0.height() / 2, 0);
      }
      else if(pt.y < (rectArea.top + rectArea.height() * 2 / 3))
      {
      ::SetWindowPos(oswindow, HWND_TOP, rectDesk0.left, rectDesk0.top, rectDesk0.width(), rectDesk0.height(), 0);
      }
      else
      {
      ::SetWindowPos(oswindow, HWND_TOP, rectDesk0.left, rectDesk0.top + rectDesk0.height() / 2, rectDesk0.width(), rectDesk0.height() / 2, 0);
      }
      }
      else if(pt.x < (rectArea.left + rectArea.width() * 2 / 3))
      {
      if(pt.y < (rectArea.top + rectArea.height() / 3))
      {
      ::SetWindowPos(oswindow, HWND_TOP, rectDesk0.left, rectDesk0.top, rectDesk1.right - rectDesk0.left, rectDesk0.height() / 2, 0);
      }
      else if(pt.y < (rectArea.top + rectArea.height() * 2 / 3))
      {
      ::SetWindowPos(oswindow, HWND_TOP, rectDesk0.left, rectDesk0.top, rectDesk1.right - rectDesk0.left, rectDesk0.height(), 0);
      }
      else
      {
      ::SetWindowPos(oswindow, HWND_TOP, rectDesk0.left, rectDesk0.top + rectDesk0.height() / 2, rectDesk1.right - rectDesk0.left, rectDesk0.height() / 2, 0);
      }
      }
      else
      {
      if(pt.y < (rectArea.top + rectArea.height() / 3))
      {
      ::SetWindowPos(oswindow, HWND_TOP, rectDesk1.left, rectDesk1.top, rectDesk1.width(), rectDesk1.height() / 2, 0);
      }
      else if(pt.y < (rectArea.top + rectArea.height() * 2 / 3))
      {
      ::SetWindowPos(oswindow, HWND_TOP, rectDesk1.left, rectDesk1.top, rectDesk1.width(), rectDesk1.height(), 0);
      }
      else
      {
      ::SetWindowPos(oswindow, HWND_TOP, rectDesk1.left, rectDesk1.top + rectDesk1.height() / 2, rectDesk1.width(), rectDesk1.height() / 2, 0);
      }
      }
      if(m_iArea != iHitArea)
      {
      m_areaa[m_iArea].m_taska.remove_at(m_iDragTask - m_iTaskOffset);
      ::count count1 = m_areaa[m_iArea].m_oswindowa.remove;
      ::count count2 = m_areaa[m_iArea].m_oswindowaHidden.remove;
      m_areaa[iHitArea].m_taska.add(area::task);
      if(count1 > 0)
      {
      m_areaa[iHitArea].m_oswindowa.add;
      }
      else
      {
      m_areaa[iHitArea].m_oswindowaHidden.add;
      }
      application & app = ::winactionarea::app_cast(get_app());
      app.m_oswindowaHidden.add;
      mt_show_window(oswindow, SW_HIDE);
      }
      return;
      }
      }*/
      if(iHitArea == m_iV)
      {
         check_apps();
         if(::IsWindow(m_oswindowWinutil))
         {
            mt_show_window(GetTopLevelFrame()->get_safe_handle(), SW_HIDE);
            ::PostMessageW(m_oswindowWinutil, WM_APP + 2000, 0, 2);
         }
      }
      else if(iHitArea == m_i_veriwell)
      {

#ifdef WINDOWSEX

         simple_shell_launcher launcher(NULL, NULL, System.dir().element("cast\\spaadmin.exe"), NULL, NULL, SW_SHOW);

         launcher.execute();

#else

         throw todo(get_app());

#endif


      }
      else if(iHitArea == m_i_winactionarea)
      {
         check_apps();
#ifdef WINDOWSEX
         if(::IsWindow(m_oswindowWinactionarea))
         {
            mt_show_window(GetTopLevelFrame()->get_safe_handle(), SW_HIDE);
            ::PostMessage(m_oswindowWinactionarea, WM_APP + 2000, 0, 2);
         }
#else
         throw todo(get_app());
#endif
      }
      /*      else if(iHitArea == m_iShutDown)
      {
      m_bShutDown = !m_bShutDown;
      RedrawWindow();
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
      if(m_oswindowaDesk.get_size() > 0)
      ::PostMessage(m_oswindowaDesk[0], WM_APP + 2000, 3, 6);
      ::PostMessage(m_oswindowWinactionarea, WM_APP + 2000, 3, 6);
      ::PostMessage(m_oswindowCommand, WM_APP + 2000, 3, 6);
      ::PostMessage(m_oswindowWinutil, WM_APP + 2000, 3, 6);
      ::PostMessage(m_oswindowWinservice1, WM_APP + 2000, 3, 6);


      simple_shell_launcher launcher(
      NULL,
      NULL,
      System.dir().element("spaadmin.exe"),
      " uninstall _set_windesk",
      System.dir().element(""),
      SW_HIDE);
      launcher.execute();


      return;
      // spa boot should cling (app.install.exe should catch
      // exit could and restart main application)
      }
      }
      else if(m_bShowCalendar)
      {
      switch(m_calendar.hit_test(pt))
      {
      case calendar::ElementPreviousMonth:
      m_calendar.previous_month();
      RedrawWindow();
      break;
      case calendar::ElementNextMonth:
      m_calendar.next_month();
      RedrawWindow();
      break;
      case calendar::ElementNextYear:
      m_calendar.next_year();
      RedrawWindow();
      break;
      case calendar::ElementPreviousYear:
      m_calendar.previous_year();
      RedrawWindow();
      break;
      default:
      {
      ::datetime::time time;
      if(m_calendar.time_hit_test(time, pt))
      {
      m_calendar.set_time(time);
      RedrawWindow();
      }
      }
      break;
      }
      }
      else if(iHitArea >= 0)
      {
      {
            else if(iHitArea == m_iNotificationAreaButtonOffset)
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
      m_dw3003Time = ::get_tick_count();
      SetTimer(3003, 300, NULL);

      }
      else if(iHitArea >= m_iTaskOffset && iHitArea < (m_iTaskOffset + m_areaa[m_iArea].m_taska.get_size()))
      {
      m_iCurrentTask = iHitArea;
      m_dwCurrentTaskChangeTime = ::get_tick_count();
      oswindow oswindow = m_areaa[m_iArea].m_taska[iHitArea - m_iTaskOffset].m_oswindow;
      if(::IsIconic)
      {
      mt_show_window(oswindow, SW_RESTORE);
      }
      else
      {
      if(oswindow != m_areaa[m_iArea].m_taska[0].m_oswindow)
      {
      mt_show_window(oswindow, -1);

      }
      else
      {
      mt_show_window(oswindow, SW_MINIMIZE);
      }
      }
      Sleep(184 + 177);
      UpdateCurrentArea();
      }
      }
      }
      */
   }

   void view::_001OnMouseMove(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj)
         pmouse->set_lresult(1);
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
      e_element eelement;
      index iHitArea = hit_test(pt, eelement);
      if(m_iHitArea < 0 && iHitArea >=0)
         track_mouse_hover();
      m_iHitArea =  iHitArea;

   }

   void view::load_links()
   {
      for(int32_t i = 0; i < m_linka.get_size(); i++)
      {
         m_linka[i]->m_button.DestroyWindow();
      }
      m_linka.remove_all();


      string str = Application.file().as_string(Application.dir().matter("platform\\main_link.xml"));

      xml::document doc(get_app());

      doc.load(str);
      //str = "<html><head></head><body>";

      for(int32_t i = 0; i < doc.get_root()->children().get_size(); i++)
      {
         if(doc.get_root()->child_at(i)->get_name() == "link")
         {
            link * plink = new link(get_app());
            m_linka.add(plink);

            plink->m_iId               = i;

            plink->m_strBrief          = doc.get_root()->child_at(i)->attr("brief");
            plink->m_strName           = doc.get_root()->child_at(i)->attr("name");
            plink->m_strDescription    = doc.get_root()->child_at(i)->attr("description");
            plink->m_strSrc            = doc.get_root()->child_at(i)->attr("src");

            plink->m_button.create_window(null_rect(), this, plink->m_strBrief);

            m_buttonschema.m_etranslucency = ::user::TranslucencyPresent;
            plink->m_button.m_pschema        = &m_buttonschema;

            plink->m_button._001SetButtonText(plink->m_strName);

            string strAttr             = doc.get_root()->child_at(i)->attr("icon");

            if(::str::begins_eat(strAttr, "matter://"))
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
      int32_t h = 20;
      int32_t y = 400;
      for(int32_t i = 0; i < m_linka.get_count(); i++)
      {
         m_linka[i]->m_button.SetWindowPos(ZORDER_TOP, 11, y, 300, h, SWP_SHOWWINDOW);
         y+=h;
      }
   }


} // namespace platform



