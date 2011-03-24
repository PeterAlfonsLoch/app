#include "StdAfx.h"
#include <math.h>
#include "window_frame/FrameSchemaHardCoded002.h"
#include "window_frame/FrameSchemaHardCoded005.h"

namespace flag
{

   HHOOK g_mousehookLL;
   frame * g_pframe;

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
      m_toolbar(papp)
   {
      m_pwinactionareaview = NULL;
      m_ppaneview = NULL;
      m_pimagelist = NULL;
      m_iFrameData = 10;
      m_dataid = "ca2::flag::frame";
      m_iAnimateStep = 0;
      m_bTimerHide = false;
      m_bHover = false;

      WfiEnableFullScreen();

      m_dataidWindow = "WindowData";
      m_bMoveDrag = true;
      m_bLastLWin = false;

      m_etranslucency = TranslucencyTotal;

   //   connect_command("app_exit", &frame::_001OnAppExit);
   //   connect_update_cmd_ui("app_exit", &frame::_001OnUpdateAppExit);
   }

   frame::~frame()
   {
   }

   void frame::_001OnCreate(gen::signal_object * pobj)
   {

      m_bCustomFrame = !Application.command_line().m_varQuery["client_only"].is_set();

      SCAST_PTR(::user::win::message::create, pcreate, pobj);
      if(!data_get("DockPosition", (int &) m_eposition))
      {
         m_eposition = position_left;
      }
      pobj->previous();
      if(pobj->m_bRet)
         return;

      if(!initialize_message_window("ca2::fontopus::message_wnd::flag"))
      {
         pcreate->set_lresult(-1);
         pcreate->m_bRet = true;
         return;
      }


      ModifyStyleEx(WS_EX_OVERLAPPEDWINDOW, 0);


      m_pimagelist = new image_list(get_app());
      m_pimagelist->create(16, 16, 0, 10, 10);
      m_pimagelist->add_matter_icon("system/language_change.ico");

      string str = Application.file().as_string(System.dir().matter("flag\\toolbar.xml"));

	   if (!m_toolbar.CreateEx(this) ||
		    !m_toolbar.LoadXmlToolBar(str))
	   {
		   TRACE0("Failed to create toolbar\n");
         pcreate->set_lresult(-1);// fail to create
         pcreate->m_bRet = true;
		   return;
	   }

      SetTimer(1000, 100, NULL);
      
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

   /////////////////////////////////////////////////////////////////////////////
   // frame message handlers



   void frame::_001OnTimer(gen::signal_object * pobj) 
   {
      /*SCAST_PTR(::user::win::message::timer, ptimer, pobj);
      UINT nIDEvent = ptimer->m_nIDEvent;
      static float theta;
      if(nIDEvent == 1000)
      {
         KillTimer(1000);
      }
      else if(nIDEvent == 85421)
      {
         post_hotspot();
      }
      else if(nIDEvent == 1001)
      {
         KillTimer(nIDEvent);
         ShowWindow(SW_HIDE);
      }
      else if(nIDEvent == 5000)
      {
         if(IsWindowVisible() && m_bAutoHideOnOutClick)
         {
            point pt;
            Application.get_cursor_pos(&pt);
            HWND hwnd = ::WindowFromPoint(pt);
            if(_get_handle() != hwnd
               && !user::WndUtil::IsAscendant(_get_handle(), hwnd))
            {
               m_bHover = false;
               ShowWindow(SW_HIDE);
            }
         }
      }*/



   }




   



   void frame::OnHoverAction(bool bShowWinActionArea)
   {
   }


   void frame::_001OnClose(gen::signal_object * pobj)
   {
      pobj->m_bRet = true;
      ShowWindow(SW_HIDE);
   }


   void frame::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      simple_frame_window::_001InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &frame::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &frame::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_MOVE, pinterface, this, &frame::_001OnMove);
      IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &frame::_001OnShowWindow);
      IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &frame::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_APP + 2000  , pinterface, this, &frame::_001OnApp2000);
      IGUI_WIN_MSG_LINK(1257821  , pinterface, this, &frame::_001On1257821);
      IGUI_WIN_MSG_LINK(WM_CLOSE, pinterface, this, &frame::_001OnClose);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &frame::_001OnMouseMove);
      IGUI_WIN_MSG_LINK(WM_MOUSELEAVE, pinterface, this, &frame::_001OnMouseLeave);
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

   void frame::_001OnShowWindow(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::show_window, pshowwindow, pobj)
      
      if(!pshowwindow->m_bShow)
      {
         if(GetActiveDocument() != NULL)
            GetActiveDocument()->update_all_views(NULL, 5432108);
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
   }

   void frame::message_window_message_handler(gen::signal_object * pobj)
   {
      SCAST_PTR(user::win::message::base, pbase, pobj);
      if(pbase->m_uiMessage == (WM_APP + 2000))
      {
         _001OnApp2000(pbase);
         pbase->m_bRet = true;
      }
      else if(pbase->m_uiMessage == WM_COPYDATA)
      {
         PCOPYDATASTRUCT  lpcopydata = (PCOPYDATASTRUCT) pbase->m_lparam;
         DWORD dwData = lpcopydata->dwData;
         if(dwData == 198477)  // simple text command
         {
            string str((const char *) lpcopydata->lpData, min(lpcopydata->cbData, 1024 * 64));
            if(gen::str::begins_eat(str, "winactionareaview::"))
            {
               if(gen::str::begins_eat(str, "show_calendar("))
               {
                  const char * pszXml = str;
//                  m_pwinactionareaview->show_calendar(gen::str::consume_quoted_value(pszXml));
               }
            }
         }

      }
   }

   void frame::_001OnApp2000(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj)
      if(pbase->m_wparam == 0)
      {
         if(pbase->m_lparam == 1)
         {
            OnHoverAction(true);
         }
         else if(pbase->m_lparam == 0)
         {
            ShowWindow(SW_HIDE);
         }
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
            Application.PostThreadMessage(WM_QUIT, 0, 0);
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
         pbase->set_lresult(67);
      }
      pbase->m_bRet = true;
   }

   void frame::_001On1257821(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj)

      SendMessageToDescendants(1257821);

   }

   window_frame::FrameSchema * frame::create_frame_schema()
   {
      window_frame::FrameSchemaHardCoded005 * pschema = new window_frame::FrameSchemaHardCoded005(get_app());
      pschema->m_pruntimeclassControlBoxButton = &typeid(MetaButton);
      pschema->SetStyle(window_frame::FrameSchemaHardCoded005::StyleTranslucidWarmGray);
      return pschema;
   }

   bool frame::calc_layered()
   {
      return true;
   }

   void frame::_000OnDraw(::ca::graphics * pdc)
   {
      if(!Application.savings().should_save(gen::resource_processing)
      && !Application.savings().should_save(gen::resource_display_bandwidth)
      && !Application.savings().should_save(gen::resource_memory))
      {
         simple_frame_window::_000OnDraw(pdc);
      }
      else
      {
         _001DrawThis(pdc);
         _001DrawChildren(pdc);
      }
   }


   void frame::post_hotspot()
   {
      if(m_pwinactionareaview != NULL)
      {
//         if(::IsWindow(m_pwinactionareaview->m_hwndWinservice1))
         {
            /*::PostMessage(
               m_pwinactionareaview->m_hwndWinservice1,
               WM_APP + 2000,
               2000,
               m_ptHotspot._001GetLparam());*/
         }
      }
   }
   void frame::_001OnMouseMove(gen::signal_object * pobj)
   {
   }

   void frame::_001OnMouseLeave(gen::signal_object * pobj)
   {
   }

} // namespace flag
