#include "StdAfx.h"

#undef USERNAME_LENGTH // from mysql

#include <wtsapi32.h>

#define USER_HOUR_TIMER_MILLIS (10000)

namespace whiteboard
{

   

   view::view(::ca::application * papp) :
      ca(papp),
      ::user::tab(papp),
      ::userbase::view(papp),
      ::userbase::tab_view(papp),
      ::userex::pane_tab_view(papp),
      place_holder_container(papp)
   {
      m_bSessionLocked = false;
      m_strOptionsTitle = "Options - Whiteboard Desktop System";
      m_pview = NULL;
      m_iTimerIconFlash = 500;
      m_bHover = false;
      m_phtmlview = NULL;
      m_phtmlviewMrts = NULL;
      m_phtmlviewMrtsQuerylist = NULL;
      m_poptionsview = NULL;
      m_iShowCalendarTrayIcon = -1;
      m_iWTSRegisterSessionNotificationRetry = 0;
      m_bWTSRegisterSessionNotification = false;


      connect_update_cmd_ui("view_whiteboard", &view::_001OnUpdateViewWhiteboard);
      connect_command("view_whiteboard", &view::_001OnViewWhiteboard);
   }

   view::~view()
   {
   }

    // BEGIN_MESSAGE_MAP(::view, ::userbase::view)
   /*   ON_COMMAND(ID_VIEW_WHITEBOARD, OnViewWhiteboard)
      ON_COMMAND(ID_VIEW_BROWSER, OnViewBrowser)
      ON_WM_CREATE()
      ON_MESSAGE(WM_APP_NOTIFYICON, OnNotifyIcon)
      ON_MESSAGE(WM_APP_CALENDARICON, OnCalendarIcon)
      ON_WM_DESTROY()
      ON_WM_TIMER()
      ON_WM_SIZE()
      ON_WM_ERASEBKGND()
      ON_MESSAGE(WM_WTSSESSION_CHANGE, OnWtsSessionChange)
      ON_COMMAND(ID_WB, OnWb)
      ON_COMMAND(ID_VIEW_MRTS, OnViewMrts)
      ON_UPDATE_COMMAND_UI(ID_VIEW_MRTS, OnUpdateViewMrts)
      ON_UPDATE_COMMAND_UI(ID_VIEW_MRTS_QUERYLIST, OnUpdateViewMrtsQuerylist)
      ON_COMMAND(ID_VIEW_MRTS_QUERYLIST, OnViewMrtsQuerylist)*/
    // END_MESSAGE_MAP()


   // ::view drawing

   void view::OnDraw(::ca::graphics * pgraphics)
   {
      UNREFERENCED_PARAMETER(pgraphics);
      //document * pDoc = get_document();
      // TODO: add draw code here
   }


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

   document* view::get_document() // non-debug version is inline
   {
      ASSERT(base < document > ::bases(::view::get_document()));
      return dynamic_cast < document * > (::view::get_document());
   }




   // ::view message handlers

   whiteboard::http_thread & view::GetConnectionThread(void)
   {
      whiteboard::application * papp = dynamic_cast < whiteboard::application * > (get_app());
      return papp->GetConnectionThread();
   }


   void view::URLOpenNew(const char * lpcsz, bool bMakeVisible)
   {
      if(m_phtmlview == NULL)
      {
         m_phtmlview = dynamic_cast < html_view * > (ensure(ViewHtml)->m_pwnd);
      }

      if(m_phtmlview != NULL)
      {
         m_phtmlview->WBNavigate(lpcsz);
         if(bMakeVisible)
         {
            set_cur_tab_by_id(ViewHtml);
         }
      }
      


   }

   void view::MrtsUrlOpenNew(const char * lpcsz, bool bMakeVisible)
   {
      if(m_phtmlviewMrts == NULL)
      {
         m_phtmlviewMrts = dynamic_cast < html_view * > (ensure(ViewMrtsHtml)->m_pwnd);
         if(m_phtmlviewMrts != NULL)
         {
            m_phtmlviewMrts->m_bSetTargetFrameName = true;
            m_phtmlviewMrts->m_strTargetFrameName = "WhiteboardSpecialFrameFor:MRTS";
         }
      }

      if(m_phtmlviewMrts != NULL)
      {
         m_phtmlviewMrts->WBNavigate(lpcsz);
         if(bMakeVisible)
         {
            set_cur_tab_by_id(ViewMrtsHtml);
         }
      }
   }

   void view::MrtsQuerylistUrlOpenNew(const char * lpcsz, bool bMakeVisible)
   {
      if(m_phtmlviewMrtsQuerylist == NULL)
      {
         m_phtmlviewMrtsQuerylist = dynamic_cast < html_view * > (ensure(ViewMrtsQuerylistHtml)->m_pwnd);
         if(m_phtmlviewMrtsQuerylist != NULL)
         {
            m_phtmlviewMrtsQuerylist->m_bSetTargetFrameName = true;
            m_phtmlviewMrtsQuerylist->m_strTargetFrameName = "WhiteboardSpecialFrameFor:MRTSQueryList";
         }

      }

      if(m_phtmlviewMrtsQuerylist != NULL)
      {
         m_phtmlviewMrtsQuerylist->WBNavigate(lpcsz);
         if(bMakeVisible)
         {
            set_cur_tab_by_id(ViewMrtsQuerylistHtml);
         }
      }
   }

