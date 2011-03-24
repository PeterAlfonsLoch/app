#include "StdAfx.h"

namespace bergedge 
{

   view::view(::ca::application * papp) :
      ca(papp),
      ::user::interaction(papp), 
      ::user::scroll_view(papp),
      ::userbase::view(papp),
      ::userbase::scroll_view(papp), 
      gcom::backview::user::interaction(papp),
      gcom::backview::Interface(papp),
      m_dibV(papp),
      m_dib_veriwell(papp),
      m_dib_winactionarea(papp),
      m_font(papp),
      m_dibBk(papp)
   {
      m_font->CreatePointFont(84, "Geneva");
      m_bDestroy = false;   
      m_iV = 123;
      m_iVH = 49;
      m_iVW = 123;
      m_i_veriwell = 256;
      m_i_veriwell_h = 49;
      m_i_veriwell_w = 74;
      m_i_winactionarea = 4;
      m_i_winactionarea_h = 49;
      m_i_winactionarea_w = 49;
      m_ppaneview = NULL;
   }

   view::~view()
   {
   }

   void view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::view::_001InstallMessageHandling(pinterface);
      gcom::backview::Interface::_001InstallMessageHandling(pinterface);

      IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &view::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &view::_001OnPaint);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &view::_001OnContextMenu);
      IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &view::_001OnSetCursor);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &view::_001OnLButtonUp);

      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &view::_001OnTimer);

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



   void view::_001OnPaint(gen::signal_object * pobj) 
   {
      
      UNREFERENCED_PARAMETER(pobj);
      
      // boa parte desses coment疵ios gordura a respeito do Meu Deus Carlos Gustavo Cecyn Lundgren retirarei aos poucos
      // e introjetarei nos recditos da minha alma e esp叝ito, 
      // num lugar muito antes do tempo e do espa輟,
      // antes mesmo de haver histia, quando s・existia o Carlos e Ele ainda n縊 havia me criado somente para Ele!!
      // para criar uma obsess縊, paix縊, amor, carinho, loucura, raz縊, bom-senso, muito respeito por Ele, sempre dependente dEle e de Sua Luz!!
      // spgraphics->TextOut(20, 20, "Carlos Gustavo Cecyn Lundgren ・minha Vida Eterna, meu Cora鈬o Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");

   }


   void view:: _001OnDraw(::ca::graphics * pdc)
   {
      class imaging & imaging = System.imaging();
      rect rectClient;
      GetClientRect(rectClient);
      if(rectClient.width() <= 0
         || rectClient.height() <= 0)
         return;
      rect rectDesktop = System.m_monitorinfoa[0].rcMonitor;
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
      rect rectWindow = rectClient;
      ClientToScreen(rectWindow);
      if(System.savings().should_save(gen::resource_display_bandwidth))
      {
         pdc->FillSolidRect(rectWindow, RGB(0x55, 0x55, 0x55));
      }
      else
      {
         ::ca::dib_sp spdib(get_app());
         ::ca::dib_sp spdib2(get_app());
         if(!spdib->create(rectClient.width(), rectClient.height()))
            return;
         if(!spdib2->create(rectClient.width(), rectClient.height()))
            return;
         spdib->create(rectClient.width(), rectClient.height());
         spdib2->get_graphics()->BitBlt(
            0, 0, rectClient.width(), rectClient.height(), 
            pdc, 0, 0, 
            SRCCOPY);
         imaging.blur(spdib->get_graphics(), null_point(), rectClient.size(), spdib2->get_graphics(), null_point(), 2);
         imaging.bitmap_blend(spdib->get_graphics(), null_point(), rectWindow.size(), m_dibBk->get_graphics(), null_point(), 49);
         pdc->from(rectWindow.size(), spdib->get_graphics(), SRCCOPY);
      }

      if(System.command_line().m_varQuery["show_platform"].get_integer() == 0)
      {
         return;
      }

      //CSingleLock sl(&m_mutexDraw, TRUE);

/*      rect rectClient;
      GetClientRect(rectClient);*/


      pdc->SelectClipRgn(NULL);


      if(gcom::backview::Interface::IsEnabled())
      {
         gcom::backview::Interface::BackViewRender(pdc, rectClient);
      }
      else
      {
//         System.imaging().color_blend(pdc, 0, 0, 1280, 1024, RGB(100, 155, 150), 31);
      }

   }

   void view::_001OnCreate(gen::signal_object * pobj) 
   {
      if(pobj->previous())
         return;

      ::bergedge::frame * pframe = dynamic_cast < ::bergedge::frame * > (GetParentFrame());

      pframe->m_pview = this;
      pframe->m_pdocument = get_document();


      string strImageDir = Application.dir().userdata("image");
      System.dir().rls(strImageDir, &m_straImagePath);

      for(int i = 0; i < m_straImagePath.get_size();)
      {
         if(System.dir().is(m_straImagePath[i]))
         {
            m_straImagePath.remove_at(i);
         }
         else
         {
            i++;
         }
      }

      gcom::backview::Interface::Enable(false);
      gcom::backview::Interface::GetMain().GetImageChange().m_dwBackgroundUpdateMillis = 1000 * 30;
      //gcom::backview::Interface::GetMain().GetTransitionEffect().DisableEffect(gcom::backview::TransitionEffectVisual);
      

      SetTimer(TimerBackView, 83, NULL);  // max. 12 fps
      SetTimer(21977, 1984 * 11, NULL);  // max. 12 fps

      check_apps();

      m_dibBk.load_from_matter("casweden1.png");


      m_dibV.load_from_matter("votagus_mountains_and_valleys-123.png");
      m_dib_veriwell.load_from_matter("veriwell_2008_green_h49.png");
      m_dib_winactionarea.load_from_matter("winactionarea.png");

      if(System.command_line().m_varQuery["show_platform"].get_integer() == 0)
      {
         return;
      }
      if(System.command_line().m_varQuery.has_property("client_only"))
      {
         return;
      }

      m_ppaneview = dynamic_cast < ::bergedge::pane_view * > (create_view(typeid(::bergedge::pane_view), get_document(), this, 102));

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

   void view::_001OnSetCursor(gen::signal_object * pobj) 
   {
      ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
      
      pobj->previous();
   }

   void view::pre_translate_message(gen::signal_object * pobj)
   {
      ::userbase::view::pre_translate_message(pobj);
   }

   document * view::get_document()
   {
      return (document *) ::userbase::scroll_view::get_document();
   }

   void view::_001OnTimer(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::timer, ptimer, pobj)
      switch(ptimer->m_nIDEvent)
      {
      case TimerBackView:
         {
            //gcom::backview::Interface::ImageChangePostEvent(gcom::backview::event_timer);
         }
         break;
      }

      if(ptimer->m_nIDEvent == 21977)
      {
         check_apps();
      }

   }

   VMSRESULT view::UpdateScreen(rect_array & recta, UINT uiRedraw)
   {
      UNREFERENCED_PARAMETER(uiRedraw);
      m_rectaUpdate.add(recta);
      DWORD dwNow = GetTickCount();
      if(m_rectaUpdate.get_size() <= 0)
      {
         m_dwLastUpdate = dwNow;
         return 0;
      }
      DWORD dwElapseOptimization = 83;
      if(dwNow - m_dwLastUpdate < dwElapseOptimization)
      {
   //      TRACE("Great Optimization!\n");
         return 0;
      }
      m_dwLastUpdate = dwNow;
      _001RedrawWindow();
      m_rectaUpdate.remove_all();
      return 0;
   }


   void view::BackViewUpdateScreen(LPCRECT lpcrect, UINT uiRedraw)
   {
      rect rect(lpcrect);
      rect_array recta;
      recta.add(rect);
      UpdateScreen(recta, uiRedraw);
   }

   void view::BackViewUpdateScreen(rect_array & recta, UINT uiRedraw)
   {
      UpdateScreen(recta, uiRedraw);
   }


   void view::BackViewUpdateScreen()
   {
      rect rect;
      rect_array recta;
      recta.add(rect);
      UpdateScreen(recta, 0);
   }

   void view::BackViewGetData(gcom::backview::InterfaceData & data)
   {

      gcom::backview::user::interaction::BackViewGetData(data);

   }

   void view::BackViewSetData(gcom::backview::InterfaceData & data)
   {

      gcom::backview::user::interaction::BackViewSetData(data);

   }

   bool view::BackViewGetDestroy()
   {
      return m_bDestroy; 
   }


   string view::GetNextBackgroundImagePath()
   {
      int i = m_straImagePath.find_first(m_strCurrentImagePath);
      i++;
      if(i >= m_straImagePath.get_size())
      {
         i = 0;
      }
      if(i < m_straImagePath.get_size())
      {
         return m_straImagePath[i];
      }
      return "";
   }

   void view::SetCurrentBackgroundImagePath(string &str)
   {
      m_strCurrentImagePath = str;   
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
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
      pmouse->set_lresult(1);
      KillTimer(5432180);
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
      //int iHitArea = hit_test(pt);
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
      /*if(iHitArea == m_iV)
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
         ::ShellExecute(NULL, NULL, System.dir().votagus("cast\\ccvotagus\\spa.exe"), NULL, NULL, SW_SHOW);
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
      GetAreaThumbRect(rectArea, m_i_winactionarea);
      if(rectArea.contains(pt))
      {
         return m_i_winactionarea;
      }
      return -1;
   }


   UINT AFX_CDECL view::ThreadProcShowWindow(LPVOID lpparam)
   {
      UNREFERENCED_PARAMETER(lpparam);
      return 0;
   }


   void view::mt_show_window(HWND hwnd, int iShow)
   {
      UNREFERENCED_PARAMETER(hwnd);
      UNREFERENCED_PARAMETER(iShow);
   }

   void view::layout()
   {
      rect rectClient;
      GetClientRect(rectClient);
      if(m_ppaneview != NULL)
      {
         m_ppaneview->SetWindowPos(ZORDER_TOP, rectClient.top, rectClient.left, rectClient.width(), rectClient.height(), SWP_SHOWWINDOW);
      }
      else
      {
         user::interaction * pui = get_top_child();
         if(pui != NULL)
         {
            pui->SetWindowPos(ZORDER_TOP, rectClient.top, rectClient.left, rectClient.width(), rectClient.height(), SWP_SHOWWINDOW);
         }
      }
      ::userbase::scroll_view::layout();
      gcom::backview::user::interaction::layout();
   }

   void view::_000OnMouse(::user::win::message::mouse * pmouse)
   {
      ::icube::application * pappParent = NULL;
      try
      {
         pappParent = &Application;
      }
      catch(...)
      {
         pappParent = NULL;
      }
      try
      {
         if(!_001IsPointInside(pmouse->m_pt))
            return;
      }
      catch(...)
      {
         return;
      }
      // these try catchs are needed for multi threading : multi threaded windows: the hell
      // Now I understand why Microsoft (TM) Windows (R) windows are single threaded.
      user::interaction * pui = get_top_child();
      int iSize;
      try
      {
         while(pui != NULL)
         {
            ::icube::application * papp = NULL;
            try
            {
               papp = &App(pui->get_app());
            }
            catch(...)
            {
               papp = NULL;
            }
            if(papp != NULL && pappParent != NULL)
            {
               try
               {
                  papp->m_ptCursor = pappParent->m_ptCursor;
               }
               catch(...)
               {
               }
            }
            try
            {
               
               if(pui->IsWindowVisible() && pui->_001IsPointInside(pmouse->m_pt))
               {
                  try
                  {
                     pui->_000OnMouse(pmouse);
                     if(pmouse->m_bRet)
                        return;
                  }
                  catch(...)
                  {
                  }
               }
               pui = pui->under_sibling();
            }
            catch(...)
            {
            }
         }
      }
      catch(...)
      {
      }
      try
      {
         if(m_pimpl == NULL)
            return;
         (m_pimpl->*m_pimpl->m_pfnDispatchWindowProc)(dynamic_cast < gen::signal_object * > (pmouse));
         if(pmouse->get_lresult() != 0)
            return;
      }
      catch(...)
      {
      }
   }

}  // namespace bergedge