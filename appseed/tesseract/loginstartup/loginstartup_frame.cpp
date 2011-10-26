#include "StdAfx.h"
#include "resource.h"

#include "loginstartup_frame.h"
#include "loginstartup_view.h"
#include <math.h>

loginstartup_frame  * g_pframe;

 // BEGIN_MESSAGE_MAP(loginstartup_frame, SimpleFrameWindow)
	//{{AFX_MSG_MAP(loginstartup_frame)
/* xxx	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
	ON_WM_MOVE()
	ON_WM_CLOSE()
	ON_WM_SYSCOMMAND()
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_WM_NCPAINT()
	ON_COMMAND(ID_TOGGLECUSTOMFRAME, OnTogglecustomframe)
	ON_UPDATE_COMMAND_UI(ID_TOGGLECUSTOMFRAME, OnUpdateTogglecustomframe)
	ON_WM_INITMENUPOPUP()
	ON_WM_INITMENU()
	ON_WM_ACTIVATE()
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, SimpleFrameWindow::OnHelpFinder)
	ON_COMMAND(ID_HELP, SimpleFrameWindow::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, SimpleFrameWindow::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, SimpleFrameWindow::OnHelpFinder)
	ON_WM_COPYDATA() */
 // END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// loginstartup_frame construction/destruction

loginstartup_frame::loginstartup_frame(::ca::application * papp) :
   ::ca::ca(papp),
   window_frame::WorkSetClientInterface(papp),
   guibase::frame_wnd_interface(papp),
   BaseFrameWnd(papp),
   SimpleFrameWindow(papp),
   m_imagelist(papp), 
   m_toolbar(papp)
{
   m_iFrameData = 10;
   m_dataid = "MusicalPlayerscreencaptureFrame";
   m_iAnimateStep = 0;
   m_bTimerHide = false;

   WfiEnableFullScreen();

   m_dataidWindow = "WindowData";
   m_bMoveDrag = true;
   m_bLastLWin = false;

//   connect_command("app_exit", &loginstartup_frame::_001OnAppExit);
//   connect_update_cmd_ui("app_exit", &loginstartup_frame::_001OnUpdateAppExit);
}

loginstartup_frame::~loginstartup_frame()
{
}

int loginstartup_frame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if(!data_get("DockPosition", (int &) m_eposition))
   {
      m_eposition = PositionLeft;
   }
//	if (SimpleFrameWindow::OnCreate(lpCreateStruct) == -1)
//		return -1;



/*BLENDFUNCTION blend;

    blend.BlendOp = AC_SRC_OVER;
    blend.BlendFlags = 0;
    blend.AlphaFormat = 0;
    blend.SourceConstantAlpha = 128;

    point ptSrc = point(0, 0);

    ::ca::graphics_sp spgraphics(get_app());
    spgraphics->CreateCompatibleDC(NULL);
 
    UpdateLayeredWindow( NULL, NULL, NULL, &spgraphics, &ptSrc, 0,
            &blend, ULW_ALPHA);*/

//   SetLayeredWindowAttributes(0, (255 * 100) / 100, LWA_ALPHA);

   
   m_bTimerOn = false;

   SetTimer(8913, 5000, 0);
   SetTimer(4033, 100, 0);
   ModifyStyleEx(WS_EX_OVERLAPPEDWINDOW, 0);

   SetTimer(4034, 500, 0);

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

   m_imagelist.create(16, 16, 0, 10, 10);
   m_imagelist.add(
      (HICON)
      ::LoadImage(
         Application.m_hInstance,
         MAKEINTRESOURCE(IDI_LANGUAGE_CHANGE),
         IMAGE_ICON,
         16, 16, 0));

   /*m_menubar._001SetImageList(&m_imagelist);
   m_menubar.SetItemImage(m_menubar._001GetItemCount() - 1, 0);*/

   string str = Application.file().as_string(
      Application.dir().matter("loginstartup\\toolbar.xml"));

	if (!m_toolbar.CreateEx(this) ||
		 !m_toolbar.LoadXmlToolBar(str))
	{
		TRACE0("Failed to create toolbar\n");
		return false;      // fail to create
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

   WindowDataLoadWindowRect();
   WindowDataEnableSaveWindowRect(true);

	return 0;
}

BOOL loginstartup_frame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !SimpleFrameWindow::PreCreateWindow(cs) )
		return FALSE;
   cs.dwExStyle &= ~WS_EX_WINDOWEDGE;
   //cs.dwExStyle |= WS_EX_LAYERED;

   ::DestroyMenu(cs.hMenu);
   cs.hMenu = NULL;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// loginstartup_frame diagnostics

#ifdef _DEBUG
void loginstartup_frame::AssertValid() const
{
	SimpleFrameWindow::AssertValid();
}