   void view::ViewWhiteboard(bool bMakeVisible)
   {
      MarkAsNotified();

      string strHomeURL;
   //   if(m_strPreviousHome.is_empty() || get_document()->m_bRead)
      {
         whiteboard::time timeMin;
      
         Application.GetProfileTime(timeMin, whiteboard::TimeLastView);
      
         GetConnectionThread().PostThreadMessage(http_thread::MessageTimer, http_thread::TimerDeferNotify, 0);
      
         UpdateNotifyIcon("notify");

         whiteboard::application * papp = dynamic_cast < whiteboard::application * > (&Application);
         papp->GetSiteUrl(SiteHomeUrl, strHomeURL);
      
   //      m_editWbHomeUrl.GetWindowText(strHomeURL);
      
      
         string strOp;

         get_document()->GetUserOp(strOp);
      
         string strEx;
         timeMin.ToString(strEx);
         strHomeURL += "?p_lastview=" + strEx + "&op=" + strOp;
      
         m_strPreviousHome = strHomeURL;
      }
      //else
      {
        // strHomeURL = m_strPreviousHome;
      }
      URLOpenNew(strHomeURL, bMakeVisible);
   }


   void view::MarkAsNotified()
   {
      whiteboard::time timeMax;
      Application.GetProfileTime(timeMax, TimeLastChange);
      Application.SetProfileTime(timeMax, TimeLastView);
      GetConnectionThread().PostThreadMessage(http_thread::MessageTimer, http_thread::TimerDeferNotify, 0);
   }




   void view::UpdateNotifyIcon(const char * pszMatter)
   {
      HICON hicon = GetIcon(pszMatter);
      m_nid.hIcon = hicon;
      m_nid.uFlags = NIF_ICON;
      Shell_NotifyIcon(NIM_MODIFY, &m_nid);

   }

   void view::OnInitialUpdate()
   {
      ::userbase::view::_001OnInitialUpdate(NULL);
      GetParentFrame()->layout();

      ViewWhiteboard(false);
      
      UpdateCalendarTrayIcon();
      UpdateMrtsTrayIcon();

      UserHour_PulseEvent(user_hour::event_logon_time);

   }

   void view::_001OnViewWhiteboard(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      ViewWhiteboard(true);
   }

