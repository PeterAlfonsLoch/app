#include "StdAfx.h"
#include "window_frame/FrameSchemaHardCoded002.h"
#include "window_frame/FrameSchemaHardCoded005.h"

namespace windesk
{

   static UINT indicators[] =
   {
	   ID_SEPARATOR,           // status line indicator
	   ID_INDICATOR_CAPS,
	   ID_INDICATOR_NUM,
	   ID_INDICATOR_SCRL,
   };

   frame::frame(::ca::application * papp) :
      ca(papp),
      window_frame::WorkSetClientInterface(papp),
      userbase::frame_window_interface(papp),
      userbase::frame_window(papp),
      simple_frame_window(papp),
      ::ca::message_window_simple_callback(papp),
      m_toolbar(papp),
      m_dibBk(papp)
   {
      m_iNewArea = 0;
      m_iArea = -1;

      m_pimagelist      = NULL;
      m_iFrameData      = 10;
      m_dataid          = "ca2::windesk::frame";
      m_iAnimateStep    = 0;
      m_bTimerHide      = false;

      WfiEnableFullScreen();

      m_dataidWindow    = "WindowData";
      m_bMoveDrag       = true;
      m_bLastLWin       = false;
      m_bLayered        = false;
      m_bCustomFrame    = false;
      m_pview           = NULL;
      m_ppaneview       = NULL;

   }

   frame::~frame()
   {
   }

