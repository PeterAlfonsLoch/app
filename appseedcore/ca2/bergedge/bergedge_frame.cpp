#include "StdAfx.h"
 
namespace bergedge
{

   // IMPLEMENT_DYNCREATE(frame, simple_frame_window)

    // BEGIN_MESSAGE_MAP(frame, simple_frame_window)
      //{{AFX_MSG_MAP(frame)
   /* xxx   ON_WM_CREATE()
      ON_WM_GETMINMAXINFO()
      ON_WM_MOVE()
      ON_WM_CLOSE()
   /*   ON_WM_TIMER()*/
   /* xxx   ON_WM_SHOWWINDOW()
      ON_WM_NCPAINT()
      ON_WM_INITMENUPOPUP()
      ON_WM_INITMENU()
      ON_WM_ACTIVATE()
      //}}AFX_MSG_MAP
      // Global help commands
      ON_COMMAND(ID_HELP_FINDER, simple_frame_window::OnHelpFinder)
      ON_COMMAND(ID_HELP, simple_frame_window::OnHelp)
      ON_COMMAND(ID_CONTEXT_HELP, simple_frame_window::OnContextHelp)
      ON_COMMAND(ID_DEFAULT_HELP, simple_frame_window::OnHelpFinder)
      ON_WM_COPYDATA() */
    // END_MESSAGE_MAP()

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
      ::ca::message_window_simple_callback(papp)
   {
      m_pdocument = NULL;
      m_iFrameData = 10;
      m_dataid = "ca2_fontopus_votagus::frame";
      m_iAnimateStep = 0;

      WfiEnableFullScreen();

      m_dataidWindow = "WindowData";

      m_bLayered = true;
      m_etranslucency = TranslucencyPresent;

      m_ppaneview = NULL;

   }

   frame::~frame()
   {
   }

   void frame::_001OnCreate(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::create, pcreate, pobj);
   //   if (simple_frame_window::OnCreate(lpCreateStruct) == -1)
   //      return -1;

/*      m_bTimerOn = false;

      SetTimer(8913, 5000, 0);
      SetTimer(4033, 100, 0);
      ModifyStyleEx(WS_EX_OVERLAPPEDWINDOW, 0);*/


      m_bCustomFrame = !System.command_line().m_varQuery["client_only"].is_set();


      if(!initialize_message_window("ca2::fontopus::message_wnd::bergedge::" + System.get_local_mutex_id()))
      {
         pcreate->set_lresult(-1);
         pcreate->m_bRet = true;
         return;
      }

      //m_menuhook.Initialize(
        // BaseMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
         //BaseMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(),
         //NULL,
         //System.font_central().GetMenuFont());

      //m_menuhook.Install(this);



      //m_hMenuDefault = NULL;

   /*    if (!m_menubar.CreateEx(this))
      {
         TRACE0("Failed to create toolbar\n");
         return -1;      // fail to create
      }

      if(!m_menubar.Initialize(
         BaseMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
         BaseMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(),
         NULL,
         System.font_central().GetMenuFont()) ||
         VMS_FAILED(m_menubar.LoadMenuBar(IDR_MAINFRAME)))
      {
         TRACE0("Failed to create toolbar\n");
         return -1;      // fail to create
      }*/
      /*m_pimagelist = new image_list(get_app());
      m_pimagelist->create(16, 16, 0, 10, 10);
      m_pimagelist->add(
         (HICON)
         ::LoadImage(
            System.m_hInstance,
            MAKEINTRESOURCE(IDI_LANGUAGE_CHANGE),
            IMAGE_ICON,
            16, 16, 0));*/

      /*m_menubar._001SetImageList(&m_imagelist);
      m_menubar.SetItemImage(m_menubar._001GetItemCount() - 1, 0);

      if (!m_toolbar.CreateEx(this, TBSTYLE_FLAT,
         WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP | CBRS_GRIPPER | CBRS_SIZE_DYNAMIC
         | CBRS_DRAGMOVE,
         rect(0, 0, 0, 0),
         AFX_IDW_TOOLBAR) ||
         !m_toolbar.LoadToolBar(IDR_MAINFRAME))
      {
         TRACE0("Failed to create toolbar\n");
         return -1;      // fail to create
      }

      if (!m_toolbarView.CreateEx(this, TBSTYLE_FLAT,
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
         return -1;      // fail to create
      }*/