   void view::_001OnUpdateViewWhiteboard(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->Enable();
   }

/*   void view::ShowView(EView eview)
   {
      m_eview = eview;
      if(m_poptionsview != NULL && m_eview != ViewOptions)
      {
         m_poptionsview->ShowWindow(SW_HIDE);
      }
      if(m_phtmlviewMrts != NULL && m_eview != ViewMrtsHtml)
      {
         m_phtmlviewMrts->ShowWindow(SW_HIDE);
      }
      if(m_phtmlviewMrtsQuerylist != NULL && m_eview != ViewMrtsQuerylistHtml)
      {
         m_phtmlviewMrtsQuerylist->ShowWindow(SW_HIDE);
      }
      if(m_phtmlview != NULL && m_eview != ViewHtml)
      {
         m_phtmlview->ShowWindow(SW_HIDE);
      }
      switch(eview)
      {
      case ViewHtml:
         {
            if(m_phtmlview == NULL)
            {
               m_phtmlview = dynamic_cast < html_view * > (CreateView(eview));
            }
            ShowView(m_phtmlview);

            if(base < whiteboard::main_frame > :: bases (GetParentFrame()))
            {
               whiteboard::main_frame * pmainframe = dynamic_cast < whiteboard::main_frame * > (GetParentFrame());
               pmainframe->m_toolbarOptions.ShowWindow(SW_HIDE);
               pmainframe->m_toolbarHtml.ShowWindow(SW_SHOW);
               pmainframe->layout();
               pmainframe->ShowWindow(SW_SHOW);
               pmainframe->InitialFramePosition();
            }
            UpdateFrameTitle();
            GetParentFrame()->SetWindowText(m_strHtmlTitle);
            
         }
         break;
      case ViewMrtsHtml:
         {
            if(m_phtmlviewMrts == NULL)
            {
               m_phtmlviewMrts = dynamic_cast < html_view * > (CreateView(eview));
            }
            ShowView(m_phtmlviewMrts);

            if(base < whiteboard::main_frame > :: bases(GetParentFrame()))
            {
               whiteboard::main_frame * pmainframe = dynamic_cast < whiteboard::main_frame * > (GetParentFrame());
               pmainframe->m_toolbarOptions.ShowWindow(SW_HIDE);
               pmainframe->m_toolbarHtml.ShowWindow(SW_SHOW);
               pmainframe->layout();
            }
            UpdateFrameTitle();
            GetParentFrame()->SetWindowText(m_strHtmlTitle);
         }
         break;
      case ViewMrtsQuerylistHtml:
         {
            if(m_phtmlviewMrtsQuerylist == NULL)
            {
               m_phtmlviewMrtsQuerylist = dynamic_cast < html_view * > (CreateView(eview));
            }
            ShowView(m_phtmlviewMrtsQuerylist);

            if(base < whiteboard::main_frame > ::bases(GetParentFrame()))
            {
               whiteboard::main_frame * pmainframe = dynamic_cast < whiteboard::main_frame * > (GetParentFrame());
               pmainframe->m_toolbarOptions.ShowWindow(SW_HIDE);
               pmainframe->m_toolbarHtml.ShowWindow(SW_SHOW);
               pmainframe->layout();
            }
            UpdateFrameTitle();
            GetParentFrame()->SetWindowText(m_strHtmlTitle);
         }
         break;
      case ViewOptions:
         {
            if(m_phtmlview != NULL)
            {
               m_phtmlview->ShowWindow(SW_HIDE);
            }
            if(m_poptionsview == NULL)
            {
               m_poptionsview = dynamic_cast < options_view * > (CreateView(eview));
            }
            ShowView(m_poptionsview);
            if(base < whiteboard::main_frame > :: bases(GetParentFrame()))
            {
               whiteboard::main_frame * pmainframe = dynamic_cast < whiteboard::main_frame * > (GetParentFrame());
               pmainframe->m_toolbarHtml.ShowWindow(SW_HIDE);
               pmainframe->m_toolbarOptions.ShowWindow(SW_SHOW);
               pmainframe->layout();
            }
            GetParentFrame()->SetWindowText(m_strOptionsTitle);
         }
         break;
      }
      m_phtmlview->GetParentFrame()->ActivateFrame(SW_SHOW);
      m_phtmlview->GetParentFrame()->SetForegroundWindow();
      m_phtmlview->GetParentFrame()->BringWindowToTop();

      whiteboard::main_frame * pframe = dynamic_cast < whiteboard::main_frame * > (GetTopLevelFrame());
      if(base < whiteboard::main_frame > :: bases(pframe))
      {
         if(m_eview == ViewMrtsHtml
         || m_eview == ViewMrtsQuerylistHtml)
         {
            pframe->SetMrtsStyle();
         }
         else
         {
            pframe->SetNormalStyle();
         }
      }
      

   }
   */

/*   void view::ShowView(::userbase::view * pview)
   {
      ASSERT(pview != NULL);
      if(pview == NULL)
         return;
      m_pview = pview;
      //m_pwnd = pview;

      LayoutChild();
      ::user::interaction* pwnd = GetParentFrame();
      userbase::frame_window * pframe = dynamic_cast <userbase::frame_window * >(pwnd);
      pframe->SetActiveView(pview);
   }
*/

   void view::on_create_view(::user::view_creator_data * pcreatordata)
   {
      ::user::interaction * pwnd = NULL;
      switch(pcreatordata->m_id)
      {
      case ViewHtml:
      case ViewMrtsHtml:
      case ViewMrtsQuerylistHtml:
      case ViewUserHour:
         pwnd = ::view::create_view(::ca::get_type_info < html_view > (), get_document(), this, pcreatordata->m_id);
         break;
      case ViewOptions:
         pwnd = ::view::create_view(::ca::get_type_info < options_view > (), get_document(), this, pcreatordata->m_id);
         break;
      }
      if(pwnd == NULL)
         return;

      ::view * pview = dynamic_cast < ::view * > (pwnd);
      ASSERT_KINDOF(::view, pview);

      pview->_001OnInitialUpdate(NULL);

      pcreatordata->m_pwnd = pwnd;
      pcreatordata->m_pdoc = get_document();

   }

