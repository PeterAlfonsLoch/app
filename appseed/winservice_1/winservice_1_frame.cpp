#include "StdAfx.h"
#include "resource.h"
#include <math.h>


// // BEGIN_MESSAGE_MAP(winservice_1_frame, SimpleFrameWindow)
	//{{AFX_MSG_MAP(winservice_1_frame)
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
// // END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

winservice_1_frame::winservice_1_frame(::ca::application * papp) :
   ::ca::ca(papp),
   SimpleFrameWindow(papp),
   m_toolbar(papp)
{
   m_pimagelist = NULL;
   m_iFrameData = 10;
   m_dataid = "MusicalPlayerscreencaptureFrame";
   m_iAnimateStep = 0;
   m_bTimerHide = false;

   WfiEnableFullScreen();

   m_dataidWindow = "WindowData";
   m_bMoveDrag = true;
}

winservice_1_frame::~winservice_1_frame()
{
}

int winservice_1_frame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if(!data_get("DockPosition", (int &) m_eposition))
   {
      m_eposition = PositionLeft;
   }
//	if (SimpleFrameWindow::OnCreate(lpCreateStruct) == -1)
//		return -1;



   m_bTimerOn = false;

   SetTimer(8913, 5000, 0);
   SetTimer(4033, 100, 0);
   ModifyStyleEx(WS_EX_OVERLAPPEDWINDOW, 0);

   MouseHook();

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
   m_pimagelist->Create(16, 16, 0, 10, 10);
   m_pimagelist->add(
      (HICON)
      ::LoadImage(
         AfxGetApp()->m_hInstance,
         MAKEINTRESOURCE(IDI_LANGUAGE_CHANGE),
         IMAGE_ICON,
         16, 16, 0));

   /*m_menubar._001SetImageList(&m_imagelist);
   m_menubar.SetItemImage(m_menubar._001GetItemCount() - 1, 0);*/

   string str = Application.file().as_string(
      Application.dir().matter("command\\toolbar.xml"));

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
   
   
	if (!m_dialogbar.Create(this, IDR_MAINFRAME, 
		WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP | CBRS_GRIPPER | CBRS_SIZE_DYNAMIC
      | CBRS_DRAGMOVE, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}*/

/*	if (!m_wndReBar.Create(this) ||
      !m_wndReBar.AddBar(&m_menubar) ||
		!m_wndReBar.AddBar(&m_wndToolBar) ||
      !m_wndReBar.AddBar(&m_toolbarView) ||
		!m_wndReBar.AddBar(&m_wndDlgBar))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}*/

/*	if (!m_statusbar.Create(this) ||
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

   ToFront();
	return 0;
}

BOOL winservice_1_frame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !SimpleFrameWindow::PreCreateWindow(cs) )
		return FALSE;
   cs.dwExStyle &= ~WS_EX_WINDOWEDGE;
   ::DestroyMenu(cs.hMenu);
   cs.hMenu = NULL;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// winservice_1_frame diagnostics

#ifdef _DEBUG
void winservice_1_frame::AssertValid() const
{
	SimpleFrameWindow::AssertValid();
}

void winservice_1_frame::Dump(CDumpContext& dc) const
{
	SimpleFrameWindow::Dump(dc);
}


#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// winservice_1_frame message handlers


void winservice_1_frame::WfiOnFullScreen(bool bFullScreen)
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
         &base_wnd::wndTop,
         rectDesktop.left, rectDesktop.top,
         rectDesktop.Width(), rectDesktop.Height(),
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

void winservice_1_frame::OnViewFullScreen() 
{
	ToggleFullScreen();
}

void winservice_1_frame::OnUpdateViewFullScreen(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable();	
   pCmdUI->SetCheck(WfiIsFullScreen() ? 1 : 0);	
}

void winservice_1_frame::ToggleFullScreen()
{
   WfiFullScreen(!WfiIsFullScreen(), true);
}

void winservice_1_frame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	if (IsFullScreen())
	{
		lpMMI->ptMaxSize.y = m_FullScreenWindowRect.Height();
		lpMMI->ptMaxTrackSize.y = lpMMI->ptMaxSize.y;
		lpMMI->ptMaxSize.x = m_FullScreenWindowRect.Width();
		lpMMI->ptMaxTrackSize.x = lpMMI->ptMaxSize.x;
	}
	else
	{
//   	SimpleFrameWindow::OnGetMinMaxInfo(lpMMI);
	}
}

bool winservice_1_frame::IsFullScreen()
{
   return WfiIsFullScreen();
}


void winservice_1_frame::OnMove(int x, int y) 
{
//	SimpleFrameWindow::OnMove(x, y);
}

void winservice_1_frame::OnClose() 
{
	SimpleFrameWindow::OnClose();
}

void winservice_1_frame::OnSysCommand(UINT nID, LPARAM lParam) 
{

   if(nID == SC_SCREENSAVE)
   {
   }
	
	SimpleFrameWindow::OnSysCommand(nID, lParam);
}





void winservice_1_frame::_001OnTimer(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::timer, ptimer, pobj);
   UINT nIDEvent = ptimer->m_nIDEvent;
   static float theta;
   if(nIDEvent == 3)
   {
      //AnimateStatusBar();
   }
   else if(nIDEvent == 1000)
   {
      KillTimer(nIDEvent);
      m_bTimerOn = false;
      if(m_bLControl)
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

void winservice_1_frame::SetAnimatedStatusBarText(LPCTSTR lpcsz)
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

void winservice_1_frame::AnimateStatusBar()
{
   if(m_strAnimatedStatusBarText.is_empty())
      return;

   int iLen = m_strAnimatedStatusBarText.GetLength();
   m_iAnimateStep++;
   if(m_iAnimateStep > iLen)
      m_iAnimateStep = 0;


//   m_statusbar.SetPaneText(0, m_strAnimatedStatusBarText.Mid(m_iAnimateStep));
}


void winservice_1_frame::ShowControlBars(bool bShow)
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

void winservice_1_frame::OnShowWindow(BOOL bShow, UINT nStatus) 
{
//	SimpleFrameWindow::OnShowWindow(bShow, nStatus);
	
	// TODO: add your message handler code here
	
}

void winservice_1_frame::OnNcPaint() 
{
	// TODO: add your message handler code here
	
	// Do not call SimpleFrameWindow::OnNcPaint() for winactionareaing messages
}

void winservice_1_frame::OnTogglecustomframe() 
{
	SetCustomFrame(!GetCustomFrame());
	
}

void winservice_1_frame::OnUpdateTogglecustomframe(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable();
   pCmdUI->SetCheck(m_bCustomFrame ? 1 : 0);
}


BOOL winservice_1_frame::OnCopyData(base_wnd * pwnd, COPYDATASTRUCT* pcds)
{

   return FALSE;
}


bool winservice_1_frame::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)  
{
	// TODO: add your specialized code here and/or call the base class
	
	return SimpleFrameWindow::_001OnCmdMsg(pcmdmsg);
}

void winservice_1_frame::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
	//SimpleFrameWindow::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	
	// TODO: add your message handler code here
	
}

void winservice_1_frame::OnInitMenu(CMenu* pMenu) 
{
//	SimpleFrameWindow::OnInitMenu(pMenu);
	
	// TODO: add your message handler code here
	
}

void winservice_1_frame::OnActivate(UINT nState, base_wnd* pWndOther, BOOL bMinimized) 
{
//	SimpleFrameWindow::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: add your message handler code here
	
}



bool winservice_1_frame::MouseHook()
{
   
   return true;
}

void winservice_1_frame::MouseMessage(          int nCode,
    WPARAM wparam,
    LPARAM lparam
)
{
}

LRESULT CALLBACK winservice_1_frame::MouseProc(          int nCode,
    WPARAM wparam,
    LPARAM lparam
)
{
return 0;
}



void winservice_1_frame::LowLevelMouseMessage(          int nCode,
    WPARAM wparam,
    LPARAM lparam
)
{
}

LRESULT CALLBACK winservice_1_frame::LowLevelMouseProc(          int nCode,
    WPARAM wparam,
    LPARAM lparam
)
{
      return 0;
}



bool winservice_1_frame::MouseUnhook()
{
   return true;
}



void winservice_1_frame::OnHoverAction(bool bShowWinActionArea)
{
   if(!IsWindowVisible())
   {
      if(bShowWinActionArea)
      {
         if(GetActiveDocument() != NULL)
         {
            GetActiveDocument()->UpdateAllViews(NULL, 543218);
         }
      }
      ToFront();
   }
}


void winservice_1_frame::_001OnClose(gen::signal_object * pobj)
{
   pobj->m_bRet = true;
   ShowWindow(SW_HIDE);
}


void winservice_1_frame::_001InstallMessageHandling(igui::win::message::Dispatch * pinterface)
{
   SimpleFrameWindow::_001InstallMessageHandling(pinterface);
   IGUI_WIN_MSG_LINK(WM_CLOSE, pinterface, this, &winservice_1_frame::_001OnClose);
   IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &winservice_1_frame::_001OnTimer);
   IGUI_WIN_MSG_LINK(WM_MOVE, pinterface, this, &winservice_1_frame::_001OnMove);
   IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &winservice_1_frame::_001OnShowWindow);
}

void winservice_1_frame::_001OnMove(gen::signal_object * pobj)
{
   if(m_wndframework.GetMovingManager()->IsMoving())
   {
      HWND hwndDesktop = ::GetDesktopWindow();
      rect rectDesktop;
      ::GetWindowRect(hwndDesktop, rectDesktop);
      rect rectWindow;
      GetWindowRect(rectWindow);
      double a = (double) rectDesktop.Height() / (double) rectDesktop.Width();
      if(rectWindow.left < (rectDesktop.Width() / 2))
      {
         // to the left
         if(rectWindow.top < rectWindow.left * a)
         {
            // top
            m_eposition = PositionTop;
         }
         else if(rectWindow.top > (rectDesktop.Height() - rectWindow.left * a))
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
         else if(rectWindow.top < (rectDesktop.Height() - rectWindow.left * a))
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

void winservice_1_frame::_001OnShowWindow(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::show_window, pshowwindow, pobj)
   
   if(!pshowwindow->m_bShow)
   {
      if(GetActiveDocument() != NULL)
         GetActiveDocument()->UpdateAllViews(NULL, 5432108);
   }
}


void winservice_1_frame::ToFront()
{
   HWND hwndDesktop = ::GetDesktopWindow();
   rect rectDesktop;
   ::GetWindowRect(hwndDesktop, rectDesktop);
   ShowWindow(SW_RESTORE);
   if(rectDesktop.Width() < 800)
   {
      rectDesktop.left = 0;
      rectDesktop.right = ::GetSystemMetrics(SM_CXSCREEN);
   }
   if(rectDesktop.Height() < 600)
   {
      rectDesktop.top = 0;
      rectDesktop.bottom = ::GetSystemMetrics(SM_CYSCREEN);
   }
   rect rectFrame = rectDesktop;
   rectFrame.DeflateRect(
      rectDesktop.Width() / 4, 
      rectDesktop.Height() / 4, 
      rectDesktop.Width() / 10, 
      0);
   rectFrame.bottom = rectFrame.top + 100;
   SetWindowPos(
      &base_wnd::wndTopMost, 
      rectFrame.left, 
      rectFrame.top, 
      rectFrame.Width(), 
      rectFrame.Height(), 
      SWP_SHOWWINDOW);
}