   /*   if (!m_wndReBar.create(this) ||
         !m_wndReBar.AddBar(&m_menubar) ||
         !m_wndReBar.AddBar(&m_wndToolBar) ||
         !m_wndReBar.AddBar(&m_toolbarView) ||
         !m_wndReBar.AddBar(&m_wndDlgBar))
      {
         TRACE0("Failed to create rebar\n");
         return -1;      // fail to create
      }*/

   /*   if (!m_statusbar.create(this) ||
         !m_statusbar.SetIndicators(indicators,
           sizeof(indicators)/sizeof(UINT)))
      {
         TRACE0("Failed to create status bar\n");
         return -1;      // fail to create
      }*/

      // TODO: remov this if you don't want tool tips
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

      /*WindowDataLoadWindowRect();
      WindowDataEnableSaveWindowRect(true);*/
   }

   void frame::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      simple_frame_window::_001InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CLOSE,          pinterface, this, &frame::_001OnClose);
      IGUI_WIN_MSG_LINK(WM_TIMER,          pinterface, this, &frame::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_CREATE,         pinterface, this, &frame::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_APP + 1,        pinterface, this, &frame::_001OnApp1);
      IGUI_WIN_MSG_LINK(WM_MOUSELEAVE,     pinterface, this, &frame::_001OnMouseLeave);
   }


   BOOL frame::PreCreateWindow(CREATESTRUCT& cs)
   {
      if( !simple_frame_window::PreCreateWindow(cs) )
         return FALSE;
      cs.dwExStyle &= ~WS_EX_WINDOWEDGE;
      ::DestroyMenu(cs.hMenu);
      cs.hMenu = NULL;
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
      if(nIDEvent == 3)
      {
         //AnimateStatusBar();
      }
      else if(nIDEvent == 1000)
      {
         ShowWindow(SW_RESTORE);
         KillTimer(nIDEvent);
         m_bTimerOn = false;
      }
      else if(nIDEvent == 8913)
      {
      }
      else if(nIDEvent == 4033)
      {
         point pt;
         if(m_bHoverMouse && GetTickCount() > m_dwLastHover + 300)
         {
            OnHoverAction();
         }
         System.get_cursor_pos(&pt);
         if(!m_bHoverMouse && pt.x == 0 && pt.y == 0)
         {
            m_dwLastHover = ::GetTickCount();
            m_bHoverMouse = true;
               
         }
         else if(m_bHoverMouse && (pt.x > 10 || pt.y > 0))
         {
            m_bHoverMouse = false;
         }
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

   

   void frame::_000OnMouse(::user::win::message::mouse * pmouse)
   {
      ::icube::application * pappParent = &App(Application.m_papp);
      ::icube::application * papp = &Application;
      papp->m_ptCursor = pappParent->m_ptCursor;

      if(pmouse->m_uiMessage == WM_MOUSEMOVE
      && m_pdocument != NULL
      && m_pdocument->m_pplatformdocument != NULL
      && m_pdocument->m_pplatformdocument->get_platform_frame() != NULL)
      {
         track_mouse_hover();
         rect rectClient;
         GetClientRect(rectClient);
         point pt = pmouse->m_pt.x;
         ScreenToClient(&pt);
         if(pt.x <= 0)
         {
            m_pdocument->m_pplatformdocument->get_platform_frame()->super_dock_on_bergedge();
         }
      }
      simple_frame_window::_000OnMouse(pmouse);
   }

   void frame::_001OnMouseLeave(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      bergedge::application * papp = dynamic_cast < bergedge::application * > (get_app());
      if(m_pdocument != NULL)
      {
         if(m_pdocument->m_pplatformdocument != NULL)
         {
            m_pdocument->m_pplatformdocument->get_platform_frame()->super_dock_on_bergedge();
         }
      }
   }

   void frame::pre_translate_message(gen::signal_object * pobj)
   {
//      SCAST_PTR(user::win::message::base, pbase, pobj);
      simple_frame_window::pre_translate_message(pobj);
   }


   void frame::OnHoverAction()
   {
      if(WfiIsFullScreen())
      {
   //      bergedge::get_app()->show_platform();
      }
      else
      {
         WfiFullScreen(true, false);
      }
   }

   void frame::message_handler(gen::signal_object * pobj)
   {
      simple_frame_window::message_handler(pobj);
   }

   void frame::_000OnDraw(::ca::graphics * pgraphics)
   {
/*      if(!IsWindowVisible())
         ShowWindow(SW_SHOWMAXIMIZED);
      if(!IsFullScreen())
         WfiFullScreen(true, true);
      point pt(0, 0);
      if(m_pdocument != NULL)
      {
         m_pdocument->get_bergedge_view()->ClientToScreen(&pt);;
         ScreenToClient(&pt);
      }
      point ptViewport =  pgraphics->GetViewportOrg();
      _001DrawChildren(pgraphics);
      pgraphics->SetViewportOrg(ptViewport);*/
      /*CURSORINFO CI;
      CI.cbSize = sizeof(CURSORINFO);
      GetCursorInfo(&CI);
      ICONINFO Info;
      GetIconInfo(CI.hCursor,&Info);*/
      ::simple_frame_window::_000OnDraw(pgraphics);
   }

   void frame::message_window_message_handler(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj);
      if(pbase->m_uiMessage == (WM_APP + 2000))
      {
         _001OnApp2000(pbase);
         pbase->m_bRet = true;
      }
      else if(pbase->m_uiMessage == WM_COPYDATA)
      {
         int iEdge = 0;
         COPYDATASTRUCT * pstruct = (COPYDATASTRUCT *) pbase->m_lparam;
         if(pstruct->dwData == 1984)
         {
            gen::memory_file file(get_app(), pstruct->lpData, pstruct->cbData);
            string strPath;
            file.to_string(strPath);
            System.open_by_file_extension(iEdge, strPath);
         }
      }

   }


   void frame::_001OnApp2000(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj)


      if(pbase->m_wparam == 0)
      {
         if(pbase->m_lparam == 2)
         {
           //OnHoverAction(true);
            ShowWindow(SW_SHOW);
            SetWindowPos(ZORDER_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
            WfiFullScreen(true, true);
         }
         else if(pbase->m_lparam == 5)
         {
            
            class rect rect;
            ::GetWindowRect(::GetDesktopWindow(), rect);
            point pt = rect.center();
            if(!IsWindowVisible() 
            || ::WindowFromPoint(pt) != get_safe_handle())
            {
               ShowWindow(SW_SHOW);
               SetWindowPos(ZORDER_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
               WfiFullScreen(true, true);
               BringWindowToTop();
            }
            else
            {
               ShowWindow(SW_HIDE);
            }
         }
      }
/*         else if(pbase->m_lparam == 1)
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
  */       
    /*  }
*/
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
  //          m_pwinutilview->KillTimer(21977);
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
         string str = System.get_local_mutex_id();
         gen::str::begins_eat_ci(str, "bergedge");
         int iEdge = atoi(str);
         if(iEdge == 0)
            iEdge = 77;
         else 
            iEdge += 1984;
         pbase->set_lresult(iEdge);
      }
      else if(pbase->m_wparam == 25)
      {
         pbase->set_lresult((LRESULT) GetTopLevelFrame()->get_safe_handle());
      }
      pbase->m_bRet = true;
   }

      /*else if(pbase->m_wparam == 1)
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
         pbase->set_lresult(68);
      }
      pbase->m_bRet = true;*/
   //}

   void frame::_001OnApp1(gen::signal_object * pobj)
   {
      SCAST_PTR(user::win::message::base, pbase, pobj);
      MSG * pmsg = (MSG *) pbase->m_lparam;
      pmsg->hwnd = get_safe_handle();
      try
      {
         if(pmsg->message != WM_KICKIDLE)
         {
            ::ca::smart_pointer < ::user::win::message::base > spbase(get_base(pmsg));
            pre_translate_message(spbase);
            if(!spbase->m_bRet)
            {
               SendMessage(spbase);
            }
         }
      }
      catch(const ::ca::exception & )
      {
      }
      catch(...)
      {
      }
      delete pmsg;
   }

} // namespace bergedge