   void view::_001OnCreate(gen::signal_object * pobj)
   {
//      SCAST_PTR(::user::win::message::create, pcreate, pobj);
      
      pobj->previous();
      if(pobj->m_bRet)
         return;

      SetTimer(TimerWTSRegisterSessionNotification, 1000, NULL);

      GetConnectionThread().m_pview = this;
      
      memset(&m_nid, 0, sizeof(m_nid));
      m_nid.cbSize = sizeof(m_nid);
      m_nid.uID = 0;
      m_nid.hWnd = GetTopLevelParent()->_get_handle();
      m_nid.uFlags =  NIF_MESSAGE;
      m_nid.uCallbackMessage = WM_APP_NOTIFYICON;

      memset(&m_nidCalendar, 0, sizeof(m_nidCalendar));
      m_nidCalendar.uID = 1;
      m_nidCalendar.cbSize = sizeof(m_nidCalendar);
      m_nidCalendar.hWnd = GetTopLevelParent()->_get_handle();
      m_nidCalendar.uFlags =  NIF_MESSAGE;
      m_nidCalendar.uCallbackMessage = WM_APP_NOTIFYICON;

      memset(&m_nidMrts, 0, sizeof(m_nidMrts));
      m_nidMrts.uID = 2;
      m_nidMrts.cbSize = sizeof(m_nidMrts);
      m_nidMrts.hWnd = GetTopLevelParent()->_get_handle();
      m_nidMrts.uFlags =  NIF_MESSAGE;
      m_nidMrts.uCallbackMessage = WM_APP_NOTIFYICON;


      memset(&m_nidMrtsQuerylist, 0, sizeof(m_nidMrtsQuerylist));
      m_nidMrtsQuerylist.uID = 3;
      m_nidMrtsQuerylist.cbSize = sizeof(m_nidMrtsQuerylist);
      m_nidMrtsQuerylist.hWnd = GetTopLevelParent()->_get_handle();
      m_nidMrtsQuerylist.uFlags =  NIF_MESSAGE;
      m_nidMrtsQuerylist.uCallbackMessage = WM_APP_NOTIFYICON;

      Shell_NotifyIcon(NIM_ADD, &m_nid);

      UpdateNotifyIcon("notify");

      SetTimer(TimerIconFlash, m_iTimerIconFlash, NULL);

      OnTimerNotify();

      ModifyStyleEx(WS_BORDER, 0, SWP_FRAMECHANGED);   
      ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);   

      whiteboard::main_frame * pframe = dynamic_cast < whiteboard::main_frame * > (GetParentFrame());
      pframe->m_pview = this;
      IGUI_WIN_MSG_LINK(WM_WTSSESSION_CHANGE, pframe->m_pimpl, this, &view::_001OnWtsSessionChange);
      IGUI_WIN_MSG_LINK(WM_APP_NOTIFYICON, pframe->m_pimpl, this, &view::_001OnNotifyIcon);