   void frame::_001OnCreate(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::create, pcreate, pobj);
      pobj->previous();
      if(pobj->m_bRet)
         return;
      if(!initialize_message_window("ca2::fontopus::message_wnd::windesk"))
      {
         pcreate->set_lresult(-1);
         pcreate->m_bRet = true;
         return;
      }
      CheckLayout();
      SetTimer(1578751, 10 * 1000, NULL);
   }

   BOOL frame::PreCreateWindow(CREATESTRUCT& cs)
   {
	   if(!simple_frame_window::PreCreateWindow(cs))
		   return FALSE;

      cs.dwExStyle = WS_EX_TOOLWINDOW;

	   return TRUE;
   }

   /////////////////////////////////////////////////////////////////////////////
   // frame diagnostics

   #ifdef _DEBUG
   void frame::assert_valid() const
   {
	   simple_frame_window::assert_valid();
   }

   void frame::dump(dump_context & dumpcontext) const
   {
	   simple_frame_window::dump(dumpcontext);
   }


   #endif //_DEBUG






   void frame::_001OnTimer(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::timer, ptimer, pobj);
      UINT nIDEvent = ptimer->m_nIDEvent;
      static float theta;
      if(nIDEvent == 1578751)
      {
         CheckLayout();
      }
   }






   void frame::_001OnClose(gen::signal_object * pobj)
   {
      pobj->m_bRet = true;
   }


   void frame::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      simple_frame_window::_001InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &frame::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &frame::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_MOVE, pinterface, this, &frame::_001OnMove);
      IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &frame::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_APP + 2000, pinterface, this, &frame::_001OnApp2000and2001);
      IGUI_WIN_MSG_LINK(WM_APP + 2001, pinterface, this, &frame::_001OnApp2000and2001);
      IGUI_WIN_MSG_LINK(1257821  , pinterface, this, &frame::_001On1257821);
      IGUI_WIN_MSG_LINK(WM_CLOSE, pinterface, this, &frame::_001OnClose);
      IGUI_WIN_MSG_LINK(WM_ACTIVATE, pinterface, this, &frame::_001OnActivate);
      IGUI_WIN_MSG_LINK(WM_NCACTIVATE, pinterface, this, &frame::_001OnNcActivate);
      IGUI_WIN_MSG_LINK(WM_NCCALCSIZE, pinterface, this, &frame::_001OnNcCalcSize);
      IGUI_WIN_MSG_LINK(WM_MOUSEACTIVATE, pinterface, this, &frame::_001OnMouseActivate);
      IGUI_WIN_MSG_LINK(WM_WINDOWPOSCHANGING, pinterface, this, &frame::_001OnWindowPosChanging);
   }

   void frame::_001OnMove(gen::signal_object * pobj)
   {
      if(m_wndframework.GetMovingManager()->IsMoving())
      {
         rect rectDesktop;
         Application.get_screen_rect(rectDesktop);
         rect rectWindow;
         GetWindowRect(rectWindow);
         double a = (double) rectDesktop.height() / (double) rectDesktop.width();
         if(rectWindow.left < (rectDesktop.width() / 2))
         {
            // to the left
            if(rectWindow.top < rectWindow.left * a)
            {
               // top
               m_eposition = position_top;
            }
            else if(rectWindow.top > (rectDesktop.height() - rectWindow.left * a))
            {
               // bottom
               m_eposition = position_bottom;
            }
            else
            {
               // left
               m_eposition = position_left;
            }
         }
         else
         {
            // to the right
            // to the left
            if(rectWindow.top > rectWindow.left * a)
            {
               // bottom
               m_eposition = position_bottom;
            }
            else if(rectWindow.top < (rectDesktop.height() - rectWindow.left * a))
            {
               // top
               m_eposition = position_top;
            }
            else
            {
               // right
               m_eposition = position_right;
            }
         }
         data_set("DockPosition", (int) m_eposition);
      }
   }

   void frame::_001OnMouseActivate(gen::signal_object * pobj)
   {
      //pobj->m_bRet = true;
   }
   void frame::_001OnChildActivate(gen::signal_object * pobj)
   {
     // pobj->m_bRet = true;
   }
   void frame::_001OnActivate(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::activate, pactivate, pobj);
   //   pobj->m_bRet = true;
   }
   void frame::_001OnNcActivate(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj);
      pbase->m_bRet = true;
      pbase->set_lresult(DefWindowProc(WM_NCACTIVATE, pbase->m_wparam, -1));
   }

   void frame::_001OnNcCalcSize(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj);

      if(pbase->m_wparam == TRUE)
      {
         pbase->m_bRet = true;
         pbase->set_lresult(0);
      }
      else if(m_iDisplay >= 0)
      {
         LPRECT lprect = (LPRECT) pbase->m_lparam;
         *lprect =  Application.m_monitorinfoaDesk[m_iDisplay].rcMonitor;
         pbase->m_bRet = true;
         pbase->set_lresult(0);
      }
   }

   bool frame::_001OnCommand(id id)
   {
      if(id == "app_exit")
      {
         simple_frame_window::OnClose();
         return true;
      }
      return simple_frame_window::_001OnCommand(id);
   }

   bool frame::_001OnUpdateCmdUi(cmd_ui * pcmdui)
   {
      if(pcmdui->m_id == "app_exit")
      {
         return true;
      }
      return simple_frame_window::_001OnUpdateCmdUi(pcmdui);
   }

   void frame::_001OnDestroy(gen::signal_object * pobj)
   {
      show_task_bar(SW_SHOW);
   }

   void frame::message_window_message_handler(gen::signal_object * pobj)
   {
      SCAST_PTR(user::win::message::base, pbase, pobj);
      if(pbase->m_uiMessage == (WM_APP + 2000)
      || pbase->m_uiMessage == (WM_APP + 2001))
      {
         _001OnApp2000and2001(pbase);
         pbase->m_bRet = true;
      }
   }


   void frame::_001OnApp2000and2001(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj)
      if(pbase->m_wparam == 0)
      {
         CheckLayout();
         windesk::application * papp = dynamic_cast < windesk::application * > (get_app());
      }
      else if(pbase->m_wparam == 1)
      {
         pbase->set_lresult(2);
      }
      else if(pbase->m_wparam == 2)
      {
         pbase->set_lresult(4);
      }
      else if(pbase->m_wparam == 3)
      {
         if(pbase->m_lparam == 6)
         {
            GetTopLevelFrame()->ShowWindow(SW_HIDE);
            AfxPostQuitMessage(36);
         }
      }
      else if(pbase->m_wparam == 4)
      {
         pbase->set_lresult(5);
      }
      else if(pbase->m_wparam == 5)
      {
         pbase->set_lresult(8);
      }
      else if(pbase->m_wparam == 8)
      {
         pbase->set_lresult(11);
      }
      else if(pbase->m_wparam == 11)
      {
         pbase->set_lresult(23);
      }
      else if(pbase->m_wparam == 23)
      {
         pbase->set_lresult(33);
      }
      else if(pbase->m_wparam == 33)
      {
         pbase->set_lresult(69);
      }
      else if(pbase->m_wparam == 102326)
      {
         m_ppaneview->m_iNewArea = pbase->m_lparam;
         m_iNewArea = m_ppaneview->m_iNewArea;
         CheckLayout();
         _001RedrawWindow();
      }
      if(pbase->m_uiMessage == (WM_APP + 2000))
      {
         windesk::application * papp = dynamic_cast < windesk::application * > (get_app());
         for(int i = 0; i < papp->m_hwndaDesktop.get_count(); i++)
         {
            if(papp->m_hwndaDesktop[i] != get_safe_handle())
            {
               ::SendMessage(papp->m_hwndaDesktop[i], WM_APP + 2001, pbase->m_wparam, pbase->m_lparam);

            }
         }
      }
      pbase->m_bRet = true;
   }

   void frame::_001On1257821(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj)

      SendMessageToDescendants(1257821);

   }


   void frame::show_task_bar(int nCmdShow)
   {
      ::ca::window * pwnd = Application.FindWindow("Shell_TrayWnd", "");
      if(pwnd == NULL)
         return;
      pwnd->ShowWindow(nCmdShow);
   }





   window_frame::FrameSchema * frame::create_frame_schema()
   {
      window_frame::FrameSchemaHardCoded005 * pschema = new window_frame::FrameSchemaHardCoded005(get_app());
      pschema->m_pruntimeclassControlBoxButton = &typeid(MetaButton);
      pschema->SetStyle(window_frame::FrameSchemaHardCoded005::StyleTranslucidWarmGray);
      return pschema;
   }

   void frame::_001OnWindowPosChanging(gen::signal_object * pobj)
   {


      SCAST_PTR(::user::win::message::window_pos, pwindowpos, pobj);
      pwindowpos->m_pwindowpos->flags |= SWP_NOZORDER;


   }


   void frame::CheckLayout()
   {
      if(m_ppaneview != NULL)
      {
         m_iDisplay = m_ppaneview->m_iDisplay;
      }
      else
      {
         m_iDisplay = 0;
      }
      if(m_pview != NULL)
      {
         m_pview->m_iDisplay = m_iDisplay;
      }
      if(m_iDisplay < 0)
      {
         SetWindowLong(GWL_STYLE, 0);
         return;
      }
      if(GetWindowLong(GWL_STYLE) & WS_VISIBLE)
      {
         SetWindowLong(GWL_STYLE, WS_VISIBLE);
      }
      if(!IsFullScreen())
      {
         WfiFullScreen(true, true);
      }
      //HWND hwndDesktop = ::GetDesktopWindow();
       //rect rectDesktop = Application.m_monitorinfoaDesk[m_iDisplay].rcMonitor;
      if(m_iDisplay >= windesk::app_cast(get_app()).m_rectaMonitor.get_count())
         return;
      class rect rectDesktop = windesk::app_cast(get_app()).m_rectaMonitor[m_iDisplay];
     //::GetWindowRect(hwndDesktop, &rectDesktop);
      //ShowWindow(SW_RESTORE);

	   // TODO: add extra initialization here
	   /*WINDOWPLACEMENT WP;
	   POINT ptMinPos;
	   POINT ptMaxPos;
	   RECT rcNormalPos;

	   ptMinPos.x = 0;
	   ptMinPos.y = 0;

	   ptMaxPos.x = 0;
	   ptMaxPos.y = 0;
   	
	   rcNormalPos.left    = rectDesktop.left;
	   rcNormalPos.top     = rectDesktop.top;
	   rcNormalPos.right   = rectDesktop.width();
	   rcNormalPos.bottom  = rectDesktop.height();

	   WP.length           = sizeof(WINDOWPLACEMENT);
	   WP.flags            = WPF_RESTORETOMAXIMIZED;
	   WP.showCmd	        = SW_SHOWMAXIMIZED;
	   WP.ptMinPosition    = ptMinPos;
	   WP.ptMaxPosition    = ptMaxPos;
	   WP.rcNormalPosition = rcNormalPos;

	   SetWindowPlacement(&WP);*/

      SetWindowPos(ZORDER_BOTTOM, rectDesktop.left, rectDesktop.top, rectDesktop.width(), rectDesktop.height(), 0);

   }


   void frame::data_on_after_change(gen::signal_object * pobj)
   {
      simple_frame_window::data_on_after_change(pobj);
      SCAST_PTR(::database::change_event, pchange, pobj);
      if(pchange->m_key.m_idKey == "ca2_fontopus_votagus")
      {
         if(pchange->m_key.m_idIndex == "savings")
         {
            m_iArea = -1;
            _001RedrawWindow();
         }
         else if(pchange->m_key.m_idIndex  == "windesk")
         {
            _001RedrawWindow();
         }
      }

   }


   void frame::_001OnDraw(::ca::graphics * pdc)
   {
      rect rectClient;
      GetClientRect(rectClient);
      if(m_iNewArea != m_iArea)
      {
         m_iArea = m_iNewArea;
         m_dibBk->Destroy();
      }
      COLORREF crBk;
      switch(m_iArea)
      {
      case 0:
         crBk = RGB(30, 50, 50);
         break;
      case 1:
         crBk = RGB(50, 109, 142);
         break;
      case 2:
         crBk = RGB(120, 184, 100);
         break;
      case 3:
         crBk = RGB(33, 33, 26);
         break;
      default:
         crBk = RGB(50, 130, 100);
         break;
      }
      pdc->FillSolidRect(rectClient, crBk);
      // this helps to save display bandwith 
      // because the plainer background
      // more compressible image
      // lesser bandwidth to transmit each image
      if(windesk::app_cast(get_app()).m_flags.is_signalized(flag_enable_wallpaper)
         && !Application.savings().should_save(gen::resource_display_bandwidth))
      {
         if(m_dibBk->get_bitmap()->is_set() == NULL)
         {
            string strWallpaper;

            switch(m_iArea)
            {
            case 0:
               strWallpaper = System.dir().matter("cgcliscstlife1_23.bmp");
               break;
            case 1:
               strWallpaper = System.dir().matter("cgcliscstlife1_24.bmp");
               break;
            case 2:
               strWallpaper = System.dir().matter("cgcliscstlife1_25.bmp");
               break;
            case 3:
               strWallpaper = System.dir().matter("cgcliscstlife1_26.bmp");
               break;
            default:         
               strWallpaper = System.dir().matter("cgcliscstlife1_23.bmp");
               break;
            }
            m_dibBk.load_from_file(strWallpaper);
         }
         if(m_iDisplay >= 0)
         {
            rect rectDesktop = windesk::app_cast(get_app()).m_rectaMonitor[m_iDisplay];
            if(m_dibBk->width() > rectDesktop.left + rectDesktop.width() / 3)
            {
               m_dibBk->to(pdc, null_point(), size(min(m_dibBk->width() - rectDesktop.left, rectClient.width()), 
                  min(m_dibBk->height() - rectDesktop.top, rectClient.height())), rectDesktop.top_left());
            }
            else
            {
               m_dibBk->to(pdc, min(m_dibBk->width(), rectClient.width()), 
                  min(m_dibBk->height(), rectClient.height()));
            }
         }
      }

   }


} // namespace windesk