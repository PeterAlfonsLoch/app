#include "StdAfx.h"
#include <math.h>


namespace winutil
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
      m_toolbar(papp)
   {
      m_iFrameData = 10;
      m_dataid = "ca2::winutil::frame";
      m_iAnimateStep = 0;
      m_bTimerHide = false;

      WfiEnableFullScreen();

      m_dataidWindow = "WindowData";
      m_bMoveDrag = true;
      m_bLastLWin = false;

   //   connect_command("app_exit", &frame::_001OnAppExit);
   //   connect_update_cmd_ui("app_exit", &frame::_001OnUpdateAppExit);
   }

   frame::~frame()
   {
   }

   void frame::_001OnCreate(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::create, pcreate, pobj);
      if(!data_get("DockPosition", (int &) m_eposition))
      {
         m_eposition = position_left;
      }
	   pobj->previous();
      if(pobj->m_bRet)
         return;

   if(!initialize_message_window("ca2::fontopus::message_wnd::winutil"))
   {
      pcreate->set_lresult(-1);
      pcreate->m_bRet = true;
      return;
   }

      show_task_bar(SW_HIDE);


   /*BLENDFUNCTION blend;

       blend.BlendOp = AC_SRC_OVER;
       blend.BlendFlags = 0;
       blend.AlphaFormat = 0;
       blend.SourceConstantAlpha = 128;

       point ptSrc = point(0, 0);

       ::ca::graphics_sp spgraphics(get_app());
       spgraphics->CreateCompatibleDC(NULL);
    
*/


      
      m_bTimerOn = false;

      SetTimer(8913, 5000, 0);
      SetTimer(4033, 100, 0);
      ModifyStyleEx(WS_EX_OVERLAPPEDWINDOW, 0);

      SetTimer(4034, 500, 0);
      SetTimer(85421, 1000 * 5, NULL);

      //m_menuhook.Initialize(
        // BaseMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
         //BaseMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(),
         //NULL,
         //Application.font_central().GetMenuFont());

      //m_menuhook.Install(this);



      //m_hMenuDefault = NULL;

   /* 	if (!m_menubar.CreateEx(this))
	   {
		   TRACE0("Failed to create toolbar\n");
		   return -1;      // fail to create
	   }

      if(!m_menubar.Initialize(
         BaseMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
         BaseMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(),
         NULL,
         Application.font_central().GetMenuFont()) ||
		   VMS_FAILED(m_menubar.LoadMenuBar(IDR_MAINFRAME)))
	   {
		   TRACE0("Failed to create toolbar\n");
		   return -1;      // fail to create
	   }*/

      m_pimagelist = new image_list(get_app());
      m_pimagelist->create(16, 16, 0, 10, 10);
      m_pimagelist->add_matter_icon("system/language_change.ico");

      /*m_menubar._001SetImageList(&m_imagelist);
      m_menubar.SetItemImage(m_menubar._001GetItemCount() - 1, 0);*/

      string str = Application.file().as_string(
         Application.dir().matter("winutil\\toolbar.xml"));

	   if (!m_toolbar.CreateEx(this) ||
		    !m_toolbar.LoadXmlToolBar(str))
	   {
		   TRACE0("Failed to create toolbar\n");
         pcreate->set_lresult(-1); // fail to create
         pcreate->m_bRet = true;
		   return;
	   }

	   /*if (!m_toolbarView.CreateEx(this, TBSTYLE_FLAT,
		   WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP | CBRS_GRIPPER | CBRS_SIZE_DYNAMIC
         | CBRS_DRAGMOVE,
         rect(0, 0, 0, 0),
		   AFX_IDW_TOOLBAR + 1) ||
		   !m_toolbarView.LoadToolBar(IDR_VIEW))
	   {
		   TRACE0("Failed to create toolbar\n");
		   return -1;      // fail to create
	   }
      
      
	   if (!m_dialogbar.create(this, IDR_MAINFRAME, 
		   WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP | CBRS_GRIPPER | CBRS_SIZE_DYNAMIC
         | CBRS_DRAGMOVE, AFX_IDW_DIALOGBAR))
	   {
		   TRACE0("Failed to create dialogbar\n");
		   return -1;		// fail to create
	   }*/

   /*	if (!m_wndReBar.create(this) ||
         !m_wndReBar.AddBar(&m_menubar) ||
		   !m_wndReBar.AddBar(&m_wndToolBar) ||
         !m_wndReBar.AddBar(&m_toolbarView) ||
		   !m_wndReBar.AddBar(&m_wndDlgBar))
	   {
		   TRACE0("Failed to create rebar\n");
		   return -1;      // fail to create
	   }*/

   /*	if (!m_statusbar.create(this) ||
		   !m_statusbar.SetIndicators(indicators,
		     sizeof(indicators)/sizeof(UINT)))
	   {
		   TRACE0("Failed to create status bar\n");
		   return -1;      // fail to create
	   }*/

	   // TODO: remove this if you don't want tool tips
	   /*m_toolbar.SetBarStyle(m_toolbar.GetBarStyle() |
		   CBRS_TOOLTIPS | CBRS_FLYBY);
	   m_dialogbar.SetBarStyle(m_dialogbar.GetBarStyle() |
		   CBRS_TOOLTIPS | CBRS_FLYBY);

      EnableDocking(CBRS_ALIGN_ANY);

      m_toolbar.EnableDocking(CBRS_ALIGN_ANY);
      DockControlBar(&m_toolbar);

      m_toolbarView.EnableDocking(CBRS_ALIGN_ANY);
      DockControlBar(&m_toolbarView);

      m_dialogbar.EnableDocking(CBRS_ALIGN_TOP);
      m_dialogbar.EnableDocking(CBRS_ALIGN_BOTTOM);
      DockControlBar(&m_toolbar);*/

      //WindowDataLoadWindowRect();
      //WindowDataEnableSaveWindowRect(true);

      //Dock();
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
      if(nIDEvent == 4034)
      {
         if(IsWindowVisible())
         {
   /*         BLENDFUNCTION blend;

            blend.BlendOp = AC_SRC_OVER;
            blend.BlendFlags = 0;
            blend.AlphaFormat = 0;
            blend.SourceConstantAlpha = 255;

            point ptSrc = point(0, 0);

            ::ca::graphics_sp spgraphics(get_app());
            spgraphics->CreateCompatibleDC(NULL);

          */

            RedrawWindow(NULL, NULL, RDW_UPDATENOW | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
         }
      }
      else if(nIDEvent == 3)
      {
         //AnimateStatusBar();
      }
      else if(nIDEvent == 1000)
      {
         KillTimer(nIDEvent);
         m_bTimerOn = false;
         bool bLControlKeyDown = (GetAsyncKeyState (VK_LCONTROL) >> ((sizeof(SHORT) * 8) - 1)) != FALSE;
         bool bLAltKeyDown = (GetAsyncKeyState (VK_LMENU) >> ((sizeof(SHORT) * 8) - 1)) != FALSE;
         if(bLControlKeyDown && bLAltKeyDown)
         {
            OnHoverAction(true);
         }
         else
         {
            ShowWindow(SW_HIDE);
         }
      }
      else if(nIDEvent == 1001)
      {
         KillTimer(nIDEvent);
         ShowWindow(SW_HIDE);
      }
      else if(nIDEvent == 8913)
      {
      }
      // every 100 ms approximately
      else if(nIDEvent == 4033)
      {
   /*      rect rectWindow;
         GetWindowRect(rectWindow);
         point pt;
         Application.get_cursor_pos(&pt);
         if(!rectWindow.contains(pt) && !m_bTimerHide)
         {
            m_bTimerHide = true;
            SetTimer(1001, 800, NULL);
         }
         else
         {
            m_bTimerHide = false;
            KillTimer(1001);
         }*/
         /*point pt;
         if(m_bHoverMouse && GetTickCount() > m_dwLastHover + 300)
         {
            OnHoverAction();
         }
         if(Application.get_cursor_pos(&pt))
         {
            if(!m_bHoverMouse && pt.x == 0 && pt.y == 0)
            {
               m_dwLastHover = ::GetTickCount();
               m_bHoverMouse = true;
               
            }
            else if(m_bHoverMouse && (pt.x > 10 || pt.y > 0))
            {
               m_bHoverMouse = false;
            }

         }*/
   // OpenGL animation code goes here
   			
			   //glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
			   //glClear( GL_COLOR_BUFFER_BIT );
   			
			   /*glPushMatrix();
			   glRotatef( theta, 0.0f, 1.0f, 1.0f );
			   glBegin( GL_TRIANGLES );
			   glColor3f( 1.0f, 0.0f, 0.0f ); glVertex2f( 0.0f, 1.0f );
			   glColor3f( 0.0f, 1.0f, 0.0f ); glVertex2f( 0.87f, -0.5f );
			   glColor3f( 0.0f, 0.0f, 1.0f ); glVertex2f( -0.87f, -0.5f );
			   glEnd();
			   glPopMatrix();*/
   			
			   //SwapBuffers( m_hdcOpenGL );
   			
			   theta += 2.0f;
   		
      }
      else if(nIDEvent == 85421)
      {
         System.assert_running_local("winservice_1");
      }
   //	simple_frame_window::OnTimer(nIDEvent);
   }

   void frame::SetAnimatedStatusBarText(const char * lpcsz)
   {
      m_strAnimatedStatusBarText = lpcsz;
      if(m_strAnimatedStatusBarText.is_empty())
      {
         KillTimer(3);
      }
      else
      {
         SetTimer(3, 500, NULL);
      }
   }

   void frame::AnimateStatusBar()
   {
      if(m_strAnimatedStatusBarText.is_empty())
         return;

      int iLen = m_strAnimatedStatusBarText.get_length();
      m_iAnimateStep++;
      if(m_iAnimateStep > iLen)
         m_iAnimateStep = 0;


   //   m_statusbar.SetPaneText(0, m_strAnimatedStatusBarText.Mid(m_iAnimateStep));
   }



   void frame::ShowControlBars(bool bShow)
   {
      UINT nShow;
      if(bShow)
      {
         nShow = SW_SHOW;
      }
      else
      {
         nShow = SW_HIDE;
      }

   /*   m_toolbar.ShowWindow(nShow);
      m_toolbarView.ShowWindow(nShow);
   //   m_statusbar.ShowWindow(nShow);
      m_menubar.ShowWindow(nShow);
      m_dialogbar.ShowWindow(nShow);*/

   }






   void frame::OnHoverAction(bool bShowWinActionArea)
   {
      if(!IsWindowVisible())
      {
         if(bShowWinActionArea)
         {
            if(GetActiveDocument() != NULL)
            {
               GetActiveDocument()->update_all_views(NULL, 543218);
            }
         }
         Dock();
      }
   }


   void frame::_001OnClose(gen::signal_object * pobj)
   {
      pobj->m_bRet = true;
      ShowWindow(SW_HIDE);
   }


   void frame::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      simple_frame_window::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &frame::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_CLOSE, pinterface, this, &frame::_001OnClose);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &frame::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_MOVE, pinterface, this, &frame::_001OnMove);
      IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &frame::_001OnShowWindow);
      IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &frame::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_APP + 2000  , pinterface, this, &frame::_001OnApp2000);
   }

   void frame::_001OnMove(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      if(m_workset.GetMovingManager()->IsMoving())
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


   void frame::Dock()
   {
      show_task_bar(SW_HIDE);
      rect rectDesktop;
      Application.get_screen_rect(rectDesktop);
      ShowWindow(SW_RESTORE);
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
      switch(m_eposition)
      {
      case position_left:
         SetWindowPos(ZORDER_TOPMOST, 0, 0, 400, rectDesktop.bottom, SWP_SHOWWINDOW);
         break;
      case position_top:
         SetWindowPos(ZORDER_TOPMOST, 0, 0, rectDesktop.right, 400, SWP_SHOWWINDOW);
         break;
      case position_bottom:
         SetWindowPos(ZORDER_TOPMOST, 0, rectDesktop.bottom - 400, rectDesktop.right, 400, SWP_SHOWWINDOW);
         break;
      case position_right:
         SetWindowPos(ZORDER_TOPMOST, rectDesktop.right - 400, 0, rectDesktop.right, 400, SWP_SHOWWINDOW);
         break;
      }
   }

   bool frame::_001OnCommand(id id)
   {
      if(id == "app_exit")
      {
         simple_frame_window::OnClose();
         return true;
      }
      return false;
   }

   bool frame::_001OnUpdateCmdUi(cmd_ui * pcmdui)
   {
      if(pcmdui->m_id == "app_exit")
      {
         pcmdui->Enable();
         return true;
      }
      return false;
   }

   void frame::_001OnDestroy(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      show_task_bar(SW_SHOW);
   }

   void frame::message_window_message_handler(gen::signal_object * pobj)
   {
      SCAST_PTR(user::win::message::base, pbase, pobj);
      if(pbase->m_uiMessage == (WM_APP + 2000))
      {
         _001OnApp2000(pbase);
         pbase->m_bRet = true;
      }
   }


   void frame::_001OnApp2000(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj)


      if(pbase->m_wparam == 0)
      {
         if(pbase->m_lparam == 2)
         {
		     OnHoverAction(true);
         }
         else if(pbase->m_lparam == 1)
         {
            m_bTimerOn = true;
            SetTimer(1000, 23, NULL);
         }
         else if(pbase->m_lparam == 0)
         {
            KillTimer(1000);
            m_bTimerOn = false;
         }
         else if(pbase->m_lparam == 3)
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
            GetTopLevelFrame()->ShowWindow(SW_HIDE);
            m_pwinutilview->KillTimer(21977);
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
         pbase->set_lresult(68);
      }
      pbase->m_bRet = true;
   }


   void frame::show_task_bar(int nCmdShow)
   {
      ::ca::window * pwnd = Application.FindWindow("Shell_TrayWnd", "");
      if(pwnd == NULL)
         return;
      pwnd->ShowWindow(nCmdShow);
   }


} // namespace winutil