      OnTimerUserHour();
      SetTimer(TimerUserHour, USER_HOUR_TIMER_MILLIS, NULL);

   }


   void view::_001OnNotifyIcon(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj);
      if(pbase->m_wparam == 0)
      {
         if(pbase->m_lparam == WM_RBUTTONUP)
         {
            NotifyIconPopup();
         }
         else if(pbase->m_lparam == WM_LBUTTONUP)
         {
            ViewWhiteboard(true);
            
         }
         else if(pbase->m_lparam == WM_MOUSEMOVE)
         {
            if(!m_bHover)
            {
               m_bHover = true;
               SetTimer(TimerHoverOut, 1000, NULL);
               UpdateNotifyIcon("notify_hover");
            }
         }
      }
      else if(pbase->m_wparam == 1)
      {
         OnCalendarIcon(pbase->m_wparam, pbase->m_lparam);
      }
      else if(pbase->m_wparam == 2 || pbase->m_wparam == 3)
      {
         OnMrtsIcon(pbase->m_wparam, pbase->m_lparam);
      }
      pobj->m_bRet = true;
   }

   LRESULT view::OnCalendarIcon(WPARAM wparam, LPARAM lparam)
   {
      UNREFERENCED_PARAMETER(wparam);
      if(lparam == WM_LBUTTONUP)
      {
         document * pdoc = (document *) get_document();
         pdoc->update_all_views(NULL, document::HintShowCalendar, NULL);
      }
      return 0;
   }

   LRESULT view::OnMrtsIcon(WPARAM wparam, LPARAM lparam)
   {
      if(lparam == WM_LBUTTONUP)
      {
         document * pdoc = (document *) get_document();
         if(wparam == 2)
         {
            pdoc->update_all_views(NULL, document::HintShowMrts, NULL);
         }
         else
         {
            pdoc->update_all_views(NULL, document::HintShowMrtsQuerylist, NULL);
         }
      }
      return 0;
   }

   void view::NotifyIconPopup()
   {
      //
      //::userbase::menu menu;

      ::userbase::menu menu(get_app());
      menu.LoadXmlMenu("whiteboard\\menu_notify.xml");

      //menu.LoadMenu(IDR_MENU_NOTIFY);

      //::userbase::menu * ppopup = menu.GetSubMenu(0);
      ::userbase::menu menuPopup(get_app(), menu.GetSubMenu(0));

      point pt;

      System.get_cursor_pos(&pt);

      menuPopup.TrackPopupMenu(
         0,
         pt.x,
         pt.y,
         GetParentFrame());


   }

   void view::_001OnDestroy(gen::signal_object * pobj)
   {
      pobj->previous();

      Shell_NotifyIcon(NIM_DELETE, &m_nid);

      WTSUnRegisterSessionNotification(GetTopLevelParent()->_get_handle());
   }

   void view::_001OnTimer(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::timer, ptimer, pobj)
      if(ptimer->m_nIDEvent == TimerNotify)
      {
         OnTimerNotify();
      }
      else if(ptimer->m_nIDEvent == TimerIconFlash)
      {
         if(!IsNotified())
         {
            m_iIcon++;
            m_iIcon %= 2;
            if(m_bHover)
            {
               string stra[] = {"IDR_NOTIFY_HOVER_CHANGE1.ico","IDR_NOTIFY_HOVER_CHANGE1.ico"};
               UpdateNotifyIcon(stra[m_iIcon]);
            }
            else
            {
               string stra[] = {"IDR_NOTIFY_CHANGE1.ico","IDR_NOTIFY_CHANGE1.ico"};
               UpdateNotifyIcon(stra[m_iIcon]);
            }
         }
         
      }
      else if(ptimer->m_nIDEvent == TimerHoverOut)
      {
         m_bHover = false;
         KillTimer(TimerHoverOut);
         UpdateNotifyIcon("notify");
      }
      else if(ptimer->m_nIDEvent == TimerUserHour)
      {
         OnTimerUserHour();
      }
      else if(ptimer->m_nIDEvent == TimerWTSRegisterSessionNotification)
      {
         KillTimer(TimerWTSRegisterSessionNotification);
         if(!DeferWTSRegisterSessionNotification())
         {
            SetTimer(TimerWTSRegisterSessionNotification, 25000, 0);
         }

      }
      

   //  ::userbase::view::OnTimer(ptimer->m_nIDEvent);
   }


   void view::OnTimerNotify()
   {

      

   }


   void view::OnDirty()
   {
      if(!IsNotified())
      {
         int i = System.GetProfileInt("Options", "Play Sound", 1);
         if(i == 1)
         {
            Beep(440, 12);
         }
      }
   }

   void view::on_show_view()
   {
      ::userex::pane_tab_view::on_show_view();
      GetTopLevelFrame()->InitialFramePosition(true);
      GetTopLevelFrame()->SetWindowPos(ZORDER_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
      GetTopLevelFrame()->BringWindowToTop();
      //GetTopLevelFrame()->SetActiveView(this);
   }

   void view::on_update(::view * pSender, LPARAM lHint, ::radix::object * phint)
   {
      ::userbase::tab_view::on_update(pSender, lHint, phint);
      if(phint != NULL)
      {
         if(base < update_hint >::bases(phint))
         {
            update_hint * puh = dynamic_cast < update_hint * > (phint);
            if(puh->m_etype == update_hint::TypeUserHour)
            {
               UserHour_PulseEvent(puh->m_euserhourevent);
            }
         }
      }
      if(lHint == 123321)
      {
         ViewWhiteboard(true);
      }
      else if(lHint == 321123)
      {
         ViewWhiteboard(true);
      }
      else if(lHint == 321124)
      {
         string strURL;
         get_document()->GetUpHomeUrl(strURL);
         URLOpenNew(strURL, true);
      }
      else if(lHint == 321200)
      {
         set_cur_tab_by_id(ViewHtml);
         string strURL;
         whiteboard::application * papp = dynamic_cast < whiteboard::application * > (&Application);
         papp->GetSiteUrl(SiteWb, strURL);
         URLOpenNew(strURL, true);
         GetParentFrame()->layout();
      }
      else if(lHint == document::HintShowAbout)
      {
         URLOpenNew("wb://about", true);
      }
      else if(lHint == document::HintRefresh)
      {
         
      }
      else if(lHint == document::HintShowCalendar)
      {
         string strURL;
         whiteboard::application * papp = dynamic_cast < whiteboard::application * > (&Application);
         papp->GetSiteUrl(SiteCalendar, strURL);
         URLOpenNew(strURL, true);
      }
      else if(lHint == document::HintShowBookmark)
      {
         string strURL;
         whiteboard::application * papp = dynamic_cast < whiteboard::application * > (&Application);
         papp->GetSiteUrl(SiteBookmark, strURL);
         URLOpenNew(strURL, true);
      }
      else if(lHint == document::HintShowAnnotate)
      {
         string strURL;
         whiteboard::application * papp = dynamic_cast < whiteboard::application * > (&Application);
         papp->GetSiteUrl(SiteAnnotate, strURL);
         URLOpenNew(strURL, true);
      }
      else if(lHint == document::HintShowUserHour)
      {
         string strPath;
         get_document()->GetUserHourFilePath(strPath, "index");
         URLOpenNew(strPath, true);
      }
   /*   else if(lHint == document::HintShowMrts)
      {
         string strURL;
         if(m_phtmlviewMrts == NULL ||
            m_phtmldocMrts->GetLocationURL().make_lower().find("mrtsserv.") < 0)
         {
            whiteboard::application * papp = dynamic_cast < whiteboard::application * > (&Application);
            papp->GetSiteUrl(SiteMrts, strURL);
            MrtsUrlOpenNew(strURL, true);
         }
         else
         {
            ShowView(ViewMrtsHtml);
         }
      }
      else if(lHint == document::HintShowMrtsQuerylist)
      {
         ShowView(ViewMrtsQuerylistHtml);
      }*/
      else if(lHint == document::HintShowCalendar)
      {
         string strURL;
         whiteboard::application * papp = dynamic_cast < whiteboard::application * > (&Application);
         papp->GetSiteUrl(SiteCalendar, strURL);
         URLOpenNew(strURL, true);
      }
      else if(lHint == 4321)
      {
         GetParentFrame()->ShowWindow(SW_SHOW);
      }
      else if(lHint == document::HintUpdateCalendarTrayIcon)
      {
         UpdateCalendarTrayIcon();
      }
      else if(lHint == document::HintUpdateMrtsTrayIcon)
      {
         UpdateMrtsTrayIcon();
      }
      else if(lHint == document::HintUpdateMrtsQuerylistTrayIcon)
      {
         UpdateMrtsQuerylistTrayIcon();
      }
      else if(lHint == document::HintShowToolsOptions)
      {
         set_cur_tab_by_id(ViewOptions);
         GetParentFrame()->layout();
      }
      else if(lHint == document::HintShowHtmlView)
      {
         set_cur_tab_by_id(ViewHtml);
         GetParentFrame()->layout();
      }
      else if(lHint == document::HintUpdateFrameTitle)
      {
         UpdateFrameTitle();
      }
   }

   bool view::IsNotified()
   {
      whiteboard::time timeLastChange;
      whiteboard::time timeLastView;
      Application.GetProfileTime(timeLastChange, TimeLastChange);
      Application.GetProfileTime(timeLastView, TimeLastView);
      return !(timeLastChange > timeLastView);
   }



   void view::_001OnSize(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      LayoutChild();
   }

   void view::LayoutChild(void)
   {
      rect rectClient;
      GetClientRect(rectClient);
      /*m_pwnd->SetWindowPos(NULL, 0, 0, rectClient.width(), rectClient.height(),
         SWP_SHOWWINDOW);*/

      

   }

   void view::_001OnEraseBkgnd(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::erase_bkgnd, perasebkgnd, pobj)

      perasebkgnd->set_lresult(1);
   }

   void view::UpdateFrameTitle()
   {
      switch(m_eview)
      {
      case ViewHtml:
         {
            GetParentFrame()->SetWindowText(m_strHtmlTitle);
         }
         break;
      case ViewOptions:
         {
            GetParentFrame()->SetWindowText(m_strOptionsTitle);
         }
         break;
      }
   }

   void view::_001OnWtsSessionChange(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj)
      switch(pbase->m_wparam)
      {
      case WTS_SESSION_LOCK:
         OnWtsSessionLock();
         break;
      case WTS_SESSION_UNLOCK:
         OnWtsSessionUnlock();
         break;
      case WTS_SESSION_LOGON:
         OnWtsSessionLogon();
         break;
      case WTS_SESSION_LOGOFF:
         OnWtsSessionLogoff();
         break;
      }
      pobj->m_bRet = true;
   }

   void view::OnWtsSessionLock()
   {
      m_bSessionLocked = true;
      TRACE("Session Locked");
      //GetConnectionThread().UserHourPulseEvent();
      UserHour_PulseEvent(user_hour::event_wts_lock);
   }

   void view::OnWtsSessionUnlock()
   {
      m_bSessionLocked = false;
      TRACE("Session Unlocked");
      UserHour_PulseEvent(user_hour::event_wts_unlock);
      //GetConnectionThread().UserHourPulseEvent();
   }
   void view::OnWtsSessionLogon()
   {
      TRACE("Session Logon");
      //GetConnectionThread().UserHourPulseEvent();
      UserHour_PulseEvent(user_hour::event_wts_logon);
   }

   void view::OnWtsSessionLogoff()
   {
      TRACE("Session Logoff");
      UserHour_PulseEvent(user_hour::event_wts_logoff);
      //GetConnectionThread().UserHourPulseEvent();
   }

   bool view::IsSessionLocked(void)
   {
      return m_bSessionLocked;
   }

   void view::OnWb()
   {
      document * pdoc = (document *) get_document();
      pdoc->update_all_views(NULL, 321200, NULL);
   }


   void view::OnTimerUserHour()
   {
      if(m_bSessionLocked)
         return;
      UserHour_PulseEvent(user_hour::event_timer);
   }


   void view::UpdateCalendarTrayIcon()
   {
      document * pdoc = get_document();
      bool bShow = pdoc->GetShowCalendarTrayIcon();
      ShowNotifyIcon(1, bShow);
   }

   void view::UpdateMrtsTrayIcon()
   {
      document * pdoc = get_document();
      bool bShow = pdoc->GetShowMrtsTrayIcon();
      ShowNotifyIcon(2, bShow);
   }

   void view::UpdateMrtsQuerylistTrayIcon()
   {
      document * pdoc = get_document();
      bool bShow = pdoc->GetShowMrtsQuerylistTrayIcon();
      ShowNotifyIcon(3, bShow);
   }

   void view::OnViewBrowser()
   {
      get_document()->update_all_views(NULL, document::HintShowHtmlView);
   }

   void view::UserHour_PulseEvent(user_hour::e_event eevent)
   {
      ThreadProcInfo * pinfo = new ThreadProcInfo;

      pinfo->m_pview    = this;
      pinfo->m_eevent   = eevent;
      AfxBeginThread(get_app(), ThreadProc_UserHour_PulseEvent, (LPVOID) pinfo);
      
   }

   void view::_UserHour_PulseEvent(user_hour::e_event eevent)
   {
      single_lock sl(&Application.m_csUserHour, TRUE);
//      int iRetry = 10;

      string strPath;
      VERIFY(get_document()->GetUserHourFilePath(strPath));

      _Backup(strPath);

      for(int iRetry = 0; iRetry < 10; iRetry++)
      {
         if(_UserHour_PulseEvent(eevent, iRetry))
            break;
         Sleep(200);
      }
   }

   bool view::_UserHour_PulseEvent(user_hour::e_event eevent,  int iRetry)
   {
      UNREFERENCED_PARAMETER(iRetry);
      string strPath;
      VERIFY(get_document()->GetUserHourFilePath(strPath));
      try
      {
         user_hour::user_hour_set set(get_app());
        if(!set.LoadFile(strPath))
         {
            _Backup(strPath);
         }
   //      set.PulseEvent(user_hour::event_logon_time, &timeLogon);
         set.PulseEvent(this, eevent);
         set.Sort();
         set.WriteFile(strPath);
      }
      catch(...)
      {
         return false;
      }
      return true;
   }

   UINT AFX_CDECL view::ThreadProc_UserHour_PulseEvent(LPVOID lpvoid)
   {
      ThreadProcInfo * pinfo = (ThreadProcInfo *) lpvoid;
      pinfo->m_pview->_UserHour_PulseEvent(pinfo->m_eevent);
      delete pinfo;
      return 0;
   }

   void view::_Backup(const char * lpcszPath)
   {
      for(int iRetry = 0; iRetry < 10; iRetry++)
      {
         if(_Backup(lpcszPath, iRetry))
            break;
         Sleep(200);
      }
   }

   bool view::_Backup(const char * lpcszPath, int iRetry)
   {
      UNREFERENCED_PARAMETER(iRetry);
      ::ex1::file_status status;
      ::ex1::filesp filesp(get_app());
      if(!filesp->GetStatus(lpcszPath, status))
      {
         _BackupAndRestore(lpcszPath);
         return false;
      }

      string strPath(lpcszPath);
      string strBackupPath;
      string str = strPath;
      util::strip_file_extension(str);
      class ::time timeCurrent;
      timeCurrent = ::time::get_current_time();
      strBackupPath.Format(
         "%s.backup-%04d-%02d-%02d.xml",
         str, 
         timeCurrent.GetYear(), 
         timeCurrent.GetMonth(), 
         timeCurrent.GetDay());

      ::ex1::file_status statusBackup;
      if(!filesp->GetStatus(strBackupPath, statusBackup))
      {
         ::CopyFile(strPath, strBackupPath, FALSE);
         return true;
      }
      // if the new file is too smaller than the backup, 
      // create helper backup
      if(status.m_size < statusBackup.m_size / 2)
      {
         _BackupAndRestore(lpcszPath);
         return true;
      }
      else
      {
         ::CopyFile(strPath, strBackupPath, FALSE);
         return true;
      }
   }

   void view::_BackupAndRestore(const char * lpcszPath)
   {
      if(!System.file().exists(lpcszPath))
         return;

      ::ex1::file_status status;
      ::ex1::filesp filesp(get_app());
      if(!filesp->GetStatus(lpcszPath, status))
      {
         status.m_size = 0;
      }
      string strPath(lpcszPath);
      string strBackupPath;
      string str = strPath;
      util::strip_file_extension(str);
      class ::time timeCurrent;
      timeCurrent = ::time::get_current_time();
      strBackupPath.Format(
         "%s.backup-%04d-%02d-%02d.xml",
         str, 
         timeCurrent.GetYear(), 
         timeCurrent.GetMonth(), 
         timeCurrent.GetDay());

      ::ex1::file_status statusBackup;
      if(!filesp->GetStatus(strBackupPath, statusBackup))
      {
         statusBackup.m_size = 0;
      }

      if(status.m_size > statusBackup.m_size / 2)
         return;

      if(status.m_size == 0 && statusBackup.m_size > 0)
      {
         ::CopyFile(strBackupPath, strPath, TRUE);
         return;
      }


      // BackupEx
      string strBackupPathEx;
      for(int i = 0; i < 100; i++)
      {
         strBackupPathEx.Format("%s.ex-%02d.xml", strBackupPath, i);
         if(::CopyFile(strPath, strBackupPathEx, TRUE))
            break;
      }


      // BackupEx
      for(int i = 0; i < 100; i++)
      {
         strBackupPathEx.Format("%s.bkex-%02d.xml", strBackupPath, i);
         if(::CopyFile(strBackupPath, strBackupPathEx, TRUE))
            break;
      }

      // Restore

      user_hour::user_hour_set set(get_app());

      try
      {
         if(!set.LoadFile(strPath))
         {
            return;
         }
      }
      catch(...)
      {
         return;
      }

      user_hour::user_hour_set setBackup(get_app());

      try
      {
         if(!setBackup.LoadFile(strBackupPath))
         {
            return;
         }
      }
      catch(...)
      {
         return;
      }

      try
      {
         setBackup.Merge(set);
         setBackup.WriteFile(strPath);
      }
      catch(...)
      {
         return;
      }

   }

   void view::ShowNotifyIcon(int iId, bool bShow)
   {
      if(iId == 1)
      {
         if(bShow)
         {
            m_nidCalendar.uFlags |= NIF_ICON;
            m_nidCalendar.hIcon = GetIcon("IDI_NOTIFY_CALENDAR.ico");
            Shell_NotifyIcon(NIM_ADD, &m_nidCalendar);
         }
         else
         {
            Shell_NotifyIcon(NIM_DELETE, &m_nidCalendar);
         }
      }
      else if(iId == 2)
      {
         if(bShow)
         {
            m_nidMrts.uFlags |= NIF_ICON;
            m_nidMrts.hIcon = GetIcon("IDI_NOTIFY_MRTS.ico");
            Shell_NotifyIcon(NIM_ADD, &m_nidMrts);
         }
         else
         {
            Shell_NotifyIcon(NIM_DELETE, &m_nidMrts);
         }
      }
      else if(iId == 3)
      {
         if(bShow)
         {
            m_nidMrtsQuerylist.uFlags |= NIF_ICON;
            m_nidMrtsQuerylist.hIcon = GetIcon("IDI_NOTIFY_MRTS_QUERYLIST.ico");
            Shell_NotifyIcon(NIM_ADD, &m_nidMrtsQuerylist);
         }
         else
         {
            Shell_NotifyIcon(NIM_DELETE, &m_nidMrtsQuerylist);
         }
      }
   }


   HICON view::GetIcon(const char * pszMatter)
   {
      HICON hicon = NULL;
      if(!m_mapIcon.Lookup(pszMatter, hicon))
      {
         hicon = (HICON) ::LoadImage(
            NULL, 
            Application.dir().matter("whiteboard/notification_area", string(pszMatter) + ".ico"), 
            IMAGE_ICON,
            16, 16,
            LR_LOADFROMFILE);
         ASSERT(hicon != NULL);
         m_mapIcon.set_at(pszMatter, hicon);
      }
      return hicon;
   }

   void view::OnViewMrts()
   {
      get_document()->update_all_views(NULL, document::HintShowMrts);
   }

   void view::OnUpdateViewMrts(cmd_ui *pcmdui)
   {
      pcmdui->Enable();
      pcmdui->_001SetCheck(IsInMrts());
   }

   void view::OnUpdateViewMrtsQuerylist(cmd_ui *pcmdui)
   {
      pcmdui->Enable(get_document()->GetShowMrtsQuerylistTrayIcon()
         && get_document()->m_bMrtsQuerylist);
      pcmdui->_001SetCheck(IsInMrtsQuerylist());
   }

   void view::OnViewMrtsQuerylist()
   {
      get_document()->update_all_views(NULL, document::HintShowMrtsQuerylist);
      
   }

   bool view::IsInMrts(void)
   {
      return m_eview == ViewMrtsHtml;
   }

   bool view::IsInMrtsQuerylist(void)
   {
      return m_eview == ViewMrtsQuerylistHtml;
   }



   void view::OnEndSessionLogoff()
   {
      TRACE("Session Logoff");
      UserHour_PulseEvent(user_hour::event_wts_logoff);
   }

   void view::OnEndSessionShutdown()
   {
      TRACE("Session Shutdown");
      UserHour_PulseEvent(user_hour::event_end_session);
   }


   bool view::DeferWTSRegisterSessionNotification()
   {
      if(::WTSRegisterSessionNotification(
         GetTopLevelParent()->_get_handle(),
         NOTIFY_FOR_THIS_SESSION))
      {
         m_bWTSRegisterSessionNotification = true;
         //System.simple_message_box("Session notification handler registered.", MB_ICONINFORMATION);
      }
      else
      {
         m_bWTSRegisterSessionNotification = false;
         m_iWTSRegisterSessionNotificationRetry++;
         if(m_iWTSRegisterSessionNotificationRetry > 30)
         {
            string strUserMessage;
            strUserMessage.Format("Could not register session notification handler. lock and unlock events will not be detected. Tried %d times.", m_iWTSRegisterSessionNotificationRetry);
            System.simple_message_box(NULL, strUserMessage, MB_ICONASTERISK);
         }
         else
         {
            string strUserMessage;
            strUserMessage.Format("Could not register session notification handler. lock and unlock events cannot be detected. Tried %d times. Retrying.", m_iWTSRegisterSessionNotificationRetry);
            System.simple_message_box(NULL, strUserMessage, MB_ICONEXCLAMATION);
         }
      }
      return m_bWTSRegisterSessionNotification;
   }


   void view::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      ::userex::pane_tab_view::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &view::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &view::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_ERASEBKGND, pinterface, this, &view::_001OnEraseBkgnd);
      IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &view::_001OnDestroy);
   }

} // namespace whiteboard