void loginstartup_frame::Dump(CDumpContext & dumpcontext) const
{
	SimpleFrameWindow::Dump(dumpcontext);
}


#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// loginstartup_frame message handlers


void loginstartup_frame::WfiOnFullScreen(bool bFullScreen)
{
   if(bFullScreen)
   {
      ModifyStyle(
         WS_BORDER |
         WS_CAPTION |
         WS_THICKFRAME,
         0,
         0);

      ShowControlBars(false);

		DWORD dwStyle = GetStyle();

      DWORD dwStyleEx = GetExStyle();

      rect rectDesktop;
		
      ::GetWindowRect ( ::GetDesktopWindow(), &rectDesktop );

		::AdjustWindowRectEx(
			&rectDesktop,
			dwStyle,
			FALSE,
			dwStyleEx);

      m_FullScreenWindowRect = rectDesktop;
      
      SetWindowPos(
         ZORDER_TOP,
         rectDesktop.left, rectDesktop.top,
         rectDesktop.width(), rectDesktop.height(),
         SWP_FRAMECHANGED |
         SWP_SHOWWINDOW);
      RecalcLayout();
   }
   else
   {
      ShowControlBars(true);
      if(!m_bCustomFrame)
      {
         ModifyStyle(
            0,
            WS_BORDER |
            WS_CAPTION |
            WS_THICKFRAME,
            SWP_FRAMECHANGED);
      }
      RecalcLayout();
   }
   if(GetActiveView() != NULL)
   {
   }
   
   data_set("FullScreen", bFullScreen);

}

void loginstartup_frame::OnViewFullScreen() 
{
	ToggleFullScreen();
}

void loginstartup_frame::OnUpdateViewFullScreen(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable();	
   pCmdUI->SetCheck(WfiIsFullScreen() ? 1 : 0);	
}

void loginstartup_frame::ToggleFullScreen()
{
   WfiFullScreen(!WfiIsFullScreen(), true);
}

void loginstartup_frame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	if (IsFullScreen())
	{
		lpMMI->ptMaxSize.y = m_FullScreenWindowRect.height();
		lpMMI->ptMaxTrackSize.y = lpMMI->ptMaxSize.y;
		lpMMI->ptMaxSize.x = m_FullScreenWindowRect.width();
		lpMMI->ptMaxTrackSize.x = lpMMI->ptMaxSize.x;
	}
	else
	{
//   	SimpleFrameWindow::OnGetMinMaxInfo(lpMMI);
	}
}

bool loginstartup_frame::IsFullScreen()
{
   return WfiIsFullScreen();
}


void loginstartup_frame::OnMove(int x, int y) 
{
//	SimpleFrameWindow::OnMove(x, y);
}

void loginstartup_frame::OnClose() 
{
	SimpleFrameWindow::OnClose();
}

void loginstartup_frame::OnSysCommand(UINT nID, LPARAM lParam) 
{

   if(nID == SC_SCREENSAVE)
   {
   }
	
	SimpleFrameWindow::OnSysCommand(nID, lParam);
}





void loginstartup_frame::_001OnTimer(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::timer, ptimer, pobj);
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

         UpdateLayeredWindow( NULL, NULL, NULL, NULL, NULL, 0,
            &blend, ULW_OPAQUE);*/

//         SetLayeredWindowAttributes(0, (255 * 100) / 100, LWA_ALPHA);
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
      bool bLControlKeyDown = GetAsyncKeyState (VK_LCONTROL) >> ((sizeof(SHORT) * 8) - 1);
      bool bLAltKeyDown = GetAsyncKeyState (VK_LMENU) >> ((sizeof(SHORT) * 8) - 1);
      if(bLControlKeyDown && bLAltKeyDown)
      {
      }
      else
      {
      }
   }
   else if(nIDEvent == 1001)
   {
      KillTimer(nIDEvent);
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
      ::GetCursorPos(&pt);
      if(!rectWindow.PtInRect(pt) && !m_bTimerHide)
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
      if(::GetCursorPos(&pt))
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
//	SimpleFrameWindow::OnTimer(nIDEvent);
}

void loginstartup_frame::SetAnimatedStatusBarText(const char * lpcsz)
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

void loginstartup_frame::AnimateStatusBar()
{
   if(m_strAnimatedStatusBarText.is_empty())
      return;

   int iLen = m_strAnimatedStatusBarText.get_length();
   m_iAnimateStep++;
   if(m_iAnimateStep > iLen)
      m_iAnimateStep = 0;


//   m_statusbar.SetPaneText(0, m_strAnimatedStatusBarText.Mid(m_iAnimateStep));
}



void loginstartup_frame::ShowControlBars(bool bShow)
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

void loginstartup_frame::OnShowWindow(BOOL bShow, UINT nStatus) 
{
//	SimpleFrameWindow::OnShowWindow(bShow, nStatus);
	
	// TODO: add your message handler code here
	
}

void loginstartup_frame::OnNcPaint() 
{
	// TODO: add your message handler code here
	
	// Do not call SimpleFrameWindow::OnNcPaint() for loginstartuping messages
}

void loginstartup_frame::OnTogglecustomframe() 
{
	SetCustomFrame(!GetCustomFrame());
	
}

void loginstartup_frame::OnUpdateTogglecustomframe(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable();
   pCmdUI->SetCheck(m_bCustomFrame ? 1 : 0);
}


BOOL loginstartup_frame::OnCopyData(::ca::window * pwnd, COPYDATASTRUCT* pcds)
{

   return FALSE;
}


bool loginstartup_frame::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)  
{
	// TODO: add your specialized code here and/or call the base class
	
	return SimpleFrameWindow::_001OnCmdMsg(pcmdmsg);
}


void loginstartup_frame::OnActivate(UINT nState, ::ca::window* pWndOther, BOOL bMinimized) 
{
//	SimpleFrameWindow::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: add your message handler code here
	
}






void loginstartup_frame::_001OnClose(gen::signal_object * pobj)
{
   pobj->m_bRet = true;
}


void loginstartup_frame::_001InstallMessageHandling(igui::win::message::Dispatch * pinterface)
{
   SimpleFrameWindow::_001InstallMessageHandling(pinterface);
   IGUI_WIN_MSG_LINK(WM_CLOSE, pinterface, this, &loginstartup_frame::_001OnClose);
   IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &loginstartup_frame::_001OnTimer);
   IGUI_WIN_MSG_LINK(WM_MOVE, pinterface, this, &loginstartup_frame::_001OnMove);
   IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &loginstartup_frame::_001OnShowWindow);
   IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &loginstartup_frame::_001OnDestroy);
   IGUI_WIN_MSG_LINK(WM_APP + 2000  , this, this, &loginstartup_frame::_001OnApp2000);
}

void loginstartup_frame::_001OnMove(gen::signal_object * pobj)
{
   if(m_wndframework.GetMovingManager()->IsMoving())
   {
      HWND hwndDesktop = ::GetDesktopWindow();
      rect rectDesktop;
      ::GetWindowRect(hwndDesktop, rectDesktop);
      rect rectWindow;
      GetWindowRect(rectWindow);
      double a = (double) rectDesktop.height() / (double) rectDesktop.width();
      if(rectWindow.left < (rectDesktop.width() / 2))
      {
         // to the left
         if(rectWindow.top < rectWindow.left * a)
         {
            // top
            m_eposition = PositionTop;
         }
         else if(rectWindow.top > (rectDesktop.height() - rectWindow.left * a))
         {
            // bottom
            m_eposition = PositionBottom;
         }
         else
         {
            // left
            m_eposition = PositionLeft;
         }
      }
      else
      {
         // to the right
         // to the left
         if(rectWindow.top > rectWindow.left * a)
         {
            // bottom
            m_eposition = PositionBottom;
         }
         else if(rectWindow.top < (rectDesktop.height() - rectWindow.left * a))
         {
            // top
            m_eposition = PositionTop;
         }
         else
         {
            // right
            m_eposition = PositionRight;
         }
      }
      data_set("DockPosition", m_eposition);
   }
}

void loginstartup_frame::_001OnShowWindow(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::show_window, pshowwindow, pobj)
   
   if(!pshowwindow->m_bShow)
   {
      if(GetActiveDocument() != NULL)
         GetActiveDocument()->UpdateAllViews(NULL, 5432108);
   }
}



bool loginstartup_frame::_001OnCommand(id id)
{
   if(id == "app_exit")
   {
      SimpleFrameWindow::OnClose();
      return true;
   }
   return false;
}

bool loginstartup_frame::_001OnUpdateCmdUi(CCmdUI * pcmdui)
{
   if(pcmdui->m_id == "app_exit")
   {
      return true;
   }
   return false;
}

void loginstartup_frame::_001OnDestroy(gen::signal_object * pobj)
{
   show_task_bar(SW_SHOW);
}


void loginstartup_frame::_001OnApp2000(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::base, pbase, pobj)


   if(pbase->m_wparam == 0)
   {
      if(pbase->m_lparam == 2)
      {
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


void loginstartup_frame::show_task_bar(int nCmdShow)
{
   ::ca::window * pwnd = Application.FindWindow("Shell_TrayWnd", "");
   if(pwnd == NULL)
      return;
   pwnd->ShowWindow(nCmdShow);
}
